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
/// @file   bps_cmd_update_checksum.h
/// @brief  definations of functions and variable types for command 'check the update firmware'
/// 
/// @version    0.1
/// @author     Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BPS_CMD_UPDATE_CHECKSUM_H
#define __BPS_CMD_UPDATE_CHECKSUM_H

#include <bps_public.h>

#if (BPS_CMD_SET == BPS_CMD_SET_B || BPS_CMD_SET == BPS_CMD_SET_T || BPS_CMD_SET == BPS_CMD_SET_C)

#include <bps_cwords.h>

#define SECURITY_WORD_UPDATE_CHKSUM     0xCBBC


typedef enum ReqTypeUpdateChecksum {
    RT_UPDATE_CHECKSUM_AUTO = 0,
    RT_UPDATE_CHECKSUM_GUIDE,
} ReqTypeUpdateChecksum;

typedef struct BPSCmdUpdateChecksumReq {
    BPS_UINT8 mode;
    BPS_UINT32 len;
    BPS_UINT32 chksum;
    BPS_UINT32 addr;
} BPSCmdUpdateChecksumReq;

typedef struct BPSCmdUpdateChecksumRsp {
    BPS_UINT8 retCode;
} BPSCmdUpdateChecksumRsp;

/** 
  * @Brief BPSPackUpdateChecksumReq construct packet of 'check the update firmware' request
  * @Param req the request parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BPS_UINT16 BPSPackUpdateChecksumReq(BPSCmdUpdateChecksumReq * req, BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSPackUpdateChecksumRsp construct packet of 'check the update firmware' response
  * @Param rsp the response parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
EXPORT_API BPS_UINT16 BPSPackUpdateChecksumRsp(BPSCmdUpdateChecksumRsp * rsp, BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSParseUpdateChecksumReq parse packet of 'check the update firmware' request
  * @Param req the request data struct to store the message
  * @Param buf the buffer stored the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BPS_UINT16 BPSParseUpdateChecksumReq(BPSCmdUpdateChecksumReq * req, const BPS_UINT8 * buf, BPS_WORD size);

/** 
  * @Brief BPSParseUpdateChecksumRsp parse packet of 'check the update firmware' response
  * @Param rsp the response data struct to store the message
  * @Param buf the buffer to store the message(point at the commond word position+1)
  * @Param size the buffer size
  * @return the number of bytes which the function handled, 0 means parsing failed/none
 */
EXPORT_API BPS_UINT16 BPSParseUpdateChecksumRsp(BPSCmdUpdateChecksumRsp * rsp, const BPS_UINT8 * buf, BPS_WORD size);

#ifdef BPS_MEM_DYN
    #define BPSParseUpdateChecksumReqDyn     BPSParseUpdateChecksumReq
    #define BPSParseUpdateChecksumRspDyn     BPSParseUpdateChecksumRsp
    #define BPSFreeMemUpdateChecksumReq(x)     
    #define BPSFreeMemUpdateChecksumRsp(x)     
#endif

#endif

#endif

