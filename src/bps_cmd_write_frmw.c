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
/// @file 	bps_cmd_write_frmw.c
/// @brief 	APIs for command 'write update firmware'
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////


#include <bps_cmd_write_frmw.h>
#include <bps_memcpy.h>
#include <bps_memset.h>

#ifdef BPS_MEM_DYN
#include <bps_memmng.h>
#endif

#if (BPS_CMD_SET == BPS_CMD_SET_B || BPS_CMD_SET == BPS_CMD_SET_T || BPS_CMD_SET == BPS_CMD_SET_C)

BPS_UINT16 BPSPackWriteFrmwReq(BPSCmdWriteFrmwReq * req, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }
    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = CMD_WRITE_FRMW_WORD_REQ;

    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = req->mode;

    BPS_ASSERT_SIZE(size, sizeof(BPS_UINT8) + req->len);
    BPS_Set1ByteField(buf+i, req->data, req->len);
    i += sizeof(BPS_UINT8) + req->len;

    BPS_ASSERT_SIZE_TYPE(size, BPS_UINT32);
    BPS_SetBig32(&(buf[i]), req->offset);
    i += sizeof(BPS_UINT32);

    return i;
}

BPS_UINT16 BPSPackWriteFrmwRsp(BPSCmdWriteFrmwRsp * rsp, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }
    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = CMD_WRITE_FRMW_WORD_RSP;

    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = rsp->retCode;

    return i;
}

BPS_UINT16 BPSParseWriteFrmwReq(BPSCmdWriteFrmwReq * req, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    BPS_UINT8 tmp;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }

    BPS_ASSERT_SIZE_UINT8(size);
    req->mode = buf[i++];

    BPS_ASSERT_SIZE_UINT8(size);
    tmp = buf[i++];
    req->len = tmp;

    if(tmp > req->maxLen) {
        return 0;
    }
    BPS_ASSERT_SIZE(size, tmp);
    memcpy_bps(req->data, buf+i, tmp);
    i += tmp;

    BPS_ASSERT_SIZE_TYPE(size, BPS_UINT32);
    BPS_GetBig32(&(buf[i]), &(req->offset));
    i += sizeof(BPS_UINT32);

    return i;
}

BPS_UINT16 BPSParseWriteFrmwRsp(BPSCmdWriteFrmwRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;

    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }

    BPS_ASSERT_SIZE_UINT8(size);
    rsp->retCode = buf[i++];

    return i;
}

#ifdef BPS_MEM_DYN
BPS_UINT16 BPSParseWriteFrmwReqDyn(BPSCmdWriteFrmwReq * req, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    BPS_UINT8 * p_data;
    BPS_UINT8 len;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }

    BPS_ASSERT_SIZE_UINT8(size);
    req->mode = buf[i++];

    BPS_ASSERT_SIZE_UINT8(size);
    len = buf[i++];
    req->len = len;

    p_data = (BPS_UINT8 *)malloc_bps(len);
    if(BPS_NULL == p_data) {
        return 0;
    }
    BPS_ASSERT_SIZE_DYN(size, len, BPSFreeMemWriteFrmwReq, req);
    memcpy_bps(p_data, buf+i, len);
    i += len;
    req->data = p_data;

    BPS_ASSERT_SIZE_TYPE_DYN(size, BPS_UINT32, BPSFreeMemWriteFrmwReq, req);
    BPS_GetBig32(&(buf[i]), &(req->offset));
    i += sizeof(BPS_UINT32);

    return i;
}

void BPSFreeMemWriteFrmwReq(BPSCmdWriteFrmwReq * req)
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
#endif

#endif

