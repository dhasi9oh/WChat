import QtQuick 2.15
import FluentUI

FluRectangle {
    id: self
    radius: [0,0,0,0]
    color: "transparent"

    signal searchBarTextEdited(string s)

    Row {
        spacing: 10
        leftPadding: 10
        anchors.fill: parent

        FluTextBox {
            id: search_bar_textbox
            width: 200
            placeholderText: qsTr("搜索")
            anchors.verticalCenter: parent.verticalCenter

            onTextChanged: {
                self.searchBarTextEdited(search_bar_textbox.text)
            }
        }

        FluIconButton {
            id: search_bar_add_btn
            width: 32
            height: 32
            normalColor: "#dcd9d8"
            hoverColor: "#d1d1d1"
            pressedColor: "#d1d1d1"
            iconSource: FluentIcons.ZoomIn
            anchors.verticalCenter: parent.verticalCenter

            FluTooltip {
                visible: search_bar_add_btn.hovered
                text: qsTr("添加好友")
                delay: 500
            }

            onClicked: {
                apply_friend_window.open();
            }
        }
    }

    ApplyFriendWindow {
        id: apply_friend_window
    }

}
