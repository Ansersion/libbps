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
/// @file 	bps_cmd_netstate_query.c
/// @brief 	APIs for command 'configure net setting'
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bps_cmd_netstate_query.h>

BPS_UINT16 BPSPackNetstateQueryReq(BPSCmdNetstateQueryReq * req, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }
    if(0 == size--) {
        return 0;
    }
    buf[i++] = CMD_NETSTATE_QUERY_WORD_REQ;

    return i;
}

BPS_UINT16 BPSPackNetstateQueryRsp(BPSCmdNetstateQueryRsp * rsp, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }
    if(0 == size--) {
        return 0;
    }
    buf[i++] = CMD_NETSTATE_QUERY_WORD_RSP;

    if(0 == size--) {
        return 0;
    }
    buf[i++] = rsp->state;

    return i;
}

BPS_UINT16 BPSParseNetstateQueryReq(BPSCmdNetstateQueryReq * req, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }

    return i;
}

BPS_UINT16 BPSParseNetstateQueryRsp(BPSCmdNetstateQueryRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }

    if(0 == size--) {
        return 0;
    }
    rsp->state = buf[i++];

    return i;
}

