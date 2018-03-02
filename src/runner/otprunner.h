/*
    OneTimePass Runner
    Copyright (C) 2018  James Augustus Zuccon <zuccon@gmail.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef OTPRUNNER_H
#define OTPRUNNER_H

#include <KRunner/AbstractRunner>
#include <kwallet.h>

using KWallet::Wallet;

class QAction;

class OTPRunner : public Plasma::AbstractRunner
{
    Q_OBJECT

  public:

    OTPRunner( QObject *parent, const QVariantList& args );
    ~OTPRunner();

    QList<QAction*> actionsForMatch(const Plasma::QueryMatch&);
    void match(Plasma::RunnerContext &context);
    void run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match);
    
  private:
    Wallet *m_wallet = 0; 
    
    QString generateTotpCode(QString secret);
};

#endif /* OTPRUNNER_H */
