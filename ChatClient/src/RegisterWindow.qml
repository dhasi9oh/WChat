import QtQuick 2.15
import QtQuick.Layouts
import FluentUI 1.0

Rectangle {

    signal registerGetVarifyCodeButtonClicked(string email);
    signal registerConfirmButtonClicked(
        string usr,
        string email,
        string pwd,
        string confirm,
        string varifycode);

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
                height: 60
                color: "transparent"
                anchors.horizontalCenter: parent.horizontalCenter
            }


            FluTextBox {
                id: usr_text
                placeholderText: qsTr("请输入用户名")
                anchors.horizontalCenter: parent.horizontalCenter
            }

            FluTextBox {
                id: email_text
                placeholderText: qsTr("请输入邮箱")
                anchors.horizontalCenter: parent.horizontalCenter
            }

            FluPasswordBox{
                id: pwd_text
                placeholderText: qsTr("请输入密码")
                width: usr_text.width
                anchors.horizontalCenter: parent.horizontalCenter
            }

            FluPasswordBox{
                id: confirm_pwd_text
                placeholderText: qsTr("再次输入密码")
                width: usr_text.width
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
                        registerGetVarifyCodeButtonClicked(varify_code_text.text);
                    }
                }
            }

            FluRectangle{
                radius: [0,0,0,0]
                width: 40
                height: 40
                color: "transparent"
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Row {
                spacing: 10
                anchors.horizontalCenter: parent.horizontalCenter

                FluFilledButton {
                    id: confirm_btn
                    text: qsTr("确认")
                    width: usr_text.width / 2 - 15
                    onClicked: {
                        if (usr_text.text.length === 0) {
                            showError(qsTr("请输入账户"));
                        }
                        else if (pwd_text.text.length === 0) {
                            showError(qsTr("请输入密码"));
                        }
                        else if (email_text.text.length === 0) {
                            showError(qsTr("请输入邮箱"));
                        }
                        else if (confirm_pwd_text.text.length === 0) {
                            showError(qsTr("请确认密码"));
                        }
                        else if (varify_code_text.text.length === 0) {
                            showError(qsTr("请输入验证码"));
                        }
                        else {
                            registerConfirmButtonClicked(
                                        usr_text.text,
                                        email_text.text,
                                        pwd_text.text,
                                        confirm_pwd_text.text,
                                        varify_code_text.text
                                        );
                        }
                    }
                }

                FluTextButton {
                    id: cancel_btn
                    text: qsTr("取消")
                    width: usr_text.width / 2 - 15
                    onClicked: {
                        init_window.mode = 0
                    }
                }
            }
        }
    }
}
