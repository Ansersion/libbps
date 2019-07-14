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
/// @file 	bps_public.h
/// @brief 	public tool functions header file
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BPS_PUBLIC_H
#define __BPS_PUBLIC_H

#include <config.h>

#define BPS_HEADER 		0xBBCC
#define BPS_HEADER_SIZE 		2
#define BPS_HEADER_POSITION 		0

#define BPS_VERSION 	0
#define BPS_VERSION_SIZE 	1
#define BPS_VERSION_POSITION 	(BPS_HEADER_POSITION + BPS_HEADER_SIZE)

#define BPS_ADDR_MCU_DEFAULT 	0
#define BPS_ADDR_SIZE 	1
#define BPS_ADDR_POSITION 	(BPS_VERSION_POSITION + BPS_VERSION_SIZE)

#define BPS_REMAIN_LEN_SIZE 	2
#define BPS_REMAIN_LEN_POSITION 	(BPS_ADDR_POSITION + BPS_ADDR_SIZE)

#define BPS_CHECKSUM_SIZE 	1

/** 
  * @Brief IsBPSHeader2 check b1==0xBB and b2==0xCC
  * @Param b1   first byte
  * @Param b2 	second byte
  * @return Success     somegthing not 0
  *         Failed      0
 */
BP_UINT8 IsBPSHeader2(BP_UINT8 b1, BP_UINT8 b2);

/** 
  * @Brief IsBPSHeader check buf[0]==0xBB and buf[1]==0xCC
  * @Param buf   the message buffer
  * @return Success     somegthing not 0
  *         Failed      0
 */
BP_UINT8 IsBPSHeader(BP_UINT8 * buf);

/** 
  * @Brief IsBPSVersionCompat check the BP-S version compatible
  * @Param buf   the version
  * @return Success     somegthing not 0 when the 'version' is smaller than BPS_VERSION
  *         Failed      0
 */
BP_UINT8 IsBPSVersionCompat(BP_UINT8 version);

/** 
  * @Brief GetBPSSenderAddr get the sender address
  * @Param buf   the address
  * @return the address of sender(from 0-15)
 */
BP_UINT8 GetBPSSenderAddr(BP_UINT8 addr);

/** 
  * @Brief GetBPSRecverAddr get the receiver address
  * @Param buf   the address
  * @return the address of receiver(from 0-15)
 */
BP_UINT8 GetBPSRecverAddr(BP_UINT8 addr);

/** 
  * @Brief GetBPSRemainLen get the remain length
  * @Param buf   the message buffer
  * @return the length, or '0' when something wrong
 */
BP_UINT16 GetBPSRemainLen(BP_UINT8 * buf);

/** 
  * @Brief GetBPSRemainLen2 get the remain length(safely)
  * @Param buf   the message buffer
  * @Param size  the buffer size
  * @return the length, or '0' when something wrong
 */
BP_UINT16 GetBPSRemainLen2(BP_UINT8 * buf, BP_WORD size);

/** 
  * @Brief IsBPSChksumOK check the checksum of the message
  * @Param buf   the message buffer
  * @return Success     somegthing not 0 when
  *         Failed      0
 */
BP_UINT8 IsBPSChksumOK(BP_UINT8 * buf);

/** 
  * @Brief IsBPSChksumOK check the checksum of the message(safely)
  * @Param buf   the message buffer
  * @Param size  the buffer size
  * @return Success     somegthing not 0 when
  *         Failed      0
 */
BP_UINT8 IsBPSChksumOK2(BP_UINT8 * buf, BP_WORD size);

/** 
  * @Brief PackBPSHeader to pack the BPS_HEADER into message buffer
  * @Param buf   the message buffer
 */
void PackBPSHeader(BP_UINT8 * buf);

/** 
  * @Brief PackBPSHeader2 to pack the BPS_HEADER into message buffer(safely)
  * @Param buf   the message buffer
  * @Param size  the buffer size
 */
void PackBPSHeader2(BP_UINT8 * buf, BP_WORD size);

/** 
  * @Brief PackBPSVersion to pack the BPS_VERSION into message buffer
  * @Param buf   the message buffer
 */
void PackBPSVersion(BP_UINT8 * buf);

/** 
  * @Brief PackBPSAddr to pack BP-S address
  * @Param buf   the message buffer
  * @Param sender   the sender address(from 0-15)
  * @Param recver  the receiver address(from 0-15)
 */
void PackBPSAddr(BP_UINT8 * buf, BP_UINT8 sender, BP_UINT8 recver);

/** 
  * @Brief PackBPSRemainLen to pack remaining length into message buffer
  * @Param buf   the message buffer
  * @Param len   the remaining length
 */
void PackBPSRemainLen(BP_UINT8 * buf, BP_UINT16 len);

/** 
  * @Brief PackBPSRemainLen to pack remaining length into message buffer(safely)
  * @Param buf   the message buffer
  * @Param len   the remaining length
  * @Param size  the buffer size
 */
void PackBPSRemainLen2(BP_UINT8 * buf, BP_UINT16 len, BP_WORD size);

#endif

