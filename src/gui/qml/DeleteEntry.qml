import QtQuick 2.1
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.1 as Controls
import org.kde.kirigami 2.2 as Kirigami
import org.kde.onetimepass.provider 1.0

Controls.Dialog {
    property string name
    
    anchors.centerIn: parent
    modal: true
    visible: true
    title: "Delete Token"
    standardButtons: Controls.Dialog.Yes | Controls.Dialog.Cancel
    Controls.Label {
      width: root.availableWidth
      text: "Are you sure you wish to delete this token?"
      wrapMode: Controls.Label.Wrap
    }
    onAccepted: {
      Provider.removeEntry(name)
    }
}
