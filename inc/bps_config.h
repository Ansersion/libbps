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

#ifndef __BPS_CONFIG_H
#define __BPS_CONFIG_H


#define BPS_NULL 	0
#define BPS_INLINE 	extern inline

/** @Brief: BPS command set */
#define BPS_CMD_SET_B   1
#define BPS_CMD_SET_T   2
#define BPS_CMD_SET_C   3

#ifdef WIN32
#define EXPORT_API __declspec(dllexport) 
#else
#define EXPORT_API
#endif

/***************************************************************************************************************
*** #define BPS_CPU64/BPS_CPU32/BPS_CPU16/BPS_CPU8, MUST BE DEFINED BY YOUR OWN
***************************************************************************************************************/

/** 
  * @Brief: BPS_CPU64/32/16/8 uncomment one of the following line to indicate the CPU type.
 */
// #define BPS_CPU_64
// #define BPS_CPU_32
// #define BPS_CPU_16
// #define BPS_CPU_8

/** 
  * @Brief: BPS_MEM_DYN for system that can alloc memory dynamically(malloc/free)
  * it will enable to compile functions 'ParseXXXReqDyn/ParseXXXRspDyn', 
  * which are more efficient for memory usage.
 */
// #define BPS_MEM_DYN

/** 
  * @Brief: BPS_CMD_SET define the command set for BPS_CMD_SET_B/BPS_CMD_SET_T/BPS_CMD_SET_C    
 */
#define BPS_CMD_SET    BPS_CMD_SET_B

/** 
  * @Brief: BPS_USE_STD define this macro to use standard c library, otherwise we will use the ones from BPS
 */
#define BPS_USE_STD


/** 
  * @Brief: BPCPUXX define determine the cpu type
  * @Note: Must define one of "BPS_CPU64/BPS_CPU32/BPS_CPU16/BPS_CPU8" to match your cpu, NO DEFAULT VALUE
 */
#ifdef BPS_CPU64
	typedef unsigned char BPS_UINT8;
	typedef char BPS_INT8;
	typedef unsigned short BPS_UINT16;
	typedef short BPS_INT16;
	typedef unsigned int BPS_UINT32;
	typedef int BPS_INT32;
	typedef unsigned long long BPS_UINT64;
	typedef long long BPS_INT64;
	typedef float BPS_FLOAT;
	typedef BPS_UINT64 BPS_WORD;
#elif defined BPS_CPU32
	typedef unsigned char BPS_UINT8;
	typedef char BPS_INT8;
	typedef unsigned short BPS_UINT16;
	typedef short BPS_INT16;
	typedef unsigned int BPS_UINT32;
	typedef int BPS_INT32;
	typedef float BPS_FLOAT;
	typedef BPS_UINT32 BPS_WORD;

#elif defined BPS_CPU16
	typedef unsigned char BPS_UINT8;
	typedef char BPS_INT8;
	typedef unsigned short BPS_UINT16;
	typedef short BPS_INT16;
	typedef unsigned long BPS_UINT32;
	typedef long BPS_INT32;
	typedef float BPS_FLOAT;
	typedef BPS_UINT16 BPS_WORD;

#elif defined BPS_CPU8
	typedef unsigned char BPS_UINT8;
	typedef char BPS_INT8;
	typedef unsigned short BPS_UINT16;
	typedef short BPS_INT16;
	typedef unsigned long BPS_UINT32;
	typedef long BPS_INT32;
	typedef float BPS_FLOAT;
	typedef BPS_UINT8 BPS_WORD;

#else
#error Please define your cpu macro first: BPS_CPU64/BPS_CPU32/BPS_CPU16/BPS_CPU8

#endif

#define BPS_BOOL        BPS_UINT8
#define BPS_TRUE        1
#define BPS_FALSE       0


#endif

