import QtQuick 2.15
import QtQuick.Controls
import FluentUI

FluRectangle {
    color: "transparent"

    signal searchPageListViewItemClicked(int idx);
    property ListModel searchPageModel: search_page_model

    ListModel {
        id: search_page_model

        ListElement {
            name: "Bill Smith"
        }
        ListElement {
            name: "John Brown"
        }
        ListElement {
            name: "Sam Wise"
        }
        ListElement {
            name: "Bill Smith"
        }
    }

    Component {
        id: search_page_delegate
        Button {
            height: 60
            width: search_page_listview.width
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
                searchPageListViewItemClicked(index);
            }
        }
    }

    Column {
        anchors.fill: parent
        FluText {
            height: 20
            width: parent.width
            text: qsTr("消息")
            color: "#404142"
            leftPadding: 10
        }

        ListView {
            id: search_page_listview
            clip: true
            width: parent.width
            height: parent.height - 20
            model: search_page_model
            delegate: search_page_delegate
            boundsBehavior: Flickable.OvershootBounds
        }
    }

}
