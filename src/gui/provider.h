/*
 * Copyright (c) 2018 James Zuccon <zuccon@gmail.com>
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

#ifndef PROVIDER_H
#define PROVIDER_H

#include <QObject>
#include <QList>
#include <QQmlEngine>
#include <QVariantList>
#include <QTimer>
#include <QDebug>

#include <KWallet>

using KWallet::Wallet;

class Provider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList tokens READ qmlTokens NOTIFY tokensUpdated)
    
public:
    Provider(QObject* parent = 0);
    ~Provider();
    
    QVariantList qmlTokens();
    Q_INVOKABLE QVariantMap addEntry(QString name, QString token);
    Q_INVOKABLE void removeEntry(QString name);
    
    Q_INVOKABLE void setClipboard(QString value);
    
    static Provider *singleton()
    {
        if (Provider::m_singleton == NULL) {
            Provider::m_singleton = new Provider();
        }

        return m_singleton;
    }
    
    static QObject *SingletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
    {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        return Provider::singleton();
    }

signals:
    void tokensUpdated();
    
private:
    QTimer *m_timer;
    Wallet *m_wallet;
    
    QString generateTotpCode(QString secret);
  
    static Provider *m_singleton;
};

#endif // PROVIDER_H
