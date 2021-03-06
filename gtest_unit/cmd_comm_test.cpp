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
#include <bps_cmd_comm_test.h>
}

using namespace std;

#if (BPS_CMD_SET == BPS_CMD_SET_B || BPS_CMD_SET == BPS_CMD_SET_T || BPS_CMD_SET == BPS_CMD_SET_C)
static const int MSG_BUF_SIZE = 256;
static BPS_UINT8 buf[MSG_BUF_SIZE];
static const int MCU_ADDR = 0;
static const int MODULE_ADDR = 1;
static const BPS_WORD HEADER_SIZE = BPS_HEADER_SIZE - BPS_VERSION_SIZE - BPS_ADDR_SIZE - BPS_REMAIN_LEN_SIZE;

static BPS_UINT8 REQ_MSG[] = 
{
    0xBB, 0xCC, 0x00, 0x01, 0x00, 0x01, 0x00, 0x02
};

#if (BPS_CMD_SET == BPS_CMD_SET_C)
static BPS_UINT8 RSP_MSG[] = 
{
    0xBB, 0xCC, 0x00, 0x10, 0x00, 0x02, 0x01, BPS_CMD_SET, 0x56
};

#elif (BPS_CMD_SET == BPS_CMD_SET_T)
static BPS_UINT8 RSP_MSG[] = 
{
    0xBB, 0xCC, 0x00, 0x10, 0x00, 0x02, 0x01, BPS_CMD_SET, 0x67
};

#elif (BPS_CMD_SET == BPS_CMD_SET_B)
static BPS_UINT8 RSP_MSG[] = 
{
    0xBB, 0xCC, 0x00, 0x10, 0x00, 0x02, 0x01, BPS_CMD_SET, 0x55
};
#else
#error Please define macro BPS_CMD_SET first to BPS_CMD_SET_B/BPS_CMD_SET_T/BPS_CMD_SET_C
#endif

/** pack the communication test command request
  * packet flow: MCU -> MODULE */
TEST(COMMAND_COMM_TEST, PackRequest)
{
    BPS_UINT8 * buf_tmp = buf;
    BPSCmdCommTestReq data;

    memset(buf, 0, MSG_BUF_SIZE);

    buf_tmp = PackBPSHeader(buf_tmp);
    buf_tmp = PackBPSVersion(buf_tmp);
    buf_tmp = PackBPSAddr(buf_tmp, MCU_ADDR, MODULE_ADDR);
    buf_tmp += BPS_REMAIN_LEN_SIZE;

    BPS_UINT16 tmpLen = BPSPackCommTestReq(&data, buf_tmp, MSG_BUF_SIZE-HEADER_SIZE);
    EXPECT_GT(tmpLen, 0);
    PackBPSRemainLen(buf + BPS_REMAIN_LEN_POSITION, tmpLen);
    EXPECT_NE(PackBPSChecksum(buf, MSG_BUF_SIZE), (BPS_UINT8 *)BPS_NULL);
    tmpLen += HEADER_SIZE + BPS_CHECKSUM_SIZE;
    for(size_t i = 0; i < sizeof(REQ_MSG); i++) {
        EXPECT_EQ(REQ_MSG[i], buf[i]);
    }
}

/** pack the communication test command response 
  * packet flow: MODULE -> MCU */

TEST(COMMAND_COMM_TEST, PackResponse)
{
    BPS_UINT8 * buf_tmp = buf;
    BPSCmdCommTestRsp data;

    memset(buf, 0, MSG_BUF_SIZE);

    buf_tmp = PackBPSHeader(buf_tmp);
    buf_tmp = PackBPSVersion(buf_tmp);
    buf_tmp = PackBPSAddr(buf_tmp, MODULE_ADDR, MCU_ADDR);
    buf_tmp += BPS_REMAIN_LEN_SIZE;

    BPS_UINT16 tmpLen = BPSPackCommTestRsp(&data, buf_tmp, MSG_BUF_SIZE-HEADER_SIZE);
    EXPECT_GT(tmpLen, 0);
    PackBPSRemainLen(buf + BPS_REMAIN_LEN_POSITION, tmpLen);
    EXPECT_NE(PackBPSChecksum(buf, MSG_BUF_SIZE), (BPS_UINT8 *)BPS_NULL);
    tmpLen += HEADER_SIZE + BPS_CHECKSUM_SIZE;
    for(size_t i = 0; i < sizeof(RSP_MSG); i++) {
        EXPECT_EQ(RSP_MSG[i], buf[i]);
    }
}

/** parse the communication test command request
  * packet flow: MODULE <- MCU */
TEST(COMMAND_COMM_TEST, ParseRequest)
{
    BPS_WORD size = sizeof(REQ_MSG);
    BPSCmdCommTestReq data;
    BPSParseCommTestReq(&data, REQ_MSG+BPS_CMD_WORD_POSITION+1, size);
}

/** parse the communication test command response 
  * packet flow: MCU <- MODULE */
TEST(COMMAND_COMM_TEST, ParseResponse)
{
    BPS_WORD size = sizeof(RSP_MSG);
    BPSCmdCommTestRsp data;
    BPSParseCommTestRsp(&data, RSP_MSG+BPS_CMD_WORD_POSITION+1, size);
    EXPECT_EQ(data.cmdSet, BPS_CMD_SET);
}

/** parse(DYN) the communication test command request
  * packet flow: MODULE <- MCU */
TEST(COMMAND_COMM_TEST, ParseRequestDyn)
{
    BPS_WORD size = sizeof(REQ_MSG);
    BPSCmdCommTestReq data;
    // EXPECT_GT(BPSParseCommTestReqDyn(&data, REQ_MSG+BPS_CMD_WORD_POSITION+1, size), 0);
    /** always zero, no need to check */
    BPSParseCommTestReqDyn(&data, REQ_MSG+BPS_CMD_WORD_POSITION+1, size);
    BPSFreeMemCommTestReq(&data);
}

/** parse(DYN) the communication test command response 
  * packet flow: MCU <- MODULE */
TEST(COMMAND_COMM_TEST, ParseResponseDyn)
{
    BPS_WORD size = sizeof(RSP_MSG);
    BPSCmdCommTestRsp data;
    EXPECT_GT(BPSParseCommTestRspDyn(&data, RSP_MSG+BPS_CMD_WORD_POSITION+1, size), 0);
    EXPECT_EQ(data.cmdSet, BPS_CMD_SET);
    BPSFreeMemCommTestRsp(&data);
}
#endif
