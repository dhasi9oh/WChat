import QtQuick 2.15
import QtQuick.Controls
import FluentUI
import UsrMgr

FluRectangle {

    ListModel {
        id: apply_friend_page_listmodel
    }

    Component {
        id: apply_friend_page_delegate

        Button {
            height: 60
            width: parent.width

            Row {
                spacing: 10
                anchors.fill: parent
                leftPadding: 10

                FluImage {
                    id: usr_img
                    width: 40
                    height: 40
                    source: "qrc:/images/private_image.png"
                    anchors.verticalCenter: parent.verticalCenter
                }

                FluText {
                    id: usr_name
                    text: qsTr(name)
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            background: FluRectangle {
                anchors.fill: parent
                color: "white"
            }

            onClicked: {
                apply_friend_page_authen.open()
            }
        }
    }

    AuthenFriendWindow {
        id: apply_friend_page_authen
    }

    Column {
        anchors.fill: parent

        FluText {
            height: 60
            width: parent.width
            leftPadding: 14
            font.pointSize: 14
            color: "#404142"
            text: qsTr("新的朋友")
            verticalAlignment: Text.AlignVCenter
        }

        ListView {
            id: apply_friend_page_listview
            clip: true
            width: parent.width
            height: parent.height - 60
            model: apply_friend_page_listmodel
            delegate: apply_friend_page_delegate
            boundsBehavior: Flickable.OvershootBounds
        }
    }

    Connections {
        target: UsrMgr
        function onAddApply(name, desc, icon, nick, sex, uid, status) {
            apply_friend_page_listmodel.append(
                        {"name": name, "desc": desc, "icon": icon,
                            "nick": nick, "sex": sex, "uid": uid, "status": status});
        }
    }
}
