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
/// @file 	bps_cmd_ping.c
/// @brief 	APIs for command 'ping'
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bps_cmd_ping.h>

BPS_UINT16 BPSPackPingReq(BPSCmdPingReq * req, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }
    if(0 == size--) {
        return 0;
    }
    buf[i++] = CMD_PING_WORD_REQ;

    if(0 == size--) {
        return 0;
    }
    buf[i++] = req->type;

    if(size < sizeof(BPS_UINT16)) {
        return 0;
    }
    size -= sizeof(BPS_UINT16);
    buf = BPS_SetBig16(&(buf[i]), req->interval);
    i += sizeof(BPS_UINT16);

    return i;
}

BPS_UINT16 BPSPackPingRsp(BPSCmdPingRsp * rsp, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }
    if(0 == size--) {
        return 0;
    }
    buf[i++] = CMD_PING_WORD_RSP;

    if(size < sizeof(BPS_UINT16)) {
        return 0;
    }
    size -= sizeof(BPS_UINT16);
    buf = BPS_SetBig16(&(buf[i]), rsp->interval);
    i += sizeof(BPS_UINT16);

    return i;
}

BPS_UINT16 BPSParsePingReq(BPSCmdPingReq * req, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }

    if(0 == size--) {
        return 0;
    }
    req->type = buf[i++];

    if(SET_RT_PING == req->type) {
        if(size < sizeof(BPS_UINT16)) {
            return 0;
        }
        size -= sizeof(BPS_UINT16);
        buf = BPS_GetBig16(&(buf[i]), &(req->interval));
        i += sizeof(BPS_UINT16);
    }

    return i;
}

BPS_UINT16 BPSParsePingRsp(BPSCmdPingRsp * rsp, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }

    if(size < sizeof(BPS_UINT16)) {
        return 0;
    }
    size -= sizeof(BPS_UINT16);
    buf = BPS_GetBig16(&(buf[i]), &(rsp->interval));
    i += sizeof(BPS_UINT16);

    return i;
}

