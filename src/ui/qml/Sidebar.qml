import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Rectangle {
    id: root

    property color sidebarColor: "#0f172a"
    property color sidebarTextColor: "#cbd5e1"
    property int currentIndex: 0
    
    signal navigationRequest(int index)

    Layout.fillHeight: true
    Layout.preferredWidth: 180
    color: sidebarColor

    ColumnLayout {
        anchors.fill: parent
        anchors.topMargin: 40
        spacing: 5

        Label {
            text: "PAZ"
            font.pixelSize: 24
            font.weight: Font.Black
            color: "white"
            Layout.alignment: Qt.AlignHCenter
            Layout.bottomMargin: 30
        }

        Repeater {
            model: [
                { name: qsTr("Timer"), icon: "⏲" },
                { name: qsTr("Settings"), icon: "⚙" }
            ]

            delegate: ItemDelegate {
                id: navItem
                Layout.fillWidth: true
                Layout.preferredHeight: 50
                Layout.leftMargin: 10
                Layout.rightMargin: 10

                contentItem: RowLayout {
                    spacing: 12
                    Label {
                        text: modelData.icon
                        color: navItem.checked ? "white" : sidebarTextColor
                        font.pixelSize: 18
                    }
                    Label {
                        text: modelData.name
                        color: navItem.checked ? "white" : sidebarTextColor
                        font.pixelSize: 14
                        font.weight: navItem.checked ? Font.DemiBold : Font.Normal
                    }
                }

                background: Rectangle {
                    radius: 8
                    color: navItem.checked ? "#1e293b" : (navItem.hovered ? "#1e293b44" : "transparent")
                }

                checkable: true
                checked: root.currentIndex === index
                onClicked: root.navigationRequest(index)
            }
        }

        Item { Layout.fillHeight: true }

        Label {


            text: "v" + appVersion
            color: "#94a3b8"
            font.pixelSize: 10
            Layout.alignment: Qt.AlignHCenter
            Layout.bottomMargin: 10
        }
    }
}
