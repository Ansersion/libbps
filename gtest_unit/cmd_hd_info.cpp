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
#include <cstring>
#include <cstdio>
#include <gtest/gtest.h>

extern "C" 
{
#include <bps_ret_code.h>
#include <bps_public.h>
#include <bps_cmd_hd_info.h>
}


using namespace std;

#if (BPS_CMD_SET == BPS_CMD_SET_B || BPS_CMD_SET == BPS_CMD_SET_T || BPS_CMD_SET == BPS_CMD_SET_C)

/** hardware info: SN="ABCDEFGHIJKLMNOP", HDVersion="1.0.0.0", STVersion="2.0.0.0" */
static const int MSG_BUF_SIZE = 256;
static BPS_UINT8 buf[MSG_BUF_SIZE];
static const int MAX_FIELD_NUM = 3;
static const int MCU_ADDR = 0;
static const int MODULE_ADDR = 1;
static const BPS_WORD HEADER_SIZE = BPS_HEADER_SIZE - BPS_VERSION_SIZE - BPS_ADDR_SIZE - BPS_REMAIN_LEN_SIZE;
static const BPSCmdHDInfoField FIELD_ARRAY[] = {
    {SN_RST_HD_INFO,    sizeof("ABCDEFGHIJKLMNOP") - 1,     (BPS_UINT8 *)"ABCDEFGHIJKLMNOP", 0},
    {HARD_V_RST_HD_INFO,  sizeof("1.0.0.0") - 1,              (BPS_UINT8 *)"1.0.0.0", 0},
    {SOFT_V_RST_HD_INFO,  sizeof("2.0.0.0") - 1,              (BPS_UINT8 *)"2.0.0.0", 0},
};

static BPS_UINT8 REQ_MSG[] = 
{
    0xBB, 0xCC, 0x00, 0x01, 0x00, 0x01, 0x02, 0x04
};

static BPS_UINT8 RSP_MSG[] = 
{
    0xBB, 0xCC, 0x00, 0x10, 0x00, 0x26, 0x03, 0x03, 0x00, 0x10, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x01, 0x07, 0x31, 0x2E, 0x30, 0x2E, 0x30, 0x2E, 0x30, 0x02, 0x07, 0x32, 0x2E, 0x30, 0x2E, 0x30, 0x2E, 0x30, 0x7C 
};

/** pack the hardware info command request
  * packet flow: MCU -> MODULE */
TEST(COMMAND_HD_INFO, PackRequest)
{
    BPS_UINT8 * buf_tmp = buf;
    BPSCmdHDInfoReq data;

    memset(buf, 0, MSG_BUF_SIZE);

    buf_tmp = PackBPSHeader(buf_tmp);
    buf_tmp = PackBPSVersion(buf_tmp);
    buf_tmp = PackBPSAddr(buf_tmp, MCU_ADDR, MODULE_ADDR);
    buf_tmp += BPS_REMAIN_LEN_SIZE;

    BPS_UINT16 tmpLen = BPSPackHDInfoReq(&data, buf_tmp, MSG_BUF_SIZE-HEADER_SIZE);
    EXPECT_GT(tmpLen, 0);
    PackBPSRemainLen(buf + BPS_REMAIN_LEN_POSITION, tmpLen);
    EXPECT_NE(PackBPSChecksum(buf, MSG_BUF_SIZE), (BPS_UINT8 *)BPS_NULL);
    tmpLen += HEADER_SIZE + BPS_CHECKSUM_SIZE;
    for(size_t i = 0; i < sizeof(REQ_MSG); i++) {
        EXPECT_EQ(REQ_MSG[i], buf[i]);
    }
}

/** pack the hardware info command response 
  * packet flow: MODULE -> MCU */

TEST(COMMAND_HD_INFO, PackResponse)
{
    BPS_UINT8 * buf_tmp = buf;
    BPSCmdHDInfoRsp data;

    memset(buf, 0, MSG_BUF_SIZE);
    data.fieldArray = (BPSCmdHDInfoField *)FIELD_ARRAY;
    data.fieldNum = sizeof(FIELD_ARRAY)/sizeof(BPSCmdHDInfoField);

    buf_tmp = PackBPSHeader(buf_tmp);
    buf_tmp = PackBPSVersion(buf_tmp);
    buf_tmp = PackBPSAddr(buf_tmp, MODULE_ADDR, MCU_ADDR);
    buf_tmp += BPS_REMAIN_LEN_SIZE;

    BPS_UINT16 tmpLen = BPSPackHDInfoRsp(&data, buf_tmp, MSG_BUF_SIZE-HEADER_SIZE);
    EXPECT_GT(tmpLen, 0);
    PackBPSRemainLen(buf + BPS_REMAIN_LEN_POSITION, tmpLen);
    EXPECT_NE(PackBPSChecksum(buf, MSG_BUF_SIZE), (BPS_UINT8 *)BPS_NULL);
    tmpLen += HEADER_SIZE + BPS_CHECKSUM_SIZE;
    for(size_t i = 0; i < sizeof(RSP_MSG); i++) {
        EXPECT_EQ(RSP_MSG[i], buf[i]);
    }
}

/** parse the hardware info command request
  * packet flow: MODULE <- MCU */
TEST(COMMAND_HD_INFO, ParseRequest)
{
    BPS_WORD size = sizeof(REQ_MSG);
    BPSCmdHDInfoReq data;
    BPSParseHDInfoReq(&data, REQ_MSG+BPS_CMD_WORD_POSITION+1, size);
}

/** parse the hardware info command response 
  * packet flow: MCU <- MODULE */
TEST(COMMAND_HD_INFO, ParseResponse)
{
    BPS_WORD size = sizeof(RSP_MSG);
    BPSCmdHDInfoField fields[MAX_FIELD_NUM];
    BPS_UINT8 buf0[128] = {0};
    BPS_UINT8 buf1[128] = {0};
    BPS_UINT8 buf2[128] = {0};
    fields[0].data = buf0;
    fields[1].data = buf1;
    fields[2].data = buf2;
    fields[0].maxLen = 128;
    fields[1].maxLen = 128;
    fields[2].maxLen = 128;
    BPSCmdHDInfoRsp data;

    data.infoTypeArray = BPS_NULL;
    data.fieldArray = fields;
    data.maxFieldNum = MAX_FIELD_NUM;

    EXPECT_GT(BPSParseHDInfoRsp(&data, RSP_MSG+BPS_CMD_WORD_POSITION+1, size), 0);
    EXPECT_EQ(data.fieldNum, sizeof(FIELD_ARRAY)/sizeof(BPSCmdHDInfoField));

    for(size_t i = 0; i < data.fieldNum; i++) {
        BPSCmdHDInfoField * field = &(data.fieldArray[i]);
        if(SN_RST_HD_INFO == field->type) {
            EXPECT_EQ(field->len, FIELD_ARRAY[0].len);
            EXPECT_EQ(strncmp((const char *)field->data, (const char *)FIELD_ARRAY[0].data, field->len), 0);
        } else if(HARD_V_RST_HD_INFO == field->type) {
            EXPECT_EQ(field->len, FIELD_ARRAY[1].len);
            EXPECT_EQ(strncmp((const char *)field->data, (const char *)FIELD_ARRAY[1].data, field->len), 0);
        } else if(SOFT_V_RST_HD_INFO == field->type) {
            EXPECT_EQ(field->len, FIELD_ARRAY[2].len);
            EXPECT_EQ(strncmp((const char *)field->data, (const char *)FIELD_ARRAY[2].data, field->len), 0);
        } else {
            ASSERT_FALSE("Unknown Hardware info type");
        }
    }
}

/** parse(DYN) the hardware info command request
  * packet flow: MODULE <- MCU */
TEST(COMMAND_HD_INFO, ParseRequestDyn)
{
    BPS_WORD size = sizeof(REQ_MSG);
    BPSCmdHDInfoReq data;
    /** always zero, no need to check */
    // EXPECT_GT(BPSParseHDInfoReqDyn(&data, REQ_MSG+BPS_CMD_WORD_POSITION+1, size), 0);
    BPSParseHDInfoReqDyn(&data, REQ_MSG+BPS_CMD_WORD_POSITION+1, size);
    BPSFreeMemHDInfoReq(&data);
}

/** parse(DYN) the hardware info command response 
  * packet flow: MCU <- MODULE */
TEST(COMMAND_HD_INFO, ParseResponseDyn)
{
    BPS_WORD size = sizeof(RSP_MSG);
    BPSCmdHDInfoField fields[MAX_FIELD_NUM];
    BPS_UINT8 buf0[128] = {0};
    BPS_UINT8 buf1[128] = {0};
    BPS_UINT8 buf2[128] = {0};
    fields[0].data = buf0;
    fields[1].data = buf1;
    fields[2].data = buf2;
    fields[0].maxLen = 128;
    fields[1].maxLen = 128;
    fields[2].maxLen = 128;
    BPSCmdHDInfoRsp data;

    data.fieldArray = fields;
    data.maxFieldNum = MAX_FIELD_NUM;

    EXPECT_GT(BPSParseHDInfoRspDyn(&data, RSP_MSG+BPS_CMD_WORD_POSITION+1, size), 0);
    EXPECT_EQ(data.fieldNum, sizeof(FIELD_ARRAY)/sizeof(BPSCmdHDInfoField));

    for(size_t i = 0; i < data.fieldNum; i++) {
        BPSCmdHDInfoField * field = &(data.fieldArray[i]);
        if(SN_RST_HD_INFO == field->type) {
            EXPECT_EQ(field->len, FIELD_ARRAY[0].len);
            EXPECT_EQ(strncmp((const char *)field->data, (const char *)FIELD_ARRAY[0].data, field->len), 0);
        } else if(HARD_V_RST_HD_INFO == field->type) {
            EXPECT_EQ(field->len, FIELD_ARRAY[1].len);
            EXPECT_EQ(strncmp((const char *)field->data, (const char *)FIELD_ARRAY[1].data, field->len), 0);
        } else if(SOFT_V_RST_HD_INFO == field->type) {
            EXPECT_EQ(field->len, FIELD_ARRAY[2].len);
            EXPECT_EQ(strncmp((const char *)field->data, (const char *)FIELD_ARRAY[2].data, field->len), 0);
        } else {
            ASSERT_FALSE("Unknown Hardware info type");
        }
    }
    BPSFreeMemHDInfoRsp(&data);
}
#endif
