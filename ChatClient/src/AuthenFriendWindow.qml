import QtQuick 2.15
import QtQuick.Controls
import FluentUI

Popup {
    id: self
    width: 280
    height: 400
    modal: true
    closePolicy: Popup.CloseOnEscape

    signal accept();
    signal reject();
    property int to_uid: 0 //对方的uid
    property int from_uid: 0 //我的uid
    property string back_name: "" //备注

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
            height: 48
            width: parent.width
            text: qsTr("通过好友验证")
            font.bold: true
            font.pointSize: 14
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        FluRectangle {
            height: 1
            color: "#404142"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        FluText {
            text: qsTr("备注")
            anchors.horizontalCenter: parent.horizontalCenter
        }

        FluTextBox{
            anchors.horizontalCenter: parent.horizontalCenter
        }

        FluText {
            text: qsTr("描述:")
            height: 100
            anchors.horizontalCenter: parent.horizontalCenter
        }

        FluCopyableText{
            text: qsTr("hello")
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Item {
            height: 80
            width: parent.width
        }

        Row {
            spacing: 40
            anchors.horizontalCenter: parent.horizontalCenter

            FluFilledButton{
                text: qsTr("接受")
                onClicked: {
                    accept();
                    close();
                }
            }

            FluButton{
                text: qsTr("拒绝")
                onClicked: {
                    reject();
                    close();
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
