import QtQuick 2.1
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.1 as Controls
import org.kde.kirigami 2.2 as Kirigami
import org.kde.onetimepass.provider 1.0
    
Kirigami.ScrollablePage {
    property string name
    property string token
    
    title: "Add Entry"
    
    ColumnLayout {
        Controls.Label {
            text: "Name:"
        }
        Controls.TextField {
            anchors.left: parent.left
            anchors.right: parent.right
            text: name
            Layout.alignment: Qt.AlignHCenter
        }
        Controls.Label {
            text: "Token:"
        }
        Controls.TextField {
            anchors.left: parent.left
            anchors.right: parent.right
            text: token
            Layout.alignment: Qt.AlignHCenter
        }
        Controls.Button {
            anchors.left: parent.left
            anchors.right: parent.right
            text: "Add Entry"
            onClicked: {
                Provider.addEntry(name.text, token.text)
                root.pageStack.pop()
            }
        }
    }
}
