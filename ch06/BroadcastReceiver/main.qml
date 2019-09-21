import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

Window {
    visible: true
    color: "#fff3b8"
    Column {
        anchors.centerIn: parent
        Button {
            objectName: "sendBroadcastButton"
            text: "sendBroadcast"
        }
        Text {
            objectName: "resultText"
            text: qsTr("Data1 Not Received")
        }
        Text {
            objectName: "resultText2"
            text: qsTr("Data2 Not Received")
        }
    }
}
