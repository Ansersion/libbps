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
/// @file 	bps_cmd_trans_bytes.c
/// @brief 	APIs for command 'transmit bytes'
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////


#include <bps_cmd_trans_bytes.h>
#include <bps_ret_code.h>
#include <bps_memcpy.h>
#include <bps_memset.h>

#ifdef BPS_MEM_DYN
    #include <bps_memmng.h>
#endif

#if (BPS_CMD_SET == BPS_CMD_SET_T || BPS_CMD_SET == BPS_CMD_SET_C)

BPS_UINT16 BPSPackTransBytesReq(BPSCmdTransBytesReq * req, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }

    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = CMD_TRANS_BYTES_WORD_REQ;

    BPS_ASSERT_SIZE(size, sizeof(BPS_UINT8) + req->len);
    BPS_Set1ByteField(buf+i, req->data, req->len);
    i += sizeof(BPS_UINT8) + req->len;

    return i;
}

BPS_UINT16 BPSPackTransBytesRsp(BPSCmdTransBytesRsp * rsp, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }

    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = CMD_TRANS_BYTES_WORD_RSP;

    BPS_ASSERT_SIZE(size, sizeof(BPS_UINT8) + rsp->len);
    BPS_Set1ByteField(buf+i, rsp->data, rsp->len);
    i += sizeof(BPS_UINT8) + rsp->len;

    return i;
}

BPS_UINT16 BPSParseTransBytesReq(BPSCmdTransBytesReq * req, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    BPS_UINT8 len;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }
    BPS_ASSERT_SIZE_UINT8(size);
    len = buf[i++];
    req->len = len;

    if(len > req->maxLen || BPS_NULL == req->data) {
        return 0;
    }
    BPS_ASSERT_SIZE(size, len);
    memcpy_bps(req->data, buf+i, len);
    i += len;

    return i;
}

BPS_UINT16 BPSParseTransBytesRsp(BPSCmdTransBytesRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    BPS_UINT8 len;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }
    BPS_ASSERT_SIZE_UINT8(size);
    len = buf[i++];
    rsp->len = len;

    if(len > rsp->maxLen || BPS_NULL == rsp->data) {
        return 0;
    }
    BPS_ASSERT_SIZE(size, len);
    memcpy_bps(rsp->data, buf+i, len);
    i += len;

    return i;
}

#ifdef BPS_MEM_DYN
BPS_UINT16 BPSParseTransBytesReqDyn(BPSCmdTransBytesReq * req, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    BPS_UINT8 len;

    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }

    BPS_ASSERT_SIZE_UINT8(size);
    len = buf[i++];
    req->len = len;

    BPS_ASSERT_SIZE(size, len);
    req->data = (BPS_UINT8 *)malloc_bps(len);
    if(BPS_NULL == req->data) {
        return 0;
    }
    memcpy_bps(req->data, buf+i, len);
    i += len;

    return i;
}

void BPSFreeMemTransBytesReq(BPSCmdTransBytesReq * req)
{
    if(BPS_NULL == req) {
        return;
    }
    if(BPS_NULL == req->data) {
        return;
    }
    free_bps(req->data);
    req->data = BPS_NULL;
}

BPS_UINT16 BPSParseTransBytesRspDyn(BPSCmdTransBytesRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    BPS_UINT8 len;

    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }

    BPS_ASSERT_SIZE_UINT8(size);
    len = buf[i++];
    rsp->len = len;

    BPS_ASSERT_SIZE(size, len);
    rsp->data = (BPS_UINT8 *)malloc_bps(len);
    if(BPS_NULL == rsp->data) {
        return 0;
    }
    memcpy_bps(rsp->data, buf+i, len);
    i += len;

    return i;
}

void BPSFreeMemTransBytesRsp(BPSCmdTransBytesRsp * rsp)
{
    if(BPS_NULL == rsp) {
        return;
    }
    if(BPS_NULL == rsp->data) {
        return;
    }
    free_bps(rsp->data);
    rsp->data = BPS_NULL;
}
#endif

#endif
