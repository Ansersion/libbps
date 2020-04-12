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
/// @file   bps_cmd_trans_bytes.h
/// @brief  definations of functions and variable types for command 'transmit bytes'
/// 
/// @version    0.1
/// @author     Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BPS_CMD_TRANS_BYTES_H
#define __BPS_CMD_TRANS_BYTES_H

#include <bps_public.h>
#include <bps_cwords.h>

#define CMD_TRANS_BYTES_WORD_REQ  0xF8
#define CMD_TRANS_BYTES_WORD_RSP  (CMD_TRANS_BYTES_WORD_REQ+1)

typedef struct BPSCmdTransBytesReq {
    BPS_UINT8 len;
    BPS_UINT8 * data;
    /** maxLen the size of 'data', 
      is set to be safe only for parsing that without dynamical memory allocation */
    BPS_WORD maxLen;
} BPSCmdTransBytesReq;

typedef struct BPSCmdTransBytesRsp {
    BPS_UINT8 len;
    BPS_UINT8 * data;
    /** maxLen the size of 'data', 
      is set to be safe only for parsing that without dynamical memory allocation */
    BPS_WORD maxLen;
} BPSCmdTransBytesRsp;

/** 
  * @Brief BPSPackTransBytesReq construct packet of 'transmit bytes' request
  * @Param req the request parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BPS_UINT16 BPSPackTransBytesReq(BPSCmdTransBytesReq * req, BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSPackTransBytesRsp construct packet of 'transmit bytes' response
  * @Param rsp the response parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BPS_UINT16 BPSPackTransBytesRsp(BPSCmdTransBytesRsp * rsp, BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSParseTransBytesReq parse packet of 'transmit bytes' request
  * @Param req the request data struct to store the message
  * @Param buf the buffer stored the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BPS_UINT16 BPSParseTransBytesReq(BPSCmdTransBytesReq * req, const BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSParseTransBytesRsp parse packet of 'transmit bytes' response
  * @Param rsp the response data struct to store the message. 
  *     Make sure that there are enough memory to store the message, or to use BPSParseTransBytesRspDyn
  *     which is more efficient for memory usage.
  * @Param buf the buffer to store the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BPS_UINT16 BPSParseTransBytesRsp(BPSCmdTransBytesRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size);

#ifdef BPS_MEM_DYN
/** 
  * @Brief BPSParseTransBytesRspDyn parse packet of 'transmit bytes' request
  * @Param req the request data struct to store the message.
  *         YOU HAVE TO CLEAR THE MEMORY OF ALL THE POINTERS RECURSIVELY IN 'req' 
  *         when the address of 'req' is unreachable(if the function return 0, you need do nothing about clearing memory)
  * @Param buf the buffer to store the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
  *         rsp 
 */
EXPORT_API BPS_UINT16 BPSParseTransBytesReqDyn(BPSCmdTransBytesReq * req, const BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSFreeMemTransBytesReq free the memory of the request struct
  * @Param req the request data struct.
 */
EXPORT_API void BPSFreeMemTransBytesReq(BPSCmdTransBytesReq * req);

/** 
  * @Brief BPSParseTransBytesRspDyn parse packet of 'transmit bytes' response
  * @Param rsp the response data struct to store the message.
  *         YOU HAVE TO CLEAR THE MEMORY OF ALL THE POINTERS RECURSIVELY IN 'rsp' 
  *         when the address of 'rsp' is unreachable(if the function return 0, you need do nothing about clearing memory)
  * @Param buf the buffer to store the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
  *         rsp 
 */
EXPORT_API BPS_UINT16 BPSParseTransBytesRspDyn(BPSCmdTransBytesRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSFreeMemTransBytesRsp free the memory of the response struct
  * @Param rsp the response data struct.
 */
EXPORT_API void BPSFreeMemTransBytesRsp(BPSCmdTransBytesRsp * rsp);
#endif

#endif

