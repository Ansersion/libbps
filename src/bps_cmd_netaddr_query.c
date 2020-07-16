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
/// @file 	bps_cmd_netaddr_query.c
/// @brief 	APIs for command 'net address query'
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bps_cmd_netaddr_query.h>
#include <bps_memcpy.h>

#ifdef BPS_MEM_DYN
    #include <bps_memmng.h>
#endif

#if (BPS_CMD_SET == BPS_CMD_SET_C)

BPS_UINT16 BPSPackNetaddrQueryReq(BPSCmdNetaddrQueryReq * req, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }
    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = CMD_NETADDR_QUERY_WORD_REQ;

    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = req->type;
    return i;
}

BPS_UINT16 BPSPackNetaddrQueryRsp(BPSCmdNetaddrQueryRsp * rsp, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }
    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = CMD_NETADDR_QUERY_WORD_RSP;

    BPS_ASSERT_SIZE(size, sizeof(BPS_UINT8) + rsp->len);
    BPS_Set1ByteField(buf+i, rsp->data, rsp->len);
    i += sizeof(BPS_UINT8) + rsp->len;

    return i;
}

BPS_UINT16 BPSParseNetaddrQueryReq(BPSCmdNetaddrQueryReq * req, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }

    BPS_ASSERT_SIZE_UINT8(size);
    req->type = buf[i++];

    return i;
}

BPS_UINT16 BPSParseNetaddrQueryRsp(BPSCmdNetaddrQueryRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size)
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
BPS_UINT16 BPSParseNetaddrQueryRspDyn(BPSCmdNetaddrQueryRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size)
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

void BPSFreeMemNetaddrQueryRsp(BPSCmdNetaddrQueryRsp * rsp)
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
