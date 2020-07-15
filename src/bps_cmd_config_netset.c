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
/// @file 	bps_cmd_config_netset.c
/// @brief 	APIs for command 'query net state'
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bps_public.h>
#include <bps_ret_code.h>
#include <bps_cmd_config_netset.h>

#ifdef BPS_MEM_DYN
    #include <bps_memmng.h>
#endif

#if (BPS_CMD_SET == BPS_CMD_SET_C)

BPS_UINT16 BPSPackConfigNetsetReq(BPSCmdConfigNetsetReq * req, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }
    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = CMD_CONFIG_NETSET_WORD_REQ;

    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = req->type;

    if(SET_RT_CONFIG_NET == req->type) {
        BPS_ASSERT_SIZE_UINT8(size);
        buf[i++] = req->mode;
    }

    return i;
}

BPS_UINT16 BPSPackConfigNetsetRsp(BPSCmdConfigNetsetRsp * rsp, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }
    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = CMD_CONFIG_NETSET_WORD_RSP;

    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = rsp->retCode;

    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = rsp->commType;

    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = rsp->mode;

    return i;
}

BPS_UINT16 BPSParseConfigNetsetReq(BPSCmdConfigNetsetReq * req, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }

    BPS_ASSERT_SIZE_UINT8(size);
    req->type = buf[i++];

    if(SET_RT_CONFIG_NET == req->type) {
        BPS_ASSERT_SIZE_UINT8(size);
        req->mode = buf[i++];
    }

    return i;
}

BPS_UINT16 BPSParseConfigNetsetRsp(BPSCmdConfigNetsetRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }

    BPS_ASSERT_SIZE_UINT8(size);
    rsp->retCode = buf[i++];

    BPS_ASSERT_SIZE_UINT8(size);
    rsp->commType = buf[i++];

    BPS_ASSERT_SIZE_UINT8(size);
    rsp->mode = buf[i++];

    return i;
}

#endif
