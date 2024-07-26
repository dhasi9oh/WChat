import QtQuick 2.15
import QtQuick.Layouts
import FluentUI 1.0

Rectangle {

    signal resetGetVarifyCodeButtonClicked(string email);
    signal resetResetButtonClicked(
        string usr,
        string email,
        string newPwd,
        string varifycode);

    StatusLayout {
        id: status_layout
        anchors.fill: parent
        statusMode: FluStatusLayoutType.Success

        Column {
            spacing: 20
            anchors.centerIn: parent

            FluTextBox {
                id: usr_text
                placeholderText: qsTr("请输入用户")
                anchors.horizontalCenter: parent.horizontalCenter
            }

            FluTextBox {
                id: email_text
                placeholderText: qsTr("请输入邮箱")
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Row {
                spacing: 10
                anchors.horizontalCenter: parent.horizontalCenter

                FluTextBox {
                    id: varify_code_text
                    placeholderText: qsTr("请输入验证码")
                    width: 155
                }

                TimerButton {
                    id: get_varify_code_btn
                    str: "获取验证码"
                    width: 75
                    onClicked: {
                        status_layout.statusMode = FluStatusLayoutType.Loading;
                        resetGetVarifyCodeButtonClicked(varify_code_text.text);
                    }
                }
            }

            FluPasswordBox{
                id: new_pwd_text
                placeholderText: qsTr("请输入新密码")
                width: usr_text.width
                anchors.horizontalCenter: parent.horizontalCenter
            }

            FluRectangle {
                radius: [25,25,25,25]
                width: 50
                height: 50
                color: "transparent"
            }

            Row {
                spacing: 10
                anchors.horizontalCenter: parent.horizontalCenter

                FluFilledButton {
                    text: qsTr("确认")
                    width: usr_text.width / 2 - 15
                    onClicked: {
                        if (usr_text.text.length === 0) {
                            showError("请输入用户");
                        }
                        else if (new_pwd_text.text.length === 0) {
                            showError("请输入新密码");
                        }
                        else if (email_text.text.length === 0) {
                            showError("请输入邮箱");
                        }
                        else if (varify_code_text.text.length === 0) {
                            showError("请输入验证码");
                        }
                        else {
                            resetResetButtonClicked(
                                        usr_text.text,
                                        email_text.text,
                                        new_pwd_text.text,
                                        varify_code_text.text);
                        }
                    }
                }

                FluTextButton {
                    text: "取消"
                    width: usr_text.width / 2 - 15
                    onClicked: {
                        init_window.mode = 0
                    }
                }
            }
        }
    }
}
