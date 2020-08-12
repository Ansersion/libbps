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
#include <bps_memcpy.h>
#include <bps_strlen.h>

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

BPS_UINT8 * BPS_SetNet16(BPS_UINT8 * dst, BPS_UINT16 val)
{
	if(BPS_NULL == dst) {
		return BPS_NULL;
	}

	*dst++ = (BPS_UINT8)((val >> 8) & (0x00FF));
	*dst++ = (BPS_UINT8)(val & 0x00FF);

	return dst;
}

BPS_UINT8 * BPS_SetNet32(BPS_UINT8 * dst, BPS_UINT32 val)
{
	if(BPS_NULL == dst) {
		return BPS_NULL;
	}

	*dst++ = (BPS_UINT8)((val >> 24) & (0x000000FF));
	*dst++ = (BPS_UINT8)((val >> 16) & (0x000000FF));
	*dst++ = (BPS_UINT8)((val >> 8) & (0x000000FF));
	*dst++ = (BPS_UINT8)(val & 0x000000FF);

	return dst;
}

BPS_UINT8 * BPS_SetNBytes(BPS_UINT8 * dst, BPS_UINT8 * src, BPS_WORD num)
{
	memcpy_bps(dst, src, num);
	dst += num;
	return dst;
}

BPS_UINT8 * BPS_Set2ByteField(BPS_UINT8 * pack, BPS_UINT8 * field, BPS_UINT16 field_len)
{
	BPS_UINT8 * p_pack = pack;
	if(BPS_NULL == pack) {
		return BPS_NULL;
	}
	// if(0 == field_len) {
	// 	return BPS_NULL;
	// }
	p_pack = BPS_SetBig16(p_pack, field_len);
	memcpy_bps(p_pack, field, field_len);

	return p_pack+field_len;
}

BPS_UINT8 * BPS_Set1ByteField(BPS_UINT8 * pack, const BPS_UINT8 * field, BPS_UINT8 field_len)
{
	BPS_UINT8 * p_pack = pack;
	if(BPS_NULL == pack) {
		return BPS_NULL;
	}
	*p_pack++ = field_len;
	memcpy_bps(p_pack, field, field_len);

	return p_pack+field_len;
}

const BPS_UINT8 * BPS_GetNet16(const BPS_UINT8 * src, BPS_UINT16 * val)
{
	if(BPS_NULL == src) {
		return BPS_NULL;
	}
	if(BPS_NULL == val) {
		return BPS_NULL;
	}
	*val = *src++;
	*val = ((*val & 0x00FF) << 8) | (0xFF & (*src++));

	return src;
}

const BPS_UINT8 * BPS_GetNet32(const BPS_UINT8 * src, BPS_UINT32 * val)
{
	if(BPS_NULL == src) {
		return BPS_NULL;
	}
	if(BPS_NULL == val) {
		return BPS_NULL;
	}
	*val = *src++;
	*val = ((*val & 0x000000FF) << 8) | (0x000000FF & (*src++));
	*val = ((*val & 0x0000FFFF) << 8) | (0x000000FF & (*src++));
	*val = ((*val & 0x00FFFFFF) << 8) | (0x000000FF & (*src++));

	return src;

}

const BPS_UINT8 * BPS_Get2ByteField(BPS_UINT8 * pack, BPS_UINT8 * field_buf, BPS_UINT16 * field_len)
{
	const BPS_UINT8 * p_pack = pack;
	if(BPS_NULL == pack) {
		return BPS_NULL;
	}
	if(BPS_NULL == field_buf) {
		return BPS_NULL;
	}
	if(BPS_NULL == field_len) {
		return BPS_NULL;
	}
	p_pack = BPS_GetBig16(p_pack, field_len);
	memcpy_bps(field_buf, p_pack, *field_len);

	return p_pack+(*field_len);
}

BPS_WORD BPS_GetSigValueLen(BPSSigType type, BPSSigTypeU * value)
{
    BPS_WORD len;
    if(BPS_NULL == value) {
        return 0;
    }

    switch(type) {
        case BPS_SIG_TYPE_U32:
            len = 4;
            break;
        case BPS_SIG_TYPE_U16:
            len = 2;
            break;
        case BPS_SIG_TYPE_I32:
            len = 4;
            break;
        case BPS_SIG_TYPE_I16:
            len = 2;
            break;
        case BPS_SIG_TYPE_ENM:
            len = 2;
            break;
        case BPS_SIG_TYPE_FLT:
            len = 4;
            break;
        case BPS_SIG_TYPE_STR: 
            if(BPS_NULL != value->t_str) {
                len = strlen_bps((const char *)value->t_str);
            } else {
                len = 0;
            }
            break;
        case BPS_SIG_TYPE_BOOLEAN:
            len = 1;
            break;
        case BPS_SIG_TYPE_TIME:
            len = 4;
            break;
        case BPS_SIG_TYPE_DATE:
            len = 4;
            break;
        default:
            len = 0;
            break;
    }

    return len;
}

BPS_WORD BPS_GetSigValueLen2(BPSSigType type)
{
    BPS_WORD len;
    switch(type) {
        case BPS_SIG_TYPE_U32:
            len = 4;
            break;
        case BPS_SIG_TYPE_U16:
            len = 2;
            break;
        case BPS_SIG_TYPE_I32:
            len = 4;
            break;
        case BPS_SIG_TYPE_I16:
            len = 2;
            break;
        case BPS_SIG_TYPE_ENM:
            len = 2;
            break;
        case BPS_SIG_TYPE_FLT:
            len = 4;
            break;
        case BPS_SIG_TYPE_STR: 
            /* not handled here */
            len = 0;
            break;
        case BPS_SIG_TYPE_BOOLEAN:
            len = 1;
            break;
        case BPS_SIG_TYPE_TIME:
            len = 4;
            break;
        case BPS_SIG_TYPE_DATE:
            len = 4;
            break;
        default:
            len = 0;
            break;
    }

    return len;
}

BPS_UINT8 * BPS_SetSigValue(BPS_UINT8 * pack, BPSSigType type, BPSSigTypeU * value)
{
	BPS_UINT8 * p_pack = pack;
    BPS_UINT8 str_len;
	if(BPS_NULL == pack) {
		return BPS_NULL;
	}
	if(BPS_NULL == value) {
		return BPS_NULL;
	}
    switch(type) {
        case BPS_SIG_TYPE_U32:
            p_pack = BPS_SetBig32(p_pack, value->t_u32);
            break;
        case BPS_SIG_TYPE_U16:
            p_pack = BPS_SetBig16(p_pack, value->t_u16);
            break;
        case BPS_SIG_TYPE_I32:
            p_pack = BPS_SetBig32(p_pack, value->t_i32);
            break;
        case BPS_SIG_TYPE_I16:
            p_pack = BPS_SetBig16(p_pack, value->t_i16);
            break;
        case BPS_SIG_TYPE_ENM:
            p_pack = BPS_SetBig16(p_pack, value->t_enm);
            break;
        case BPS_SIG_TYPE_FLT:
            p_pack = BPS_SetBig32(p_pack, value->t_flt);
            break;
        case BPS_SIG_TYPE_STR: 
            str_len = strlen_bps((const char *)value->t_str);
            *p_pack++ = str_len;
            memcpy_bps(p_pack, value->t_str, str_len);
            p_pack += str_len;
            break;
        case BPS_SIG_TYPE_BOOLEAN:
            *p_pack++ = value->t_bool;
            break;
        case BPS_SIG_TYPE_TIME:
            p_pack = BPS_SetBig32(p_pack, value->t_time);
            break;
        case BPS_SIG_TYPE_DATE:
            p_pack = BPS_SetBig32(p_pack, value->t_date);
            break;
        default:
            return BPS_NULL;
    }

	return p_pack;
}

const BPS_UINT8 * BPS_GetSigValue(const BPS_UINT8 * pack, BPSSigType type, BPSSigTypeU * value, BPS_WORD len)
{
	const BPS_UINT8 * p_pack = pack;
	if(BPS_NULL == pack || BPS_NULL == value) {
		return BPS_NULL;
	}
    switch(type) {
        case BPS_SIG_TYPE_U32:
            p_pack = BPS_GetBig32(p_pack, &value->t_u32);
            break;
        case BPS_SIG_TYPE_U16:
            p_pack = BPS_GetBig16(p_pack, &value->t_u16);
            break;
        case BPS_SIG_TYPE_I32:
            p_pack = BPS_GetBig32(p_pack, (BPS_UINT32 *)&value->t_i32);
            break;
        case BPS_SIG_TYPE_I16:
            p_pack = BPS_GetBig16(p_pack, (BPS_UINT16 *)&value->t_i16);
            break;
        case BPS_SIG_TYPE_ENM:
            p_pack = BPS_GetBig16(p_pack, &value->t_enm);
            break;
        case BPS_SIG_TYPE_FLT:
            p_pack = BPS_GetBig32(p_pack, (BPS_UINT32 *)&value->t_flt);
            break;
        case BPS_SIG_TYPE_STR: 
            if(BPS_NULL == value->t_str || len > BPS_MAX_STRING_LEN) {
                return BPS_NULL;
            }
            memcpy_bps(value->t_str, p_pack, len);
            p_pack += len;
            break;
        case BPS_SIG_TYPE_BOOLEAN:
            value->t_bool = *p_pack++;
            break;
        case BPS_SIG_TYPE_TIME:
            p_pack = BPS_GetBig32(p_pack, &value->t_time);
            break;
        case BPS_SIG_TYPE_DATE:
            p_pack = BPS_GetBig32(p_pack, &value->t_date);
            break;
        default:
            return BPS_NULL;
    }

	return p_pack;
}

BPS_UINT8 IsBPSHeader2(BPS_UINT8 b1, BPS_UINT8 b2)
{
	return 0xBB == b1 && 0xCC == b2;
}

BPS_UINT8 IsBPSHeader(BPS_UINT8 * buf)
{
	if(BPS_NULL == buf) {
		return 0;
	}
	return IsBPSHeader2(buf[0], buf[1]);
}

BPS_UINT8 IsBPSVersionCompat(BPS_UINT8 version)
{
	return version <= BPS_VERSION;
}

BPS_UINT8 GetBPSSenderAddr(BPS_UINT8 addr)
{
	return (addr >> 4) & 0xF;
}

BPS_UINT8 GetBPSRecverAddr(BPS_UINT8 addr)
{
	return addr & 0xF;
}

BPS_UINT16 GetBPSRemainLen(BPS_UINT8 * buf)
{
	BPS_UINT16 ret = 0;
	if(BPS_NULL == buf) {
		return ret;
	}
    BPS_GetBig16(buf, &ret);

	return ret;
}

BPS_UINT16 GetBPSRemainLen2(BPS_UINT8 * buf, BPS_WORD size)
{
	if(size < BPS_REMAIN_LEN_SIZE) {
		return 0;
	}
	return GetBPSRemainLen(buf);
}

BPS_UINT8 IsCmdWordValid(BPS_UINT8 cmd_word)
{
    switch(cmd_word) {
        case CMD_COMM_TEST_WORD_REQ:
        case CMD_COMM_TEST_WORD_RSP:
        case CMD_HD_INFO_WORD_REQ:
        case CMD_HD_INFO_WORD_RSP:
        case CMD_PING_WORD_REQ:
        case CMD_PING_WORD_RSP:
        case CMD_OPEN_NETSET_WORD_REQ:
        case CMD_OPEN_NETSET_WORD_RSP:
        case CMD_CONFIG_NETSET_WORD_REQ:
        case CMD_CONFIG_NETSET_WORD_RSP:
        case CMD_NETSTATE_QUERY_WORD_REQ:
        case CMD_NETSTATE_QUERY_WORD_RSP:
        case CMD_GET_SIGTAB_WORD_REQ:
        case CMD_GET_SIGTAB_WORD_RSP:
        case CMD_REPORT_SIG_WORD_REQ:
        case CMD_REPORT_SIG_WORD_RSP:
        case CMD_POST_WORD_REQ:
        case CMD_POST_WORD_RSP:
        case CMD_GET_SIG_WORD_REQ:
        case CMD_GET_SIG_WORD_RSP:
            return 1;
    }

    return 0;
}

BPS_UINT8 IsBPSChksumOK(BPS_UINT8 * buf)
{
	BPS_UINT16 len;
	BPS_UINT8 * tmp;
	BPS_UINT8 checksum;

	if(BPS_NULL == buf) {
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

BPS_UINT8 IsBPSChksumOK2(BPS_UINT8 * buf, BPS_WORD size)
{
	BPS_UINT16 len;
	BPS_UINT8 * tmp;
	BPS_UINT8 checksum;

	if(BPS_NULL == buf) {
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

BPS_UINT8 * PackBPSHeader(BPS_UINT8 * buf)
{
	if(BPS_NULL == buf) {
		return BPS_NULL;
	}
    return BPS_SetBig16(buf, BPS_HEADER);
}

BPS_UINT8 * PackBPSHeader2(BPS_UINT8 * buf, BPS_WORD size)
{
	if(size < BPS_HEADER_SIZE) {
		return BPS_NULL;
	}
	return PackBPSHeader(buf);
}

BPS_UINT8 * PackBPSVersion(BPS_UINT8 * buf)
{
	*buf++ = BPS_VERSION;
    return buf;
}

BPS_UINT8 * PackBPSAddr(BPS_UINT8 * buf, BPS_UINT8 sender, BPS_UINT8 recver)
{
	if(BPS_NULL == buf) {
		return BPS_NULL;
	}
	*buf++ = ((sender << 4) & 0xF0) | (recver & 0x0F);
    return buf;
}

BPS_UINT8 * PackBPSRemainLen(BPS_UINT8 * buf, BPS_UINT16 len)
{
	if(BPS_NULL == buf) {
		return BPS_NULL;
	}
    return BPS_SetBig16(buf, len);
}

BPS_UINT8 * PackBPSRemainLen2(BPS_UINT8 * buf, BPS_UINT16 len, BPS_WORD size)
{
	if(size < BPS_REMAIN_LEN_SIZE) {
		return BPS_NULL;
	}
	return PackBPSRemainLen(buf, len);
}

BPS_UINT8 * PackBPSChecksum(BPS_UINT8 * buf, BPS_WORD size)
{
	BPS_UINT16 len;
	BPS_UINT8 * tmp;
	BPS_UINT8 checksum;

	if(BPS_NULL == buf) {
		return BPS_NULL;
	}

	len = GetBPSRemainLen(buf + BPS_REMAIN_LEN_POSITION);
	len += BPS_VERSION_SIZE;
	len += BPS_ADDR_SIZE;
	len += BPS_REMAIN_LEN_SIZE;

    if(len > size) {
        return BPS_NULL;
    }

	tmp = buf + BPS_VERSION_POSITION;
	checksum = 0;
	while(len--) {
		checksum += *tmp++;
	}
    *tmp = checksum;

	return buf;
}

