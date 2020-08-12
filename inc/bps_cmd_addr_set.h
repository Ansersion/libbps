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
/// @file   bps_cmd_addr_set.h
/// @brief  definations of functions and variable types for command 'set the BPS address'
/// 
/// @version    0.1
/// @author     Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BPS_CMD_ADDR_SET_H
#define __BPS_CMD_ADDR_SET_H

#include <bps_public.h>

#if (BPS_CMD_SET == BPS_CMD_SET_B || BPS_CMD_SET == BPS_CMD_SET_T || BPS_CMD_SET == BPS_CMD_SET_C)

#include <bps_cwords.h>

#define SECURITY_WORD_ADDR_SET     0xCCBB

typedef struct BPSCmdAddrSetReq {
    BPS_UINT8 addr;
} BPSCmdAddrSetReq;

typedef struct BPSCmdAddrSetRsp {
    BPS_UINT8 retCode;
} BPSCmdAddrSetRsp;

/** 
  * @Brief BPSPackAddrSetReq construct packet of 'set the BPS address' request
  * @Param req the request parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BPS_UINT16 BPSPackAddrSetReq(BPSCmdAddrSetReq * req, BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSPackAddrSetRsp construct packet of 'set the BPS address' response
  * @Param rsp the response parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BPS_UINT16 BPSPackAddrSetRsp(BPSCmdAddrSetRsp * rsp, BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSParseAddrSetReq parse packet of 'set the BPS address' request
  * @Param req the request data struct to store the message
  * @Param buf the buffer stored the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BPS_UINT16 BPSParseAddrSetReq(BPSCmdAddrSetReq * req, const BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSParseAddrSetRsp parse packet of 'set the BPS address' response
  * @Param rsp the response data struct to store the message
  * @Param buf the buffer to store the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BPS_UINT16 BPSParseAddrSetRsp(BPSCmdAddrSetRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size);

#ifdef BPS_MEM_DYN
    #define BPSParseAddrSetReqDyn     BPSParseAddrSetReq
    #define BPSParseAddrSetRspDyn     BPSParseAddrSetRsp
    #define BPSFreeMemAddrSetReq(x)     
    #define BPSFreeMemAddrSetRsp(x)     
#endif

#endif

#endif

