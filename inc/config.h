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
/// @file 	config.h
/// @brief 	configurations for different platforms
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __CONFIG_H
#define __CONFIG_H


#define BP_NULL 	0
#define BP_INLINE 	extern inline

#ifdef WIN32
#define EXPORT_API __declspec(dllexport) 
#else
#define EXPORT_API
#endif

/***************************************************************************************************************
*** #define BP_CPU64/BP_CPU32/BP_CPU16/BP_CPU8, MUST BE DEFINED BY YOUR OWN
*** #define BP_MEM_DYN, for system that can malloc dynamically
***************************************************************************************************************/


/** 
  * @Brief: BPCPUXX define determine the cpu type
  * @Note: Must define one of "BP_CPU64/BP_CPU32/BP_CPU16/BP_CPU8" to match your cpu, NO DEFAULT VALUE
 */

#ifdef BP_CPU64
	#define BP_UINT8 	unsigned char
	#define BP_INT8 	char
	#define BP_UINT16 	unsigned short
	#define BP_INT16 	short
	#define BP_UINT32 	unsigned int
	#define BP_INT32 	int
	#define BP_UINT64 	unsigned long long
	#define BP_INT64 	long long
	#define BP_FLOAT 	float
	#define BP_WORD 	BP_UINT64
#elif defined BP_CPU32
	#define BP_UINT8 	unsigned char
	#define BP_INT8 	char
	#define BP_UINT16 	unsigned short
	#define BP_INT16 	short
	#define BP_UINT32 	unsigned int
	#define BP_INT32 	int
	#define BP_FLOAT 	float
	#define BP_WORD 	BP_UINT32

#elif defined BP_CPU16
	#define BP_UINT8 	unsigned char
	#define BP_INT8 	char
	#define BP_UINT16 	unsigned short
	#define BP_INT16 	short
	#define BP_UINT32 	unsigned long
	#define BP_INT32 	long
	#define BP_FLOAT 	float
	#define BP_WORD 	BP_UINT16

#elif defined BP_CPU8
	#define BP_UINT8 	unsigned char
	#define BP_INT8 	char
	#define BP_UINT16 	unsigned short
	#define BP_INT16 	short
	#define BP_UINT32 	unsigned long
	#define BP_INT32 	long
	#define BP_FLOAT 	float
	#define BP_WORD 	BP_UINT8

#else
#error Please define your cpu macro first: BP_CPU64/BP_CPU32/BP_CPU16/BP_CPU8

#endif

/** 
  * @Brief: BP_MEM_DYN for system that can alloc memory dynamically(malloc/free)
  * it will enable to compile functions 'ParseXXXReqDyn/ParseXXXRspDyn', 
  * which are more efficient for memory usage.
 */
// #define BP_MEM_DYN

#endif

