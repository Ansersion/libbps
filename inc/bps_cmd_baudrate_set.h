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
/// @file   bps_cmd_baudrate_set.h
/// @brief  definations of functions and variable types for command 'set/query serial baudrate'
/// 
/// @version    0.1
/// @author     Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BPS_CMD_BAUDRATE_SET_H
#define __BPS_CMD_BAUDRATE_SET_H

#include <bps_public.h>
#include <bps_cwords.h>

#define CMD_BAUDRATE_SET_WORD_REQ  0x0E
#define CMD_BAUDRATE_SET_WORD_RSP  (CMD_BAUDRATE_SET_WORD_REQ+1)

typedef enum ReqTypeBaudrateSet {
    QUERY_RT_BAUDRATE_SET = 0,
    SET_RT_BAUDRATE_SET,
} ReqTypeBaudrateSet;

typedef struct BPSCmdBaudrateSetReq {
    BPS_UINT8 type;
    BPS_UINT32 baudrate;
} BPSCmdBaudrateSetReq;

typedef struct BPSCmdBaudrateSetRsp {
    BPS_UINT8 retCode;
    BPS_UINT32 baudrate;
} BPSCmdBaudrateSetRsp;

/** 
  * @Brief BPSPackBaudrateSetReq construct packet of 'set serial baudrate' request
  * @Param req the request parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BPS_UINT16 BPSPackBaudrateSetReq(BPSCmdBaudrateSetReq * req, BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSPackBaudrateSetRsp construct packet of 'set serial baudrate' response
  * @Param rsp the response parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BPS_UINT16 BPSPackBaudrateSetRsp(BPSCmdBaudrateSetRsp * rsp, BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSParseBaudrateSetReq parse packet of 'set serial baudrate' request
  * @Param req the request data struct to store the message
  * @Param buf the buffer stored the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BPS_UINT16 BPSParseBaudrateSetReq(BPSCmdBaudrateSetReq * req, const BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSParseBaudrateSetRsp parse packet of 'set serial baudrate' response
  * @Param rsp the response data struct to store the message
  * @Param buf the buffer to store the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BPS_UINT16 BPSParseBaudrateSetRsp(BPSCmdBaudrateSetRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size);

#ifdef BPS_MEM_DYN
    #define ParseBaudrateSetReqDyn     ParseBaudrateSetReq
    #define ParseBaudrateSetRspDyn     ParseBaudrateSetRsp
    #define BPSFreeMemBaudrateSetReq(x)     
    #define BPSFreeMemBaudrateSetRsp(x)     
#endif

#endif

