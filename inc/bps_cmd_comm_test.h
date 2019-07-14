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
/// @file   bps_cmd_comm_test.h
/// @brief  definations of functions and variable types for command 'communication test'
/// 
/// @version    0.1
/// @author     Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BPS_CMD_COMM_TEST_H
#define __BPS_CMD_COMM_TEST_H

#include <bps_public.h>
#include <bps_cwords.h>

#define CMD_COMM_TEST_WORD_REQ  0x00
#define CMD_COMM_TEST_WORD_RSP  0x01

typedef BPSCmdCommTestReq {
    BP_UINT8 recv;
} BPSCmdCommTestReq;

typedef BPSCmdCommTestRsp {
    BP_UINT8 recv;
} BPSCmdCommTestRsp;

/** 
  * @Brief BPSPackCommTestReq construct packet of 'communication test' request
  * @Param req the request parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
BP_UINT16 BPSPackCommTestReq(BPSCmdCommTestReq * req, BP_UINT8 * buf, BP_WORD size);

/** 
  * @Brief BPSPackCommTestRsp construct packet of 'communication test' response
  * @Param rsp the response parameter
  * @Param buf the buffer to store the message(point at the commond word position)
  * @Param size the buffer size
  * @return the number of bytes which the function handled
 */
BP_UINT16 BPSPackCommTestRsp(BPSCmdCommTestRsp * rsp, BP_UINT8 * buf, BP_WORD size);
BP_UINT16 BPSParseCommTestReq(BPSCmdCommTestReq * req, BP_UINT8 * buf, BP_WORD size);
BP_UINT16 BPSParseCommTestRsp(BPSCmdCommTestRsp * rsp, BP_UINT8 * buf, BP_WORD size);

#ifdef BP_MEM_DYN
    #define ParseCommTestReqDyn     ParseCommTestReq
    #define ParseCommTestRspDyn     ParseCommTestRsp
#endif

#endif

