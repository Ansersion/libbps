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

#include <bps_cmd_comm_test.h>
#include <bps_cmd_hd_info.h>
#include <bps_cmd_ping.h>
#include <bps_cmd_open_netset.h>
#include <bps_cmd_config_netset.h>
#include <bps_cmd_netstate_query.h>
#include <bps_cmd_get_sigtab.h>
#include <bps_cmd_report_sig.h>
#include <bps_cmd_post.h>
#include <bps_cmd_get_sig.h>

BPSPacketData * BPSParseNoCheck(BPS_UINT8 * buf, BPSPacketData * pd)
{
    BPS_UINT8 * buf_tmp;
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
        case CMD_COMM_TEST_WORD_REQ:
            /* parse the command commnication test request. */
            parse_ret = BPSParseCommTestReq(&(pd->pu.commTestReq), buf_tmp, rmn_len);
            /* because the function will never fail and return 0, so set 'parse_ret = 1' to make the error check to pass through*/
            parse_ret = 1;
            break;
        case CMD_COMM_TEST_WORD_RSP:
            /* parse the command commnication test response, */
            parse_ret = BPSParseCommTestRsp(&(pd->pu.commTestRsp), buf_tmp, rmn_len);
            /* because the function will never fail and return 0, so set 'parse_ret = 1' to make the error check to pass through*/
            parse_ret = 1;
            break;
        case CMD_HD_INFO_WORD_REQ:
            /* parse the command query hardware info request, */
            parse_ret = BPSParseHDInfoReq(&(pd->pu.hdInfoReq), buf_tmp, rmn_len);
            /* because the function will never fail and return 0, so set 'parse_ret = 1' to make the error check to pass through*/
            parse_ret = 1;
            break;
        case CMD_HD_INFO_WORD_RSP:
            /* parse the command query hardware info response, */
            parse_ret = BPSParseHDInfoRsp(&(pd->pu.hdInfoRsp), buf_tmp, rmn_len);
            break;
        case CMD_PING_WORD_REQ:
            /* parse the command ping request, */
            parse_ret = BPSParsePingReq(&(pd->pu.pingReq), buf_tmp, rmn_len);
            break;
        case CMD_PING_WORD_RSP:
            /* parse the command ping response, */
            parse_ret = BPSParsePingRsp(&(pd->pu.pingRsp), buf_tmp, rmn_len);
            break;
        case CMD_OPEN_NETSET_WORD_REQ:
            /* parse the command open net setting request, */
            parse_ret = BPSParseOpenNetsetReq(&(pd->pu.openNetsetReq), buf_tmp, rmn_len);
            break;
        case CMD_OPEN_NETSET_WORD_RSP:
            /* parse the command open net setting response, */
            parse_ret = BPSParseOpenNetsetRsp(&(pd->pu.openNetsetRsp), buf_tmp, rmn_len);
            break;
        case CMD_CONFIG_NETSET_WORD_REQ:
            /* parse the command configure net setting request, */
            parse_ret = BPSParseConfigNetsetReq(&(pd->pu.configNetsetReq), buf_tmp, rmn_len);
            /* because the function will never fail and return 0, so set 'parse_ret = 1' to make the error check to pass through*/
            parse_ret = 1;
            break;
        case CMD_CONFIG_NETSET_WORD_RSP:
            /* parse the command configure net setting response, */
            parse_ret = BPSParseConfigNetsetRsp(&(pd->pu.configNetsetRsp), buf_tmp, rmn_len);
            break;
        case CMD_NETSTATE_QUERY_WORD_REQ:
            /* parse the command query net state request, */
            parse_ret = BPSParseNetstateQueryReq(&(pd->pu.netstateQueryReq), buf_tmp, rmn_len);
            /* because the function will never fail and return 0, so set 'parse_ret = 1' to make the error check to pass through*/
            parse_ret = 1;
            break;
        case CMD_NETSTATE_QUERY_WORD_RSP:
            /* parse the command query net state response, */
            parse_ret = BPSParseNetstateQueryRsp(&(pd->pu.netstateQueryRsp), buf_tmp, rmn_len);
            break;
        case CMD_GET_SIGTAB_WORD_REQ:
            /* parse the command get signal table request, */
            parse_ret = BPSParseGetSigtabReq(&(pd->pu.getSigtabReq), buf_tmp, rmn_len);
            /* because the function will never fail and return 0, so set 'parse_ret = 1' to make the error check to pass through*/
            parse_ret = 1;
            break;
        case CMD_GET_SIGTAB_WORD_RSP:
            /* parse the command get signal table response, */
            parse_ret = BPSParseGetSigtabRsp(&(pd->pu.getSigtabRsp), buf_tmp, rmn_len);
            break;
        case CMD_REPORT_SIG_WORD_REQ:
            /* parse the command report signal values request, */
            parse_ret = BPSParseReportSigReq(&(pd->pu.reportSigReq), buf_tmp, rmn_len);
            break;
        case CMD_REPORT_SIG_WORD_RSP:
            /* parse the command report signal values response, */
            parse_ret = BPSParseReportSigRsp(&(pd->pu.reportSigRsp), buf_tmp, rmn_len);
            break;
        case CMD_POST_WORD_REQ:
            /* parse the command post signal request, */
            parse_ret = BPSParsePostReq(&(pd->pu.postReq), buf_tmp, rmn_len);
            break;
        case CMD_POST_WORD_RSP:
            /* parse the command post signal response, */
            parse_ret = BPSParsePostRsp(&(pd->pu.postRsp), buf_tmp, rmn_len);
            break;
        case CMD_GET_SIG_WORD_REQ:
            /* parse the command get signal values request, */
            parse_ret = BPSParseGetSigReq(&(pd->pu.getSigReq), buf_tmp, rmn_len);
            break;
        case CMD_GET_SIG_WORD_RSP:
            /* parse the command get signal values response, */
            parse_ret = BPSParseGetSigRsp(&(pd->pu.getSigRsp), buf_tmp, rmn_len);
            break;
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
