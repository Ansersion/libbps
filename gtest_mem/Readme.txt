Test project for testing libbps memory management.
It uses the gtest framework to check libbps APIs.


Usage:
1. cp memtools/bps_memmng.h ../inc
2. cp memtools/bps_memmng.c ../src
3. Make libbps.a with macros 'BPS_CMD_SET=BPS_CMD_SET_C' and 'BPS_MEM_DYN' in 'bps_config.h'
4. Change the gtest directory in the Makefile
5. Compile(make) it
