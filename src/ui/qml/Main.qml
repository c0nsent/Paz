import Paz.PomodoroTimer

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


ApplicationWindow {
    visible: true
    title: "Paz"

    color: "#f4f4f5"

    TabBar {
        id: bar

        width: parent.width

        TabButton {
            text: qsTr("Pomodoro Timer")
        }

        TabButton {
            text: qsTr("Settings")
        }
    }

    required property PomodoroTimer pomodoroTimer

    ColumnLayout {
        id: ptWindow
        anchors.centerIn: parent
        visible: bar.currentIndex === 0
        spacing: 20

        Label {
            id: phaseLabel
            text: {
                if (pomodoroTimer.phase === PomodoroTimer.Work) return qsTr("Work");
                if (pomodoroTimer.phase === PomodoroTimer.ShortBreak) return qsTr("Short Break");
                if (pomodoroTimer.phase === PomodoroTimer.LongBreak) return qsTr("Long Break");
                return "Unknown";
            }
            font.pixelSize: 24
            font.weight: Font.Bold
            color: "#e74c3c"
            Layout.alignment: Qt.AlignHCenter
        }

        Item {
            id: timerRing

            Layout.preferredWidth: 220
            Layout.preferredHeight: 220
            Layout.alignment: Qt.AlignHCenter

            property real progress: pomodoroTimer.currentPhaseDuration > 0 ? pomodoroTimer.remainingTime / pomodoroTimer.currentPhaseDuration : 0

            Canvas {
                id: ringCanvas
                anchors.fill: parent

                property real animatedProgress: timerRing.progress

                onPaint: {
                    const ctx = getContext("2d")
                    ctx.reset()

                    const centerX = width / 2
                    const centerY = height / 2
                    const radius = Math.min(width, height) / 2 - 12
                    const lineWidth = 14

                    const startAngle = -Math.PI / 2
                    const endAngle = startAngle + animatedProgress * Math.PI * 2

                    ctx.lineWidth = lineWidth
                    ctx.lineCap = "round"

                    ctx.beginPath()
                    ctx.strokeStyle = "#d1d5db"
                    ctx.arc(centerX, centerY, radius, Math.PI * 2, Math.PI * 2)
                    ctx.stroke()

                    ctx.beginPath()
                    ctx.strokeStyle = "#e74c3c"
                    ctx.arc(centerX, centerY, radius, startAngle, endAngle)
                    ctx.stroke()
                }

                Behavior on animatedProgress {
                    NumberAnimation {
                        duration: 350
                        easing.type: Easing.OutCubic
                    }
                }

                onAnimatedProgressChanged: requestPaint()
                Component.onCompleted: requestPaint()
            }

            Column {
                anchors.centerIn: parent
                spacing: 4

                Label {
                    id: timeLabel
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: pomodoroTimer.timeRemainingString
                    font.pixelSize: 48
                    font.family: "Monospace"
                    font.weight: Font.Bold
                    color: "#2c3e50"
                }
            }
        }

        Button {
            id: startPauseButton
            text: {
                if (pomodoroTimer.state === PomodoroTimer.Running) return "Pause";
                if (pomodoroTimer.state === PomodoroTimer.Paused) return "Resume";
                return "Start"
            }

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

    required property SettingsManager settingsManager

    ScrollView {
        id: settingsWindow
        anchors.centerIn: parent
        width: parent.width
        height: parent.height - bar.height
        visible: bar.currentIndex === 1

        GridLayout {
            anchors.centerIn: parent
            //spacing: 20
            columns: 2
            columnSpacing: parent.width / 2

            Text { text: "Autostart break phase"}
            CheckBox {
                checkState:

                onCheckStateChanged: settingsManager.togglePomodoroAutoStart()

            }
        }
    }
}