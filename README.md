# OneTimePass

A KDE/Plasma Google Authenticator-like App written using C++/QML.

It includes a KRunner that can be triggered by typing "otp" and a QML GUI Management program.

OTP Keys are stored in KWallet under the Default KDE Wallet (usually "kdewallet") in a folder titled "onetimepass". 

## Compiling/Building

### Requirements (Ubuntu 17.10):

`sudo apt install liboath-dev libkf5wallet-dev libkf5runner-dev libkf5service-dev libkf5i18n-dev`

### Building

```sh
git clone https://github.com/jimtendo/onetimepass-plasma
cd onetimepass-plasma
mkdir build
cmake -D KDE_INSTALL_USE_QT_SYS_PATHS=ON ../
make
sudo make install
```
