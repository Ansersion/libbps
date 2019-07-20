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

BP_UINT16 BPSPackPingReq(BPSCmdPingReq * req, BP_UINT8 * buf, BP_WORD size)
{
    BP_UINT16 i = 0;
    if(BP_NULL == req || BP_NULL == buf) {
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

    if(size < sizeof(BP_UINT16)) {
        return 0;
    }
    size -= sizeof(BP_UINT16);
    buf = BP_SetBig16(&(buf[i]), req->interval);
    i += sizeof(BP_UINT16);

    return i;
}

BP_UINT16 BPSPackPingRsp(BPSCmdPingRsp * rsp, BP_UINT8 * buf, BP_WORD size)
{
    BP_UINT16 i = 0;
    if(BP_NULL == rsp || BP_NULL == buf) {
        return 0;
    }
    if(0 == size--) {
        return 0;
    }
    buf[i++] = CMD_PING_WORD_RSP;

    if(size < sizeof(BP_UINT16)) {
        return 0;
    }
    size -= sizeof(BP_UINT16);
    buf = BP_SetBig16(&(buf[i]), rsp->interval);
    i += sizeof(BP_UINT16);

    return i;
}

BP_UINT16 BPSParsePingReq(BPSCmdPingReq * req, BP_UINT8 * buf, BP_WORD size)
{
    BP_UINT16 i = 0;
    if(BP_NULL == req || BP_NULL == buf) {
        return 0;
    }
    if(0 == size--) {
        return 0;
    }
    if(CMD_PING_WORD_REQ != buf[i++]) {
        return 0;
    }

    if(0 == size--) {
        return 0;
    }
    req->type = buf[i++];

    if(size < sizeof(BP_UINT16)) {
        return 0;
    }
    size -= sizeof(BP_UINT16);
    buf = BP_GetBig16(&(buf[i]), &(req->interval));
    i += sizeof(BP_UINT16);

    return i;
}

BP_UINT16 BPSParsePingRsp(BPSCmdPingRsp * rsp, BP_UINT8 * buf, BP_WORD size)
{
    BP_UINT16 i = 0;
    if(BP_NULL == rsp || BP_NULL == buf) {
        return 0;
    }
    if(0 == size--) {
        return 0;
    }
    if(CMD_PING_WORD_RSP != buf[i++]) {
        return 0;
    }

    if(size < sizeof(BP_UINT16)) {
        return 0;
    }
    size -= sizeof(BP_UINT16);
    buf = BP_GetBig16(&(buf[i]), &(rsp->interval));
    i += sizeof(BP_UINT16);

    return i;
}

