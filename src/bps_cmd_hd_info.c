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

BPS_UINT16 BPSPackHDInfoReq(BPSCmdHDInfoReq * req, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }
    if(0 == size--) {
        return 0;
    }
    buf[i++] = CMD_HD_INFO_WORD_REQ;

    return i;
}

BPS_UINT16 BPSPackHDInfoRsp(BPSCmdHDInfoRsp * rsp, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    BPS_WORD j;
    BPS_WORD tmp;
    BPSCmdHDInfoField * field_tmp;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }
    if(0 == size--) {
        return 0;
    }
    buf[i++] = CMD_HD_INFO_WORD_RSP;

    for(j = 0; j < rsp->fieldNum; j++) {
        field_tmp = &(rsp->fieldArray[j]);
        tmp = sizeof(BPS_UINT8) + sizeof(BPS_UINT8) + field_tmp->len;
        if(tmp > size) {
            return 0;
        }
        size -= tmp;
        buf[i++] = field_tmp->type;
        if(BPS_NULL == BPS_Set1ByteField(&(buf[i]), field_tmp->data, field_tmp->len)) {
            return 0;
        }
        i += sizeof(BPS_UINT8) + field_tmp->len;
    }

    if(0 == size--) {
        return 0;
    }
    buf[i++] = CMD_HD_INFO_FIELD_END;

    return i;
}

BPS_UINT16 BPSParseHDInfoReq(BPSCmdHDInfoReq * req, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }

    return i;
}

BPS_UINT16 BPSParseHDInfoRsp(BPSCmdHDInfoRsp * rsp, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    BPS_UINT8 type;
    BPSCmdHDInfoField * field_tmp;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }
    rsp->fieldNum = 0;
    while(1) {
        if(0 == size--) {
            return 0;
        }
        type = buf[i++];
        if(CMD_HD_INFO_FIELD_END == type) {
            return i;
        }
        field_tmp = &(rsp->fieldArray[rsp->fieldNum]);
        field_tmp->type = type;

        if(0 == size--) {
            return 0;
        }
        field_tmp->len = buf[i++];

        if(field_tmp->len > size) {
            return 0;
        }
        size -= field_tmp->len;
        memcpy_bps(field_tmp->data, &(buf[i]), field_tmp->len);
        i += field_tmp->len;

        rsp->fieldNum++;
    }

    return i;
}

#ifdef BPS_MEM_DYN
BPS_UINT16 BPSParseHDInfoRspDyn(BPSCmdHDInfoRsp * rsp, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0;
    BPS_UINT8 type;
    BPSCmdHDInfoField * field_tmp;
    const BPS_WORD field_num_step = 4;
    BPS_WORD field_num_left;
    BPS_WORD field_mem_step_num = 1;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }
    rsp->fieldArray = (BPSCmdHDInfoField *)malloc(field_mem_step_num * sizeof(BPSCmdHDInfoField) * field_num_step);
    memset_bps(rsp->fieldArray, 0, field_mem_step_num * sizeof(BPSCmdHDInfoField) * field_num_step);
    field_num_left = field_num_step;
    rsp->fieldNum = 0;
    while(1) {
        if(0 == size--) {
            BPSFreeMemHDInfoRsp(rsp);
            return 0;
        }
        type = buf[i++];
        if(CMD_HD_INFO_FIELD_END == type) {
            return i;
        }
        if(0 == field_num_left--) {
            field_mem_step_num++;
            field_tmp = (BPSCmdHDInfoField *)malloc(field_mem_step_num * sizeof(BPSCmdHDInfoField) * field_num_step);
            memset_bps(field_tmp, 0, field_mem_step_num * sizeof(BPSCmdHDInfoField) * field_num_step);
            memcpy_bps(field_tmp, rsp->fieldArray, (field_mem_step_num - 1) * sizeof(BPSCmdHDInfoField) * field_num_step);
            free(rsp->fieldArray);
            rsp->fieldArray = field_tmp;
            field_num_left = field_num_step - 1;
        }

        field_tmp = &(rsp->fieldArray[rsp->fieldNum]);
        field_tmp->type = type;

        if(0 == size--) {
            BPSFreeMemHDInfoRsp(rsp);
            return 0;
        }
        field_tmp->len = buf[i++];

        if(field_tmp->len > size) {
            BPSFreeMemHDInfoRsp(rsp);
            return 0;
        }
        size -= field_tmp->len;
        field_tmp->data = (BPS_UINT8 *)malloc(field_tmp->len);
        memcpy_bps(field_tmp->data, &(buf[i]), field_tmp->len);
        i += field_tmp->len;

        rsp->fieldNum++;
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
       free(field_tmp->data);
    }
    free(rsp->fieldArray);
    rsp->fieldArray = BPS_NULL;
}
#endif

