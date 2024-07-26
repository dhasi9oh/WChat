import QtQuick 2.15
import QtQuick.Controls 2.15
import FluentUI 1.0

FluRectangle {
    color: "transparent"

    signal usrMsgPageListViewItemClicked(int idx);
    property ListModel usrMsgPageModel: usr_msg_page_model

    ListModel {
        id: usr_msg_page_model
    }

    Component {
        id: usr_msg_page_delegate

        Button {
            height: 60
            width: parent.width
            background: Rectangle {
                color: usr_msg_page_listview.currentIndex == index ? "#eeeeee" :"white"
            }

            Row {
                spacing: 10
                anchors.fill: parent
                leftPadding: 10
                rightPadding: 10

                FluImage {
                    id: usr_img
                    width: 40
                    height: 40
                    source: "qrc:/images/private_image.png"
                    anchors.verticalCenter: parent.verticalCenter

                    FluBadge {
                        isDot: true
                        topRight: true
                        color: "red"
                    }
                }

                Column {
                    width: 140
                    height: 40
                    spacing: 4
                    anchors.verticalCenter: parent.verticalCenter

                    FluText {
                        id: usr_name
                        text: qsTr(name)
                    }

                    FluText {
                        id: usr_msg
                        text: qsTr(msg)
                    }
                }

                FluText {
                    id: usr_time
                    text: qsTr(msg_time)
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            onClicked: {
                chat_window_stacklayout.currentIndex = 1;
                usrMsgPageListViewItemClicked(index);
            }
        }
    }

    Column {
        spacing: 0
        anchors.fill: parent

        FluText {
            height: 20
            width: parent.width
            text: qsTr("消息")
            color: "#404142"
            leftPadding: 10
            verticalAlignment: verticalAlignment
        }

        ListView {
            id: usr_msg_page_listview
            height: parent.height - 20
            width: parent.width
            model: usr_msg_page_model
            clip: true  // 超出边界的内容自动隐藏
            delegate: usr_msg_page_delegate
            boundsBehavior: Flickable.OvershootBounds
        }
    }

    onUsrMsgPageListViewItemClicked: (idx) => {
        usr_msg_page_listview.currentIndex = idx;
    }
}
