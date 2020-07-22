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
/// @file   bps_memmng.h
/// @brief  memory management
/// 
/// @version    0.1
/// @author     Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BPS_MEMMNG_H
#define __BPS_MEMMNG_H

#include <bps_config.h>
#include <stdlib.h>

#ifdef BPS_MEM_DYN

/** 
  * @Brief memory management APIs, you can customize this based on different OS
 */

#define malloc_bps(X) malloc_bps_test( X, __FILE__, __LINE__, __FUNCTION__)
#define free_bps(X) free_bps_test( X, __FILE__, __LINE__, __FUNCTION__)

typedef void(*MallocHookPtr)(void *);
typedef void(*FreeHookPtr)(void *);

void* malloc_bps_test(size_t size, const char *file, int line, const char *func);
void free_bps_test(void * ptr, const char *file, int line, const char *func);
void set_malloc_hook(MallocHookPtr p);
void set_free_hook(FreeHookPtr p);

#endif

#endif

