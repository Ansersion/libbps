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
/// @file 	bps_cmd_get_sigtab.c
/// @brief 	APIs for command 'get signal table'
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////


#include <bps_public.h>
#include <bps_cmd_get_sigtab.h>
#include <bps_memcpy.h>
#include <bps_memset.h>

#ifdef BPS_MEM_DYN
    #include <bps_memmng.h>
#endif

#if (BPS_CMD_SET == BPS_CMD_SET_C)

BPS_UINT16 BPSPackGetSigtabReq(BPSCmdGetSigtabReq * req, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }
    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = CMD_GET_SIGTAB_WORD_REQ;

    return i;
}

BPS_UINT16 BPSPackGetSigtabRsp(BPSCmdGetSigtabRsp * rsp, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    BPS_WORD j;
    BPSCmdGetSigtabField * field_tmp;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }
    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = CMD_GET_SIGTAB_WORD_RSP;

    BPS_ASSERT_SIZE_TYPE(size, BPS_UINT16);
    BPS_SetBig16(buf+i, rsp->fieldNum);
    i += sizeof(BPS_UINT16);

    for(j = 0; j < rsp->fieldNum; j++) {
        field_tmp = rsp->fieldArray + j;

        BPS_ASSERT_SIZE_TYPE(size, BPS_UINT16);
        BPS_SetBig16(buf+i, field_tmp->signalId);
        i += sizeof(BPS_UINT16);

        BPS_ASSERT_SIZE_UINT8(size);
        buf[i++] = field_tmp->signalType;

        BPS_ASSERT_SIZE_UINT8(size);
        buf[i++] = field_tmp->accuracy;
    }

    return i;
}

BPS_UINT16 BPSParseGetSigtabReq(BPSCmdGetSigtabReq * req, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }

    return i;
}

BPS_UINT16 BPSParseGetSigtabRsp(BPSCmdGetSigtabRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0, j;
    BPS_UINT16 tmpU16;
    BPSCmdGetSigtabField * field_tmp;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }

    BPS_ASSERT_SIZE_TYPE(size, BPS_UINT16);
    BPS_GetBig16(buf+i, &tmpU16);
    rsp->fieldNum = tmpU16;
    i += sizeof(BPS_UINT16);

    if(tmpU16 > rsp->maxFieldNum || BPS_NULL == rsp->fieldArray) {
        return 0;
    }

    for(j = 0; j < rsp->fieldNum; j++) {
        field_tmp = rsp->fieldArray + j;

        BPS_ASSERT_SIZE_TYPE(size, BPS_UINT16);
        BPS_GetBig16(buf+i, &tmpU16);
        field_tmp->signalId = tmpU16;
        i += sizeof(BPS_UINT16);

        BPS_ASSERT_SIZE_UINT8(size);
        field_tmp->signalType = buf[i++];

        BPS_ASSERT_SIZE_UINT8(size);
        field_tmp->accuracy = buf[i++];
    }

    return i;
}

#ifdef BPS_MEM_DYN
BPS_UINT16 BPSParseGetSigtabRspDyn(BPSCmdGetSigtabRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0, j;
    BPS_UINT16 tmpU16;
    BPSCmdGetSigtabField * field_tmp;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }
    BPS_ASSERT_SIZE_TYPE(size, BPS_UINT16);
    BPS_GetBig16(buf+i, &tmpU16);
    rsp->fieldNum = tmpU16;
    i += sizeof(BPS_UINT16);

    if(0 == rsp->fieldNum) {
        return i;
    }

    rsp->fieldArray = (BPSCmdGetSigtabField *)malloc_bps(rsp->fieldNum * sizeof(BPSCmdGetSigtabField));
    if(BPS_NULL == rsp->fieldArray) {
        return 0;
    }

    for(j = 0; j < rsp->fieldNum; j++) {
        field_tmp = rsp->fieldArray + j;
        BPS_ASSERT_SIZE_TYPE_DYN(size, BPS_UINT16, BPSFreeMemGetSigtabRsp, rsp);
        BPS_GetBig16(buf+i, &(field_tmp->signalId));
        i += sizeof(BPS_UINT16);

        BPS_ASSERT_SIZE_UINT8_DYN(size, BPSFreeMemGetSigtabRsp, rsp);
        field_tmp->signalType = buf[i++];

        BPS_ASSERT_SIZE_UINT8_DYN(size, BPSFreeMemGetSigtabRsp, rsp);
        field_tmp->accuracy = buf[i++];
    }

    return i;
}

void BPSFreeMemGetSigtabRsp(BPSCmdGetSigtabRsp * rsp)
{
    if(BPS_NULL == rsp) {
        return;
    }
    if(BPS_NULL == rsp->fieldArray) {
        return;
    }
    free_bps(rsp->fieldArray);
    rsp->fieldArray = BPS_NULL;
}

#endif

#endif
