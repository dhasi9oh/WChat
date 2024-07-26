import QtQuick
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Controls
import FluentUI 1.0
import HttpMgr
import TcpMgr

FluWindow {
    id: init_window
    visible: true
    title: qsTr("微信")
    backgroundColor: "#f5f5f5"
    width: 280
    height: 400
    minimumWidth: 280
    maximumWidth: 280
    minimumHeight: 400
    maximumHeight: 400

    property int mode: 0

    StackLayout {
        id: init_window_stacklayout
        currentIndex: 0
        anchors.fill: parent

        FluRectangle {
            StackLayout {
                anchors.fill: parent
                currentIndex: mode

                LoginWindow {
                    id: login_window
                }
                RegisterWindow {
                    id: register_window
                }
                ResetWindow {
                    id: reset_window
                }
            }
        }

        ChatWindow {
        }

        onCurrentIndexChanged: {
            if (currentIndex === 1) {
                init_window.width = 840
                init_window.height = 590
                init_window.minimumWidth = 840
                init_window.maximumWidth = 840
                init_window.minimumHeight = 590
                init_window.maximumHeight = 590

                var screen = Qt.application.screens[0]
                var screenWidth = screen.width
                var screenHeight = screen.height
                var windowWidth = init_window.width
                var windowHeight = init_window.height

                init_window.x = (screenWidth - windowWidth) / 2
                init_window.y = (screenHeight - windowHeight) / 2 - 50
            }
        }
    }

    Connections {
        target: login_window
        function onLoginButtonClicked(usr, pwd) {
            HttpMgr.onLoginButtonClicked(usr, pwd);
        }
    }
    Connections {
        target: reset_window
        function onResetResetButtonClicked(usr, email, newPwd, varifycode) {
            HttpMgr.onResetButtonClicked(usr, email, newPwd, varifycode);
        }
    }
    Connections {
        target: register_window
        function onRegisterConfirmButtonClicked(usr, email, pwd, confirm_pwd, varifycode) {
            HttpMgr.onRegisterButtonClicked(usr, email, pwd, confirm_pwd, varifycode);
        }
    }
    Connections {
        target: HttpMgr
        function onSignalShowInfo(str) {
            showSuccess(qsTr(str));
        }
        function onSignalShowError(str) {
            showError(qsTr(str));
        }
    }
    Connections {
        target: TcpMgr
        function onSignalSwichChatdlg() {
            init_window_stacklayout.currentIndex = 1;
        }
    }
}
