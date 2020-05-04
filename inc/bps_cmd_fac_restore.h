///////////////////////////////////////////////////////////////////////////////
/// Copyright 2020 Ansersion
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
/// @file   bps_cmd_fac_restore.h
/// @brief  definations of functions and variable types for command 'restore to factory settings'
/// 
/// @version    0.1
/// @author     Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BPS_CMD_FAC_RESTORE_H
#define __BPS_CMD_FAC_RESTORE_H

#if (BPS_CMD_SET == BPS_CMD_SET_B || BPS_CMD_SET == BPS_CMD_SET_T || BPS_CMD_SET == BPS_CMD_SET_C)

#include <bps_public.h>
#include <bps_cwords.h>

#define SECURITY_WORD_FAC_RESTORE     0xCBCB

typedef struct BPSCmdFacRestoreReq {
    BPS_UINT8 recv;
} BPSCmdFacRestoreReq;

typedef struct BPSCmdFacRestoreRsp {
    BPS_UINT8 retCode;
} BPSCmdFacRestoreRsp;

/** 
  * @Brief BPSPackFacRestoreReq construct packet of 'restore to factory settings' request
  * @Param req the request parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BPS_UINT16 BPSPackFacRestoreReq(BPSCmdFacRestoreReq * req, BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSPackFacRestoreRsp construct packet of 'restore to factory settings' response
  * @Param rsp the response parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BPS_UINT16 BPSPackFacRestoreRsp(BPSCmdFacRestoreRsp * rsp, BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSParseFacRestoreReq parse packet of 'restore to factory settings' request
  * @Param req the request data struct to store the message
  * @Param buf the buffer stored the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BPS_UINT16 BPSParseFacRestoreReq(BPSCmdFacRestoreReq * req, const BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSParseFacRestoreRsp parse packet of 'restore to factory settings' response
  * @Param rsp the response data struct to store the message
  * @Param buf the buffer to store the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BPS_UINT16 BPSParseFacRestoreRsp(BPSCmdFacRestoreRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size);

#ifdef BPS_MEM_DYN
    #define ParseFacRestoreReqDyn     ParseFacRestoreReq
    #define ParseFacRestoreRspDyn     ParseFacRestoreRsp
    #define BPSFreeMemFacRestoreReq(x)     
    #define BPSFreeMemFacRestoreRsp(x)     
#endif

#endif

#endif

