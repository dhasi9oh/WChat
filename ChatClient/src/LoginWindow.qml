import QtQuick 2.15
import FluentUI 1.0
import HttpMgr

Rectangle {

    signal loginButtonClicked(string usr, string pwd);

    StatusLayout {
        id: status_layout
        anchors.fill: parent
        statusMode: FluStatusLayoutType.Success
        Column {
            spacing: 10
            anchors.centerIn: parent
            FluRectangle{
                radius: [0,0,0,0]
                width: 40
                height: 40
                color: "transparent"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            FluImage{
                id: my_image
                width: 100
                height: 100
                source: "qrc:/images/private_image.png"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            FluTextBox {
                id: usr_text
                placeholderText: qsTr("请输入账户")
                anchors.horizontalCenter: parent.horizontalCenter
            }
            FluPasswordBox {
                id: pwd_text
                placeholderText: qsTr("请输入密码")
                anchors.horizontalCenter: parent.horizontalCenter
            }
            FluFilledButton{
                text: qsTr("登录")
                width: usr_text.width
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    if (usr_text.text.length === 0) {
                        showError(qsTr("请输入账户"));
                    }
                    else if (pwd_text.text.length === 0) {
                        showError(qsTr("请输入密码"));
                    }
                    else {
                        status_layout.statusMode = FluStatusLayoutType.Loading;
                        HttpMgr.loginButtonClicked(usr_text.text, pwd_text.text);
                    }
                }
            }
            FluButton{
                text: qsTr("注册")
                width: usr_text.width
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    init_window.mode = 1
                }
            }
            FluTextButton{
                id: reset_pwd
                text: qsTr("找回密码")
                width: usr_text.width
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    init_window.mode = 2
                }
            }
        }
    }

}
