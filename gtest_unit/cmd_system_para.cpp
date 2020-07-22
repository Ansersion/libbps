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
#include <bps_cmd_system_para.h>
}


using namespace std;

/** write system parameter SN: "ABCDEFGHIJKLMNOP" */
static const int MSG_BUF_SIZE = 256;
static BPS_UINT8 buf[MSG_BUF_SIZE];
static const int MCU_ADDR = 0;
static const int MODULE_ADDR = 1;
static const BPS_WORD HEADER_SIZE = BPS_HEADER_SIZE - BPS_VERSION_SIZE - BPS_ADDR_SIZE - BPS_REMAIN_LEN_SIZE;
static const ConfigTypeSystemPara REQ_TYPE = WRITE_SYS_PARA;
static const ParaTypeSystemPara PARA_TYPE = SN_SYS_PARA_TYPE;
// static const BPS_UINT16 INTERVAL = 0x5A5A;;
static const char * SN = "ABCDEFGHIJKLMNOP";

static BPS_UINT8 REQ_MSG[] = 
{
    0xBB, 0xCC, 0x00, 0x01, 0x00, 0x14, 0xEE, 0x01, 0x01, 0x10, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x9D
};

// bb cc 00 10 00 15 ee 01 01 00 10
static BPS_UINT8 RSP_MSG[] = 
{
    0xBB, 0xCC, 0x00, 0x10, 0x00, 0x04, 0xEF, 0x01, 0x01, 0x00, 0x05
};

/** pack the system parameter command request
  * packet flow: MCU -> MODULE */
TEST(COMMAND_SYSTEM_PARA, PackRequest)
{
    BPS_UINT8 * buf_tmp = buf;
    BPSCmdSystemParaReq data;
    data.configType = REQ_TYPE;
    data.paraType = PARA_TYPE;
    data.len = strlen(SN);
    data.data = (BPS_UINT8 *)SN;

    memset(buf, 0, MSG_BUF_SIZE);

    buf_tmp = PackBPSHeader(buf_tmp);
    buf_tmp = PackBPSVersion(buf_tmp);
    buf_tmp = PackBPSAddr(buf_tmp, MCU_ADDR, MODULE_ADDR);
    buf_tmp += BPS_REMAIN_LEN_SIZE;

    BPS_UINT16 tmpLen = BPSPackSystemParaReq(&data, buf_tmp, MSG_BUF_SIZE-HEADER_SIZE);
    EXPECT_GT(tmpLen, 0);
    PackBPSRemainLen(buf + BPS_REMAIN_LEN_POSITION, tmpLen);
    EXPECT_NE(PackBPSChecksum(buf, MSG_BUF_SIZE), (BPS_UINT8 *)BPS_NULL);
    tmpLen += HEADER_SIZE + BPS_CHECKSUM_SIZE;
    for(size_t i = 0; i < sizeof(REQ_MSG); i++) {
        EXPECT_EQ(REQ_MSG[i], buf[i]);
    }
}

/** pack the system parameter command response 
  * packet flow: MODULE -> MCU */

TEST(COMMAND_SYSTEM_PARA, PackResponse)
{
    BPS_UINT8 * buf_tmp = buf;
    BPSCmdSystemParaRsp data;
    data.configType = REQ_TYPE;
    data.paraType = PARA_TYPE;
    data.retCode = BPS_RET_CODE_OK;;
    data.len = strlen(SN);
    data.data = (BPS_UINT8 *)SN;

    memset(buf, 0, MSG_BUF_SIZE);

    buf_tmp = PackBPSHeader(buf_tmp);
    buf_tmp = PackBPSVersion(buf_tmp);
    buf_tmp = PackBPSAddr(buf_tmp, MODULE_ADDR, MCU_ADDR);
    buf_tmp += BPS_REMAIN_LEN_SIZE;

    BPS_UINT16 tmpLen = BPSPackSystemParaRsp(&data, buf_tmp, MSG_BUF_SIZE-HEADER_SIZE);
    EXPECT_GT(tmpLen, 0);
    PackBPSRemainLen(buf + BPS_REMAIN_LEN_POSITION, tmpLen);
    EXPECT_NE(PackBPSChecksum(buf, MSG_BUF_SIZE), (BPS_UINT8 *)BPS_NULL);
    tmpLen += HEADER_SIZE + BPS_CHECKSUM_SIZE;
    for(size_t i = 0; i < sizeof(RSP_MSG); i++) {
        // printf("%02x ", buf[i]);
        EXPECT_EQ(RSP_MSG[i], buf[i]);
    }
    // printf("\n");
}

/** parse the system parameter command request
  * packet flow: MODULE <- MCU */
TEST(COMMAND_SYSTEM_PARA, ParseRequest)
{
    BPS_WORD size = sizeof(REQ_MSG);
    BPSCmdSystemParaReq data;
    BPS_UINT8 buffer[256];
    data.data = buffer;
    EXPECT_GT(BPSParseSystemParaReq(&data, REQ_MSG+BPS_CMD_WORD_POSITION+1, size), 0);
    EXPECT_EQ(data.configType, REQ_TYPE);
    EXPECT_EQ(data.paraType, PARA_TYPE);
    EXPECT_EQ(data.len, strlen(SN));
    EXPECT_EQ(strncmp((const char *)data.data, (const char *)SN, strlen(SN)), 0);
}

/** parse the system parameter command response 
  * packet flow: MCU <- MODULE */
TEST(COMMAND_SYSTEM_PARA, ParseResponse)
{
    BPS_WORD size = sizeof(RSP_MSG);
    BPSCmdSystemParaRsp data;
    EXPECT_GT(BPSParseSystemParaRsp(&data, RSP_MSG+BPS_CMD_WORD_POSITION+1, size), 0);
    EXPECT_EQ(data.configType, REQ_TYPE);
    EXPECT_EQ(data.paraType, PARA_TYPE);
}
