//   Copyright 2020 Ansersion
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
#include <bps_cmd_clear_space.h>
}


using namespace std;
#if (BPS_CMD_SET == BPS_CMD_SET_B || BPS_CMD_SET == BPS_CMD_SET_T || BPS_CMD_SET == BPS_CMD_SET_C)

/** clear space of 64KB by auto mode */
static const int MSG_BUF_SIZE = 256;
static BPS_UINT8 buf[MSG_BUF_SIZE];
static const int MCU_ADDR = 0;
static const int MODULE_ADDR = 1;
static const BPS_WORD HEADER_SIZE = BPS_HEADER_SIZE - BPS_VERSION_SIZE - BPS_ADDR_SIZE - BPS_REMAIN_LEN_SIZE;

static const ReqTypeClearSpace ReqType = RT_CLR_SPC_AUTO;
static const BPS_UINT32 SpaceLen = 0x10000;
static const BPS_UINT8 RET_CODE = BPS_RET_CODE_OK;

static BPS_UINT8 REQ_MSG[] = 
{
    0xBB, 0xCC, 0x00, 0x01, 0x00, 0x06, 0x08, 0x00, 0x00, 0x01, 0x00, 0x00, 0x10,
};

static BPS_UINT8 RSP_MSG[] = 
{
    0xBB, 0xCC, 0x00, 0x10, 0x00, 0x02, 0x09, 0x00, 0x1B,
};

/** pack the clear space command request
  * packet flow: MCU -> MODULE */
TEST(COMMAND_CLEAR_SPACE, PackRequest)
{
    BPS_UINT8 * buf_tmp = buf;
    BPSCmdClearSpaceReq data;
    data.mode = ReqType;
    data.len = SpaceLen;

    memset(buf, 0, MSG_BUF_SIZE);

    buf_tmp = PackBPSHeader(buf_tmp);
    buf_tmp = PackBPSVersion(buf_tmp);
    buf_tmp = PackBPSAddr(buf_tmp, MCU_ADDR, MODULE_ADDR);
    buf_tmp += BPS_REMAIN_LEN_SIZE;

    BPS_UINT16 tmpLen = BPSPackClearSpaceReq(&data, buf_tmp, MSG_BUF_SIZE-HEADER_SIZE);
    EXPECT_GT(tmpLen, 0);
    PackBPSRemainLen(buf + BPS_REMAIN_LEN_POSITION, tmpLen);
    EXPECT_NE(PackBPSChecksum(buf, MSG_BUF_SIZE), (BPS_UINT8 *)BPS_NULL);
    tmpLen += HEADER_SIZE + BPS_CHECKSUM_SIZE;
    for(size_t i = 0; i < sizeof(REQ_MSG); i++) {
        EXPECT_EQ(REQ_MSG[i], buf[i]);
    }
}

/** pack the clear space command response 
  * packet flow: MODULE -> MCU */

TEST(COMMAND_CLEAR_SPACE, PackResponse)
{
    BPS_UINT8 * buf_tmp = buf;
    BPSCmdClearSpaceRsp data;
    data.retCode = RET_CODE;

    memset(buf, 0, MSG_BUF_SIZE);

    buf_tmp = PackBPSHeader(buf_tmp);
    buf_tmp = PackBPSVersion(buf_tmp);
    buf_tmp = PackBPSAddr(buf_tmp, MODULE_ADDR, MCU_ADDR);
    buf_tmp += BPS_REMAIN_LEN_SIZE;

    BPS_UINT16 tmpLen = BPSPackClearSpaceRsp(&data, buf_tmp, MSG_BUF_SIZE-HEADER_SIZE);
    EXPECT_GT(tmpLen, 0);
    PackBPSRemainLen(buf + BPS_REMAIN_LEN_POSITION, tmpLen);
    EXPECT_NE(PackBPSChecksum(buf, MSG_BUF_SIZE), (BPS_UINT8 *)BPS_NULL);
    tmpLen += HEADER_SIZE + BPS_CHECKSUM_SIZE;
    for(size_t i = 0; i < sizeof(RSP_MSG); i++) {
        EXPECT_EQ(RSP_MSG[i], buf[i]);
    }
}
// 
/** parse the clear space command request
  * packet flow: MODULE <- MCU */
TEST(COMMAND_CLEAR_SPACE, ParseRequest)
{
    BPS_WORD size = sizeof(REQ_MSG);
    BPSCmdClearSpaceReq data;
    EXPECT_GT(BPSParseClearSpaceReq(&data, REQ_MSG+BPS_CMD_WORD_POSITION+1, size), 0);
    EXPECT_EQ(data.mode, ReqType);
}

/** parse the clear space command response 
  * packet flow: MCU <- MODULE */
TEST(COMMAND_CLEAR_SPACE, ParseResponse)
{
    BPS_WORD size = sizeof(RSP_MSG);
    BPSCmdClearSpaceRsp data;
    EXPECT_GT(BPSParseClearSpaceRsp(&data, RSP_MSG+BPS_CMD_WORD_POSITION+1, size), 0);
    EXPECT_EQ(data.retCode, RET_CODE);
}

/** parse(DYN) the clear space command request
  * packet flow: MODULE <- MCU */
TEST(COMMAND_CLEAR_SPACE, ParseRequestDyn)
{
    BPS_WORD size = sizeof(REQ_MSG);
    BPSCmdClearSpaceReq data;
    EXPECT_GT(BPSParseClearSpaceReqDyn(&data, REQ_MSG+BPS_CMD_WORD_POSITION+1, size), 0);
    EXPECT_EQ(data.mode, ReqType);
    BPSFreeMemClearSpaceReq(&data);
}

/** parse(DYN) the clear space command response 
  * packet flow: MCU <- MODULE */
TEST(COMMAND_CLEAR_SPACE, ParseResponseDyn)
{
    BPS_WORD size = sizeof(RSP_MSG);
    BPSCmdClearSpaceRsp data;
    EXPECT_GT(BPSParseClearSpaceRspDyn(&data, RSP_MSG+BPS_CMD_WORD_POSITION+1, size), 0);
    EXPECT_EQ(data.retCode, RET_CODE);
    BPSFreeMemClearSpaceRsp(&data);
}
#endif
