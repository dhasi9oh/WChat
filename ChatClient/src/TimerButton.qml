import QtQuick 2.15
import QtQuick.Controls
import FluentUI 1.0

FluFilledButton {
    id: self

    property string str: ""
    property int repeat_cnt: 10
    property int cur_cnt: repeat_cnt

    text: str

    Timer {
        id: timer
        repeat: true
        interval: 1000
        onTriggered: {
            self.cur_cnt -= 1

            if (self.cur_cnt <= 0) {
                self.cur_cnt = repeat_cnt
                self.disabled = false
                self.text = str
                stop()
            }
            else {
                self.text = self.cur_cnt.toString()
                self.disabled = true
            }
        }

    }

    onReleased: {
        self.text = self.cur_cnt.toString()
        self.disabled = true
        timer.start()
    }
}
