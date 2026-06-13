import PomodoroTimerWidget

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


ApplicationWindow {
    id: root
/*    width: 420
    height: 320*/
    visible: true
    title: "Paz"

    color: "#f4f4f5"

    menuBar: MenuBar {
        Menu {
            title: "Menu1"
            MenuSeparator{}

        }
        Menu {
            title: "Menu2"
        }
    }


    RowLayout {
        anchors.fill: parent
        spacing: 0

        PomodoroTimerWidget {}
    }



}
