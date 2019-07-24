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
/// @file 	bps_cmd_post.c
/// @brief 	APIs for command 'post signal'
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bps_public.h>
#include <bps_sig_ret_code.h>
#include <bps_cmd_post.h>
#include <bps_memcpy.h>
#include <bps_memset.h>

#ifdef BP_MEM_DYN
    #include <bps_memmng.h>
#endif

BP_UINT16 BPSPackPostReq(BPSCmdPostReq * req, BP_UINT8 * buf, BP_WORD size)
{
    BP_UINT16 i = 0;
    BP_UINT8 field_num, j;
    BP_WORD len;
    BPSCmdPostField * field_tmp;
    if(BP_NULL == req || BP_NULL == buf) {
        return 0;
    }
    if(0 == size--) {
        return 0;
    }
    buf[i++] = CMD_POST_WORD_REQ;

    if(0 == size--) {
        return 0;
    }
    field_num = (BP_UINT8)(req->fieldNum & 0xFF);
    buf[i++] = field_num;

    for(j = 0; j < field_num; j++) {
        if(sizeof(BP_UINT16) > size) {
            return 0;
        }
        size -= sizeof(BP_UINT16);
        field_tmp = req->fieldArray + j;
        BPS_SetBig16(buf+i, field_tmp->signalId);
        i += sizeof(BP_UINT16);

        if(0 == size--) {
            return 0;
        }
        buf[i++] = field_tmp->signalType;

        len = BPS_GetSigValueLen(field_tmp->signalType, field_tmp->value);
        if(len > size) {
            return 0;
        }
        size -= len;
        BPS_SetSigValue(buf+i, field_tmp->signalType, field_tmp->value);
        i += len;
    }

    return i;
}

BP_UINT16 BPSPackPostRsp(BPSCmdPostRsp * rsp, BP_UINT8 * buf, BP_WORD size)
{
    BP_UINT16 i = 0;
    if(BP_NULL == rsp || BP_NULL == buf) {
        return 0;
    }
    if(0 == size--) {
        return 0;
    }
    buf[i++] = CMD_POST_WORD_RSP;


    if(0 == size--) {
        return 0;
    }
    buf[i++] = rsp->retCode;

    switch(rsp->retCode) {
        case BPS_RET_CODE_SIG_ID_INVALID:
        case BPS_RET_CODE_SIG_VAL_INVALID:
            if(sizeof(BP_UINT16) > size) {
                return 0;
            }
            size -= sizeof(BP_UINT16);
            BPS_SetBig16(buf, *((BP_UINT16 *)(rsp->extension)));
            i += sizeof(BP_UINT16);
            break;
    }

    return i;
}

BP_UINT16 BPSParsePostReq(BPSCmdPostReq * req, BP_UINT8 * buf, BP_WORD size)
{
    BP_UINT16 i = 0;
    BP_UINT8 field_num, j;
    BP_WORD len;
    BPSCmdPostField * field_tmp;
    if(BP_NULL == req || BP_NULL == buf) {
        return 0;
    }
    if(0 == size--) {
        return 0;
    }
    field_num = buf[i++];
    req->fieldNum = field_num;

    for(j = 0; j < field_num; j++) {
        if(sizeof(BP_UINT16) > size) {
            return 0;
        }
        size -= sizeof(BP_UINT16);
        field_tmp = req->fieldArray + j;
        BPS_GetBig16(buf+i, &(field_tmp->signalId));
        i += sizeof(BP_UINT16);

        if(0 == size--) {
            return 0;
        }
        field_tmp->signalType = buf[i++];

        if(BPS_SIG_TYPE_STR == field_tmp->signalType) {
            if(0 == size--) {
                return 0;
            }
            len = buf[i++];
        } else {
            len = BPS_GetSigValueLen2(field_tmp->signalType);
        }

        if(len > size) {
            return 0;
        }
        size -= len;
        BPS_GetSigValue(buf+i, field_tmp->signalType, &(field_tmp->value), len);
        i += len;
    }

    return i;
}

BP_UINT16 BPSParsePostRsp(BPSCmdPostRsp * rsp, BP_UINT8 * buf, BP_WORD size)
{
    BP_UINT16 i = 0;
    if(BP_NULL == rsp || BP_NULL == buf) {
        return 0;
    }

    if(0 == size--) {
        return 0;
    }
    rsp->retCode = buf[i++];

    switch(rsp->retCode) {
        case BPS_RET_CODE_SIG_ID_INVALID:
        case BPS_RET_CODE_SIG_VAL_INVALID:
            if(sizeof(BP_UINT16) > size) {
                return 0;
            }
            size -= sizeof(BP_UINT16);
            BPS_GetBig16(buf, (BP_UINT16 *)(rsp->extension));
            i += sizeof(BP_UINT16);
            break;
    }

    return i;
}

#ifdef BP_MEM_DYN
BP_UINT16 BPSParsePostReqDyn(BPSCmdPostReq * req, BP_UINT8 * buf, BP_WORD size)
{
    BP_UINT16 i = 0;
    BP_UINT8 field_num, j;
    BP_WORD len;
    BPSCmdPostField * field_tmp;
    if(BP_NULL == req || BP_NULL == buf) {
        return 0;
    }
    req->fieldArray = BP_NULL;
    if(0 == size--) {
        return 0;
    }
    field_num = buf[i++];
    req->fieldNum = field_num;

    req->fieldArray = (BPSCmdPostField *)malloc_bps(field_num * sizeof(BPSCmdPostField));
    memset_bps(req->fieldArray, 0, field_num * sizeof(BPSCmdPostField));

    for(j = 0; j < field_num; j++) {
        if(sizeof(BP_UINT16) > size) {
            BPSFreeMemPostReq(req);
            return 0;
        }
        size -= sizeof(BP_UINT16);
        field_tmp = req->fieldArray + j;
        BPS_GetBig16(buf+i, &(field_tmp->signalId));
        i += sizeof(BP_UINT16);

        if(0 == size--) {
            BPSFreeMemPostReq(req);
            return 0;
        }
        field_tmp->signalType = buf[i++];

        if(BPS_SIG_TYPE_STR == field_tmp->signalType) {
            if(0 == size--) {
                BPSFreeMemPostReq(req);
                return 0;
            }
            len = buf[i++];
            field_tmp->value.t_str = (BP_UINT8 *)malloc_bps(len + 1);
        } else {
            len = BPS_GetSigValueLen2(field_tmp->signalType);
        }

        if(len > size) {
            BPSFreeMemPostReq(req);
            return 0;
        }
        size -= len;
        BPS_GetSigValue(buf+i, field_tmp->signalType, &(field_tmp->value), len);
        i += len;
    }

    return i;
}

BP_UINT16 BPSParsePostRspDyn(BPSCmdPostRsp * rsp, BP_UINT8 * buf, BP_WORD size)
{
    BP_UINT16 i = 0;
    if(BP_NULL == rsp || BP_NULL == buf) {
        return 0;
    }
    rsp->extension = BP_NULL;
    if(0 == size--) {
        return 0;
    }
    rsp->retCode = buf[i++];

    switch(rsp->retCode) {
        case BPS_RET_CODE_SIG_ID_INVALID:
        case BPS_RET_CODE_SIG_VAL_INVALID:
            if(sizeof(BP_UINT16) > size) {
                return 0;
            }
            size -= sizeof(BP_UINT16);
            rsp->extension = malloc_bps(sizeof(BP_UINT16));
            BPS_GetBig16(buf, (BP_UINT16 *)(rsp->extension));
            i += sizeof(BP_UINT16);
            break;
    }

    return i;
}

void BPSFreeMemPostReq(BPSCmdPostReq * req)
{
    BP_WORD i;
    BPSCmdPostField * field_tmp;
    if(BP_NULL == req) {
        return;
    }
    if(BP_NULL == req->fieldArray) {
        return;
    }
    for(i = 0; i < req->fieldNum; i++) {
       field_tmp = req->fieldArray + i;
       if(BPS_SIG_TYPE_STR == field_tmp->signalType && BP_NULL != field_tmp->value.t_str) {
           free_bps(field_tmp->value.t_str);
       }
    }
    free_bps(req->fieldArray);
    req->fieldArray = BP_NULL;
}

void BPSFreeMemPostRsp(BPSCmdPostRsp * rsp)
{
    if(BP_NULL == rsp) {
        return;
    }
    if(BP_NULL == rsp->extension) {
        return;
    }
    free_bps(rsp->extension);
    rsp->extension = BP_NULL;
}

#endif

