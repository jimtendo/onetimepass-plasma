import QtQuick 2.1
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.1 as Controls
import org.kde.kirigami 2.2 as Kirigami
import org.kde.onetimepass.provider 1.0

Kirigami.ApplicationWindow {
    id: root
    width: 320
    pageStack.initialPage: mainPageComponent
    Kirigami.Theme.colorSet: Kirigami.Theme.Window
    Kirigami.Theme.inherit: false
    
    Component {
        id: mainPageComponent
        Kirigami.ScrollablePage {
            title: "OneTimePass"
            actions {
                main: Kirigami.Action {
                    iconName: "list-add"
                    visible: Provider.isWalletOpen()
                    tooltip: "Add new token"
                    onTriggered: {
                        root.pageStack.push(addEntry);
                    }
                }
            }
            ListView {
                id: otpView
                anchors.fill: parent
                model: Provider.tokens
                delegate: OTPDelegate {
                    name: modelData.name
                    code: modelData.code
                }
                focus: true
            }
            Controls.Dialog {
                id: disabledDialog
                modal: true
                visible: Provider.isWalletOpen() ? false : true
                title: "KWallet Subsystem Disabled"
                standardButtons: Controls.Dialog.Ok
                Controls.Label {
                  width: disabledDialog.availableWidth
                  text: "KWallet subsystem must be enabled to use OneTimePass. Please enable KWallet and restart the application."
                  wrapMode: Controls.Label.Wrap
                }
                onAccepted: Qt.quit()
            }
        }
    }
    
    AddEntry {
      id: addEntry
    }
    
    function deleteEntry(name) {
      var component = Qt.createComponent("DeleteEntry.qml");
      var dialog = component.createObject(root);
      dialog.name = name;
    }
    
    Component.onCompleted: {
        if (typeof addOTP !== 'undefined') {
            try {
              // Set the name and token
              addEntry.initialName = addOTP.path;
              addEntry.initialToken = addOTP.secret;
              
              root.pageStack.push(addEntry);
            } catch(err) {
              console.error(err.message);
            }
        }
    }
}
