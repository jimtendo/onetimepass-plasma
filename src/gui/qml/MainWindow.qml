import QtQuick 2.1
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.1 as Controls
import org.kde.kirigami 2.2 as Kirigami
import org.kde.onetimepass.provider 1.0

Kirigami.ApplicationWindow {
    id: root
    width: 320
    header: Kirigami.ApplicationHeader {
      background: Rectangle {
        anchors.fill: parent
        color: Kirigami.Theme.highlightColor
      }
    }
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
                    //token: modelData.token
                }
                focus: true
            }
        }
    }
    
    Component {
        id: addEntry
        Kirigami.ScrollablePage {
            title: "Add Entry"
            ColumnLayout {
                Controls.Label {
                    text: "Name:"
                }
                Controls.TextField {
                    id: name
                    anchors.left: parent.left
                    anchors.right: parent.right
                    text: ""
                    Layout.alignment: Qt.AlignHCenter
                }
                Controls.Label {
                    text: "Token:"
                }
                Controls.TextField {
                    id: token
                    anchors.left: parent.left
                    anchors.right: parent.right
                    text: ""
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
    }
}
