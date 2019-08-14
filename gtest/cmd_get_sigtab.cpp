//   Copyright 2019 Ansersion
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.
//

#include <stdio.h>
#include <sys/types.h>
#include <memory.h>
#include <stdlib.h>
#include <string>
#include <list>
#include <iostream>
#include <gtest/gtest.h>

extern "C" 
{
#include <config.h>
#include <bps_ret_code.h>
#include <bps_public.h>
#include <bps_cmd_get_sigtab.h>
}


using namespace std;

/** get signal table: 4 signal at all, they are:
  signalID=0x0000, type=string, 
  signalID=0xE000, type=string, 
  signalID=0xE001, type=enum, 
  signalID=0xE002, type=boolean, 
  */
static const int MSG_BUF_SIZE = 256;
static BPS_UINT8 buf[MSG_BUF_SIZE];
static const int MCU_ADDR = 0;
static const int MODULE_ADDR = 1;
static const BPS_WORD HEADER_SIZE = BPS_HEADER_SIZE - BPS_VERSION_SIZE - BPS_ADDR_SIZE - BPS_REMAIN_LEN_SIZE;
static BPSCmdGetSigtabField FIELD_ARRAY[] = {
    {0x0000, BPS_SIG_TYPE_STR, 0},
    {0xE000, BPS_SIG_TYPE_STR, 0},
    {0xE001, BPS_SIG_TYPE_ENM, 0},
    {0xE002, BPS_SIG_TYPE_BOOLEAN, 0},
};
static const int MAX_FIELD_NUM = 10;

static BPS_UINT8 REQ_MSG[] = 
{
    0xBB, 0xCC, 0x00, 0x01, 0x00, 0x01, 0x80, 0x82
};

static BPS_UINT8 RSP_MSG[] = 
{
    0xBB, 0xCC, 0x00, 0x10, 0x00, 0x13, 0x81, 0x00, 0x04, 0x00, 0x00, 0x06, 0x00, 0xE0, 0x00, 0x06, 0x00, 0xE0, 0x01, 0x04, 0x00, 0xE0, 0x02, 0x07, 0x00, 0x62
};

/** pack the get signal table command request
  * packet flow: MCU -> MODULE */
TEST(COMMAND_GET_SIGTAB, PackRequest)
{
    BPS_UINT8 * buf_tmp = buf;
    BPSCmdGetSigtabReq data;

    memset(buf, 0, MSG_BUF_SIZE);

    buf_tmp = PackBPSHeader(buf_tmp);
    buf_tmp = PackBPSVersion(buf_tmp);
    buf_tmp = PackBPSAddr(buf_tmp, MCU_ADDR, MODULE_ADDR);
    buf_tmp += BPS_REMAIN_LEN_SIZE;

    BPS_UINT16 tmpLen = BPSPackGetSigtabReq(&data, buf_tmp, MSG_BUF_SIZE-HEADER_SIZE);
    EXPECT_GT(tmpLen, 0);
    PackBPSRemainLen(buf + BPS_REMAIN_LEN_POSITION, tmpLen);
    EXPECT_NE(PackBPSChecksum(buf, MSG_BUF_SIZE), (BPS_UINT8 *)BPS_NULL);
    tmpLen += HEADER_SIZE + BPS_CHECKSUM_SIZE;
    for(size_t i = 0; i < sizeof(REQ_MSG); i++) {
        EXPECT_EQ(REQ_MSG[i], buf[i]);
    }
}

/** pack the get signal table command response 
  * packet flow: MODULE -> MCU */

TEST(COMMAND_GET_SIGTAB, PackResponse)
{
    BPS_UINT8 * buf_tmp = buf;
    BPSCmdGetSigtabRsp data;

    memset(buf, 0, MSG_BUF_SIZE);
    data.fieldArray = FIELD_ARRAY;
    data.fieldNum = sizeof(FIELD_ARRAY) / sizeof(BPSCmdGetSigtabField);

    buf_tmp = PackBPSHeader(buf_tmp);
    buf_tmp = PackBPSVersion(buf_tmp);
    buf_tmp = PackBPSAddr(buf_tmp, MODULE_ADDR, MCU_ADDR);
    buf_tmp += BPS_REMAIN_LEN_SIZE;

    BPS_UINT16 tmpLen = BPSPackGetSigtabRsp(&data, buf_tmp, MSG_BUF_SIZE-HEADER_SIZE);
    EXPECT_GT(tmpLen, 0);
    PackBPSRemainLen(buf + BPS_REMAIN_LEN_POSITION, tmpLen);
    EXPECT_NE(PackBPSChecksum(buf, MSG_BUF_SIZE), (BPS_UINT8 *)BPS_NULL);
    tmpLen += HEADER_SIZE + BPS_CHECKSUM_SIZE;
    for(size_t i = 0; i < sizeof(RSP_MSG); i++) {
        EXPECT_EQ(RSP_MSG[i], buf[i]);
    }
}

/** parse the get signal table command request
  * packet flow: MODULE <- MCU */
TEST(COMMAND_GET_SIGTAB, ParseRequest)
{
    BPS_WORD size = sizeof(REQ_MSG);
    BPSCmdGetSigtabReq data;
    BPSParseGetSigtabReq(&data, REQ_MSG+BPS_CMD_WORD_POSITION+1, size);
}

/** parse the get signal table command response 
  * packet flow: MCU <- MODULE */
TEST(COMMAND_GET_SIGTAB, ParseResponse)
{
    BPS_WORD size = sizeof(RSP_MSG);
    BPSCmdGetSigtabRsp data;
    BPSCmdGetSigtabField fields[MAX_FIELD_NUM];
    data.fieldArray = fields;
    data.maxFieldNum = MAX_FIELD_NUM;
    EXPECT_GT(BPSParseGetSigtabRsp(&data, RSP_MSG+BPS_CMD_WORD_POSITION+1, size), 0);
    for(size_t i = 0; i < data.fieldNum; i++) {
        BPSCmdGetSigtabField * field = &(data.fieldArray[i]);
        if(field->signalId == FIELD_ARRAY[0].signalId) {
            EXPECT_EQ(field->signalType, FIELD_ARRAY[0].signalType);
            EXPECT_EQ(field->accuracy, FIELD_ARRAY[0].accuracy);
        } else if(field->signalId == FIELD_ARRAY[1].signalId) {
            EXPECT_EQ(field->signalType, FIELD_ARRAY[1].signalType);
            EXPECT_EQ(field->accuracy, FIELD_ARRAY[1].accuracy);
        } else if(field->signalId == FIELD_ARRAY[2].signalId) {
            EXPECT_EQ(field->signalType, FIELD_ARRAY[2].signalType);
            EXPECT_EQ(field->accuracy, FIELD_ARRAY[2].accuracy);
        } else if(field->signalId == FIELD_ARRAY[3].signalId) {
            EXPECT_EQ(field->signalType, FIELD_ARRAY[3].signalType);
            EXPECT_EQ(field->accuracy, FIELD_ARRAY[3].accuracy);
        } else {
            ASSERT_FALSE("Unknown signal ID");
        }
    }
}
