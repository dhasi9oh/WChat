import QtQuick 2.15
import QtQuick.Layouts
import FluentUI 1.0

FluStatusLayout {

    signal stopClicked

    id: self

    loadingItem: Component{
        id:com_loading
        FluFrame{
            padding: 0
            border.width: 0
            radius: 0
            color:self.color
            ColumnLayout{
                anchors.centerIn: parent
                FluProgressRing{
                    indeterminate: true
                    Layout.alignment: Qt.AlignHCenter
                }
                FluText{
                    text:self.loadingText
                    Layout.alignment: Qt.AlignHCenter
                }
                FluFilledButton {
                    id:btn_stop
                    Layout.alignment: Qt.AlignHCenter
                    text: qsTr("取消")
                    onClicked:{
                        self.stopClicked()
                    }
                }
            }
        }
    }



}
