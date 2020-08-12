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
/// @file   bps_cmd_write_frmw.h
/// @brief  definations of functions and variable types for command 'write update firmware'
/// 
/// @version    0.1
/// @author     Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BPS_CMD_WRITE_FRMW_H
#define __BPS_CMD_WRITE_FRMW_H

#include <bps_public.h>

#if (BPS_CMD_SET == BPS_CMD_SET_B || BPS_CMD_SET == BPS_CMD_SET_T || BPS_CMD_SET == BPS_CMD_SET_C)

#include <bps_cwords.h>

typedef enum ReqTypeWriteFrmwSet {
    RT_WRT_FRMW_AUTO = 0,
    RT_WRT_FRMW_GUIDE,
} ReqTypeWriteFrmwSet;

typedef struct BPSCmdWriteFrmwReq {
    BPS_UINT8 mode;
    BPS_UINT8 len;
    BPS_UINT8 * data;
    BPS_UINT32 offset;

    /** maxLen the size of 'data', 
      is set to be safe only for parsing that without dynamical memory allocation */
    BPS_WORD maxLen;
} BPSCmdWriteFrmwReq;

typedef struct BPSCmdWriteFrmwRsp {
    BPS_UINT8 retCode;
} BPSCmdWriteFrmwRsp;

/** 
  * @Brief BPSPackWriteFrmwReq construct packet of 'write update firmware' request
  * @Param req the request parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BPS_UINT16 BPSPackWriteFrmwReq(BPSCmdWriteFrmwReq * req, BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSPackWriteFrmwRsp construct packet of 'write update firmware' response
  * @Param rsp the response parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BPS_UINT16 BPSPackWriteFrmwRsp(BPSCmdWriteFrmwRsp * rsp, BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSParseWriteFrmwReq parse packet of 'write update firmware' request
  * @Param req the request data struct to store the message
  * @Param buf the buffer stored the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BPS_UINT16 BPSParseWriteFrmwReq(BPSCmdWriteFrmwReq * req, const BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSParseWriteFrmwRsp parse packet of 'write update firmware' response
  * @Param rsp the response data struct to store the message. 
  *     Make sure that there are enough memory to store the message, or to use BPSParseWriteFrmwRspDyn
  *     which is more efficient for memory usage.
  * @Param buf the buffer to store the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BPS_UINT16 BPSParseWriteFrmwRsp(BPSCmdWriteFrmwRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size);

#ifdef BPS_MEM_DYN
/** 
  * @Brief BPSParseWriteFrmwReq parse packet of 'write update firmware' request
  * @Param req the request data struct to store the message.
  *         YOU HAVE TO CLEAR THE MEMORY OF ALL THE POINTERS RECURSIVELY IN 'req' 
  *         when the address of 'req' is unreachable(if the function return 0, you need do nothing about clearing memory)
  * @Param buf the buffer to store the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BPS_UINT16 BPSParseWriteFrmwReqDyn(BPSCmdWriteFrmwReq * req, const BPS_UINT8 * buf, BPS_WORD size);

    #define BPSParseWriteFrmwRspDyn     BPSParseWriteFrmwRsp

/** 
  * @Brief BPSFreeMemWriteFrmwReq free the memory of the response struct
  * @Param req the request data struct.
 */
EXPORT_API void BPSFreeMemWriteFrmwReq(BPSCmdWriteFrmwReq * req);

    #define BPSFreeMemWriteFrmwRsp(x)  
#endif

#endif

#endif

