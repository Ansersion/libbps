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
/// @file 	bps_cmd_post.c
/// @brief 	APIs for command 'post signal'
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bps_public.h>
#include <bps_ret_code.h>
#include <bps_cmd_post.h>
#include <bps_memcpy.h>
#include <bps_memset.h>

#ifdef BPS_MEM_DYN
    #include <bps_memmng.h>
#endif

#if (BPS_CMD_SET == BPS_CMD_SET_C)

BPS_UINT16 BPSPackPostReq(BPSCmdPostReq * req, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    BPS_UINT8 field_num, j;
    BPS_WORD len;
    BPSCmdPostField * field_tmp;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }
    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = CMD_POST_WORD_REQ;

    BPS_ASSERT_SIZE_UINT8(size);
    field_num = (BPS_UINT8)(req->fieldNum & 0xFF);
    buf[i++] = field_num;

    for(j = 0; j < field_num; j++) {
        BPS_ASSERT_SIZE_TYPE(size, BPS_UINT16);
        field_tmp = req->fieldArray + j;
        BPS_SetBig16(buf+i, field_tmp->signalId);
        i += sizeof(BPS_UINT16);

        BPS_ASSERT_SIZE_UINT8(size);
        buf[i++] = field_tmp->signalType;

        len = BPS_GetSigValueLen(field_tmp->signalType, field_tmp->value);
        BPS_ASSERT_SIZE(size, len);
        BPS_SetSigValue(buf+i, field_tmp->signalType, field_tmp->value);
        i += len;
    }

    return i;
}

BPS_UINT16 BPSPackPostRsp(BPSCmdPostRsp * rsp, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }
    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = CMD_POST_WORD_RSP;


    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = rsp->retCode;

    switch(rsp->retCode) {
        case BPS_RET_CODE_SIG_ID_INVALID:
        case BPS_RET_CODE_SIG_VAL_INVALID:
            if(BPS_NULL != rsp->extension) {
                BPS_ASSERT_SIZE_TYPE(size, BPS_UINT16);
                BPS_SetBig16(buf, *((BPS_UINT16 *)(rsp->extension)));
                i += sizeof(BPS_UINT16);
            }
            break;
    }

    return i;
}

BPS_UINT16 BPSParsePostReq(BPSCmdPostReq * req, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    BPS_UINT8 field_num, j;
    BPS_WORD len;
    BPSCmdPostField * field_tmp;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }

    BPS_ASSERT_SIZE_UINT8(size);
    field_num = buf[i++];
    req->fieldNum = field_num;

    if(field_num > req->maxFieldNum) {
        return 0;
    }

    for(j = 0; j < field_num; j++) {
        BPS_ASSERT_SIZE_TYPE(size, BPS_UINT16);
        field_tmp = req->fieldArray + j;
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

    return i;
}

BPS_UINT16 BPSParsePostRsp(BPSCmdPostRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }

    BPS_ASSERT_SIZE_UINT8(size);
    rsp->retCode = buf[i++];

    switch(rsp->retCode) {
        case BPS_RET_CODE_SIG_ID_INVALID:
        case BPS_RET_CODE_SIG_VAL_INVALID:
            if(BPS_NULL != rsp->extension) {
                BPS_ASSERT_SIZE_TYPE(size, BPS_UINT16);
                BPS_GetBig16(buf, (BPS_UINT16 *)(rsp->extension));
                i += sizeof(BPS_UINT16);
            }
            break;
    }

    return i;
}

#ifdef BPS_MEM_DYN
BPS_UINT16 BPSParsePostReqDyn(BPSCmdPostReq * req, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    BPS_UINT8 field_num, j;
    BPS_WORD len;
    BPSCmdPostField * field_tmp;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }
    req->fieldArray = BPS_NULL;
    BPS_ASSERT_SIZE_UINT8(size);
    field_num = buf[i++];
    req->fieldNum = field_num;

    req->fieldArray = (BPSCmdPostField *)malloc_bps(field_num * sizeof(BPSCmdPostField));
    if(BPS_NULL == req->fieldArray) {
        return 0;
    }
    memset_bps(req->fieldArray, 0, field_num * sizeof(BPSCmdPostField));

    for(j = 0; j < field_num; j++) {
        BPS_ASSERT_SIZE_TYPE_DYN(size, BPS_UINT16, BPSFreeMemPostReq, req);
        field_tmp = req->fieldArray + j;
        BPS_GetBig16(buf+i, &(field_tmp->signalId));
        i += sizeof(BPS_UINT16);

        BPS_ASSERT_SIZE_UINT8_DYN(size, BPSFreeMemPostReq, req);
        field_tmp->signalType = buf[i++];

        if(BPS_SIG_TYPE_STR == field_tmp->signalType) {
            BPS_ASSERT_SIZE_UINT8_DYN(size, BPSFreeMemPostReq, req);
            len = buf[i++];
            field_tmp->value.t_str = (BPS_UINT8 *)malloc_bps(len);
            if(len != 0 && BPS_NULL == field_tmp->value.t_str) {
                BPSFreeMemPostReq(req);
                return 0;
            }
        } else {
            len = BPS_GetSigValueLen2(field_tmp->signalType);
        }

        BPS_ASSERT_SIZE_DYN(size, len, BPSFreeMemPostReq, req);
        BPS_GetSigValue(buf+i, field_tmp->signalType, &(field_tmp->value), len);
        i += len;
    }

    return i;
}

BPS_UINT16 BPSParsePostRspDyn(BPSCmdPostRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }
    rsp->extension = BPS_NULL;
    BPS_ASSERT_SIZE_UINT8(size);
    rsp->retCode = buf[i++];

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

    return i;
}

void BPSFreeMemPostReq(BPSCmdPostReq * req)
{
    BPS_WORD i;
    BPSCmdPostField * field_tmp;
    if(BPS_NULL == req) {
        return;
    }
    if(BPS_NULL == req->fieldArray) {
        return;
    }
    for(i = 0; i < req->fieldNum; i++) {
       field_tmp = req->fieldArray + i;
       if(BPS_SIG_TYPE_STR == field_tmp->signalType && BPS_NULL != field_tmp->value.t_str) {
           free_bps(field_tmp->value.t_str);
       }
    }
    free_bps(req->fieldArray);
    req->fieldArray = BPS_NULL;
}

void BPSFreeMemPostRsp(BPSCmdPostRsp * rsp)
{
    if(BPS_NULL == rsp) {
        return;
    }
    if(BPS_NULL == rsp->extension) {
        return;
    }
    free_bps(rsp->extension);
    rsp->extension = BPS_NULL;
}

#endif

#endif
