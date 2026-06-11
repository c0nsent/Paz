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

    PomodoroTimer {
        id: pomodoroTimer
    }

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 20

        // Индикатор текущей фазы
        Label {
            id: phaseLabel
            text: {
                if (pomodoroTimer.phase === PomodoroTimer.Work) return "Work Phase";
                if (pomodoroTimer.phase === PomodoroTimer.ShortBreak) return "Short Break";
                if (pomodoroTimer.phase === PomodoroTimer.LongBreak) return "Long Break";
                return "Unknown";
            }
            font.pixelSize: 24
            font.weight: Font.Bold
            color: "#e74c3c" // Красный оттенок, ассоциирующийся с "pomodoro"
            Layout.alignment: Qt.AlignHCenter
        }



        // Таймер
        Label {
            id: timeLabel
            text: pomodoroTimer.timeRemainingString
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
                text: pomodoroTimer.state === PomodoroTimer.Running ? "Running..." : "Start"
                enabled: pomodoroTimer.state !== PomodoroTimer.Running
                font.pixelSize: 16
                onClicked: pomodoroTimer.start()
            }

            Button {
                text: "Pause"
                enabled: pomodoroTimer.state === PomodoroTimer.Running
                font.pixelSize: 16
                onClicked: pomodoroTimer.pause()
            }

            Button {
                text: "Reset"
                font.pixelSize: 16
                onClicked: pomodoroTimer.reset()
            }


        }



        Label {

           property int pomodoroCount: pomodoroTimer.currentSessionCount

            text: pomodoroCount + " pomodoro";

        /*    if (pomodoroCount !== 0)
                text += "s"*/

            font.pixelSize: 42
            font.weight: timeLabel.font.weight
            color: timeLabel.color
            Layout.alignment: Qt.AlignHCenter
        }
    }
}
