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
#include <bps_cmd_write_frmw.h>
}


using namespace std;
#if (BPS_CMD_SET == BPS_CMD_SET_B || BPS_CMD_SET == BPS_CMD_SET_T || BPS_CMD_SET == BPS_CMD_SET_C)

/** write update firmware data(64 bytes) to offset 0x00000000 by auto mode */
static const int MSG_BUF_SIZE = 256;
static BPS_UINT8 buf[MSG_BUF_SIZE];
static const int MCU_ADDR = 0;
static const int MODULE_ADDR = 1;
static const BPS_WORD HEADER_SIZE = BPS_HEADER_SIZE - BPS_VERSION_SIZE - BPS_ADDR_SIZE - BPS_REMAIN_LEN_SIZE;

static const ReqTypeWriteFrmwSet ReqType = RT_WRT_FRMW_AUTO;
static const BPS_UINT32 DataLen = 0x40;
static const BPS_UINT8 ReqData[0x40] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
};
static const BPS_UINT32 DataOffset = 0x00000000;
static const BPS_UINT8 RET_CODE = BPS_RET_CODE_OK;

static BPS_UINT8 REQ_MSG[] = 
{
    0xBB, 0xCC, 0x00, 0x01, 0x00, 0x47, 0x0A, 0x00, 0x40, 

    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,

    0x00, 0x00, 0x00, 0x00, 0x72,
};

static BPS_UINT8 RSP_MSG[] = 
{
    0xBB, 0xCC, 0x00, 0x10, 0x00, 0x02, 0x0B, 0x00, 0x1D,
};

/** pack the write update firmware command request
  * packet flow: MCU -> MODULE */
TEST(COMMAND_WRITE_FRMW, PackRequest)
{
    BPS_UINT8 * buf_tmp = buf;
    BPSCmdWriteFrmwReq data;
    data.mode = ReqType;
    data.len = DataLen;
    data.data = (BPS_UINT8 *)ReqData;
    data.offset = DataOffset;

    memset(buf, 0, MSG_BUF_SIZE);

    buf_tmp = PackBPSHeader(buf_tmp);
    buf_tmp = PackBPSVersion(buf_tmp);
    buf_tmp = PackBPSAddr(buf_tmp, MCU_ADDR, MODULE_ADDR);
    buf_tmp += BPS_REMAIN_LEN_SIZE;

    BPS_UINT16 tmpLen = BPSPackWriteFrmwReq(&data, buf_tmp, MSG_BUF_SIZE-HEADER_SIZE);
    EXPECT_GT(tmpLen, 0);
    PackBPSRemainLen(buf + BPS_REMAIN_LEN_POSITION, tmpLen);
    EXPECT_NE(PackBPSChecksum(buf, MSG_BUF_SIZE), (BPS_UINT8 *)BPS_NULL);
    tmpLen += HEADER_SIZE + BPS_CHECKSUM_SIZE;
    for(size_t i = 0; i < sizeof(REQ_MSG); i++) {
        EXPECT_EQ(REQ_MSG[i], buf[i]);
    }
}

/** pack the write update firmware command response 
  * packet flow: MODULE -> MCU */

TEST(COMMAND_WRITE_FRMW, PackResponse)
{
    BPS_UINT8 * buf_tmp = buf;
    BPSCmdWriteFrmwRsp data;
    data.retCode = RET_CODE;

    memset(buf, 0, MSG_BUF_SIZE);

    buf_tmp = PackBPSHeader(buf_tmp);
    buf_tmp = PackBPSVersion(buf_tmp);
    buf_tmp = PackBPSAddr(buf_tmp, MODULE_ADDR, MCU_ADDR);
    buf_tmp += BPS_REMAIN_LEN_SIZE;

    BPS_UINT16 tmpLen = BPSPackWriteFrmwRsp(&data, buf_tmp, MSG_BUF_SIZE-HEADER_SIZE);
    EXPECT_GT(tmpLen, 0);
    PackBPSRemainLen(buf + BPS_REMAIN_LEN_POSITION, tmpLen);
    EXPECT_NE(PackBPSChecksum(buf, MSG_BUF_SIZE), (BPS_UINT8 *)BPS_NULL);
    tmpLen += HEADER_SIZE + BPS_CHECKSUM_SIZE;
    for(size_t i = 0; i < sizeof(RSP_MSG); i++) {
        EXPECT_EQ(RSP_MSG[i], buf[i]);
    }  
}
// 
/** parse the write update firmware command request
  * packet flow: MODULE <- MCU */
TEST(COMMAND_WRITE_FRMW, ParseRequest)
{
    BPS_WORD size = sizeof(REQ_MSG);
    BPSCmdWriteFrmwReq data;
    BPS_UINT8 data_buf[DataLen];
    data.data = data_buf;
    data.maxLen = DataLen;

    EXPECT_GT(BPSParseWriteFrmwReq(&data, REQ_MSG+BPS_CMD_WORD_POSITION+1, size), 0);
    EXPECT_EQ(data.mode, ReqType);
    EXPECT_EQ(data.len, DataLen);
    for(int i = 0; i < data.len; i++) {
        EXPECT_EQ(data.data[i], ReqData[i]);
    }
    EXPECT_EQ(data.offset, DataOffset);
}

/** parse the write update firmware command response 
  * packet flow: MCU <- MODULE */
TEST(COMMAND_WRITE_FRMW, ParseResponse)
{
    BPS_WORD size = sizeof(RSP_MSG);
    BPSCmdWriteFrmwRsp data;
    EXPECT_GT(BPSParseWriteFrmwRsp(&data, RSP_MSG+BPS_CMD_WORD_POSITION+1, size), 0);
    EXPECT_EQ(data.retCode, RET_CODE);
}

/** parse(DYN) the write update firmware command request
  * packet flow: MODULE <- MCU */
TEST(COMMAND_WRITE_FRMW, ParseRequestDyn)
{
    BPS_WORD size = sizeof(REQ_MSG);
    BPSCmdWriteFrmwReq data;
    EXPECT_GT(BPSParseWriteFrmwReqDyn(&data, REQ_MSG+BPS_CMD_WORD_POSITION+1, size), 0);
    EXPECT_EQ(data.mode, ReqType);
    EXPECT_EQ(data.len, DataLen);
    for(int i = 0; i < data.len; i++) {
        EXPECT_EQ(data.data[i], ReqData[i]);
    }
    EXPECT_EQ(data.offset, DataOffset);
    BPSFreeMemWriteFrmwReq(&data);
}

/** parse(DYN) the write update firmware command response 
  * packet flow: MCU <- MODULE */
TEST(COMMAND_WRITE_FRMW, ParseResponseDyn)
{
    BPS_WORD size = sizeof(RSP_MSG);
    BPSCmdWriteFrmwRsp data;
    EXPECT_GT(BPSParseWriteFrmwRspDyn(&data, RSP_MSG+BPS_CMD_WORD_POSITION+1, size), 0);
    EXPECT_EQ(data.retCode, RET_CODE);
    BPSFreeMemWriteFrmwRsp(&data);
}
#endif
