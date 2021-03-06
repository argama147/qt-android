import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Window 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls.Material 2.0

ApplicationWindow {
    visible: true

    Page {
        id: page
        anchors.fill: parent
        background: Rectangle {
            color: "#fff3b8"
        }
        header: ToolBar {
            id: toolBar
            Material.foreground: "white"
            Material.background: "white"
            Material.accent: "white"
            Label {
                id: label
                anchors.centerIn: parent
                font.pixelSize: 60
                color: "#f0f0f0"
                text: "QtActivitySample"

            }
            background: Rectangle {
                anchors.fill: parent
                color : "gray"
            }
        }
    }
    Column {
        anchors.centerIn: parent

        Button {
            objectName: "startActivityButton"
            text: "startActivity"
        }
        Text {
            objectName: "resultText"
            text: qsTr("No Called")
        }
    }

}
