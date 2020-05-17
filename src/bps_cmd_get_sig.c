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
/// @file 	bps_cmd_get_sig.c
/// @brief 	APIs for command 'get signal values'
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bps_public.h>
#include <bps_ret_code.h>
#include <bps_cmd_get_sig.h>
#include <bps_memcpy.h>
#include <bps_memset.h>

#ifdef BPS_MEM_DYN
    #include <bps_memmng.h>
#endif

#if (BPS_CMD_SET == BPS_CMD_SET_C)

BPS_UINT16 BPSPackGetSigReq(BPSCmdGetSigReq * req, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    BPS_UINT8 sig_num, j;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }
    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = CMD_GET_SIG_WORD_REQ;

    BPS_ASSERT_SIZE_UINT8(size);
    sig_num = (BPS_UINT8)(req->sigNum & 0xFF);
    buf[i++] = sig_num;

    for(j = 0; j < sig_num; j++) {
        BPS_ASSERT_SIZE_TYPE(size, BPS_UINT16);
        BPS_SetBig16(buf+i, req->sigArray[j]);
        i += sizeof(BPS_UINT16);
    }

    return i;
}

BPS_UINT16 BPSPackGetSigRsp(BPSCmdGetSigRsp * rsp, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    BPS_UINT8 field_num, j;
    BPS_WORD len;
    BPSCmdGetSigField * field_tmp;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }
    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = CMD_GET_SIG_WORD_REQ;

    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = rsp->retCode;

    if(BPS_RET_CODE_OK == rsp->retCode) {
        BPS_ASSERT_SIZE_UINT8(size);
        field_num = (BPS_UINT8)(rsp->fieldNum & 0xFF);
        buf[i++] = field_num;

        for(j = 0; j < field_num; j++) {
            BPS_ASSERT_SIZE_TYPE(size, BPS_UINT16);
            field_tmp = rsp->fieldArray + j;
            BPS_SetBig16(buf+i, field_tmp->signalId);
            i += sizeof(BPS_UINT16);

            BPS_ASSERT_SIZE_UINT8(size);
            buf[i++] = field_tmp->signalType;

            len = BPS_GetSigValueLen(field_tmp->signalType, field_tmp->value);
            BPS_ASSERT_SIZE(size, len);
            BPS_SetSigValue(buf+i, field_tmp->signalType, field_tmp->value);
            i += len;
        }
    } else {
        switch(rsp->retCode) {
            case BPS_RET_CODE_SIG_ID_INVALID:
            case BPS_RET_CODE_SIG_VAL_INVALID:
                BPS_ASSERT_SIZE_TYPE(size, BPS_UINT16);
                BPS_SetBig16(buf, *(BPS_UINT16 *)(rsp->extension));
                i += sizeof(BPS_UINT16);
                break;
        }
    }

    return i;
}

BPS_UINT16 BPSParseGetSigReq(BPSCmdGetSigReq * req, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    BPS_UINT8 j;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }

    BPS_ASSERT_SIZE_UINT8(size);
    req->sigNum = buf[i++];

    if(req->sigNum > req->maxFieldNum) {
        return 0;
    }

    for(j = 0; j < req->sigNum; j++) {
        BPS_ASSERT_SIZE_TYPE(size, BPS_UINT16);
        BPS_GetBig16(buf+i, req->sigArray + j);
        i += sizeof(BPS_UINT16);
    }

    return i;
}

BPS_UINT16 BPSParseGetSigRsp(BPSCmdGetSigRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    BPS_UINT8 field_num, j;
    BPS_WORD len;
    BPSCmdGetSigField * field_tmp;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }

    BPS_ASSERT_SIZE_UINT8(size);
    rsp->retCode = buf[i++];

    if(BPS_RET_CODE_OK == rsp->retCode) {
        BPS_ASSERT_SIZE_UINT8(size);
        field_num = buf[i++];
        if(field_num > rsp->maxFieldNum) {
            return 0;
        }
        rsp->fieldNum = field_num;

        for(j = 0; j < field_num; j++) {
            BPS_ASSERT_SIZE_TYPE(size, BPS_UINT16);
            field_tmp = rsp->fieldArray + j;
            BPS_GetBig16(buf+i, &(field_tmp->signalId));
            i += sizeof(BPS_UINT16);

            BPS_ASSERT_SIZE_UINT8(size);
            field_tmp->signalType = buf[i++];

            if(BPS_SIG_TYPE_STR == field_tmp->signalType) {
                BPS_ASSERT_SIZE_UINT8(size);
                len = buf[i++];
            } else {
                len = BPS_GetSigValueLen2(field_tmp->signalType);
            }
            BPS_ASSERT_SIZE(size, len);
            BPS_GetSigValue(buf+i, field_tmp->signalType, &(field_tmp->value), len);
            i += len;
        }
    } else {
        switch(rsp->retCode) {
            case BPS_RET_CODE_SIG_ID_INVALID:
            case BPS_RET_CODE_SIG_VAL_INVALID:
                BPS_ASSERT_SIZE_TYPE(size, BPS_UINT16);
                if(BPS_NULL == rsp->extension) {
                    return 0;
                }
                BPS_GetBig16(buf, (BPS_UINT16 *)(rsp->extension));
                i += sizeof(BPS_UINT16);
                break;
        }
    }

    return i;
}

#ifdef BPS_MEM_DYN
BPS_UINT16 BPSParseGetSigReqDyn(BPSCmdGetSigReq * req, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    BPS_UINT8 j;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }
    req->sigArray = BPS_NULL;

    BPS_ASSERT_SIZE_TYPE(size, BPS_UINT16);
    req->sigNum = buf[i++];
    req->sigArray = (BPS_UINT16 *)malloc_bps(req->sigNum * sizeof(BPS_UINT16));
    if(BPS_NULL == req->sigArray) {
        return 0;
    }
    memset_bps(req->sigArray, 0, req->sigNum * sizeof(BPS_UINT16));

    for(j = 0; j < req->sigNum; j++) {
        BPS_ASSERT_SIZE_TYPE_DYN(size, BPS_UINT16, BPSFreeMemGetSigReq, req);
        BPS_GetBig16(buf+i, req->sigArray + j);
        i += sizeof(BPS_UINT16);
    }

    return i;
}

BPS_UINT16 BPSParseGetSigRspDyn(BPSCmdGetSigRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    BPS_UINT8 field_num, j;
    BPS_WORD len;
    BPSCmdGetSigField * field_tmp;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }
    rsp->fieldArray = BPS_NULL;
    rsp->extension = BPS_NULL;

    BPS_ASSERT_SIZE_UINT8(size);
    rsp->retCode = buf[i++];

    if(BPS_RET_CODE_OK == rsp->retCode) {
        BPS_ASSERT_SIZE_UINT8(size);
        field_num = buf[i++];
        rsp->fieldNum = field_num;
        rsp->fieldArray = (BPSCmdGetSigField *)malloc_bps(field_num * sizeof(BPSCmdGetSigField));
        if(BPS_NULL == rsp->fieldArray) {
            return 0;
        }
        memset_bps(rsp->fieldArray, 0, field_num * sizeof(BPSCmdGetSigField));

        for(j = 0; j < field_num; j++) {
            if(sizeof(BPS_UINT16) > size) {
                BPSFreeMemGetSigRsp(rsp);
                return 0;
            }
            size -= sizeof(BPS_UINT16);
            field_tmp = rsp->fieldArray + j;
            BPS_GetBig16(buf+i, &(field_tmp->signalId));
            i += sizeof(BPS_UINT16);

            BPS_ASSERT_SIZE_UINT8_DYN(size, BPSFreeMemGetSigRsp, rsp);
            field_tmp->signalType = buf[i++];

            if(BPS_SIG_TYPE_STR == field_tmp->signalType) {
                BPS_ASSERT_SIZE_UINT8_DYN(size, BPSFreeMemGetSigRsp, rsp);
                len = buf[i++];
                field_tmp->value.t_str = (BPS_UINT8 *)malloc_bps(len+1);
            } else {
                len = BPS_GetSigValueLen2(field_tmp->signalType);
            }
            BPS_ASSERT_SIZE_DYN(size, len, BPSFreeMemGetSigRsp, rsp);
            BPS_GetSigValue(buf+i, field_tmp->signalType, &(field_tmp->value), len);
            i += len;
        }
    } else {
        switch(rsp->retCode) {
            case BPS_RET_CODE_SIG_ID_INVALID:
            case BPS_RET_CODE_SIG_VAL_INVALID:
                BPS_ASSERT_SIZE_TYPE(size, BPS_UINT16);
                rsp->extension = (void *)malloc_bps(sizeof(BPS_UINT16));
                if(BPS_NULL == rsp->extension) {
                    return 0;
                }
                BPS_GetBig16(buf, (BPS_UINT16 *)(rsp->extension));
                i += sizeof(BPS_UINT16);
                break;
        }
    }

    return i;
}

void BPSFreeMemGetSigReq(BPSCmdGetSigReq * req)
{
    if(BPS_NULL == req) {
        return;
    }
    if(BPS_NULL == req->sigArray) {
        return;
    }
    free_bps(req->sigArray);
    req->sigArray = BPS_NULL;
}

void BPSFreeMemGetSigRsp(BPSCmdGetSigRsp * rsp)
{
    BPS_WORD i;
    BPSCmdGetSigField * field_tmp;
    if(BPS_NULL == rsp) {
        return;
    }
    if(BPS_NULL != rsp->fieldArray) {
        for(i = 0; i < rsp->fieldNum; i++) {
            field_tmp = rsp->fieldArray + i;
            if(BPS_SIG_TYPE_STR == field_tmp->signalType && BPS_NULL != field_tmp->value.t_str) {
                free_bps(field_tmp->value.t_str);
            }
        }
        free_bps(rsp->fieldArray);
        rsp->fieldArray = BPS_NULL;
    }

    if(BPS_NULL != rsp->extension) {
        free_bps(rsp->extension);
        rsp->extension = BPS_NULL;
    }
}

#endif

#endif
