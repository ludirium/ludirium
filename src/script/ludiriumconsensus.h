// Copyright (c) 2009-2010 Kenshin Nakamoto
// Copyright (c) 2009-2018 The Ludirium Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef LUDIRIUM_SCRIPT_LUDIRIUMCONSENSUS_H
#define LUDIRIUM_SCRIPT_LUDIRIUMCONSENSUS_H

#include <stdint.h>

#if defined(BUILD_LUDIRIUM_INTERNAL) && defined(HAVE_CONFIG_H)
#include <config/ludirium-config.h>
  #if defined(_WIN32)
    #if defined(HAVE_DLLEXPORT_ATTRIBUTE)
      #define EXPORT_SYMBOL __declspec(dllexport)
    #else
      #define EXPORT_SYMBOL
    #endif
  #elif defined(HAVE_DEFAULT_VISIBILITY_ATTRIBUTE)
    #define EXPORT_SYMBOL __attribute__ ((visibility ("default")))
  #endif
#elif defined(MSC_VER) && !defined(STATIC_LIBLUDIRIUMCONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define LUDIRIUMCONSENSUS_API_VER 1

typedef enum ludiriumconsensus_error_t
{
    ludiriumconsensus_ERR_OK = 0,
    ludiriumconsensus_ERR_TX_INDEX,
    ludiriumconsensus_ERR_TX_SIZE_MISMATCH,
    ludiriumconsensus_ERR_TX_DESERIALIZE,
    ludiriumconsensus_ERR_AMOUNT_REQUIRED,
    ludiriumconsensus_ERR_INVALID_FLAGS,
} ludiriumconsensus_error;

/** Script verification flags */
enum
{
    ludiriumconsensus_SCRIPT_FLAGS_VERIFY_NONE                = 0,
    ludiriumconsensus_SCRIPT_FLAGS_VERIFY_P2SH                = (1U << 0), // evaluate P2SH (BIP16) subscripts
    ludiriumconsensus_SCRIPT_FLAGS_VERIFY_DERSIG              = (1U << 2), // enforce strict DER (BIP66) compliance
    ludiriumconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY           = (1U << 4), // enforce NULLDUMMY (BIP147)
    ludiriumconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY = (1U << 9), // enable CHECKLOCKTIMEVERIFY (BIP65)
    ludiriumconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY = (1U << 10), // enable CHECKSEQUENCEVERIFY (BIP112)
    ludiriumconsensus_SCRIPT_FLAGS_VERIFY_WITNESS             = (1U << 11), // enable WITNESS (BIP141)
    ludiriumconsensus_SCRIPT_FLAGS_VERIFY_ALL                 = ludiriumconsensus_SCRIPT_FLAGS_VERIFY_P2SH | ludiriumconsensus_SCRIPT_FLAGS_VERIFY_DERSIG |
                                                               ludiriumconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY | ludiriumconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY |
                                                               ludiriumconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY | ludiriumconsensus_SCRIPT_FLAGS_VERIFY_WITNESS
};

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not nullptr, err will contain an error/success code for the operation
EXPORT_SYMBOL int ludiriumconsensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                                 const unsigned char *txTo        , unsigned int txToLen,
                                                 unsigned int nIn, unsigned int flags, ludiriumconsensus_error* err);

EXPORT_SYMBOL int ludiriumconsensus_verify_script_with_amount(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen, int64_t amount,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, ludiriumconsensus_error* err);

EXPORT_SYMBOL unsigned int ludiriumconsensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // LUDIRIUM_SCRIPT_LUDIRIUMCONSENSUS_H
