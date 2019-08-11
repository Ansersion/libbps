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
#include <bps_sig_ret_code.h>
#include <bps_public.h>
#include <bps_cmd_comm_test.h>
}


using namespace std;

/** post siangl: signal ID=0x0001, type=0x04(ENUM), value=0x0002 */
static const int MSG_BUF_SIZE = 256;
static BPS_UINT8 buf[MSG_BUF_SIZE];
static const int MCU_ADDR = 0;
static const int MODULE_ADDR = 1;
static const BPS_WORD HEADER_SIZE = BPS_HEADER_SIZE - BPS_VERSION_SIZE - BPS_ADDR_SIZE - BPS_REMAIN_LEN_SIZE;

BPS_UINT8 COMM_TEST_REQ_MSG[] = 
{
    0xBB, 0xCC, 0x00, 0x01, 0x00, 0x01, 0x00, 0x02
};

BPS_UINT8 COMM_TEST_RSP_MSG[] = 
{
    0xBB, 0xCC, 0x00, 0x10, 0x00, 0x01, 0x01, 0x12
};

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
    for(size_t i = 0; i < sizeof(COMM_TEST_REQ_MSG); i++) {
        EXPECT_EQ(COMM_TEST_REQ_MSG[i], buf[i]);
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
    for(size_t i = 0; i < sizeof(COMM_TEST_RSP_MSG); i++) {
        EXPECT_EQ(COMM_TEST_RSP_MSG[i], buf[i]);
    }
}

/** parse the communication test command request
  * packet flow: MODULE <- MCU */
TEST(COMMAND_COMM_TEST, ParseRequest)
{
    BPS_WORD size = sizeof(COMM_TEST_REQ_MSG);
    BPSCmdCommTestReq data;
    BPSParseCommTestReq(&data, COMM_TEST_REQ_MSG+BPS_CMD_WORD_POSITION+1, size);
}

/** parse the communication test command response 
  * packet flow: MCU <- MODULE */
TEST(COMMAND_COMM_TEST, ParseResponse)
{
    BPS_WORD size = sizeof(COMM_TEST_RSP_MSG);
    BPSCmdCommTestRsp data;
    BPSParseCommTestRsp(&data, COMM_TEST_RSP_MSG+BPS_CMD_WORD_POSITION+1, size);
}
