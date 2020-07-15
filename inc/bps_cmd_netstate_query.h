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

#if (BPS_CMD_SET == BPS_CMD_SET_C)

#include <bps_public.h>
#include <bps_cwords.h>

typedef struct BPSCmdNetstateQueryReq {
    BPS_UINT8 recv;
} BPSCmdNetstateQueryReq;

typedef struct BPSCmdNetstateQueryRsp {
    BPS_UINT8 state;
} BPSCmdNetstateQueryRsp;

/** 
  * @Brief BPSPackNetstateQueryReq construct packet of 'query net state' request
  * @Param req the request parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BPS_UINT16 BPSPackNetstateQueryReq(BPSCmdNetstateQueryReq * req, BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSPackNetstateQueryRsp construct packet of 'query net state' response
  * @Param rsp the response parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BPS_UINT16 BPSPackNetstateQueryRsp(BPSCmdNetstateQueryRsp * rsp, BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSParseNetstateQueryReq parse packet of 'query net state' request
  * @Param req the request data struct to store the message
  * @Param buf the buffer stored the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BPS_UINT16 BPSParseNetstateQueryReq(BPSCmdNetstateQueryReq * req, const BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSParseNetstateQueryRsp parse packet of 'query net state' response
  * @Param rsp the response data struct to store the message
  * @Param buf the buffer to store the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BPS_UINT16 BPSParseNetstateQueryRsp(BPSCmdNetstateQueryRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size);

#ifdef BPS_MEM_DYN
    #define BPSParseNetstateQueryReqDyn     BPSParseNetstateQueryReq
    #define BPSParseNetstateQueryRspDyn     BPSParseNetstateQueryRsp
    #define BPSFreeMemNetstateQueryReq(x)     
    #define BPSFreeMemNetstateQueryRsp(x)     
#endif

#endif

#endif
