import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Решение методом LU-разложения")

    background: Rectangle {
        anchors.fill: parent
        color: "gray"
    }

    //open input file
    FileDialog {
        id: fileDialogOpen

        nameFilters: ["Text files (*.txt)", "All files (*)"]
        selectMultiple: false
        selectExisting: true
        onAccepted: {
            calculator.calculateFromFile(fileUrl.toString())
            textAreaAb.text = calculator.getInput()
            textAreaLU.text = calculator.getLU()
            textAreaX.text = calculator.getX()
        }
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr ("Файл")

            MenuItem { action: actionFileOpen }
        }

    }
    Action {
        id: actionFileOpen

        text: qsTr("Открыть")
        onTriggered: {
            fileDialogOpen.open()
        }
    }

    TextArea {
        id: textAreaAb

        width: parent.width / 2
        text: qsTr("")
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 5
        background: Rectangle {
            anchors.fill: parent
            color: "white"
        }
    }

    TextArea {
        id: textAreaLU

        text: qsTr("")
        anchors.right: textAreaX.left
        anchors.rightMargin: 5
        anchors.left: textAreaAb.right
        anchors.leftMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 5
        background: Rectangle {
            anchors.fill: parent
            color: "white"
        }
    }

    TextArea {
        id: textAreaX

        width: parent.width / 10
        text: qsTr("")
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 5
        background: Rectangle {
            anchors.fill: parent
            color: "white"
        }
    }
}

/*##^##
Designer {
    D{i:6;anchors_height:142;anchors_x:45;anchors_y:32}D{i:7;anchors_x:228;anchors_y:48}
D{i:8;anchors_y:40}
}
##^##*/
