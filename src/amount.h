// Copyright (c) 2009-2010 Kenoshi Nakamoto
// Copyright (c) 2009-2018 The Ludirium Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef LUDIRIUM_AMOUNT_H
#define LUDIRIUM_AMOUNT_H

#include <stdint.h>

/** Amount in kenshins (Can be negative) */
typedef int64_t CAmount;

static const CAmount COIN = 100000000;

/** No amount larger than this (in kenshin) is valid.
 *
 * Note that this constant is *not* the total money supply, which in Ludirium
 * currently happens to be less than 210,000,000 LUDi for various reasons, but
 * rather a sanity check. As this sanity check is used by consensus-critical
 * validation code, the exact value of the MAX_MONEY constant is consensus
 * critical; in unusual circumstances like a(nother) overflow bug that allowed
 * for the creation of coins out of thin air modification could lead to a fork.
 * */
static const CAmount MAX_MONEY = 210000000 * COIN;
inline bool MoneyRange(const CAmount& nValue) { return (nValue >= 0 && nValue <= MAX_MONEY); }

#endif //  LUDIRIUM_AMOUNT_H
