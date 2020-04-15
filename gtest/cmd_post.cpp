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
#include <bps_ret_code.h>
#include <bps_public.h>
#include <bps_cmd_post.h>
}


using namespace std;

/** post siangl: signal ID=0x0001, type=0x04(ENUM), value=0x0002 */
static const BPS_UINT16     SIGNAL_ID = 0x0001;;
static const BPS_UINT8      VALUE_TYPE = 0x04;
static const BPSSigTypeU    VALUE = {.t_enm=0x0002 };
static const int MSG_BUF_SIZE = 256;
static BPS_UINT8 buf[MSG_BUF_SIZE];
static const int MAX_FIELD_NUM = 2;
static const int MCU_ADDR = 0;
static const int MODULE_ADDR = 1;
static const BPS_WORD HEADER_SIZE = BPS_HEADER_SIZE - BPS_VERSION_SIZE - BPS_ADDR_SIZE - BPS_REMAIN_LEN_SIZE;

static BPS_UINT8 REQ_MSG[] = 
{
    0xBB, 0xCC, 0x00, 0x10, 0x00, 0x07, 0x84, 0x01, 0x00, 0x01, 0x04, 0x00, 0x02, 0xA3
};

static BPS_UINT8 RSP_MSG[] = 
{
    0XBB, 0xCC, 0x00, 0x01, 0x00, 0x02, 0x85, 0x00, 0x88
};

/** pack the post command request
  * packet flow: MODULE -> MCU */
TEST(COMMAND_POST, PackRequest)
{
    BPS_UINT8 * buf_tmp = buf;
    BPSCmdPostField field;
    BPSCmdPostReq data;

    memset(buf, 0, MSG_BUF_SIZE);
    field.signalId = SIGNAL_ID;
    field.signalType = VALUE_TYPE;
    field.value = VALUE;
    data.fieldArray = &field;
    data.fieldNum = 1;

    buf_tmp = PackBPSHeader(buf_tmp);
    buf_tmp = PackBPSVersion(buf_tmp);
    buf_tmp = PackBPSAddr(buf_tmp, MODULE_ADDR, MCU_ADDR);
    buf_tmp += BPS_REMAIN_LEN_SIZE;

    BPS_UINT16 tmpLen = BPSPackPostReq(&data, buf_tmp, MSG_BUF_SIZE-HEADER_SIZE);
    EXPECT_GT(tmpLen, 0);
    PackBPSRemainLen(buf + BPS_REMAIN_LEN_POSITION, tmpLen);
    EXPECT_NE(PackBPSChecksum(buf, MSG_BUF_SIZE), (BPS_UINT8 *)BPS_NULL);
    tmpLen += HEADER_SIZE + BPS_CHECKSUM_SIZE;
    for(size_t i = 0; i < sizeof(REQ_MSG); i++) {
        EXPECT_EQ(REQ_MSG[i], buf[i]);
    }
}

/** pack the post command response 
  * packet flow: MCU -> MODULE */
TEST(COMMAND_POST, PackResponse)
{
    BPS_UINT8 * buf_tmp = buf;
    BPSCmdPostRsp data;

    memset(buf, 0, MSG_BUF_SIZE);
    data.retCode = BPS_RET_CODE_OK;

    buf_tmp = PackBPSHeader(buf_tmp);
    buf_tmp = PackBPSVersion(buf_tmp);
    buf_tmp = PackBPSAddr(buf_tmp, MCU_ADDR, MODULE_ADDR);
    buf_tmp += BPS_REMAIN_LEN_SIZE;

    BPS_UINT16 tmpLen = BPSPackPostRsp(&data, buf_tmp, MSG_BUF_SIZE-HEADER_SIZE);
    EXPECT_GT(tmpLen, 0);
    PackBPSRemainLen(buf + BPS_REMAIN_LEN_POSITION, tmpLen);
    EXPECT_NE(PackBPSChecksum(buf, MSG_BUF_SIZE), (BPS_UINT8 *)BPS_NULL);
    tmpLen += HEADER_SIZE + BPS_CHECKSUM_SIZE;
    for(size_t i = 0; i < sizeof(RSP_MSG); i++) {
        EXPECT_EQ(RSP_MSG[i], buf[i]);
    }
}

/** parse the post command request
  * packet flow: MCU <- MODULE */
TEST(COMMAND_POST, ParseRequest)
{
    BPS_WORD size = sizeof(REQ_MSG);
    BPSCmdPostField fields[MAX_FIELD_NUM];
    BPSCmdPostReq data;

    data.fieldArray = fields;;
    data.maxFieldNum = MAX_FIELD_NUM;
    EXPECT_GT(BPSParsePostReq(&data, REQ_MSG+BPS_CMD_WORD_POSITION+1, size), 0);
    EXPECT_EQ(data.fieldNum, 1);
    EXPECT_EQ(data.fieldArray[0].signalId, SIGNAL_ID);
    EXPECT_EQ(data.fieldArray[0].signalType, VALUE_TYPE);
    EXPECT_EQ(data.fieldArray[0].value.t_enm, VALUE.t_enm);
}

/** parse the post command response 
  * packet flow: MODULE <- MCU */
TEST(COMMAND_POST, ParseResponse)
{
    BPS_WORD size = sizeof(RSP_MSG);
    BPSCmdPostRsp data;

    EXPECT_GT(BPSParsePostRsp(&data, RSP_MSG+BPS_CMD_WORD_POSITION+1, size), 0);
    EXPECT_EQ(data.retCode, BPS_RET_CODE_OK);
}
