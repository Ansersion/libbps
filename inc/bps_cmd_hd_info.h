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

#include <bps_public.h>
#include <bps_cwords.h>

#define CMD_HD_INFO_WORD_REQ  0x02
#define CMD_HD_INFO_WORD_RSP  0x03
#define CMD_HD_INFO_FIELD_END  0xFF

typedef struct BPSCmdHDInfoReq {
    BP_UINT8 recv;
} BPSCmdHDInfoReq;

typedef struct BPSCmdHDInfoField {
    BP_UINT8 type;
    BP_UINT8 len;
    BP_UINT8 * data;
} BPSCmdHDInfoField;

typedef struct BPSCmdHDInfoRsp {
    BPSCmdHDInfoField * fieldArray;
    BP_WORD fieldNum;
} BPSCmdHDInfoRsp;

/** 
  * @Brief BPSPackHDInfoReq construct packet of 'query hardware info' request
  * @Param req the request parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BP_UINT16 BPSPackHDInfoReq(BPSCmdHDInfoReq * req, BP_UINT8 * buf, BP_WORD size);

/** 
  * @Brief BPSPackHDInfoRsp construct packet of 'query hardware info' response
  * @Param rsp the response parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BP_UINT16 BPSPackHDInfoRsp(BPSCmdHDInfoRsp * rsp, BP_UINT8 * buf, BP_WORD size);

/** 
  * @Brief BPSParseHDInfoReq parse packet of 'query hardware info' request
  * @Param req the request data struct to store the message
  * @Param buf the buffer stored the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BP_UINT16 BPSParseHDInfoReq(BPSCmdHDInfoReq * req, BP_UINT8 * buf, BP_WORD size);

/** 
  * @Brief BPSParseHDInfoRsp parse packet of 'query hardware info' response
  * @Param rsp the response data struct to store the message. 
  *     Make sure that there are enough memory to store the message, or to use BPSParseHDInfoRspDyn
  *     which is more efficient for memory usage.
  * @Param buf the buffer to store the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BP_UINT16 BPSParseHDInfoRsp(BPSCmdHDInfoRsp * rsp, BP_UINT8 * buf, BP_WORD size);

#ifdef BP_MEM_DYN
    #define ParseHDInfoReqDyn     ParseHDInfoReq
/** 
  * @Brief BPSParseHDInfoRsp parse packet of 'query hardware info' response
  * @Param rsp the response data struct to store the message.
  *         YOU HAVE TO CLEAR THE MEMORY OF ALL THE POINTERS RECURSIVELY IN 'rsp' 
  *         when the address of 'rsp' is unreachable
  * @Param buf the buffer to store the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
  *         rsp 
 */
EXPORT_API BP_UINT16 BPSParseHDInfoRspDyn(BPSCmdHDInfoRsp * rsp, BP_UINT8 * buf, BP_WORD size);
#endif

#endif

