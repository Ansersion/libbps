///////////////////////////////////////////////////////////////////////////////
/// Copyright 2019-2020 Ansersion
/// 
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
/// 
///     http://www.apache.org/licenses/LICENSE-2.0
/// 
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// @file 	bps_cmd_launch_update.c
/// @brief 	APIs for command 'launching update'
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////


#include <bps_cmd_launch_update.h>

#if (BPS_CMD_SET == BPS_CMD_SET_B || BPS_CMD_SET == BPS_CMD_SET_T || BPS_CMD_SET == BPS_CMD_SET_C)
BPS_UINT16 BPSPackLnchUpdateReq(BPSCmdLnchUpdateReq * req, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }
    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = CMD_LAUNCH_UPDATE_WORD_REQ;

    BPS_ASSERT_SIZE_TYPE(size, BPS_UINT16);
    BPS_SetBig16(&(buf[i]), SECURITY_WORD_LNCH_UPDATE);
    i += sizeof(BPS_UINT16);

    return i;
}

BPS_UINT16 BPSPackLnchUpdateRsp(BPSCmdLnchUpdateRsp * rsp, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }

    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = CMD_LAUNCH_UPDATE_WORD_RSP;

    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = rsp->retCode;

    return i;
}

BPS_UINT16 BPSParseLnchUpdateReq(BPSCmdLnchUpdateReq * req, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    BPS_UINT16 security_word = 0;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }
    BPS_ASSERT_SIZE_TYPE(size, BPS_UINT16);
    BPS_GetBig16(&(buf[i]), &security_word);
    if(SECURITY_WORD_LNCH_UPDATE != security_word) {
        return 0;
    }
    i += sizeof(BPS_UINT16);

    return i;
}

BPS_UINT16 BPSParseLnchUpdateRsp(BPSCmdLnchUpdateRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }
    BPS_ASSERT_SIZE_UINT8(size);
    rsp->retCode = buf[i++];

    return i;
}

#endif
