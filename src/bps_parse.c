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
/// @file 	bps_parse.c
/// @brief 	APIs for parsing BPS packets
/// 
/// @version 	0.1
/// @author 	Ansersion
/// 
/// 
///////////////////////////////////////////////////////////////////////////////

#include <bps_parse.h>

BPSPacketData * BPSParseNoCheck(BPS_UINT8 * buf, BPSPacketData * pd)
{
    const BPS_UINT8 * buf_tmp;
    BPS_UINT16 rmn_len = 0;
    BPS_UINT16 parse_ret = 0;

    /* check the input parameters */
    if(BPS_NULL == buf || BPS_NULL == pd) {
        return BPS_NULL;
    } 
    buf_tmp = buf + BPS_REMAIN_LEN_POSITION;

    /* check remaining length at least is 2 bytes for "command word" and "checksum" */
    buf_tmp = BPS_GetNet16(buf_tmp, &rmn_len);
    if(rmn_len < BPS_CMD_WORD_SIZE) {
        return BPS_NULL;
    }

    /* get the command word and switch to the parsing routine */
    pd->cmdWord = *buf_tmp++;
    /* the following parsing routing will not parse command and the checksum*/
    rmn_len -= BPS_CMD_WORD_SIZE;
    switch(pd->cmdWord) {
#if (BPS_CMD_SET == BPS_CMD_SET_B || BPS_CMD_SET == BPS_CMD_SET_T || BPS_CMD_SET == BPS_CMD_SET_C)
        case CMD_COMM_TEST_WORD_REQ:
            /* parse the command "commnication test" request. */
            parse_ret = BPSParseCommTestReq(&(pd->pu.commTestReq), buf_tmp, rmn_len);
            /* because the function will never fail and return 0, so set 'parse_ret = 1' to make the error check to pass through*/
            parse_ret = 1;
            break;
        case CMD_COMM_TEST_WORD_RSP:
            /* parse the command "commnication test" response, */
            parse_ret = BPSParseCommTestRsp(&(pd->pu.commTestRsp), buf_tmp, rmn_len);
            /* because the function will never fail and return 0, so set 'parse_ret = 1' to make the error check to pass through*/
            parse_ret = 1;
            break;
        case CMD_HD_INFO_WORD_REQ:
            /* parse the command "query hardware info" request, */
            parse_ret = BPSParseHDInfoReq(&(pd->pu.hdInfoReq), buf_tmp, rmn_len);
            /* because the function will never fail and return 0, so set 'parse_ret = 1' to make the error check to pass through*/
            parse_ret = 1;
            break;
        case CMD_HD_INFO_WORD_RSP:
            /* parse the command "query hardware info" response, */
            parse_ret = BPSParseHDInfoRsp(&(pd->pu.hdInfoRsp), buf_tmp, rmn_len);
            break;
        case CMD_BAUDRATE_SET_WORD_REQ:
            /* parse the command "set/query baudrate" request, */
            parse_ret = BPSParseBaudrateSetReq(&(pd->pu.baudrateSetReq), buf_tmp, rmn_len);
            break;
        case CMD_BAUDRATE_SET_WORD_RSP:
            /* parse the command "set/query baudrate" response, */
            parse_ret = BPSParseBaudrateSetRsp(&(pd->pu.baudrateSetRsp), buf_tmp, rmn_len);
            break;
        case CMD_LAUNCH_UPDATE_WORD_REQ:
            /* parse the command "launching update" request, */
            parse_ret = BPSParseLnchUpdateReq(&(pd->pu.lnchUpdateReq), buf_tmp, rmn_len);
            break;
        case CMD_LAUNCH_UPDATE_WORD_RSP:
            /* parse the command "launching update" response, */
            parse_ret = BPSParseLnchUpdateRsp(&(pd->pu.lnchUpdateRsp), buf_tmp, rmn_len);
            break;
        case CMD_CLEAR_SPACE_WORD_REQ:
            /* parse the command "clear space" request, */
            parse_ret = BPSParseClearSpaceReq(&(pd->pu.clearSpaceReq), buf_tmp, rmn_len);
            break;
        case CMD_CLEAR_SPACE_WORD_RSP:
            /* parse the command "clear space" response, */
            parse_ret = BPSParseClearSpaceRsp(&(pd->pu.clearSpaceRsp), buf_tmp, rmn_len);
            break;
        case CMD_WRITE_FRMW_WORD_REQ:
            /* parse the command "write update firmware" request, */
            parse_ret = BPSParseWriteFrmwReq(&(pd->pu.writeFrmwReq), buf_tmp, rmn_len);
            break;
        case CMD_WRITE_FRMW_WORD_RSP:
            /* parse the command "write update firmware" response, */
            parse_ret = BPSParseWriteFrmwRsp(&(pd->pu.writeFrmwRsp), buf_tmp, rmn_len);
            break;
        case CMD_UPDATE_CHECKSUM_WORD_REQ:
            /* parse the command "check the update firmware" request, */
            parse_ret = BPSParseUpdateChecksumReq(&(pd->pu.updateChksumReq), buf_tmp, rmn_len);
            break;
        case CMD_UPDATE_CHECKSUM_WORD_RSP:
            /* parse the command "check the update firmware" response, */
            parse_ret = BPSParseUpdateChecksumRsp(&(pd->pu.updateChksumRsp), buf_tmp, rmn_len);
            break;
        case CMD_RESET_WORD_REQ:
            /* parse the command "reset the system" request, */
            parse_ret = BPSParseResetReq(&(pd->pu.resetReq), buf_tmp, rmn_len);
            break;
        case CMD_RESET_WORD_RSP:
            /* parse the command "reset the system" response, */
            parse_ret = BPSParseResetRsp(&(pd->pu.resetRsp), buf_tmp, rmn_len);
            break;
        case CMD_FAC_RESTORE_WORD_REQ:
            /* parse the command "restore to factory settings" request, */
            parse_ret = BPSParseFacRestoreReq(&(pd->pu.facRestoreReq), buf_tmp, rmn_len);
            break;
        case CMD_FAC_RESTORE_WORD_RSP:
            /* parse the command "restore to factory settings" response, */
            parse_ret = BPSParseFacRestoreRsp(&(pd->pu.facRestoreRsp), buf_tmp, rmn_len);
            break;
        case CMD_ADDR_SET_WORD_REQ:
            /* parse the command "set the BPS address" request, */
            parse_ret = BPSParseAddrSetReq(&(pd->pu.addrSetReq), buf_tmp, rmn_len);
            break;
        case CMD_ADDR_SET_WORD_RSP:
            /* parse the command "set the BPS address" response, */
            parse_ret = BPSParseAddrSetRsp(&(pd->pu.addrSetRsp), buf_tmp, rmn_len);
            break;
#endif
        // case CMD_PING_WORD_REQ:
        //     /* parse the command ping request, */
        //     parse_ret = BPSParsePingReq(&(pd->pu.pingReq), buf_tmp, rmn_len);
        //     break;
        // case CMD_PING_WORD_RSP:
        //     /* parse the command ping response, */
        //     parse_ret = BPSParsePingRsp(&(pd->pu.pingRsp), buf_tmp, rmn_len);
        //     break;
        // case CMD_OPEN_NETSET_WORD_REQ:
        //     /* parse the command open net setting request, */
        //     parse_ret = BPSParseOpenNetsetReq(&(pd->pu.openNetsetReq), buf_tmp, rmn_len);
        //     break;
        // case CMD_OPEN_NETSET_WORD_RSP:
        //     /* parse the command open net setting response, */
        //     parse_ret = BPSParseOpenNetsetRsp(&(pd->pu.openNetsetRsp), buf_tmp, rmn_len);
        //     break;
        // case CMD_CONFIG_NETSET_WORD_REQ:
        //     /* parse the command configure net setting request, */
        //     parse_ret = BPSParseConfigNetsetReq(&(pd->pu.configNetsetReq), buf_tmp, rmn_len);
        //     /* because the function will never fail and return 0, so set 'parse_ret = 1' to make the error check to pass through*/
        //     parse_ret = 1;
        //     break;
        // case CMD_CONFIG_NETSET_WORD_RSP:
        //     /* parse the command configure net setting response, */
        //     parse_ret = BPSParseConfigNetsetRsp(&(pd->pu.configNetsetRsp), buf_tmp, rmn_len);
        //     break;
        // case CMD_NETSTATE_QUERY_WORD_REQ:
        //     /* parse the command query net state request, */
        //     parse_ret = BPSParseNetstateQueryReq(&(pd->pu.netstateQueryReq), buf_tmp, rmn_len);
        //     /* because the function will never fail and return 0, so set 'parse_ret = 1' to make the error check to pass through*/
        //     parse_ret = 1;
        //     break;
        // case CMD_NETSTATE_QUERY_WORD_RSP:
        //     /* parse the command query net state response, */
        //     parse_ret = BPSParseNetstateQueryRsp(&(pd->pu.netstateQueryRsp), buf_tmp, rmn_len);
        //     break;
        // case CMD_BAUDRATE_SET_WORD_REQ:
        //     /* parse the command 'set/query serial baudrate' request, */
        //     parse_ret = BPSParseBaudrateSetReq(&(pd->pu.baudrateSetReq), buf_tmp, rmn_len);
        //     /* because the function will never fail and return 0, so set 'parse_ret = 1' to make the error check to pass through*/
        //     parse_ret = 1;
        //     break;
        // case CMD_BAUDRATE_SET_WORD_RSP:
        //     /* parse the command 'set/query serial baudrate' response, */
        //     parse_ret = BPSParseBaudrateSetRsp(&(pd->pu.baudrateSetRsp), buf_tmp, rmn_len);
        //     break;
        // case CMD_GET_SIGTAB_WORD_REQ:
        //     /* parse the command get signal table request, */
        //     parse_ret = BPSParseGetSigtabReq(&(pd->pu.getSigtabReq), buf_tmp, rmn_len);
        //     /* because the function will never fail and return 0, so set 'parse_ret = 1' to make the error check to pass through*/
        //     parse_ret = 1;
        //     break;
        // case CMD_GET_SIGTAB_WORD_RSP:
        //     /* parse the command get signal table response, */
        //     parse_ret = BPSParseGetSigtabRsp(&(pd->pu.getSigtabRsp), buf_tmp, rmn_len);
        //     break;
        // case CMD_REPORT_SIG_WORD_REQ:
        //     /* parse the command report signal values request, */
        //     parse_ret = BPSParseReportSigReq(&(pd->pu.reportSigReq), buf_tmp, rmn_len);
        //     break;
        // case CMD_REPORT_SIG_WORD_RSP:
        //     /* parse the command report signal values response, */
        //     parse_ret = BPSParseReportSigRsp(&(pd->pu.reportSigRsp), buf_tmp, rmn_len);
        //     break;
        // case CMD_POST_WORD_REQ:
        //     /* parse the command post signal request, */
        //     parse_ret = BPSParsePostReq(&(pd->pu.postReq), buf_tmp, rmn_len);
        //     break;
        // case CMD_POST_WORD_RSP:
        //     /* parse the command post signal response, */
        //     parse_ret = BPSParsePostRsp(&(pd->pu.postRsp), buf_tmp, rmn_len);
        //     break;
        // case CMD_GET_SIG_WORD_REQ:
        //     /* parse the command get signal values request, */
        //     parse_ret = BPSParseGetSigReq(&(pd->pu.getSigReq), buf_tmp, rmn_len);
        //     break;
        // case CMD_GET_SIG_WORD_RSP:
        //     /* parse the command get signal values response, */
        //     parse_ret = BPSParseGetSigRsp(&(pd->pu.getSigRsp), buf_tmp, rmn_len);
        //     break;
        // case CMD_SYSTEM_PARA_WORD_REQ: // 0xEE
        //     /* parse the command configure system parameter request, */
        //     parse_ret = BPSParseSystemParaReq(&(pd->pu.sysParaReq), buf_tmp, rmn_len);
        //     break;
        // case CMD_SYSTEM_PARA_WORD_RSP: // 0xEF
        //     /* parse the command configure system parameter response, */
        //     parse_ret = BPSParseSystemParaRsp(&(pd->pu.sysParaRsp), buf_tmp, rmn_len);
        //     break;
        // case CMD_TRANS_BYTES_WORD_REQ: // 0xF8
        //     /* parse the command 'transmit bytes' request, */
        //     parse_ret = BPSParseTransBytesReq(&(pd->pu.transBytesReq), buf_tmp, rmn_len);
        //     break;
        // case CMD_TRANS_BYTES_WORD_RSP: // 0xF9
        //     /* parse the command 'transmit bytes' response, */
        //     parse_ret = BPSParseTransBytesRsp(&(pd->pu.transBytesRsp), buf_tmp, rmn_len);
        //     break;
        default:
            /* unknown command word */
            parse_ret = 0;
    }

    /* error check */
    if(!parse_ret) {
        return BPS_NULL;
    }

    return pd;

}
