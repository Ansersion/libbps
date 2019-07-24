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

BP_UINT8 * BPS_SetNet16(BP_UINT8 * dst, BP_UINT16 val)
{
	if(BP_NULL == dst) {
		return BP_NULL;
	}

	*dst++ = (BP_UINT8)((val >> 8) & (0x00FF));
	*dst++ = (BP_UINT8)(val & 0x00FF);

	return dst;
}

BP_UINT8 * BPS_SetNet32(BP_UINT8 * dst, BP_UINT32 val)
{
	if(BP_NULL == dst) {
		return BP_NULL;
	}

	*dst++ = (BP_UINT8)((val >> 24) & (0x000000FF));
	*dst++ = (BP_UINT8)((val >> 16) & (0x000000FF));
	*dst++ = (BP_UINT8)((val >> 8) & (0x000000FF));
	*dst++ = (BP_UINT8)(val & 0x000000FF);

	return dst;
}

BP_UINT8 * BPS_SetNBytes(BP_UINT8 * dst, BP_UINT8 * src, BP_WORD num)
{
	memcpy_bps(dst, src, num);
	dst += num;
	return dst;
}

BP_UINT8 * BPS_Set2ByteField(BP_UINT8 * pack, BP_UINT8 * field, BP_UINT16 field_len)
{
	BP_UINT8 * p_pack = pack;
	if(BP_NULL == pack) {
		return BP_NULL;
	}
	// if(0 == field_len) {
	// 	return BP_NULL;
	// }
	p_pack = BPS_SetBig16(p_pack, field_len);
	memcpy_bps(p_pack, field, field_len);

	return p_pack+field_len;
}

BP_UINT8 * BPS_Set1ByteField(BP_UINT8 * pack, const BP_UINT8 * field, BP_UINT8 field_len)
{
	BP_UINT8 * p_pack = pack;
	if(BP_NULL == pack) {
		return BP_NULL;
	}
	*p_pack++ = field_len;
	memcpy_bps(p_pack, field, field_len);

	return p_pack+field_len;
}

BP_UINT8 * BPS_GetNet16(BP_UINT8 * src, BP_UINT16 * val)
{
	if(BP_NULL == src) {
		return BP_NULL;
	}
	if(BP_NULL == val) {
		return BP_NULL;
	}
	*val = *src++;
	*val = ((*val & 0x00FF) << 8) | (0xFF & (*src++));

	return src;
}

BP_UINT8 * BPS_GetNet32(BP_UINT8 * src, BP_UINT32 * val)
{
	if(BP_NULL == src) {
		return BP_NULL;
	}
	if(BP_NULL == val) {
		return BP_NULL;
	}
	*val = *src++;
	*val = ((*val & 0x000000FF) << 8) | (0x000000FF & (*src++));
	*val = ((*val & 0x0000FFFF) << 8) | (0x000000FF & (*src++));
	*val = ((*val & 0x00FFFFFF) << 8) | (0x000000FF & (*src++));

	return src;

}

BP_UINT8 * BPS_Get2ByteField(BP_UINT8 * pack, BP_UINT8 * field_buf, BP_UINT16 * field_len)
{
	BP_UINT8 * p_pack = pack;
	if(BP_NULL == pack) {
		return BP_NULL;
	}
	if(BP_NULL == field_buf) {
		return BP_NULL;
	}
	if(BP_NULL == field_len) {
		return BP_NULL;
	}
	p_pack = BPS_GetBig16(p_pack, field_len);
	memcpy_bps(field_buf, p_pack, *field_len);

	return p_pack+(*field_len);
}

BP_WORD BPS_GetSigValueLen(BPSSigType type, BPSSigTypeU value)
{
    BP_WORD len;
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
            len = strlen_bps((const char *)value.t_str) + 1;
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

BP_WORD BPS_GetSigValueLen2(BPSSigType type)
{
    BP_WORD len;
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

BP_UINT8 * BPS_SetSigValue(BP_UINT8 * pack, BPSSigType type, BPSSigTypeU value)
{
	BP_UINT8 * p_pack = pack;
    BP_UINT8 str_len;
	if(BP_NULL == pack) {
		return BP_NULL;
	}
    switch(type) {
        case BPS_SIG_TYPE_U32:
            p_pack = BPS_SetBig32(p_pack, value.t_u32);
            break;
        case BPS_SIG_TYPE_U16:
            p_pack = BPS_SetBig16(p_pack, value.t_u16);
            break;
        case BPS_SIG_TYPE_I32:
            p_pack = BPS_SetBig32(p_pack, value.t_i32);
            break;
        case BPS_SIG_TYPE_I16:
            p_pack = BPS_SetBig16(p_pack, value.t_i16);
            break;
        case BPS_SIG_TYPE_ENM:
            p_pack = BPS_SetBig16(p_pack, value.t_enm);
            break;
        case BPS_SIG_TYPE_FLT:
            p_pack = BPS_SetBig32(p_pack, value.t_flt);
            break;
        case BPS_SIG_TYPE_STR: 
            str_len = strlen_bps((const char *)value.t_str);
            *p_pack++ = str_len;
            memcpy_bps(p_pack, value.t_str, str_len);
            p_pack += str_len;
            break;
        case BPS_SIG_TYPE_BOOLEAN:
            *p_pack++ = value.t_bool;
            break;
        case BPS_SIG_TYPE_TIME:
            p_pack = BPS_SetBig32(p_pack, value.t_time);
            break;
        case BPS_SIG_TYPE_DATE:
            p_pack = BPS_SetBig32(p_pack, value.t_date);
            break;
        default:
            return BP_NULL;
    }

	return p_pack;
}

BP_UINT8 * BPS_GetSigValue(BP_UINT8 * pack, BPSSigType type, BPSSigTypeU * value, BP_WORD len)
{
	BP_UINT8 * p_pack = pack;
	if(BP_NULL == pack || BP_NULL == value) {
		return BP_NULL;
	}
    switch(type) {
        case BPS_SIG_TYPE_U32:
            p_pack = BPS_GetBig32(p_pack, &value->t_u32);
            break;
        case BPS_SIG_TYPE_U16:
            p_pack = BPS_GetBig16(p_pack, &value->t_u16);
            break;
        case BPS_SIG_TYPE_I32:
            p_pack = BPS_GetBig32(p_pack, (BP_UINT32 *)&value->t_i32);
            break;
        case BPS_SIG_TYPE_I16:
            p_pack = BPS_GetBig16(p_pack, (BP_UINT16 *)&value->t_i16);
            break;
        case BPS_SIG_TYPE_ENM:
            p_pack = BPS_GetBig16(p_pack, &value->t_enm);
            break;
        case BPS_SIG_TYPE_FLT:
            p_pack = BPS_GetBig32(p_pack, (BP_UINT32 *)&value->t_flt);
            break;
        case BPS_SIG_TYPE_STR: 
            if(len > MAX_STRING_LEN) {
                return BP_NULL;
            }
            memcpy_bps(value->t_str, p_pack, len);
            value->t_str[len] = '\0';
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
            return BP_NULL;
    }

	return p_pack;
}

BP_INLINE BP_UINT8 IsBPSHeader2(BP_UINT8 b1, BP_UINT8 b2)
{
	return 0xBB == b1 && 0xCC == b2;
}

BP_UINT8 IsBPSHeader(BP_UINT8 * buf)
{
	if(BP_NULL == buf) {
		return 0;
	}
	return IsBPSHeader2(buf[0], buf[1]);
}

BP_INLINE BP_UINT8 IsBPSVersionCompat(BP_UINT8 version)
{
	return version <= BPS_VERSION;
}

BP_INLINE BP_UINT8 GetBPSSenderAddr(BP_UINT8 addr)
{
	return (addr >> 4) & 0xF;
}

BP_INLINE BP_UINT8 GetBPSRecverAddr(BP_UINT8 addr)
{
	return addr & 0xF;
}

BP_UINT16 GetBPSRemainLen(BP_UINT8 * buf)
{
	BP_UINT16 ret = 0;
	if(BP_NULL == buf) {
		return ret;
	}
    BPS_GetNet16(buf, &ret);

	return ret;
}

BP_UINT16 GetBPSRemainLen2(BP_UINT8 * buf, BP_WORD size)
{
	if(size < BPS_REMAIN_LEN_SIZE) {
		return 0;
	}
	return GetBPSRemainLen(buf);
}

BP_UINT8 IsBPSChksumOK(BP_UINT8 * buf)
{
	BP_UINT16 len;
	BP_UINT8 * tmp;
	BP_UINT8 checksum;

	if(BP_NULL == buf) {
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

BP_UINT8 IsBPSChksumOK2(BP_UINT8 * buf, BP_WORD size)
{
	BP_UINT16 len;
	BP_UINT8 * tmp;
	BP_UINT8 checksum;

	if(BP_NULL == buf) {
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

void PackBPSHeader(BP_UINT8 * buf)
{
	if(BP_NULL == buf) {
		return;
	}
    BPS_SetNet32(buf, BPS_HEADER);
}

void PackBPSHeader2(BP_UINT8 * buf, BP_WORD size)
{
	if(size < BPS_HEADER_SIZE) {
		return;
	}
	PackBPSHeader(buf);
}

BP_INLINE void PackBPSVersion(BP_UINT8 * buf)
{
	*buf = BPS_VERSION;
}

void PackBPSAddr(BP_UINT8 * buf, BP_UINT8 sender, BP_UINT8 recver)
{
	if(BP_NULL == buf) {
		return;
	}
	*buf = ((sender << 4) & 0xF0) | (recver & 0x0F);
}

void PackBPSRemainLen(BP_UINT8 * buf, BP_UINT16 len)
{
	if(BP_NULL == buf) {
		return;
	}
    BPS_SetNet16(buf, len);
}

void PackBPSRemainLen2(BP_UINT8 * buf, BP_UINT16 len, BP_WORD size)
{
	if(size < BPS_REMAIN_LEN_SIZE) {
		return;
	}
	PackBPSRemainLen(buf, len);
}
