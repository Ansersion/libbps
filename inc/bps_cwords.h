///////////////////////////////////////////////////////////////////////////////
/// Copyright 2019-2020 Ansersion
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
/// @file   bps_cwords.h
/// @brief  macros of command words
/// 
/// @version    0.1
/// @author     Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#ifndef __BPS_CWORDS_H
#define __BPS_CWORDS_H

/** 
  command set B
 */
#define CMD_COMM_TEST_WORD_REQ  0x00
#define CMD_COMM_TEST_WORD_RSP  (CMD_COMM_TEST_WORD_REQ+1)

#define CMD_HD_INFO_WORD_REQ  0x02
#define CMD_HD_INFO_WORD_RSP  (CMD_HD_INFO_WORD_REQ+1)

#define CMD_BAUDRATE_SET_WORD_REQ  0x04
#define CMD_BAUDRATE_SET_WORD_RSP  (CMD_BAUDRATE_SET_WORD_REQ+1)

#define CMD_LAUNCH_UPDATE_WORD_REQ  0x06
#define CMD_LAUNCH_UPDATE_WORD_RSP  (CMD_LAUNCH_UPDATE_WORD_REQ+1)

#define CMD_CLEAR_SPACE_WORD_REQ  0x08
#define CMD_CLEAR_SPACE_WORD_RSP  (CMD_CLEAR_SPACE_WORD_REQ+1)

#define CMD_WRITE_FRMW_WORD_REQ  0x0A
#define CMD_WRITE_FRMW_WORD_RSP  (CMD_WRITE_FRMW_WORD_REQ+1)

#define CMD_UPDATE_CHECKSUM_WORD_REQ  0x0C
#define CMD_UPDATE_CHECKSUM_WORD_RSP  (CMD_UPDATE_CHECKSUM_WORD_REQ+1)

#define CMD_RESET_WORD_REQ  0x0E
#define CMD_RESET_WORD_RSP  (CMD_RESET_WORD_REQ+1)

#define CMD_FAC_RESTORE_WORD_REQ  0x10
#define CMD_FAC_RESTORE_WORD_RSP  (CMD_FAC_RESTORE_WORD_REQ+1)

#define CMD_ADDR_SET_WORD_REQ  0x12
#define CMD_ADDR_SET_WORD_RSP  (CMD_ADDR_SET_WORD_REQ+1)

/** 
  command set T
 */
#define CMD_TRANS_BYTES_WORD_REQ  0x40
#define CMD_TRANS_BYTES_WORD_RSP  (CMD_TRANS_BYTES_WORD_REQ+1)

/** 
  command set C
 */
#define CMD_GET_SIGTAB_WORD_REQ  0x80
#define CMD_GET_SIGTAB_WORD_RSP  (CMD_GET_SIGTAB_WORD_REQ+1)

#define CMD_REPORT_SIG_WORD_REQ  0x82
#define CMD_REPORT_SIG_WORD_RSP  (CMD_REPORT_SIG_WORD_REQ+1)

#define CMD_POST_WORD_REQ  0x84
#define CMD_POST_WORD_RSP  (CMD_POST_WORD_REQ+1)

#define CMD_GET_SIG_WORD_REQ  0x86
#define CMD_GET_SIG_WORD_RSP  (CMD_GET_SIG_WORD_REQ+1)


/** 
  commands O
 */
#define CMD_SYSTEM_PARA_WORD_REQ  0xEE
#define CMD_SYSTEM_PARA_WORD_RSP  (CMD_SYSTEM_PARA_WORD_REQ+1)


#endif

