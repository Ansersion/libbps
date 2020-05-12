///////////////////////////////////////////////////////////////////////////////
/// Copyright 2020 Ansersion
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
/// @file 	bps_cmd_baudrate_set.c
/// @brief 	APIs for command 'set/query serial baudrate'
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////


#include <bps_cmd_baudrate_set.h>

#if (BPS_CMD_SET == BPS_CMD_SET_B || BPS_CMD_SET == BPS_CMD_SET_T || BPS_CMD_SET == BPS_CMD_SET_C)

BPS_UINT16 BPSPackBaudrateSetReq(BPSCmdBaudrateSetReq * req, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }
    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = CMD_BAUDRATE_SET_WORD_REQ;

    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = req->type;

    if(SET_RT_BAUDRATE_SET == req->type) {
        BPS_ASSERT_SIZE_TYPE(size, BPS_UINT32);
        BPS_SetBig32(&(buf[i]), req->baudrate);
        i += sizeof(BPS_UINT32);
    }

    return i;
}

BPS_UINT16 BPSPackBaudrateSetRsp(BPSCmdBaudrateSetRsp * rsp, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }
    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = CMD_BAUDRATE_SET_WORD_RSP;

    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = rsp->retCode;

    BPS_ASSERT_SIZE_TYPE(size, BPS_UINT32);
    BPS_SetBig32(&(buf[i]), rsp->baudrate);
    i += sizeof(BPS_UINT32);

    return i;
}

BPS_UINT16 BPSParseBaudrateSetReq(BPSCmdBaudrateSetReq * req, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }

    BPS_ASSERT_SIZE_UINT8(size);
    req->type = buf[i++];

    if(SET_RT_BAUDRATE_SET == req->type) {
        BPS_ASSERT_SIZE_TYPE(size, BPS_UINT32);
        buf = BPS_GetBig32(&(buf[i]), &(req->baudrate));
        i += sizeof(BPS_UINT32);
    }

    return i;
}

BPS_UINT16 BPSParseBaudrateSetRsp(BPSCmdBaudrateSetRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }

    BPS_ASSERT_SIZE_UINT8(size);
    rsp->retCode = buf[i++];

    BPS_ASSERT_SIZE_TYPE(size, BPS_UINT32);
    buf = BPS_GetBig32(&(buf[i]), &(rsp->baudrate));
    i += sizeof(BPS_UINT32);

    return i;
}

#endif

