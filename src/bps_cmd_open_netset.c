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
/// @file 	bps_cmd_open_netset.c
/// @brief 	APIs for command 'open net setting'
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bps_cmd_open_netset.h>

BP_UINT16 BPSPackOpenNetsetReq(BPSCmdOpenNetsetReq * req, BP_UINT8 * buf, BP_WORD size)
{
    BP_UINT16 i = 0;
    if(BP_NULL == req || BP_NULL == buf) {
        return 0;
    }
    if(0 == size--) {
        return 0;
    }
    buf[i++] = CMD_OPEN_NETSET_WORD_REQ;

    if(0 == size--) {
        return 0;
    }
    buf[i++] = req->type;

    return i;
}

BP_UINT16 BPSPackOpenNetsetRsp(BPSCmdOpenNetsetRsp * rsp, BP_UINT8 * buf, BP_WORD size)
{
    BP_UINT16 i = 0;
    if(BP_NULL == rsp || BP_NULL == buf) {
        return 0;
    }
    if(0 == size--) {
        return 0;
    }
    buf[i++] = CMD_OPEN_NETSET_WORD_RSP;

    if(0 == size--) {
        return 0;
    }
    buf[i++] = rsp->retCode;

    return i;
}

BP_UINT16 BPSParseOpenNetsetReq(BPSCmdOpenNetsetReq * req, BP_UINT8 * buf, BP_WORD size)
{
    BP_UINT16 i = 0;
    if(BP_NULL == req || BP_NULL == buf) {
        return 0;
    }

    if(0 == size--) {
        return 0;
    }
    req->type = buf[i++];

    return i;
}

BP_UINT16 BPSParseOpenNetsetRsp(BPSCmdOpenNetsetRsp * rsp, BP_UINT8 * buf, BP_WORD size)
{
    BP_UINT16 i = 0;
    if(BP_NULL == rsp || BP_NULL == buf) {
        return 0;
    }

    if(0 == size--) {
        return 0;
    }
    rsp->retCode = buf[i++];

    return i;
}
