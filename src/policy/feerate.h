// Copyright (c) 2009-2010 Kenshin Nakamoto
// Copyright (c) 2009-2020 The Ludirium Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef LUDIRIUM_POLICY_FEERATE_H
#define LUDIRIUM_POLICY_FEERATE_H

#include <amount.h>
#include <serialize.h>

#include <string>

const std::string CURRENCY_UNIT = "LUDi"; // One formatted unit
const std::string CURRENCY_ATOM = "ken"; // One indivisible minimum value unit

/* Used to determine type of fee estimation requested */
enum class FeeEstimateMode {
    UNSET,        //!< Use default settings based on other criteria
    ECONOMICAL,   //!< Force estimateSmartFee to use non-conservative estimates
    CONSERVATIVE, //!< Force estimateSmartFee to use conservative estimates
    LUDi_KVB,      //!< Use LUDi/kvB fee rate unit
    KEN_VB,       //!< Use ken/vB fee rate unit
};

/**
 * Fee rate in kenshins per kilobyte: CAmount / kB
 */
class CFeeRate
{
private:
    CAmount nKenshinsPerK; // unit is kenshins-per-1,000-bytes

public:
    /** Fee rate of 0 kenshins per kB */
    CFeeRate() : nKenshinsPerK(0) { }
    template<typename I>
    explicit CFeeRate(const I _nKenshinsPerK): nKenshinsPerK(_nKenshinsPerK) {
        // We've previously had bugs creep in from silent double->int conversion...
        static_assert(std::is_integral<I>::value, "CFeeRate should be used without floats");
    }
    /** Constructor for a fee rate in kenshins per kvB (ken/kvB).
     *
     *  Passing a num_bytes value of COIN (1e8) returns a fee rate in kenshins per vB (ken/vB),
     *  e.g. (nFeePaid * 1e8 / 1e3) == (nFeePaid / 1e5),
     *  where 1e5 is the ratio to convert from LUDi/kvB to ken/vB.
     */
    CFeeRate(const CAmount& nFeePaid, uint32_t num_bytes);
    /**
     * Return the fee in kenshins for the given size in bytes.
     */
    CAmount GetFee(uint32_t num_bytes) const;
    /**
     * Return the fee in kenshins for a size of 1000 bytes
     */
    CAmount GetFeePerK() const { return GetFee(1000); }
    friend bool operator<(const CFeeRate& a, const CFeeRate& b) { return a.nKenshinsPerK < b.nKenshinsPerK; }
    friend bool operator>(const CFeeRate& a, const CFeeRate& b) { return a.nKenshinsPerK > b.nKenshinsPerK; }
    friend bool operator==(const CFeeRate& a, const CFeeRate& b) { return a.nKenshinsPerK == b.nKenshinsPerK; }
    friend bool operator<=(const CFeeRate& a, const CFeeRate& b) { return a.nKenshinsPerK <= b.nKenshinsPerK; }
    friend bool operator>=(const CFeeRate& a, const CFeeRate& b) { return a.nKenshinsPerK >= b.nKenshinsPerK; }
    friend bool operator!=(const CFeeRate& a, const CFeeRate& b) { return a.nKenshinsPerK != b.nKenshinsPerK; }
    CFeeRate& operator+=(const CFeeRate& a) { nKenshinsPerK += a.nKenshinsPerK; return *this; }
    std::string ToString(const FeeEstimateMode& fee_estimate_mode = FeeEstimateMode::LUDi_KVB) const;

    SERIALIZE_METHODS(CFeeRate, obj) { READWRITE(obj.nKenshinsPerK); }
};

#endif //  LUDIRIUM_POLICY_FEERATE_H
