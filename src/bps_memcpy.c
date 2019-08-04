///////////////////////////////////////////////////////////////////////////////
/// Copyright 2017 Ansersion
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
/// @file 	bps_memcpy.c
/// @brief 	function "bps_memcpy" source file
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bps_memcpy.h>
// #include <stdio.h>

#ifndef BPS_USE_STD
void * memcpy_bps(void * dst, const void * src, BPS_WORD count)
{
	BPS_WORD nword, npad;
	BPS_WORD *s, *d;
	BPS_UINT8 *s8, *d8;

	if (dst == BPS_NULL || src == BPS_NULL)  {
		return BPS_NULL;  
	}

	if(dst == src) {
		return dst;
	}
    if(0 == count) {
        return dst;
    }

	nword = count/sizeof(dst);
	npad = count%sizeof(dst);

	s = (BPS_WORD *)src;  
	d = (BPS_WORD *)dst;  

	while(nword--)  
	{
		*d++ = *s++;  
		// printf("%x ", *(d-1));
	}
	// printf("\n");

	s8 = (BPS_UINT8 *)s;
	d8 = (BPS_UINT8 *)d;
	while(npad--)  
	{
		*d8++ = *s8++;  
		// printf("%x ", *(d8-1));
	}
	// printf("\n");

	return dst;  
}
#endif
