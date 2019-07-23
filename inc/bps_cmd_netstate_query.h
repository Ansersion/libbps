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
/// @file   bps_cmd_netstate_query.h
/// @brief  definations of functions and variable types for command 'query net state'
/// 
/// @version    0.1
/// @author     Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BPS_CMD_NETSTATE_QUERY_H
#define __BPS_CMD_NETSTATE_QUERY_H

#include <bps_public.h>
#include <bps_cwords.h>

#define CMD_NETSTATE_QUERY_WORD_REQ  0x0A
#define CMD_NETSTATE_QUERY_WORD_RSP  0x0B

typedef struct BPSCmdNetstateQueryReq {
    BP_UINT8 recv;
} BPSCmdNetstateQueryReq;

typedef struct BPSCmdNetstateQueryRsp {
    BP_UINT8 state;
} BPSCmdNetstateQueryRsp;

/** 
  * @Brief BPSPackNetstateQueryReq construct packet of 'query net state' request
  * @Param req the request parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BP_UINT16 BPSPackNetstateQueryReq(BPSCmdNetstateQueryReq * req, BP_UINT8 * buf, BP_WORD size);

/** 
  * @Brief BPSPackNetstateQueryRsp construct packet of 'query net state' response
  * @Param rsp the response parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BP_UINT16 BPSPackNetstateQueryRsp(BPSCmdNetstateQueryRsp * rsp, BP_UINT8 * buf, BP_WORD size);

/** 
  * @Brief BPSParseNetstateQueryReq parse packet of 'query net state' request
  * @Param req the request data struct to store the message
  * @Param buf the buffer stored the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BP_UINT16 BPSParseNetstateQueryReq(BPSCmdNetstateQueryReq * req, BP_UINT8 * buf, BP_WORD size);

/** 
  * @Brief BPSParseNetstateQueryRsp parse packet of 'query net state' response
  * @Param rsp the response data struct to store the message
  * @Param buf the buffer to store the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BP_UINT16 BPSParseNetstateQueryRsp(BPSCmdNetstateQueryRsp * rsp, BP_UINT8 * buf, BP_WORD size);

#ifdef BP_MEM_DYN
    #define ParseNetstateQueryReqDyn     ParseNetstateQueryReq
    #define ParseNetstateQueryRspDyn     ParseNetstateQueryRsp
#endif

#endif

