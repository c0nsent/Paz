import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Paz.PomodoroTimer

Item {
    id: root

    required property PomodoroTimer pomodoroTimer
    property color primaryColor: "#ef4444"
    property color textColor: "#1e293b"

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 30

        Label {
            id: phaseLabel
            text: {
                if (pomodoroTimer.phase === PomodoroTimer.Work) return qsTr("Focus Time");
                if (pomodoroTimer.phase === PomodoroTimer.ShortBreak) return qsTr("Short Break");
                if (pomodoroTimer.phase === PomodoroTimer.LongBreak) return qsTr("Long Break");
                return "Unknown";
            }
            font.pixelSize: 28
            font.weight: Font.Bold
            color: pomodoroTimer.phase === PomodoroTimer.Work ? primaryColor : "#10b981"
            Layout.alignment: Qt.AlignHCenter
        }

        Item {
            id: timerRingContainer
            Layout.preferredWidth: 260
            Layout.preferredHeight: 260
            Layout.alignment: Qt.AlignHCenter

            property real progress: pomodoroTimer.currentPhaseDuration > 0 ? pomodoroTimer.remainingTime / pomodoroTimer.currentPhaseDuration : 0

            Canvas {
                id: ringCanvas
                anchors.fill: parent
                antialiasing: true

                property real animatedProgress: timerRingContainer.progress

                onPaint: {
                    const ctx = getContext("2d")
                    ctx.reset()

                    const centerX = width / 2
                    const centerY = height / 2
                    const radius = Math.min(width, height) / 2 - 15
                    const lineWidth = 12

                    const startAngle = -Math.PI / 2
                    const endAngle = startAngle + animatedProgress * Math.PI * 2

                    ctx.lineWidth = lineWidth
                    ctx.lineCap = "round"

                    // Background circle
                    ctx.beginPath()
                    ctx.strokeStyle = "#e2e8f0"
                    ctx.arc(centerX, centerY, radius, 0, Math.PI * 2)
                    ctx.stroke()

                    // Progress arc
                    ctx.beginPath()
                    ctx.strokeStyle = pomodoroTimer.phase === PomodoroTimer.Work ? primaryColor : "#10b981"
                    ctx.arc(centerX, centerY, radius, startAngle, endAngle)
                    ctx.stroke()
                }

                Behavior on animatedProgress {
                    NumberAnimation {
                        duration: 500
                        easing.type: Easing.OutCubic
                    }
                }

                onAnimatedProgressChanged: requestPaint()
                Component.onCompleted: requestPaint()
            }

            Column {
                anchors.centerIn: parent
                spacing: 5

                Label {
                    id: timeLabel
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: pomodoroTimer.timeRemainingString
                    font.pixelSize: 56
                    font.family: "Monospace"
                    font.weight: Font.Bold
                    color: textColor
                }

                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: pomodoroTimer.currentSessionCount + " / " + pomodoroTimer.sessionLength
                    font.pixelSize: 16
                    color: "#64748b"
                }
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 20

            Button {
                id: startPauseButton
                text: {
                    if (pomodoroTimer.state === PomodoroTimer.Running) return "Pause";
                    if (pomodoroTimer.state === PomodoroTimer.Paused) return "Resume";
                    return "Start"
                }
                
                onClicked: pomodoroTimer.state === PomodoroTimer.Running ? pomodoroTimer.pause() : pomodoroTimer.start()

                contentItem: Label {
                    text: parent.text
                    font.pixelSize: 18
                    font.weight: Font.Bold
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    implicitWidth: 140
                    implicitHeight: 50
                    radius: 25
                    color: startPauseButton.pressed ? "#dc2626" : primaryColor
                }
            }

            Button {
                id: skipButton
                onClicked: pomodoroTimer.changeToNextPhase()
                
                background: Rectangle {
                    implicitWidth: 50
                    implicitHeight: 50
                    radius: 25
                    color: "#f1f5f9"
                    border.color: "#e2e8f0"
                }

                contentItem: Label {
                    text: "⏭"
                    font.pixelSize: 20
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    color: "#64748b"
                }
            }

            Button {
                id: resetButton
                onClicked: pomodoroTimer.reset()
                
                background: Rectangle {
                    implicitWidth: 50
                    implicitHeight: 50
                    radius: 25
                    color: "#f1f5f9"
                    border.color: "#e2e8f0"
                }

                contentItem: Label {
                    text: "↺"
                    font.pixelSize: 20
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    color: "#64748b"
                }
            }
        }
    }
}
