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
/// @file   bps_cmd_hd_info.h
/// @brief  definations of functions and variable types for command 'query hardware info'
/// 
/// @version    0.1
/// @author     Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BPS_CMD_HD_INFO_H
#define __BPS_CMD_HD_INFO_H

#if (BPS_CMD_SET == BPS_CMD_SET_B || BPS_CMD_SET == BPS_CMD_SET_T || BPS_CMD_SET == BPS_CMD_SET_C)

#include <bps_public.h>
#include <bps_cwords.h>

typedef enum RspTypeHdInfo {
    SN_RST_HD_INFO = 0,
    HARD_V_RST_HD_INFO,
    SOFT_V_RST_HD_INFO,
    /** customise your own info ID here */

    HD_INFO_NUM,
} HdInfoType;

typedef struct BPSCmdHDInfoReq {
    BPS_UINT8 recv;
} BPSCmdHDInfoReq;

typedef struct BPSCmdHDInfoField {
    BPS_UINT8 type;
    BPS_UINT8 len;
    BPS_UINT8 * data;

    /** maxLen the size of 'data', 
      is set to be safe only for parsing that without dynamical memory allocation */
    BPS_WORD maxLen;
} BPSCmdHDInfoField;

typedef struct BPSCmdHDInfoRsp {
    BPSCmdHDInfoField * fieldArray;
    BPS_WORD fieldNum;

    /** infoTypeArray info type array which the user concerns.
      * only the info type included in the array will be parsed, the other will be 
      * ignored. It's a good use for memory saving. 
      * Setting it to BPS_NULL means parsing all the info types.
      * Only for API without dynamical memory allocation.
      */
    HdInfoType * infoTypeArray;
    BPS_UINT8 infoTypeArrayLen;

    /** maxFieldNum is set to be safe only for parsing that without dynamical memory allocation. */
    BPS_WORD maxFieldNum;
} BPSCmdHDInfoRsp;

/** 
  * @Brief BPSPackHDInfoReq construct packet of 'query hardware info' request
  * @Param req the request parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BPS_UINT16 BPSPackHDInfoReq(BPSCmdHDInfoReq * req, BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSPackHDInfoRsp construct packet of 'query hardware info' response
  * @Param rsp the response parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BPS_UINT16 BPSPackHDInfoRsp(BPSCmdHDInfoRsp * rsp, BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSParseHDInfoReq parse packet of 'query hardware info' request
  * @Param req the request data struct to store the message
  * @Param buf the buffer stored the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BPS_UINT16 BPSParseHDInfoReq(BPSCmdHDInfoReq * req, const BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSParseHDInfoRsp parse packet of 'query hardware info' response
  * @Param rsp the response data struct to store the message. 
  *     Make sure that there are enough memory to store the message, or to use BPSParseHDInfoRspDyn
  *     which is more efficient for memory usage.
  * @Param buf the buffer to store the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BPS_UINT16 BPSParseHDInfoRsp(BPSCmdHDInfoRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size);

#ifdef BPS_MEM_DYN
    #define BPSParseHDInfoReqDyn     BPSParseHDInfoReq
/** 
  * @Brief BPSParseHDInfoRsp parse packet of 'query hardware info' response
  * @Param rsp the response data struct to store the message.
  *         YOU HAVE TO CLEAR THE MEMORY OF ALL THE POINTERS RECURSIVELY IN 'rsp' 
  *         when the address of 'rsp' is unreachable(if the function return 0, you need do nothing about clearing memory)
  * @Param buf the buffer to store the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
  *         rsp 
 */
EXPORT_API BPS_UINT16 BPSParseHDInfoRspDyn(BPSCmdHDInfoRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size);

    #define BPSFreeMemHDInfoReq(x)  
/** 
  * @Brief BPSFreeMemHDInfoRsp free the memory of the response struct
  * @Param rsp the response data struct.
 */
EXPORT_API void BPSFreeMemHDInfoRsp(BPSCmdHDInfoRsp * rsp);
#endif

#endif

#endif

