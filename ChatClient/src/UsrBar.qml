import QtQuick 2.15
import QtQuick.Layouts
import FluentUI
import TcpMgr
import UsrMgr

FluRectangle {
    color: "#efefef"
    radius: [0,0,0,0]

    signal usrBarMsgItemClicked(int idx);
    property ListModel usrBarMsgListModel: usr_msg_page.usrMsgPageModel
    property int usrBarStackIndex: 0

    Column {
        spacing: 0
        anchors.fill: parent

        SearchBar {
            id: search_bar
            height: 60
            width: parent.width
        }

        StackLayout {
            id: usr_bar_stack
            height: 500
            width: parent.width
            currentIndex: usrBarStackIndex

            UsrInfoPage {
                id: usr_info_page
            }

            UsrMsgPage {
                id: usr_msg_page
            }

            SearchPage {
                id: search_page
            }
        }
    }
    Connections {
        target: search_bar
        function onSearchBarTextEdited(str) {
            //根据字符串查找联系人
            var items = [];
            var lowerStr = str.toLowerCase();
            for (var i = 0; i < usr_info_page.usrInfoPageModel.count; i++) {
                var name = usr_info_page.usrInfoPageModel.get(i).name;
                if (name.toLowerCase().startsWith(lowerStr)) {
                    items.push(usr_info_page.usrInfoPageModel.get(i));
                }
            }
            search_page.searchPageModel.clear()
            search_page.searchPageModel.append(items)
            usrBarStackIndex = 2
        }
    }
    Connections {
        target: usr_info_page
        function onUsrInfoPageListViewItemClicked(idx) {
            //点击infopage中的联系人
            chat_window_stacklayout.currentIndex = 1;
            var i = 0;
            var exist = false;
            var usr_info_idx_item_uid = usr_info_page.usrInfoPageModel.get(idx).uid;
            for (; i < usr_msg_page.usrMsgPageModel.count; i++) {
                var uid = usr_msg_page.usrMsgPageModel.get(i).uid;
                if (usr_info_idx_item_uid === uid) {
                    exist = true;
                    break;
                }
            }
            if (exist) {
                usrBarStackIndex = 1;
                usr_msg_page.usrMsgPageListViewItemClicked(i);
            }
            else {
                usr_msg_page.usrMsgPageModel.insert(0, usr_info_page.usrInfoPageModel.get(idx));
                usrBarStackIndex = 1;
                usr_msg_page.usrMsgPageListViewItemClicked(0);
            }
        }
    }
    Connections {
        target: search_page
        function onSearchPageListViewItemClicked(idx) {
            //点击搜索出的联系人
            chat_window_stacklayout.currentIndex = 1;
            var i = 0;
            var exist = false;
            var search_idx_item_uid = usr_info_page.usrInfoPageModel.get(idx).uid;
            for (; i < usr_msg_page.usrMsgPageModel.count; i++) {
                var uid = usr_msg_page.usrMsgPageModel.get(i).uid;
                if (search_idx_item_uid === uid) {
                    exist = true;
                    break;
                }
            }
            if (exist) {
                usrBarStackIndex = 1;
                usr_msg_page.usrMsgPageListViewItemClicked(i);
            }
            else {
                usr_msg_page.usrMsgPageModel.insert(0, search_page.searchPageModel.get(idx));
                usrBarStackIndex = 1;
                usr_msg_page.usrMsgPageListViewItemClicked(0);
            }
        }
    }
    Connections {
        target: usr_msg_page
        function onUsrMsgPageListViewItemClicked(idx) {
            usrBarMsgItemClicked(idx);
        }
    }
}
