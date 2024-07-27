import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts
import FluentUI
import TcpMgr

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
                    id: chat_window_chatpage_repeater
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

    Connections {
        target: TcpMgr
        function onSignalChatMsg(uid, msg, left) {
            var j = 0;
            var item;
            for (; j < usr_bar.usrInfoModel.count; j++) {
                if (uid === usr_bar.usrInfoModel.get(j).uid) {
                    item = usr_bar.usrInfoModel.get(j);
                    break;
                }
            }

            var i = 0;
            var exist = false;
            for (; i < usr_bar.usrBarMsgListModel.count; i++) {
                if (uid === usr_bar.usrBarMsgListModel.get(i).uid) {
                    chat_window_chatpage_repeater
                    .itemAt(i)
                    .chat_page_listmodel
                    .append({"is_left": left, "msg": msg});
                    exist = true;
                    break;
                }
            }

            if (!exist) {
                usr_bar.usrBarMsgListModel.insert(0, item);
                chat_window_chatpage_repeater
                .itemAt(i)
                .chat_page_listmodel
                .append({"is_left": left, "msg": msg, "name": item["name"]});
            }
        }
    }
}
