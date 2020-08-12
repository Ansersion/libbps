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
/// @file   bps_cmd_launch_update.h
/// @brief  definations of functions and variable types for command 'launching update'
/// 
/// @version    0.1
/// @author     Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BPS_CMD_LAUNCH_UPDATE_H
#define __BPS_CMD_LAUNCH_UPDATE_H

#include <bps_public.h>

#if (BPS_CMD_SET == BPS_CMD_SET_B || BPS_CMD_SET == BPS_CMD_SET_T || BPS_CMD_SET == BPS_CMD_SET_C)

#include <bps_cwords.h>

#define SECURITY_WORD_LNCH_UPDATE   0xBCCB

typedef struct BPSCmdLnchUpdateReq {
    BPS_UINT8 recv;
} BPSCmdLnchUpdateReq;

typedef struct BPSCmdLnchUpdateRsp {
    BPS_UINT8 retCode;
} BPSCmdLnchUpdateRsp;

/** 
  * @Brief BPSPackLnchUpdateReq construct packet of 'launching update' request
  * @Param req the request parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BPS_UINT16 BPSPackLnchUpdateReq(BPSCmdLnchUpdateReq * req, BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSPackLnchUpdateRsp construct packet of 'launching update' response
  * @Param rsp the response parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BPS_UINT16 BPSPackLnchUpdateRsp(BPSCmdLnchUpdateRsp * rsp, BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSParseLnchUpdateReq parse packet of 'launching update' request
  * @Param req the request data struct to store the message
  * @Param buf the buffer stored the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BPS_UINT16 BPSParseLnchUpdateReq(BPSCmdLnchUpdateReq * req, const BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSParseLnchUpdateRsp parse packet of 'launching update' response
  * @Param rsp the response data struct to store the message
  * @Param buf the buffer to store the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BPS_UINT16 BPSParseLnchUpdateRsp(BPSCmdLnchUpdateRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size);

#ifdef BPS_MEM_DYN
    #define BPSParseLnchUpdateReqDyn     BPSParseLnchUpdateReq
    #define BPSParseLnchUpdateRspDyn     BPSParseLnchUpdateRsp
    #define BPSFreeMemLnchUpdateReq(x)     
    #define BPSFreeMemLnchUpdateRsp(x)     
#endif

#endif

#endif

