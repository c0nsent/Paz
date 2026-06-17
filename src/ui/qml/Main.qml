import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import PazQml


ApplicationWindow {
    width: 420
    height: 320
    visible: true
    title: "Paz"

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

        Rectangle {
            id: buttonBg

            color: "#2c3e50"
            radius: 8
        }

        Label {
            id: timeLabel
            text: pomodoroTimer.timeRemainingString
            font.pixelSize: 72
            font.family: "Monospace" // Моноширный шрифт, чтобы цифры не "прыгали"
            font.weight: Font.DemiBold
            color: "#2c3e50"
            Layout.alignment: Qt.AlignHCenter
        }


        Button {
            id: startPauseButton
            text: pomodoroTimer.state === PomodoroTimer.Running ? "Pause" : "Start"

            font.pixelSize: 20
            onClicked: pomodoroTimer.state === PomodoroTimer.Running ? pomodoroTimer.pause() : pomodoroTimer.start()

            background: Rectangle {
                implicitWidth: timeLabel.width
                implicitHeight: parent.font.pixelSize * 3
                radius: 16
                color: "#2c3e50"
                border.color: "#1f2d3a"
            }

            contentItem: Text {
                text: parent.text
                color: "white"
                font.pixelSize: parent.font.pixelSize
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            Layout.alignment: Qt.AlignHCenter
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 16

            Button {
                text: "Skip"
                font.pixelSize: 16
                onClicked: pomodoroTimer.toNextPhase()

                background: Rectangle {
                    implicitWidth: (startPauseButton.width - parent.parent.spacing ) / 2
                    implicitHeight: parent.font.pixelSize * 2
                    radius: 8
                    color: "#2c3e50"
                    border.color: "#1f2d3a"
                }

                contentItem: Text {
                    text: parent.text
                    color: "white"
                    font.pixelSize: parent.font.pixelSize
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

            Button {
                text: "Reset"
                font.pixelSize: 16
                onClicked: pomodoroTimer.reset()

                background: Rectangle {
                    implicitWidth: (startPauseButton.width - parent.parent.spacing ) / 2
                    implicitHeight: parent.font.pixelSize * 2
                    radius: 8
                    color: "#2c3e50"
                    border.color: "#1f2d3a"
                }

                contentItem: Text {
                    text: parent.text
                    color: "white"
                    font.pixelSize: parent.font.pixelSize
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }


        Label
        {
            property int pomodoroCount: pomodoroTimer.currentSessionCount

            text: pomodoroCount + " pomodoro" + (pomodoroCount <= 1 ? "" : "s")

            font.pixelSize: 42
            font.weight: timeLabel.font.weight
            color: timeLabel.color
            Layout.alignment: Qt.AlignHCenter
        }
    }
}