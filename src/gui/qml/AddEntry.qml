import QtQuick 2.1
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.1 as Controls
import org.kde.kirigami 2.2 as Kirigami
import org.kde.onetimepass.provider 1.0
    
Kirigami.ScrollablePage {
    id: addEntry
    property string initialName
    property string initialToken
    
    title: "Add Entry"
    
    ColumnLayout {
        Controls.Label {
            text: "Name:"
        }
        Controls.TextField {
            id: name
            text: initialName
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
        }
        Controls.Label {
            id: errorName
            text: ""
            color: "red"
        }
        Controls.Label {
            text: "Token:"
        }
        Controls.TextField {
            id: token
            text: initialToken
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
        }
        Controls.Label {
            id: errorToken
            text: ""
            color: "red"
        }
        Controls.Button {
            Layout.fillWidth: true
            text: "Add Entry"
            onClicked: {
                var response = Provider.addEntry(name.text, token.text)
                if (response.name || response.token) {
                  if (response.name) errorName.text = response.name;
                  if (response.token) errorToken.text = response.token;
                  return;
                }
                
                root.pageStack.pop()
            }
        }
    }
}
