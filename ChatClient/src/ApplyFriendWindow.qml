import QtQuick 2.15
import QtQuick.Controls
import FluentUI
import TcpMgr
import UsrMgr

Popup {
    id: self
    width: 280
    height: 400
    modal: true
    closePolicy: Popup.CloseOnEscape

    Column {
        spacing: 5
        leftPadding: 5
        rightPadding: 5
        anchors.fill: parent

        Row {
            height: 32
            width: parent.width

            Item {
                height: parent.height
                width: parent.width - 40
            }

            FluIconButton {
                width: 32
                height: 32
                iconSize: 20
                iconSource: FluentIcons.Cancel
                onClicked: {
                    self.close()
                }
            }
        }

        FluText {
            width: parent.width
            height: 40

            text: qsTr("申请添加好友")
            font.bold: true
            font.pointSize: 12
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        FluRectangle {
            width: parent.width - 40
            height: 1
            color: "#404142"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        FluText {
            text: qsTr("好友的账户")
            anchors.horizontalCenter: parent.horizontalCenter
        }

        FluTextBox{
            placeholderText: qsTr(usrNameStr)
            anchors.horizontalCenter: parent.horizontalCenter
        }

        FluText {
            id: back_name
            text: qsTr("备注")
            anchors.horizontalCenter: parent.horizontalCenter
        }

        FluTextBox{
            placeholderText: qsTr("备注")
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Item {
            width: parent.width
            height: 120
        }

        Row {
            spacing: 40
            anchors.horizontalCenter: parent.horizontalCenter

            FluFilledButton{
                id: accept_btn
                text: qsTr("确认")
                onClicked: {
                    TcpMgr.addFriend(UsrMgr.getUid(),
                                     UsrMgr.getUsrName(),
                                     back_name.text,
                                     to_uid);
                    self.close();
                }
            }

            FluButton{
                id: reject_btn
                text: qsTr("取消")
                onClicked: {
                    self.close();
                }
            }
        }

    }

    onOpened: {
        var screenWidth = init_window.width
        var screenHeight = init_window.height
        var windowWidth = self.width
        var windowHeight = self.height

        self.x = (screenWidth - windowWidth) / 2
        self.y = (screenHeight - windowHeight) / 2 - 50
    }

}
