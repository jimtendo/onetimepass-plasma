/*
 * Copyright (c) 2017 Jim Hamill <jim.hamill@gigya-inc.com>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "provider.h"

#include <QDebug>
#include <QApplication>
#include <QClipboard>
#include <QVariantMap>

#include <KWallet>

#include <liboath/oath.h>

#define KWALLET_FOLDER "onetimepass"

Provider::Provider(QObject* parent)
        : QObject(parent)
{
    // Open the wallet and connect slots
    m_wallet = Wallet::openWallet(Wallet::LocalWallet(), 0, Wallet::Synchronous);
    
    // If KWallet folder is updated, update the tokens
    // TODO My KWallet API might be outdated... this won't compile
    /*connect(m_wallet, &KWallet::folderUpdated, [=](QString folderName) {
        if (folderName == KWALLET_FOLDER) {
            tokensUpdated();
        }
    });*/
    
    // Create timer that triggers the TOTP's to update 30 seconds
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, [=]() {
        // If 30 seconds is up
        if (std::time(0) % 30 == 0) {
            tokensUpdated(); 
        }
    });
    m_timer->start(1000);
}

Provider::~Provider()
{
    delete m_wallet;
}

bool Provider::isWalletOpen()
{
    return m_wallet ? true : false;
}

QVariantList Provider::qmlTokens()
{
    if (!m_wallet) {
        return QVariantList();
    }
  
    QVariantList tokens;
  
    // Open the KWallet folder
    if (m_wallet->setFolder(KWALLET_FOLDER)) {
      
        // Cycle through each entry
        Q_FOREACH (QString entryName, m_wallet->entryList()) {
            // Read the entry's contents
            QString token;
            m_wallet->readPassword(entryName, token);
            
            // Generate TOTP Code
            QString code = generateTotpCode(token);
            
            // Add it to tokens
            tokens.append(QVariantMap{
                { "name", entryName },
                { "code", code },
                { "token", token }
            });
        }
    }
    
    return tokens;
}

QVariantMap Provider::addEntry(QString name, QString token)
{
    if (!m_wallet->setFolder(KWALLET_FOLDER)) {
        m_wallet->createFolder(KWALLET_FOLDER);
    }
    
    if (m_wallet->hasEntry(name)) {
        return QVariantMap {
          { "name", "Entry already exists" }
        };
    }
    
    m_wallet->writePassword(name, token);
    
    tokensUpdated();
  
    return QVariantMap();
}

void Provider::removeEntry(QString name)
{
    if (m_wallet->setFolder(KWALLET_FOLDER)) {
        if (m_wallet->hasEntry(name)) {
            m_wallet->removeEntry(name);
            tokensUpdated();
        }
    }
}

void Provider::setClipboard(QString value)
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(value);
}

QString Provider::generateTotpCode(QString secret)
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

Provider *Provider::m_singleton = NULL;
