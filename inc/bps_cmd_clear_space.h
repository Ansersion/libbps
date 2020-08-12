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
/// @file   bps_cmd_clear_space.h
/// @brief  definations of functions and variable types for command 'clear space'
/// 
/// @version    0.1
/// @author     Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BPS_CMD_CLEAR_SPACE_H
#define __BPS_CMD_CLEAR_SPACE_H

#include <bps_public.h>

#if (BPS_CMD_SET == BPS_CMD_SET_B || BPS_CMD_SET == BPS_CMD_SET_T || BPS_CMD_SET == BPS_CMD_SET_C)

#include <bps_cwords.h>


typedef enum ReqTypeClearSpace {
    RT_CLR_SPC_AUTO = 0,
    RT_CLR_SPC_GUIDE,
} ReqTypeClearSpace;

typedef struct BPSCmdClearSpaceReq {
    BPS_UINT8 mode;
    BPS_UINT32 len;
    BPS_UINT32 addr;
} BPSCmdClearSpaceReq;

typedef struct BPSCmdClearSpaceRsp {
    BPS_UINT8 retCode;
} BPSCmdClearSpaceRsp;

/** 
  * @Brief BPSPackClearSpaceReq construct packet of 'clear space' request
  * @Param req the request parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BPS_UINT16 BPSPackClearSpaceReq(BPSCmdClearSpaceReq * req, BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSPackClearSpaceRsp construct packet of 'clear space' response
  * @Param rsp the response parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BPS_UINT16 BPSPackClearSpaceRsp(BPSCmdClearSpaceRsp * rsp, BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSParseClearSpaceReq parse packet of 'clear space' request
  * @Param req the request data struct to store the message
  * @Param buf the buffer stored the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BPS_UINT16 BPSParseClearSpaceReq(BPSCmdClearSpaceReq * req, const BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSParseClearSpaceRsp parse packet of 'clear space' response
  * @Param rsp the response data struct to store the message
  * @Param buf the buffer to store the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BPS_UINT16 BPSParseClearSpaceRsp(BPSCmdClearSpaceRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size);

#ifdef BPS_MEM_DYN
    #define BPSParseClearSpaceReqDyn     BPSParseClearSpaceReq
    #define BPSParseClearSpaceRspDyn     BPSParseClearSpaceRsp
    #define BPSFreeMemClearSpaceReq(x)     
    #define BPSFreeMemClearSpaceRsp(x)     
#endif

#endif

#endif

