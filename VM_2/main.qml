import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 640
    height: 480
    property alias buttonSolve: buttonSolve
    title: qsTr("Решение СЛАУ")

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
            relaxCalculator.setFromFile(fileUrl.toString())
            calculator.setFromFile(fileUrl.toString())

            if (radioButtonGauss.checked){
                textAreaAb.text = calculator.getInput()
            }
            else {
                textAreaAb.text = relaxCalculator.getInput()
            }


//            relaxCalculator.calculateFromFile(fileUrl.toString())
//            textAreaAb.text = calculator.getInput()
//            textAreaX.text = calculator.getX()

//            calculator.calculateFromFile(fileUrl.toString())
//            textAreaAb.text = calculator.getInput()
//            textAreaLU.text = calculator.getLU()
//            textAreaX.text = calculator.getX()
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
        anchors.bottom: textAreaLU.bottom
//        anchors.bottomMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 5
        background: Rectangle {
            anchors.fill: parent
            color: "white"
        }


    }
    TextField {
        id: textFieldW

        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        width: textAreaAb.width / 2
        height: 30
        placeholderText: "W"

        text: qsTr("1.25")
    }

    Button {
        id: buttonSolve
        anchors.left: textFieldW.right
        anchors.leftMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.right: textAreaLU.left
        anchors.rightMargin: 5
        anchors.top: textFieldW.top
        text: qsTr("Решить")

        onClicked: {
            if (radioButtonGauss.checked){
                //            relaxCalculator.calculateFromFile(fileUrl.toString())
                //            textAreaAb.text = calculator.getInput()
                //            textAreaX.text = calculator.getX()

                calculator.calculate()
                textAreaLU.text = calculator.getLU()
                textAreaX.text = calculator.getX()
            }
            else {
                relaxCalculator.setW(Number(textFieldW.text.toString()))
                relaxCalculator.calculate()
                textAreaLU.text = relaxCalculator.getIterCount()
                textAreaX.text = relaxCalculator.getX()
            }
        }
    }

    TextArea {
        id: textAreaLU

        text: qsTr("")
        anchors.right: textAreaX.left
        anchors.rightMargin: 5
        anchors.left: textAreaAb.right
        anchors.leftMargin: 5
        anchors.bottom: columnButtons.top
        anchors.bottomMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 5
        background: Rectangle {
            anchors.fill: parent
            color: "white"
        }
    }

    ButtonGroup { buttons: columnButtons.children }
    Column {
        id: columnButtons
        anchors.right: textAreaLU.right
        anchors.left: textAreaLU.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        height: 50

        RadioButton {
            id: radioButtonGauss
            height: 25

            text: "Метод LU-разложения"
            indicator.width: 15
            indicator.height: 15
            checked: true
        }
        RadioButton {
            id: radioButtonRelax
            height: 25

            text: "Метод релаксации"
            indicator.width: 15
            indicator.height: 15
        }
    }

    TextArea {
        id: textAreaX

        width: parent.width / 8
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
    D{i:6;anchors_height:142;anchors_x:45;anchors_y:32}D{i:8;anchors_y:40}D{i:7;anchors_x:228;anchors_y:48}
}
##^##*/
