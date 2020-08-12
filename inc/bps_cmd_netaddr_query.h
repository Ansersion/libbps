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
/// @file   bps_cmd_netaddr_query.h
/// @brief  definations of functions and variable types for command 'query net address'
/// 
/// @version    0.1
/// @author     Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BPS_CMD_NETADDR_QUERY_H
#define __BPS_CMD_NETADDR_QUERY_H

#include <bps_public.h>

#if (BPS_CMD_SET == BPS_CMD_SET_C)

#include <bps_cwords.h>

typedef struct BPSCmdNetaddrQueryReq {
    BPS_UINT8 type;
} BPSCmdNetaddrQueryReq;

typedef struct BPSCmdNetaddrQueryRsp {
    BPS_UINT8 len;
    BPS_UINT8 * data;
    /** maxLen the size of 'data', 
      is set to be safe only for parsing that without dynamical memory allocation */
    BPS_WORD maxLen;
} BPSCmdNetaddrQueryRsp;

/** 
  * @Brief BPSPackNetaddrQueryReq construct packet of 'query net address' request
  * @Param req the request parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BPS_UINT16 BPSPackNetaddrQueryReq(BPSCmdNetaddrQueryReq * req, BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSPackNetaddrQueryRsp construct packet of 'query net address' response
  * @Param rsp the response parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BPS_UINT16 BPSPackNetaddrQueryRsp(BPSCmdNetaddrQueryRsp * rsp, BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSParseNetaddrQueryReq parse packet of 'query net address' request
  * @Param req the request data struct to store the message
  * @Param buf the buffer stored the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BPS_UINT16 BPSParseNetaddrQueryReq(BPSCmdNetaddrQueryReq * req, const BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSParseNetaddrQueryRsp parse packet of 'query net address' response
  * @Param rsp the response data struct to store the message
  * @Param buf the buffer to store the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BPS_UINT16 BPSParseNetaddrQueryRsp(BPSCmdNetaddrQueryRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size);

#ifdef BPS_MEM_DYN
    #define BPSParseNetaddrQueryReqDyn     BPSParseNetaddrQueryReq
    #define BPSFreeMemNetaddrQueryReq(x)     
/** 
  * @Brief BPSParseNetaddrQueryRspDyn parse packet of 'net address query' response
  * @Param rsp the response data struct to store the message.
  *         YOU HAVE TO CLEAR THE MEMORY OF ALL THE POINTERS RECURSIVELY IN 'rsp' 
  *         when the address of 'rsp' is unreachable(if the function return 0, you need do nothing about clearing memory)
  * @Param buf the buffer to store the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
  *         rsp 
 */
EXPORT_API BPS_UINT16 BPSParseNetaddrQueryRspDyn(BPSCmdNetaddrQueryRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSFreeMemNetaddrQueryRsp free the memory of the response struct
  * @Param rsp the response data struct.
 */
EXPORT_API void BPSFreeMemNetaddrQueryRsp(BPSCmdNetaddrQueryRsp * rsp);
#endif

#endif

#endif
