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
/// @file 	bps_cmd_hd_info.c
/// @brief 	APIs for command 'query hardware info'
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////


#include <bps_cmd_hd_info.h>
#include <bps_memcpy.h>
#include <bps_memset.h>

#ifdef BPS_MEM_DYN
#include <bps_memmng.h>
#endif

#if (BPS_CMD_SET == BPS_CMD_SET_B || BPS_CMD_SET == BPS_CMD_SET_T || BPS_CMD_SET == BPS_CMD_SET_C)

BPS_UINT16 BPSPackHDInfoReq(BPSCmdHDInfoReq * req, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }
    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = CMD_HD_INFO_WORD_REQ;

    return i;
}

BPS_UINT16 BPSPackHDInfoRsp(BPSCmdHDInfoRsp * rsp, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    BPS_UINT8 field_num, j;
    BPS_WORD tmp;
    BPSCmdHDInfoField * field_tmp;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }
    BPS_ASSERT_SIZE_UINT8(size);
    buf[i++] = CMD_HD_INFO_WORD_RSP;

    BPS_ASSERT_SIZE_UINT8(size);
    field_num = (BPS_UINT8)(rsp->fieldNum & 0xFF);
    buf[i++] = field_num;

    for(j = 0; j < field_num; j++) {
        field_tmp = rsp->fieldArray + j;
        tmp = sizeof(BPS_UINT8) + sizeof(BPS_UINT8) + field_tmp->len; // the field length == 'sizeof(type) + sizeof(len) + sizeof(data)';
        BPS_ASSERT_SIZE(size, tmp);
        buf[i++] = field_tmp->type;
        if(BPS_NULL == BPS_Set1ByteField(buf+i, field_tmp->data, field_tmp->len)) {
            return 0;
        }
        i += sizeof(BPS_UINT8) + field_tmp->len;
    }

    return i;
}

BPS_UINT16 BPSParseHDInfoReq(BPSCmdHDInfoReq * req, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }

    return i;
}

BPS_UINT16 BPSParseHDInfoRsp(BPSCmdHDInfoRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    BPS_UINT8 field_num, j, k, tmp, info_type_array_len = 0;
    BPSCmdHDInfoField * field_tmp;
    BPS_WORD max_field_num;
    HdInfoType * info_type_array = BPS_NULL;
    BPS_BOOL to_parse;


    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }

    max_field_num = rsp->maxFieldNum;

    info_type_array = rsp->infoTypeArray;
    info_type_array_len = rsp->infoTypeArrayLen;

    BPS_ASSERT_SIZE_UINT8(size);
    field_num = buf[i++];
    rsp->fieldNum = field_num;

    field_tmp = rsp->fieldArray;

    for(j = 0; (j < field_num) && (0 != max_field_num); j++) {
        to_parse = BPS_TRUE;
        BPS_ASSERT_SIZE_UINT8(size);
        tmp = buf[i++];

        if(BPS_NULL != info_type_array) {
            /** only the info type in the array will be parsed, if not BPS_NULL */
            to_parse = BPS_FALSE;
            for(k = 0; k < info_type_array_len; k++) {
                if(tmp == info_type_array[k]) {
                    to_parse = BPS_TRUE;
                    break;
                }
            }
        }

        if(!to_parse) {
            /** skip the filed */
            BPS_ASSERT_SIZE_UINT8(size);
            tmp = buf[i++];

            BPS_ASSERT_SIZE(size, tmp);
            i += tmp;
            continue;
        }

        field_tmp->type = tmp;

        /** parse field length */
        BPS_ASSERT_SIZE_UINT8(size);
        tmp = buf[i++];
        field_tmp->len = tmp;

        if(field_tmp->maxLen < tmp) {
            return 0;
        }
        BPS_ASSERT_SIZE(size, tmp);

        /** memcpy the field data*/
        memcpy_bps(field_tmp->data, buf+i, field_tmp->len);
        i += field_tmp->len;

        /** set to next field and max field subtract one */
        field_tmp++;
        max_field_num--;
    }

    return i;
}

#ifdef BPS_MEM_DYN
BPS_UINT16 BPSParseHDInfoRspDyn(BPSCmdHDInfoRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    BPS_UINT8 field_num, j;
    BPSCmdHDInfoField * field_tmp;

    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }

    rsp->fieldArray = BPS_NULL;
    BPS_ASSERT_SIZE_UINT8(size);
    field_num = buf[i++];
    rsp->fieldNum = field_num;
    rsp->fieldArray = (BPSCmdHDInfoField *)malloc_bps(field_num * sizeof(BPSCmdHDInfoField));
    if(BPS_NULL == rsp->fieldArray) {
        return 0;
    }
    memset_bps(rsp->fieldArray, 0, field_num * sizeof(BPSCmdHDInfoField));

    for(j = 0; j < field_num; j++) {
        BPS_ASSERT_SIZE_UINT8_DYN(size, BPSFreeMemHDInfoRsp, rsp);
        field_tmp = rsp->fieldArray + j;
        field_tmp->type = buf[i++];

        BPS_ASSERT_SIZE_UINT8_DYN(size, BPSFreeMemHDInfoRsp, rsp);
        field_tmp->len = buf[i++];

        BPS_ASSERT_SIZE_DYN(size, field_tmp->len, BPSFreeMemHDInfoRsp, rsp);
        field_tmp->data = (BPS_UINT8 *)malloc_bps(field_tmp->len);
        if(BPS_NULL == field_tmp->data) {
            BPSFreeMemHDInfoRsp(rsp);
            return 0;
        }
        memcpy_bps(field_tmp->data, buf+i, field_tmp->len);
        i += field_tmp->len;
    }

    return i;
}

void BPSFreeMemHDInfoRsp(BPSCmdHDInfoRsp * rsp)
{
    BPS_WORD i;
    BPSCmdHDInfoField * field_tmp;
    if(BPS_NULL == rsp) {
        return;
    }
    if(BPS_NULL == rsp->fieldArray) {
        return;
    }
    for(i = 0; i < rsp->fieldNum; i++) {
        field_tmp = rsp->fieldArray + i;
        if(BPS_NULL != field_tmp->data) {
            free_bps(field_tmp->data);
        }
    }
    free_bps(rsp->fieldArray);
    rsp->fieldArray = BPS_NULL;
}
#endif

#endif

