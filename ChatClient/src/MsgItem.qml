import QtQuick 2.15
import QtQuick.Controls
import FluentUI
import MsgControls

FluRectangle {
    id: self
    color: "transparent"
    height: textArea.height + msg_usr_name.height

    Row {
        spacing: 2
        anchors.fill: parent
        leftPadding: 8

        FluImage {
            id: msg_left_img
            width: is_left ? 32 : 0
            height: is_left ? 32 : 0
            source: is_left ? "qrc:/images/private_image.png" : ""
            y: 8
        }

        Column {
            height: parent.height
            width: parent.width - 36

            FluText {
                id: msg_usr_name
                height: 16
                width: parent.width
                text: name
                leftPadding: 10
            }

            MsgRectangle {
                isLeft: is_left
                color: is_left ? "white" : "#9eea6a"
                width: Math.min(textArea.implicitWidth, self.width - 48)
                height: textArea.implicitHeight + 16

                Text {
                    id: textArea
                    text: msg
                    width: self.width - 48
                    height: parent.height
                    font.family: "微软雅黑"
                    font.pointSize: 12
                    leftPadding: is_left ? 12 : 8
                    rightPadding: is_left ? 8 : 12
                    wrapMode: Text.Wrap
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }

        FluImage {
            id: msg_right_img
            width: is_left ? 0 : 32
            height: is_left ? 0 : 32
            source: is_left ? "" : "qrc:/images/private_image.png"
        }
    }

    FontMetrics {
        id: fontMetrics
        font: textArea.font
    }

    function getDynamicHeight(max_len, cur_len, row_height) {
        if (cur_len < max_len) {
            return row_height;
        }

        var cnt = Math.ceil(cur_len / max_len);
        if (cur_len !== max_len) {
            cnt += 1;
        }
        var h = cnt * row_height;
        return h;
    }
}
