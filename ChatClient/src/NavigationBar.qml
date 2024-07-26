import QtQuick 2.15
import QtQuick.Controls
import FluentUI

FluRectangle {
    radius: [0,0,0,0]
    color: "#f8f8f8"

    Column {
        spacing: 15
        anchors.fill: parent

        FluRectangle{
            height: 1
            width: 40
            color: "#d2d2d2"
        }

        FluImage {
            id: private_img
            width: 40
            height: 40
            source: "qrc:/images/private_image.png"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        FluIconButton {
            id: message
            iconSource: FluentIcons.ChatBubbles
            anchors.horizontalCenter: parent.horizontalCenter

            FluTooltip {
                visible: message.hovered
                text: qsTr("消息")
                delay: 500
            }

            onClicked: {
                usr_bar.usrBarStackIndex = 1
            }
        }

        FluIconButton {
            id: linkman
            iconSource: FluentIcons.Contact
            anchors.horizontalCenter: parent.horizontalCenter

            FluTooltip {
                visible: linkman.hovered
                text: qsTr("联系人")
                delay: 500
            }

            onClicked: {
                usr_bar.usrBarStackIndex = 0
            }
        }


        FluIconButton {
            id: addfrend
            iconSource: FluentIcons.AddFriend
            anchors.horizontalCenter: parent.horizontalCenter

            FluTooltip {
                visible: addfrend.hovered
                text: qsTr("新的朋友")
                delay: 500
            }

            onClicked: {
                chat_window_stacklayout.currentIndex = 2
            }
        }

    }
}
