import Paz.PomodoroTimer

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    minimumWidth: 500
    minimumHeight: 400
    title: "Paz"

    color: "#f8fafc"

    required property PomodoroTimer pomodoroTimer
    required property SettingsManager settingsManager

    readonly property color primaryColor: "#ef4444"
    readonly property color textColor: "#1e293b"
    readonly property color sidebarColor: "#0f172a"
    readonly property color sidebarTextColor: "#cbd5e1"

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Sidebar {
            id: sidebar
            sidebarColor: window.sidebarColor
            sidebarTextColor: window.sidebarTextColor
            currentIndex: mainStack.currentIndex
            onNavigationRequest: (index) => mainStack.currentIndex = index
        }

        StackLayout {
            id: mainStack
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: 0

            TimerPage {
                pomodoroTimer: window.pomodoroTimer
                primaryColor: window.primaryColor
                textColor: window.textColor
            }

            SettingsPage {
                pomodoroTimer: window.pomodoroTimer
                settingsManager: window.settingsManager
                textColor: window.textColor
            }
        }
    }
}