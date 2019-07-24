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

#ifdef BP_MEM_DYN
    #include <bps_memmng.h>
#endif

BP_UINT16 BPSPackGetSigtabReq(BPSCmdGetSigtabReq * req, BP_UINT8 * buf, BP_WORD size)
{
    BP_UINT16 i = 0;
    if(BP_NULL == req || BP_NULL == buf) {
        return 0;
    }
    if(0 == size--) {
        return 0;
    }
    buf[i++] = CMD_GET_SIGTAB_WORD_REQ;

    return i;
}

BP_UINT16 BPSPackGetSigtabRsp(BPSCmdGetSigtabRsp * rsp, BP_UINT8 * buf, BP_WORD size)
{
    BP_UINT16 i = 0;
    BP_WORD j;
    BP_WORD tmp;
    BPSCmdGetSigtabField * field_tmp;
    if(BP_NULL == rsp || BP_NULL == buf) {
        return 0;
    }
    if(0 == size--) {
        return 0;
    }
    buf[i++] = CMD_GET_SIGTAB_WORD_RSP;

    if(size < sizeof(BP_UINT16)) {
        return 0;
    }
    size -= sizeof(BP_UINT16);
    BPS_SetBig16(buf+i, (BP_UINT16)(rsp->fieldNum & 0xFFFF));
    i += sizeof(BP_UINT16);

    for(j = 0; j < rsp->fieldNum; j++) {
        field_tmp = rsp->fieldArray + j;
        tmp = sizeof(BP_UINT16) + sizeof(BP_UINT16) + sizeof(BP_UINT8) + sizeof(BP_UINT8);
        if(tmp > size) {
            return 0;
        }
        size -= tmp;
        BPS_SetBig16(buf+i, field_tmp->signalId);
        i += sizeof(BP_UINT16);

        if(0 == size--) {
            return 0;
        }
        buf[i++] = field_tmp->signalType;

        if(0 == size--) {
            return 0;
        }
        buf[i++] = field_tmp->accuracy;
    }

    return i;
}

BP_UINT16 BPSParseGetSigtabReq(BPSCmdGetSigtabReq * req, BP_UINT8 * buf, BP_WORD size)
{
    BP_UINT16 i = 0;
    if(BP_NULL == req || BP_NULL == buf) {
        return 0;
    }

    return i;
}

BP_UINT16 BPSParseGetSigtabRsp(BPSCmdGetSigtabRsp * rsp, BP_UINT8 * buf, BP_WORD size)
{
    BP_UINT16 i = 0, j;
    BP_UINT16 tmpU16;
    BPSCmdGetSigtabField * field_tmp;
    if(BP_NULL == rsp || BP_NULL == buf) {
        return 0;
    }
    if(sizeof(BP_UINT16) > size) {
        return 0;
    }
    size -= sizeof(BP_UINT16);
    BPS_GetBig16(buf+i, &tmpU16);
    rsp->fieldNum = tmpU16;
    i += sizeof(BP_UINT16);

    for(j = 0; j < tmpU16; j++) {
        field_tmp = rsp->fieldArray + j;

        if(sizeof(BP_UINT16) > size) {
            return 0;
        }
        size -= sizeof(BP_UINT16);
        BPS_GetBig16(buf+i, &tmpU16);
        field_tmp->signalId = tmpU16;
        i += sizeof(BP_UINT16);

        if(0 == size--) {
            return 0;
        }
        field_tmp->signalType = buf[i++];

        if(0 == size--) {
            return 0;
        }
        field_tmp->accuracy = buf[i++];
    }

    return i;
}

#ifdef BP_MEM_DYN
BP_UINT16 BPSParseGetSigtabRspDyn(BPSCmdGetSigtabRsp * rsp, BP_UINT8 * buf, BP_WORD size)
{
    BP_UINT16 i = 0, j;
    BP_UINT16 tmpU16;
    BPSCmdGetSigtabField * field_tmp;
    if(BP_NULL == rsp || BP_NULL == buf) {
        return 0;
    }
    rsp->fieldArray = BP_NULL;
    if(sizeof(BP_UINT16) > size) {
        return 0;
    }
    size -= sizeof(BP_UINT16);
    BPS_GetBig16(buf+i, &tmpU16);
    rsp->fieldNum = tmpU16;
    i += sizeof(BP_UINT16);

    if(0 == rsp->fieldNum) {
        return i;
    }

    rsp->fieldArray = (BPSCmdGetSigtabField *)malloc_bps(rsp->fieldNum * sizeof(BPSCmdGetSigtabField));
    memset_bps(rsp->fieldArray, 0, rsp->fieldNum * sizeof(BPSCmdGetSigtabField));
    for(j = 0; j < rsp->fieldNum; j++) {
        field_tmp = rsp->fieldArray + j;
        if(sizeof(BP_UINT16) > size) {
            BPSFreeMemGetSigtabRsp(rsp);
            return 0;
        }
        size -= sizeof(BP_UINT16);
        BPS_GetBig16(buf+i, &(field_tmp->signalId));
        i += sizeof(BP_UINT16);

        if(0 == size--) {
            BPSFreeMemGetSigtabRsp(rsp);
            return 0;
        }
        field_tmp->signalType = buf[i++];

        if(0 == size--) {
            BPSFreeMemGetSigtabRsp(rsp);
            return 0;
        }
        field_tmp->accuracy = buf[i++];
    }

    return i;
}

void BPSFreeMemGetSigtabRsp(BPSCmdGetSigtabRsp * rsp)
{
    if(BP_NULL == rsp) {
        return;
    }
    if(BP_NULL == rsp->fieldArray) {
        return;
    }
    free_bps(rsp->fieldArray);
    rsp->fieldArray = BP_NULL;
}

#endif

