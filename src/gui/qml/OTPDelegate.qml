/*
 *   Copyright 2010 Marco Martin <notmart@gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Library General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  2.010-1301, USA.
 */

import QtQuick 2.1
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.1 as Controls
import org.kde.kirigami 2.2 as Kirigami
import org.kde.onetimepass.provider 1.0

/**
 * An item delegate for the primitive ListView component.
 *
 * It's intended to make all listviews look coherent.
 * It has a default icon and a label
 *
 * @inherit AbstractListItem
 */
Kirigami.AbstractListItem {
    id: listItem

    property alias name: nameItem.text
    property alias code: codeItem.text

    ColumnLayout {
        anchors {
            left: parent.left
            right: parent.right
            verticalCenter: parent.verticalCenter
        }
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        RowLayout {
            ColumnLayout {
                Controls.Label {
                    id: codeItem
                    font.pointSize: 36
                    color: Kirigami.Theme.activeTextColor
                }
                Controls.Label {
                    id: nameItem
                    color: listItem.checked || listItem.pressed ? listItem.activeTextColor : listItem.textColor
                }
            }
            Item {
                Layout.fillWidth: true
            }
            Controls.Button {
                id: removeButton
                text: "Remove"
                onClicked: {
                  root.deleteEntry(name);
                }
            }
        }
        Controls.ProgressBar {
            Layout.fillWidth: true
            id: progressBar
            value: 30 - (+new Date()/1000 % 30)
            from: 0
            to: 30
            Timer {
                interval: 1000; running: true; repeat: true
                onTriggered: progressBar.value = 30 - (+new Date()/1000 % 30);
            }
        }
    }
    
    onClicked: Provider.setClipboard(code)
}
