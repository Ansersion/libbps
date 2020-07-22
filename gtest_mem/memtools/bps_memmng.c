//   Copyright 2020 Ansersion
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.
//

#include <bps_memmng.h>
#include <stdlib.h>
#include <stdio.h>

MallocHookPtr mallocHook = BPS_NULL;
FreeHookPtr freeHook = BPS_NULL;

void set_malloc_hook(MallocHookPtr p)
{
    mallocHook = p;
}

void set_free_hook(FreeHookPtr p)
{
    freeHook = p;
}

void* malloc_bps_test(size_t size, const char *file, int line, const char *func)
{

    void *p = malloc(size);
    printf ("Allocated = %s, %i, %s, %p[%li]\n", file, line, func, p, size);

    /*Link List functionality goes in here*/
    if(BPS_NULL != mallocHook) {
        mallocHook(p);
    }

    return p;
}

void free_bps_test(void * ptr, const char *file, int line, const char *func)
{

    printf ("Free = %s, %i, %s, %p\n", file, line, func, ptr);
    free(ptr);

    /*Link List functionality goes in here*/
    if(BPS_NULL != freeHook) {
        freeHook(ptr);
    }
}
