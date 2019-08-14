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
/// @brief 	APIs for command 'configure system parameters'
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bps_cmd_system_para.h>
#include <bps_ret_code.h>
#include <bps_memcpy.h>
#include <bps_memset.h>

#ifdef BPS_MEM_DYN
    #include <bps_memmng.h>
#endif

BPS_UINT16 BPSPackSystemParaReq(BPSCmdSystemParaReq * req, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0, j;
    BPS_UINT8 len;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }
    if(0 == size--) {
        return 0;
    }
    buf[i++] = CMD_SYSTEM_PARA_WORD_REQ;

    if(0 == size--) {
        return 0;
    }
    buf[i++] = req->configType;

    if(0 == size--) {
        return 0;
    }
    buf[i++] = req->paraType;

    if(RESERVED_SYS_PARA_TYPE != req->paraType && req->paraType < NUM_SYS_PARA_TYPE) {
        if(0 == size--) {
            return 0;
        }
        len = req->len;
        buf[i++] = len;

        if(len > size) {
            return 0;
        }
        size -= len;

        for(j = 0; j < len; j++) {
            buf[i++] = req->data[j];
        }
    }

    return i;
}

BPS_UINT16 BPSPackSystemParaRsp(BPSCmdSystemParaRsp * rsp, BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0, j;
    BPS_UINT8 len;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }
    if(0 == size--) {
        return 0;
    }
    buf[i++] = CMD_SYSTEM_PARA_WORD_RSP;

    if(0 == size--) {
        return 0;
    }
    buf[i++] = rsp->configType;

    if(0 == size--) {
        return 0;
    }
    buf[i++] = rsp->paraType;

    if(0 == size--) {
        return 0;
    }
    buf[i++] = rsp->retCode;

    if(READ_SYS_PARA == rsp->configType && BPS_RET_CODE_OK == rsp->retCode) {
        if(0 == size--) {
            return 0;
        }
        len = rsp->len;
        buf[i++] = len;

        if(len > size) {
            return 0;
        }
        size -= len;

        for(j = 0; j < len; j++) {
            buf[i++] = rsp->data[j];
        }
    }

    return i;
}

BPS_UINT16 BPSParseSystemParaReq(BPSCmdSystemParaReq * req, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0, j;
    BPS_UINT8 len;
    if(BPS_NULL == req || BPS_NULL == buf) {
        return 0;
    }
    if(0 == size--) {
        return 0;
    }
    req->configType = buf[i++];

    if(0 == size--) {
        return 0;
    }
    req->paraType = buf[i++];

    if(WRITE_SYS_PARA == req->paraType) {
        if(0 == size--) {
            return 0;
        }
        len = buf[i++];
        req->len = len;

        if(len > size || len > BPS_MAX_STRING_LEN) {
            return 0;
        }
        size -= len;
        for(j = 0; j < len; j++) {
            req->data[j] = buf[i++];
        }
    }

    return i;
}

BPS_UINT16 BPSParseSystemParaRsp(BPSCmdSystemParaRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size)
{
    BPS_UINT16 i = 0, j;
    BPS_UINT8 len;
    if(BPS_NULL == rsp || BPS_NULL == buf) {
        return 0;
    }
    if(0 == size--) {
        return 0;
    }
    rsp->configType = buf[i++];

    if(0 == size--) {
        return 0;
    }
    rsp->paraType = buf[i++];

    if(0 == size--) {
        return 0;
    }
    rsp->retCode = buf[i++];

    if(BPS_RET_CODE_OK == rsp->retCode && READ_SYS_PARA == rsp->paraType) {
        if(0 == size--) {
            return 0;
        }
        len = buf[i++];
        rsp->len = len;

        if(len > size || len > BPS_MAX_STRING_LEN) {
            return 0;
        }
        size -= len;
        for(j = 0; j < len; j++) {
            rsp->data[j] = buf[i++];
        }
    }

    return i;
}
// TODO
// #ifdef BPS_MEM_DYN
// BPS_UINT16 BPSParseSystemParaRspDyn(BPSCmdSystemParaRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size)
// {
//     BPS_UINT16 i = 0;
//     BPS_UINT8 field_num, j;
//     BPSCmdSystemParaField * field_tmp;
// 
//     if(BPS_NULL == rsp || BPS_NULL == buf) {
//         return 0;
//     }
// 
//     rsp->fieldArray = BPS_NULL;
//     if(0 == size--) {
//         return 0;
//     }
//     field_num = buf[i++];
//     rsp->fieldNum = field_num;
//     rsp->fieldArray = (BPSCmdSystemParaField *)malloc(field_num * sizeof(BPSCmdSystemParaField));
//     memset_bps(rsp->fieldArray, 0, field_num * sizeof(BPSCmdSystemParaField));
// 
//     for(j = 0; j < field_num; j++) {
//         if(0 == size--) {
//             BPSFreeMemSystemParaRsp(rsp);
//             return 0;
//         }
//         field_tmp = rsp->fieldArray + j;
//         field_tmp->type = buf[i++];
// 
//         if(0 == size--) {
//             BPSFreeMemSystemParaRsp(rsp);
//             return 0;
//         }
//         field_tmp->len = buf[i++];
// 
//         if(field_tmp->len > size) {
//             BPSFreeMemSystemParaRsp(rsp);
//             return 0;
//         }
//         size -= field_tmp->len;
//         field_tmp->data = (BPS_UINT8 *)malloc(field_tmp->len + 1);
//         memcpy_bps(field_tmp->data, buf+i, field_tmp->len);
//         field_tmp->data[field_tmp->len] = '\0';
//         i += field_tmp->len;
//     }
// 
//     return i;
// }
// 
// void BPSFreeMemSystemParaRsp(BPSCmdSystemParaRsp * rsp)
// {
//     BPS_WORD i;
//     BPSCmdSystemParaField * field_tmp;
//     if(BPS_NULL == rsp) {
//         return;
//     }
//     if(BPS_NULL == rsp->fieldArray) {
//         return;
//     }
//     for(i = 0; i < rsp->fieldNum; i++) {
//        field_tmp = rsp->fieldArray + i;
//        if(BPS_NULL != field_tmp->data) {
//            free(field_tmp->data);
//        }
//     }
//     free(rsp->fieldArray);
//     rsp->fieldArray = BPS_NULL;
// }
// #endif

