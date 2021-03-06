//   Copyright 2019-2020 Ansersion
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
#include <bps_cmd_get_sig.h>
}


using namespace std;

#if (BPS_CMD_SET == BPS_CMD_SET_C)

/** get signal: signal ID=0x0001, type=0x04(ENUM), value=0x0002 */
static const int MSG_BUF_SIZE = 256;
static BPS_UINT8 buf[MSG_BUF_SIZE];
static const int MCU_ADDR = 0;
static const int MODULE_ADDR = 1;
static const BPS_WORD HEADER_SIZE = BPS_HEADER_SIZE - BPS_VERSION_SIZE - BPS_ADDR_SIZE - BPS_REMAIN_LEN_SIZE;
static const BPS_WORD MAX_FIELD_NUM = 4;
static const BPS_UINT16 SIG_ARRAY[] = {
    0x0002
};
static const BPSCmdGetSigField FIELD_ARRAY[] = {
    {0x0002, BPS_SIG_TYPE_ENM, {.t_enm=0x0002}}
};

static BPS_UINT8 REQ_MSG[] = 
{
    0xBB, 0xCC, 0x00, 0x10, 0x00, 0x04, 0x86, 0x01, 0x00, 0x02, 0x9D
};

static BPS_UINT8 RSP_MSG[] = 
{
    0xBB, 0xCC, 0x00, 0x01, 0x00, 0x08, 0x87, 0x00, 0x01, 0x00, 0x02, 0x04, 0x00, 0x02, 0x99
};

/** pack the get signal values command request
  * packet flow: MODULE -> MCU */
TEST(COMMAND_GET_SIG, PackRequest)
{
    BPS_UINT8 * buf_tmp = buf;
    BPSCmdGetSigReq data;

    memset(buf, 0, MSG_BUF_SIZE);
    data.sigArray = (BPS_UINT16 *)SIG_ARRAY;
    data.sigNum = sizeof(SIG_ARRAY) / sizeof(SIG_ARRAY[0]);

    buf_tmp = PackBPSHeader(buf_tmp);
    buf_tmp = PackBPSVersion(buf_tmp);
    buf_tmp = PackBPSAddr(buf_tmp, MODULE_ADDR, MCU_ADDR);
    buf_tmp += BPS_REMAIN_LEN_SIZE;

    BPS_UINT16 tmpLen = BPSPackGetSigReq(&data, buf_tmp, MSG_BUF_SIZE-HEADER_SIZE);
    EXPECT_GT(tmpLen, 0);
    PackBPSRemainLen(buf + BPS_REMAIN_LEN_POSITION, tmpLen);
    EXPECT_NE(PackBPSChecksum(buf, MSG_BUF_SIZE), (BPS_UINT8 *)BPS_NULL);
    tmpLen += HEADER_SIZE + BPS_CHECKSUM_SIZE;
    for(size_t i = 0; i < sizeof(REQ_MSG); i++) {
        EXPECT_EQ(REQ_MSG[i], buf[i]);
    }
}

/** pack the get signal values command response 
  * packet flow: MCU -> MODULE_ADDR */

TEST(COMMAND_GET_SIG, PackResponse)
{
    BPS_UINT8 * buf_tmp = buf;
    BPSCmdGetSigRsp data;

    memset(buf, 0, MSG_BUF_SIZE);
    data.retCode = BPS_RET_CODE_OK;
    data.fieldNum = sizeof(FIELD_ARRAY) / sizeof(BPSCmdGetSigField);
    data.fieldArray = (BPSCmdGetSigField *)FIELD_ARRAY;

    buf_tmp = PackBPSHeader(buf_tmp);
    buf_tmp = PackBPSVersion(buf_tmp);
    buf_tmp = PackBPSAddr(buf_tmp, MCU_ADDR, MODULE_ADDR);
    buf_tmp += BPS_REMAIN_LEN_SIZE;

    BPS_UINT16 tmpLen = BPSPackGetSigRsp(&data, buf_tmp, MSG_BUF_SIZE-HEADER_SIZE);
    EXPECT_GT(tmpLen, 0);
    PackBPSRemainLen(buf + BPS_REMAIN_LEN_POSITION, tmpLen);
    EXPECT_NE(PackBPSChecksum(buf, MSG_BUF_SIZE), (BPS_UINT8 *)BPS_NULL);
    tmpLen += HEADER_SIZE + BPS_CHECKSUM_SIZE;
    for(size_t i = 0; i < sizeof(RSP_MSG); i++) {
        EXPECT_EQ(RSP_MSG[i], buf[i]);
    }
}

/** parse the get signal values command request
  * packet flow: MCU <- MODULE */
TEST(COMMAND_GET_SIG, ParseRequest)
{
    BPS_WORD size = sizeof(REQ_MSG);
    BPS_UINT16 fields[MAX_FIELD_NUM];
    BPSCmdGetSigReq data;
    data.sigArray = fields;
    data.maxFieldNum = MAX_FIELD_NUM;

    EXPECT_GT(BPSParseGetSigReq(&data, REQ_MSG+BPS_CMD_WORD_POSITION+1, size), 0);
    EXPECT_EQ(data.sigNum, sizeof(SIG_ARRAY)/sizeof(SIG_ARRAY[0]));
    for(size_t i = 0; i < data.sigNum; i++) {
        BPS_UINT16 sig = data.sigArray[i];
        if(SIG_ARRAY[0] == sig) {
            ASSERT_TRUE(BPS_TRUE);
        } else {
            ASSERT_FALSE("Unknown Hardware info type");
        }
    }
}

/** parse the get signal values command response 
  * packet flow: MODULE <- MCU */
TEST(COMMAND_GET_SIG, ParseResponse)
{
    BPS_WORD size = sizeof(RSP_MSG);
    BPSCmdGetSigField fields[MAX_FIELD_NUM];
    BPSCmdGetSigRsp data;
    data.fieldArray = fields;
    data.maxFieldNum = MAX_FIELD_NUM;

    EXPECT_GT(BPSParseGetSigRsp(&data, RSP_MSG+BPS_CMD_WORD_POSITION+1, size), 0);
    EXPECT_EQ(data.fieldNum, sizeof(FIELD_ARRAY)/sizeof(FIELD_ARRAY[0]));
    for(size_t i = 0; i < data.fieldNum; i++) {
        BPSCmdGetSigField * field = &(data.fieldArray[i]);
        if(FIELD_ARRAY[0].signalId == field->signalId) {
            EXPECT_EQ(field->signalType, FIELD_ARRAY[0].signalType);
            EXPECT_EQ(field->value.t_enm, FIELD_ARRAY[0].value.t_enm);
        } else {
            ASSERT_FALSE("Unknown Hardware info type");
        }
    }
}

/** parse(DYN) the get signal values command request
  * packet flow: MODULE <- MCU */
TEST(COMMAND_GET_SIG, ParseRequestDyn)
{
    BPS_WORD size = sizeof(REQ_MSG);
    BPSCmdGetSigReq data;

    EXPECT_GT(BPSParseGetSigReqDyn(&data, REQ_MSG+BPS_CMD_WORD_POSITION+1, size), 0);
    EXPECT_EQ(data.sigNum, sizeof(SIG_ARRAY)/sizeof(SIG_ARRAY[0]));
    for(size_t i = 0; i < data.sigNum; i++) {
        BPS_UINT16 sig = data.sigArray[i];
        if(SIG_ARRAY[0] == sig) {
            ASSERT_TRUE(BPS_TRUE);
        } else {
            ASSERT_FALSE("Unknown Hardware info type");
        }
    }
    BPSFreeMemGetSigReq(&data);
}

/** parse(DYN) the get signal values command response 
  * packet flow: MCU <- MODULE */
TEST(COMMAND_GET_SIG, ParseResponseDyn)
{
    BPS_WORD size = sizeof(RSP_MSG);
    BPSCmdGetSigRsp data;

    EXPECT_GT(BPSParseGetSigRspDyn(&data, RSP_MSG+BPS_CMD_WORD_POSITION+1, size), 0);
    EXPECT_EQ(data.fieldNum, sizeof(FIELD_ARRAY)/sizeof(FIELD_ARRAY[0]));
    for(size_t i = 0; i < data.fieldNum; i++) {
        BPSCmdGetSigField * field = &(data.fieldArray[i]);
        if(FIELD_ARRAY[0].signalId == field->signalId) {
            EXPECT_EQ(field->signalType, FIELD_ARRAY[0].signalType);
            EXPECT_EQ(field->value.t_enm, FIELD_ARRAY[0].value.t_enm);
        } else {
            ASSERT_FALSE("Unknown Hardware info type");
        }
    }
    BPSFreeMemGetSigRsp(&data);
}
#endif
