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
/// @file   bps_cmd_report_sig.h
/// @brief  definations of functions and variable types for command 'report signal values'
/// 
/// @version    0.1
/// @author     Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BPS_CMD_REPORT_SIG_H
#define __BPS_CMD_REPORT_SIG_H

#include <bps_public.h>
#include <bps_cwords.h>

#define CMD_REPORT_SIG_WORD_REQ  0x82
#define CMD_REPORT_SIG_WORD_RSP  0x83

typedef struct BPSCmdReportSigField {
    BP_UINT16 signalId;
    BP_UINT8 signalType;
    BPSSigTypeU value;
} BPSCmdReportSigField;

typedef struct BPSCmdReportSigReq {
    BP_WORD fieldNum;
    BPSCmdReportSigField * fieldArray;
} BPSCmdReportSigReq;

typedef struct BPSCmdReportSigRsp {
    BP_UINT8 retCode;
    void * extension;
} BPSCmdReportSigRsp;

/** 
  * @Brief BPSPackReportSigReq construct packet of 'report signal values' request
  * @Param req the request parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BP_UINT16 BPSPackReportSigReq(BPSCmdReportSigReq * req, BP_UINT8 * buf, BP_WORD size);

/** 
  * @Brief BPSPackReportSigRsp construct packet of 'report signal values' response
  * @Param rsp the response parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BP_UINT16 BPSPackReportSigRsp(BPSCmdReportSigRsp * rsp, BP_UINT8 * buf, BP_WORD size);

/** 
  * @Brief BPSParseReportSigReq parse packet of 'report signal values' request
  * @Param req the request data struct to store the message
  * @Param buf the buffer stored the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BP_UINT16 BPSParseReportSigReq(BPSCmdReportSigReq * req, BP_UINT8 * buf, BP_WORD size);

/** 
  * @Brief BPSParseReportSigRsp parse packet of 'report signal values' response
  * @Param rsp the response data struct to store the message. 
  *     Make sure that there are enough memory to store the message, or to use BPSParseReportSigRspDyn
  *     which is more efficient for memory usage.
  * @Param buf the buffer to store the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BP_UINT16 BPSParseReportSigRsp(BPSCmdReportSigRsp * rsp, BP_UINT8 * buf, BP_WORD size);

#ifdef BP_MEM_DYN
/** 
  * @Brief BPSParseReportSigReqDyn parse packet of 'report signal values' request
  * @Param req the request data struct to store the message.
  *         YOU HAVE TO CLEAR THE MEMORY OF ALL THE POINTERS RECURSIVELY IN 'req' 
  *         when the address of 'req' is unreachable(if the function return 0, you need do nothing about clearing memory)
  * @Param buf the buffer stored the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */

BP_UINT16 BPSParseReportSigReqDyn(BPSCmdReportSigReq * req, BP_UINT8 * buf, BP_WORD size);
/** 
  * @Brief BPSParseReportSigRsp parse packet of 'report signal values' response
  * @Param rsp the response data struct to store the message.
  *         YOU HAVE TO CLEAR THE MEMORY OF ALL THE POINTERS RECURSIVELY IN 'rsp' 
  *         when the address of 'rsp' is unreachable(if the function return 0, you need do nothing about clearing memory)
  * @Param buf the buffer to store the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
  *         rsp 
 */
EXPORT_API BP_UINT16 BPSParseReportSigRspDyn(BPSCmdReportSigRsp * rsp, BP_UINT8 * buf, BP_WORD size);

/** 
  * @Brief BPSParseReportSigRsp parse packet of 'report signal values' response
  * @Param rsp the response data struct to store the message.
  *         YOU HAVE TO CLEAR THE MEMORY OF ALL THE POINTERS RECURSIVELY IN 'rsp' 
  *         when the address of 'rsp' is unreachable(if the function return 0, you need do nothing about clearing memory)
  * @Param buf the buffer to store the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
  *         rsp 
 */

/** 
  * @Brief BPSFreeMemReportSigReq free the memory of the request struct
  * @Param req the request data struct.
 */
EXPORT_API void BPSFreeMemReportSigReq(BPSCmdReportSigReq * req);

/** 
  * @Brief BPSFreeMemReportSigRsp free the memory of the response struct
  * @Param rsp the response data struct.
 */
EXPORT_API void BPSFreeMemReportSigRsp(BPSCmdReportSigRsp * rsp);
#endif

#endif
