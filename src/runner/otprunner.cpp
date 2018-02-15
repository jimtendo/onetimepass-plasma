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

#include "otprunner.h"

#include <QDebug>
#include <KLocalizedString>
#include <QList>
#include <QAction>
#include <QClipboard>
#include <QApplication>
#include <QProcess>

#include <liboath/oath.h>

#define KWALLET_FOLDER "onetimepass"

OTPRunner::OTPRunner(QObject *parent, const QVariantList &args):
    Plasma::AbstractRunner(parent, args)
{
    Q_UNUSED(args);

    setObjectName(QLatin1String("OneTimePass Runner"));

    // Add the syntax
    addSyntax(Plasma::RunnerSyntax(QLatin1String("otp :q:"), i18n("Return a TOTP code based on query :q:")));
    
    // Add actions
    addAction("delete", QIcon::fromTheme("list-remove"), "Remove");
    
    // Open the wallet
    m_wallet = Wallet::openWallet(Wallet::LocalWallet(), 0, Wallet::Synchronous);
}

OTPRunner::~OTPRunner()
{
    delete m_wallet;
}

QList<QAction*> OTPRunner::actionsForMatch(const Plasma::QueryMatch &match)
{
    QList<QAction*> actions;
    
    qInfo() << match.id();
    
    if (match.type() != Plasma::QueryMatch::HelperMatch) {
        actions << action("delete");
    }
    
    return actions;    
}

void OTPRunner::match(Plasma::RunnerContext &context)
{
    // Make sure command starts with "otp"
    if (context.isValid() && context.query().startsWith(QLatin1String("otp "), Qt::CaseInsensitive)) {
        
        // Show option to open OneTimePass
        Plasma::QueryMatch newAction(this);
        newAction.setId("show");
        newAction.setType(Plasma::QueryMatch::HelperMatch);
        newAction.setIconName("clock");
        newAction.setText("Open OneTimePass");
        context.addMatch(newAction);
      
        // Get the search term
        QString searchTerm = context.query().split(" ", QString::SkipEmptyParts).at(1);
        
        // Open the kwallet folder
        if (m_wallet->setFolder(KWALLET_FOLDER)) {
          
            // Cycle through each entry
            Q_FOREACH (QString entryName, m_wallet->entryList()) {
                
                // If there's no search term or the entry contains the search term...
                if (!searchTerm.length() || entryName.contains(searchTerm, Qt::CaseInsensitive)) {
                    // Create match
                    Plasma::QueryMatch match(this);
                    match.setType(Plasma::QueryMatch::PossibleMatch);
                    match.setIconName("clock");
                    match.setText(entryName);
                    
                    // Read the entry contents
                    QString entryPassword;
                    m_wallet->readPassword(entryName, entryPassword);
                    
                    // Generate TOTP Code
                    match.setSubtext(generateTotpCode(entryPassword));
                    
                    // Add it to the results
                    context.addMatch(match);
                }
            }
        }
    }
}

void OTPRunner::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
    Q_UNUSED(context)
    
    QString folder = match.subtext();
    QString entry = match.text();
    
    if (match.type() == Plasma::QueryMatch::HelperMatch) {
        QProcess::startDetached("onetimepass");
    } else if (match.selectedAction()) {
        qInfo() << "Selected Action";
    } else {
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(match.subtext());
    }
}

QString OTPRunner::generateTotpCode(QString secret)
{
    // Decode from Base32
    char *secretDecoded;
    size_t secretLength;
    if (oath_base32_decode(secret.toUtf8().constData(), secret.toUtf8().size(), &secretDecoded, &secretLength) != OATH_OK) {
        return QString();
    }

    // Generate the TOTP code
    char totpCode[16];
    if (oath_totp_generate(secretDecoded, secretLength, std::time(0), 0, 0, 6, totpCode) != OATH_OK) {
        return QString();
    }
    
    return totpCode;
}

K_EXPORT_PLASMA_RUNNER(otprunner, OTPRunner)

#include "otprunner.moc"
