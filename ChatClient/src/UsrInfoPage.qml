import QtQuick 2.15
import QtQuick.Controls 2.15
import FluentUI 1.0
import UsrMgr

FluRectangle {
    color: "transparent"

    signal usrInfoPageListViewItemClicked(int idx);
    property ListModel usrInfoPageModel: usr_info_page_model

    ListModel {
        id: usr_info_page_model
    }

    Component {
        id: usr_info_page_delegate
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
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
            onClicked: {
                chat_window_stacklayout.currentIndex = 1;
                usrInfoPageListViewItemClicked(index);
            }
        }
    }

    Column {
        anchors.fill: parent
        FluText {
            height: 20
            width: parent.width
            text: qsTr("联系人")
            color: "#404142"
            leftPadding: 10
        }
        ListView {
            id: usr_info_page_listview
            height: parent.height - 50
            width: parent.width
            model: usr_info_page_model
            clip: true  // 超出边界的内容自动隐藏
            delegate: usr_info_page_delegate
            boundsBehavior: Flickable.OvershootBounds
        }
    }

    Connections {
        target: UsrMgr
        function onAddFriend(name, icon, nick, sex, uid) {
            usr_info_page_model.append({"name": name, "icon": icon, "nick": nick, "sex": sex, "uid": uid})
        }
    }
}
