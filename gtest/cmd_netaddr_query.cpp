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
#include <bps_cmd_netaddr_query.h>
#include <bps_net_addr.h>
}


using namespace std;

#if (BPS_CMD_SET == BPS_CMD_SET_C)

/** query the net address: WIFI CONNECTED */
static const int MSG_BUF_SIZE = 256;
static BPS_UINT8 buf[MSG_BUF_SIZE];
static const int MCU_ADDR = 0;
static const int MODULE_ADDR = 1;
static const BPS_WORD HEADER_SIZE = BPS_HEADER_SIZE - BPS_VERSION_SIZE - BPS_ADDR_SIZE - BPS_REMAIN_LEN_SIZE;

static BPS_UINT8 NET_ADDR_TYPE = NA_MAC;
static BPS_UINT8 NET_ADDR_MAC[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};

static BPS_UINT8 REQ_MSG[] = 
{
    0xBB, 0xCC, 0x00, 0x01, 0x00, 0x02, 0x8E, 0x00, 0x91
};

static BPS_UINT8 RSP_MSG[] = 
{
    0xBB, 0xCC, 0x00, 0x10, 0x00, 0x08, 0x8F, 0x06, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x12
};

/** pack the query net address command request
  * packet flow: MCU -> MODULE */
TEST(COMMAND_NETADDR_QUERY, PackRequest)
{
    BPS_UINT8 * buf_tmp = buf;
    BPSCmdNetaddrQueryReq data;

    memset(buf, 0, MSG_BUF_SIZE);
    data.type = NET_ADDR_TYPE;

    buf_tmp = PackBPSHeader(buf_tmp);
    buf_tmp = PackBPSVersion(buf_tmp);
    buf_tmp = PackBPSAddr(buf_tmp, MCU_ADDR, MODULE_ADDR);
    buf_tmp += BPS_REMAIN_LEN_SIZE;

    BPS_UINT16 tmpLen = BPSPackNetaddrQueryReq(&data, buf_tmp, MSG_BUF_SIZE-HEADER_SIZE);
    EXPECT_GT(tmpLen, 0);
    PackBPSRemainLen(buf + BPS_REMAIN_LEN_POSITION, tmpLen);
    EXPECT_NE(PackBPSChecksum(buf, MSG_BUF_SIZE), (BPS_UINT8 *)BPS_NULL);
    tmpLen += HEADER_SIZE + BPS_CHECKSUM_SIZE;
    for(size_t i = 0; i < sizeof(REQ_MSG); i++) {
        EXPECT_EQ(REQ_MSG[i], buf[i]);
    }
}

/** pack the query net address command response 
  * packet flow: MODULE -> MCU */

TEST(COMMAND_NETADDR_QUERY, PackResponse)
{
    BPS_UINT8 * buf_tmp = buf;
    BPSCmdNetaddrQueryRsp data;

    memset(buf, 0, MSG_BUF_SIZE);
    data.len = sizeof(NET_ADDR_MAC);
    data.data = NET_ADDR_MAC;

    buf_tmp = PackBPSHeader(buf_tmp);
    buf_tmp = PackBPSVersion(buf_tmp);
    buf_tmp = PackBPSAddr(buf_tmp, MODULE_ADDR, MCU_ADDR);
    buf_tmp += BPS_REMAIN_LEN_SIZE;

    BPS_UINT16 tmpLen = BPSPackNetaddrQueryRsp(&data, buf_tmp, MSG_BUF_SIZE-HEADER_SIZE);
    EXPECT_GT(tmpLen, 0);
    PackBPSRemainLen(buf + BPS_REMAIN_LEN_POSITION, tmpLen);
    EXPECT_NE(PackBPSChecksum(buf, MSG_BUF_SIZE), (BPS_UINT8 *)BPS_NULL);
    tmpLen += HEADER_SIZE + BPS_CHECKSUM_SIZE;
    for(size_t i = 0; i < sizeof(RSP_MSG); i++) {
        EXPECT_EQ(RSP_MSG[i], buf[i]);
    }
}

/** parse the query net address command request
  * packet flow: MODULE <- MCU */
TEST(COMMAND_NETADDR_QUERY, ParseRequest)
{
    BPS_WORD size = sizeof(REQ_MSG);
    BPSCmdNetaddrQueryReq data;
    BPSParseNetaddrQueryReq(&data, REQ_MSG+BPS_CMD_WORD_POSITION+1, size);
    EXPECT_EQ(data.type, NET_ADDR_TYPE);
}

/** parse the query net address command response 
  * packet flow: MCU <- MODULE */
TEST(COMMAND_NETADDR_QUERY, ParseResponse)
{
    BPS_WORD size = sizeof(RSP_MSG);
    BPSCmdNetaddrQueryRsp data;
    EXPECT_GT(BPSParseNetaddrQueryRsp(&data, RSP_MSG+BPS_CMD_WORD_POSITION+1, size), 0);
    EXPECT_EQ(data.len, sizeof(NET_ADDR_MAC));
    for(int i = 0; i < data.len; i++) {
        EXPECT_EQ(data.data[i], NET_ADDR_MAC[i]);
    }
}

#endif
