import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Paz

ScrollView {
    id: root
    
    required property PomodoroTimer pomodoroTimer
    required property SettingsManager settingsManager
    property color textColor: "#1e293b"

    contentWidth: availableWidth
    
    ColumnLayout {
        width: Math.min(parent.width - 80, 500)
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 40
        spacing: 25

        Label {
            text: qsTr("Settings")
            font.pixelSize: 28
            font.weight: Font.Bold
            color: textColor
            Layout.bottomMargin: 10
        }


        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: generalLayout.implicitHeight + 40
            color: "white"
            radius: 16
            border.color: "#e2e8f0"

            ColumnLayout {
                id: generalLayout
                anchors.fill: parent
                anchors.margins: 20
                spacing: 20

                RowLayout {
                    Layout.fillWidth: true
                    Label {
                        text: qsTr("Autostart break phase")
                        Layout.fillWidth: true
                        font.pixelSize: 16
                        font.weight: Font.Medium
                        color: textColor
                    }
                    Switch {

                        checked: settingsManager.isPomodoroAutoStarEnabled
                        onToggled: settingsManager.togglePomodoroAutoStart()
                    }
                }

                Rectangle { Layout.fillWidth: true; height: 1; color: "#f1f5f9" }

                RowLayout {
                    Layout.fillWidth: true
                    Label {
                        text: qsTr("Session Length")
                        Layout.fillWidth: true
                        font.pixelSize: 16
                        font.weight: Font.Medium
                        color: textColor
                    }
                    SpinBox {
                        value: pomodoroTimer.sessionLength
                        from: 1
                        to: 10
                        editable: true
                        onValueModified: settingsManager.setSessionLength(value)
                    }
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: durationsLayout.implicitHeight + 40
            color: "white"
            radius: 16
            border.color: "#e2e8f0"

            ColumnLayout {
                id: durationsLayout
                anchors.fill: parent
                anchors.margins: 20
                spacing: 15

                Label {
                    text: qsTr("Phase Durations (minutes)")
                    font.weight: Font.Bold
                    color: "#334155"
                    Layout.bottomMargin: 5
                }

                Repeater {
                    model: [
                        { name: qsTr("Work"), phase: PomodoroTimer.Work, duration: pomodoroTimer.workDuration },
                        { name: qsTr("Short Break"), phase: PomodoroTimer.ShortBreak, duration: pomodoroTimer.shortBreakDuration },
                        { name: qsTr("Long Break"), phase: PomodoroTimer.LongBreak, duration: pomodoroTimer.longBreakDuration }
                    ]

                    RowLayout {
                        Layout.fillWidth: true
                        Label {
                            text: modelData.name
                            Layout.fillWidth: true
                            font.pixelSize: 16
                            font.weight: Font.Medium
                            color: textColor
                        }

                        TextInput {
                            text: modelData.duration / 60
                            maximumLength: 3
                            validator: IntValidator{bottom: (60); top: (99);}
                            onAccepted: settingsManager.setPhaseDuration(modelData.phase, Number(text) * 60)
                        }
                    }
                }
            }
        }

        Item { Layout.preferredHeight: 40 } // Spacer
    }
}
