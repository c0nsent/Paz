import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import PazQml

ApplicationWindow {
    width: 420
    height: 320
    visible: true
    title: "Paz Timer"

    // Задаем базовый фон окна
    color: "#f4f4f5"

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 20

        // Индикатор текущей фазы
        Label {
            id: phaseLabel
            text: "Work Phase" // В будущем здесь будет привязка к переменной из C++
            font.pixelSize: 24
            font.weight: Font.Bold
            color: "#e74c3c" // Красный оттенок, ассоциирующийся с "pomodoro"
            Layout.alignment: Qt.AlignHCenter
        }

        // Таймер
        Label {
            id: timeLabel
            text: "25:00" // В будущем: pomodoroTimer.timeRemainingString
            font.pixelSize: 72
            font.family: "Monospace" // Моноширный шрифт, чтобы цифры не "прыгали"
            font.weight: Font.DemiBold
            color: "#2c3e50"
            Layout.alignment: Qt.AlignHCenter
        }

        // Панель управления (кнопки)
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 15

            Button {
                text: "Start"
                font.pixelSize: 16
                onClicked:
            }

            Button {
                text: "Pause"
                font.pixelSize: 16
                // onClicked: myCplusplusTimer.pause()
            }

            Button {
                text: "Reset"
                font.pixelSize: 16
                // onClicked: myCplusplusTimer.reset()
            }
        }
    }
}
