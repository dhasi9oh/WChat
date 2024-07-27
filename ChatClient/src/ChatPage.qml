import QtQuick
import QtQuick.Controls
import Qt5Compat.GraphicalEffects
import FluentUI

FluRectangle {
    color: "#f5f5f5"

    property alias chatPageListmodel: chat_page_listmodel

    ListModel {
        id: chat_page_listmodel
    }

    Component {
        id: chat_page_delegate

        MsgItem {
            width: chat_page_listview.width
        }
    }

    Column {
        spacing: 1
        anchors.fill: parent

        FluRectangle {
            height: 40
            width: parent.width
            color: "#f5f5f5"

            Text{
                id: usr_name_text
                anchors.fill: parent
                text: qsTr(name)
                font.bold: true
                font.pointSize: 12
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }

        FluRectangle {
            color: "#f5f5f5"
            height: 360
            width: parent.width

            ListView {
                id: chat_page_listview
                clip: true
                anchors.fill: parent
                model: chat_page_listmodel
                delegate: chat_page_delegate
                boundsBehavior: Flickable.StopAtBounds
            }
        }

        FluRectangle {
            height: 38
            width: parent.width
            color: "#ffffff"

            Row {
                spacing: 5
                leftPadding: 10
                anchors.fill: parent

                FluIconButton {
                    id: emoji_btn
                    iconSource: FluentIcons.Emoji2
                    anchors.verticalCenter: parent.verticalCenter

                    FluTooltip {
                        visible: emoji_btn.hovered
                        text: qsTr("表情")
                        delay: 500
                    }
                }

                FluIconButton {
                    id: file_btn
                    iconSource: FluentIcons.FolderFill
                    anchors.verticalCenter: parent.verticalCenter

                    FluTooltip {
                        visible: file_btn.hovered
                        text: qsTr("文件")
                        delay: 500
                    }
                }
            }
        }

        FluRectangle {
            height: 80
            width: parent.width
            color: "#ffffff"
            TextArea {
                font.pointSize: 12
                anchors.fill: parent
            }
        }

        FluRectangle {
            height: 38
            width: parent.width
            color: "#ffffff"

            Row {
                spacing: 5
                anchors.fill: parent
                Item {
                    width: 400
                    height: 60
                }

                FluFilledButton {
                    id: send_btn
                    text: qsTr("发送")
                    anchors.verticalCenter: parent.verticalCenter
                }

                FluButton {
                    id: recv_btn
                    text: qsTr("接收")
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
    }
}
