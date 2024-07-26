import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts
import FluentUI

FluRectangle {
    id: chat_window
    color: "#f5f5f5"

    property var map: new Map();

    Row {
        spacing: 0
        anchors.fill: parent

        NavigationBar {
            width: 60
            height: parent.height
        }
        UsrBar {
            id: usr_bar
            width: 260
            height: parent.height
        }
        StackLayout {
            id: chat_window_stacklayout
            width: 520
            height: parent.height

            FluRectangle {
                color: "transparent"
                FluImage {
                    width: 72
                    height: 72
                    anchors.centerIn: parent
                    source: "qrc:/images/private_image.png"
                }
            }

            StackLayout {
                id: chat_window_chatpage_stacklayout

                Repeater {
                    model: usr_bar.usrBarMsgListModel
                    ChatPage {

                    }
                }
            }

            ApplyFirendPage {

            }
        }
    }

    Connections {
        target: usr_bar
        function onUsrBarMsgItemClicked(idx) {
            chat_window_chatpage_stacklayout.currentIndex = idx
        }
    }
}
