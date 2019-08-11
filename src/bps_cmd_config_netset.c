///////////////////////////////////////////////////////////////////////////////
/// Copyright 2019 Ansersion
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

#include <bps_cmd_config_netset.h>

BPS_UINT16 BPSPackConfigNetsetReq(BPSCmdConfigNetsetReq * req, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }
    if(0 == size--) {
        return 0;
    }
    buf[i++] = CMD_CONFIG_NETSET_WORD_REQ;

    if(0 == size--) {
        return 0;
    }
    buf[i++] = req->type;

    if(SET_RT_CONFIG_NET == req->type) {
        if(0 == size--) {
            return 0;
        }
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
    if(0 == size--) {
        return 0;
    }
    buf[i++] = CMD_CONFIG_NETSET_WORD_RSP;

    if(0 == size--) {
        return 0;
    }
    buf[i++] = rsp->retCode;

    if(0 == size--) {
        return 0;
    }
    buf[i++] = rsp->commType;

    if(0 == size--) {
        return 0;
    }
    buf[i++] = rsp->mode;

    return i;
}

BPS_UINT16 BPSParseConfigNetsetReq(BPSCmdConfigNetsetReq * req, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }

    if(0 == size--) {
        return 0;
    }
    req->type = buf[i++];

    if(SET_RT_CONFIG_NET == req->type) {
        if(0 == size--) {
            return 0;
        }
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

    if(0 == size--) {
        return 0;
    }
    rsp->retCode = buf[i++];

    if(0 == size--) {
        return 0;
    }
    rsp->commType = buf[i++];

    if(0 == size--) {
        return 0;
    }
    rsp->mode = buf[i++];

    return i;
}

