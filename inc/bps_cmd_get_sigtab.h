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
/// @file   bps_cmd_get_sigtab.h
/// @brief  definations of functions and variable types for command 'get signal table'
/// 
/// @version    0.1
/// @author     Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BPS_CMD_GET_SIGTAB_H
#define __BPS_CMD_GET_SIGTAB_H

#include <bps_public.h>
#include <bps_cwords.h>

#define CMD_GET_SIGTAB_WORD_REQ  0x80
#define CMD_GET_SIGTAB_WORD_RSP  0x81

typedef struct BPSCmdGetSigtabReq {
    BP_UINT8 recv;
} BPSCmdGetSigtabReq;

typedef struct BPSCmdGetSigtabField {
    BP_UINT16 signalId;
    BP_UINT8 signalType;
    BP_UINT8 accuracy;
} BPSCmdGetSigtabField;

typedef struct BPSCmdGetSigtabRsp {
    BP_WORD fieldNum;
    BPSCmdGetSigtabField * fieldArray;
} BPSCmdGetSigtabRsp;

/** 
  * @Brief BPSPackGetSigtabReq construct packet of 'get signal table' request
  * @Param req the request parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BP_UINT16 BPSPackGetSigtabReq(BPSCmdGetSigtabReq * req, BP_UINT8 * buf, BP_WORD size);

/** 
  * @Brief BPSPackGetSigtabRsp construct packet of 'get signal table' response
  * @Param rsp the response parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BP_UINT16 BPSPackGetSigtabRsp(BPSCmdGetSigtabRsp * rsp, BP_UINT8 * buf, BP_WORD size);

/** 
  * @Brief BPSParseGetSigtabReq parse packet of 'get signal table' request
  * @Param req the request data struct to store the message
  * @Param buf the buffer stored the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BP_UINT16 BPSParseGetSigtabReq(BPSCmdGetSigtabReq * req, BP_UINT8 * buf, BP_WORD size);

/** 
  * @Brief BPSParseGetSigtabRsp parse packet of 'get signal table' response
  * @Param rsp the response data struct to store the message. 
  *     Make sure that there are enough memory to store the message, or to use BPSParseGetSigtabRspDyn
  *     which is more efficient for memory usage.
  * @Param buf the buffer to store the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BP_UINT16 BPSParseGetSigtabRsp(BPSCmdGetSigtabRsp * rsp, BP_UINT8 * buf, BP_WORD size);

#ifdef BP_MEM_DYN
    #define ParseGetSigtabReqDyn     ParseGetSigtabReq
/** 
  * @Brief BPSParseGetSigtabRsp parse packet of 'get signal table' response
  * @Param rsp the response data struct to store the message.
  *         YOU HAVE TO CLEAR THE MEMORY OF ALL THE POINTERS RECURSIVELY IN 'rsp' 
  *         when the address of 'rsp' is unreachable
  * @Param buf the buffer to store the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
  *         rsp 
 */
EXPORT_API BP_UINT16 BPSParseGetSigtabRspDyn(BPSCmdGetSigtabRsp * rsp, BP_UINT8 * buf, BP_WORD size);
#endif

#endif

