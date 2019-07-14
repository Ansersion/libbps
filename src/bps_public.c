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
/// @file 	bps_public.c
/// @brief 	public tool functions
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bps_public.h>

BP_INLINE BP_UINT8 IsBPSHeader2(BP_UINT8 b1, BP_UINT8 b2)
{
	return 0xBB == b1 && 0xCC == b2;
}

BP_UINT8 IsBPSHeader(BP_UINT8 * buf)
{
	if(BP_NULL == buf) {
		return 0;
	}
	return IsBPSHeader2(buf[0], buf[1]);
}

BP_INLINE BP_UINT8 IsBPSVersionCompat(BP_UINT8 version)
{
	return version <= BPS_VERSION;
}

BP_INLINE BP_UINT8 GetBPSSenderAddr(BP_UINT8 addr)
{
	return (addr >> 4) & 0xF;
}

BP_INLINE BP_UINT8 GetBPSRecverAddr(BP_UINT8 addr)
{
	return addr & 0xF;
}

BP_UINT16 GetBPSRemainLen(BP_UINT8 * buf)
{
	BP_UINT16 ret = 0;
	if(BP_NULL == buf) {
		return ret;
	}
	ret = (buf[0] << 8);
	ret += buf[1];

	return ret;
}

BP_UINT16 GetBPSRemainLen2(BP_UINT8 * buf, BP_WORD size)
{
	if(size < BPS_REMAIN_LEN_SIZE) {
		return 0;
	}
	return GetBPSRemainLen(buf);
}

BP_UINT8 IsBPSChksumOK(BP_UINT8 * buf)
{
	BP_UINT16 len;
	BP_UINT8 * tmp;
	BP_UINT8 checksum;

	if(BP_NULL == buf) {
		return 0;
	}

	len = GetBPSRemainLen(buf + BPS_REMAIN_LEN_POSITION);
	len += BPS_VERSION_SIZE;
	len += BPS_ADDR_SIZE;
	len += BPS_REMAIN_LEN_SIZE;

	tmp = buf + BPS_VERSION_POSITION;
	checksum = 0;
	while(len--) {
		checksum += *tmp++;
	}

	return checksum == *tmp;
}

BP_UINT8 IsBPSChksumOK2(BP_UINT8 * buf, BP_WORD size)
{
	BP_UINT16 len;
	BP_UINT8 * tmp;
	BP_UINT8 checksum;

	if(BP_NULL == buf) {
		return 0;
	}

	if(size < BPS_REMAIN_LEN_POSITION) {
		return 0;
	}
	len = GetBPSRemainLen2(buf + BPS_REMAIN_LEN_POSITION, size - BPS_REMAIN_LEN_POSITION);
	len += BPS_VERSION_SIZE;
	len += BPS_ADDR_SIZE;
	len += BPS_REMAIN_LEN_SIZE;
	if(len + BPS_HEADER_SIZE + BPS_CHECKSUM_SIZE < size) {
		return 0;
	}

	tmp = buf + BPS_VERSION_POSITION;
	checksum = 0;
	while(len--) {
		checksum += *tmp++;
	}

	return checksum == *tmp;
}

void PackBPSHeader(BP_UINT8 * buf)
{
	if(BP_NULL == buf) {
		return;
	}
	buf[0] = 0xBB;
	buf[1] = 0xCC;
}

void PackBPSHeader2(BP_UINT8 * buf, BP_WORD size)
{
	if(size < BPS_HEADER_SIZE) {
		return;
	}
	PackBPSHeader(buf);
}

BP_INLINE void PackBPSVersion(BP_UINT8 * buf)
{
	*buf = BPS_VERSION;
}

void PackBPSAddr(BP_UINT8 * buf, BP_UINT8 sender, BP_UINT8 recver)
{
	if(BP_NULL == buf) {
		return;
	}
	*buf = ((sender << 4) & 0xF0) | (recver & 0x0F);
}

void PackBPSRemainLen(BP_UINT8 * buf, BP_UINT16 len)
{
	if(BP_NULL == buf) {
		return;
	}
	buf[0] = (len >> 8) & 0xFF;
	buf[1] = (len & 0xFF);
}

void PackBPSRemainLen2(BP_UINT8 * buf, BP_UINT16 len, BP_WORD size)
{
	if(size < BPS_REMAIN_LEN_SIZE) {
		return;
	}
	PackBPSRemainLen(buf, len);
}
