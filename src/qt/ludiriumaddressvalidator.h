// Copyright (c) 2011-2020 The Ludirium Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef LUDIRIUM_QT_LUDIRIUMADDRESSVALIDATOR_H
#define LUDIRIUM_QT_LUDIRIUMADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class LudiriumAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit LudiriumAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

/** Ludirium address widget validator, checks for a valid ludirium address.
 */
class LudiriumAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit LudiriumAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

#endif // LUDIRIUM_QT_LUDIRIUMADDRESSVALIDATOR_H
