import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2
import QtCharts 2.3

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 640
    height: 480
    property alias buttonSolve: buttonSolve
    title: currIndex == 0 ? qsTr("Решение СЛАУ") : qsTr("Интерполяция Фурье")


    property var headerHeight: 0
    property alias swipeView: swipeView
    property var currIndex: swipeView.currentIndex

    FileDialog {
        id: fileDialogOpen

        nameFilters: ["Text files (*.txt)", "All files (*)"]
        selectMultiple: false
        selectExisting: true
        onAccepted: {
            if (currIndex == 0)
            {
                relaxCalculator.setFromFile(fileUrl.toString())
                calculator.setFromFile(fileUrl.toString())
                minDiscCalc.setFromFile(fileUrl.toString())


                if (radioButtonGauss.checked){
                    textAreaAb.text = calculator.getInput()
                }
                else {
                    textAreaAb.text = relaxCalculator.getInput()
                }
            }
            else
            {
                furieInterpolator.setFromFile(fileUrl.toString())
            }
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

    SwipeView {
        id: swipeView

        anchors.fill: parent

        Page {
            id: pagePlans

            background: Rectangle {
                anchors.fill: parent
                color: "gray"
            }

            //open input file



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
                    else if (radioButtonRelax.checked) {
                        relaxCalculator.setW(Number(textFieldW.text.toString()))
                        relaxCalculator.calculate()
                        textAreaLU.text = relaxCalculator.getIterCount()
                        textAreaX.text = relaxCalculator.getX()
                    }
                    else {
        //                relaxCalculator.setW(Number(textFieldW.text.toString()))
                        minDiscCalc.calculate()
                        textAreaLU.text = minDiscCalc.getIterCount()
                        textAreaX.text = minDiscCalc.getX()
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

            ButtonGroup {
                id: bg

                buttons: columnButtons.children
            }
            Column {
                id: columnButtons
                anchors.right: textAreaLU.right
                anchors.left: textAreaLU.left
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5
                height: 75

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
                RadioButton {
                    id: radioButtonMinDiscr

                    height: 25
                    text: "Метод мин. невязок"
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



        Page {
            id: pageRecords

            background: Rectangle {
                anchors.fill: parent
                color: "gray"
            }

//            TextArea {
//                id: textAreaFurie

////                width: parent.width / 2
//                text: qsTr("")
//                anchors.right: parent.right
//                anchors.left: parent.left
//                anchors.top: parent.top
//                anchors.margins: 5
//                anchors.bottom: buttonInterpolate.top
//        //        anchors.bottomMargin: 5

////                anchors.top: parent.top
////                anchors.topMargin: 5
//                background: Rectangle {
//                    anchors.fill: parent
//                    color: "white"
//                }


//            }

            ChartView {
                id: chart

                title: "График"
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.margins: 5
                anchors.bottom: buttonInterpolate.top
                antialiasing: true

                //sc

                LineSeries {
                    id: lineInterpolated

//                    name: "LineSeries"
//                    XYPoint { x: 0; y: 0 }
//                    XYPoint { x: 1.1; y: 2.1 }
//                    XYPoint { x: 1.9; y: 3.3 }
//                    XYPoint { x: 2.1; y: 2.1 }
//                    XYPoint { x: 2.9; y: 4.9 }
//                    XYPoint { x: 3.4; y: 3.0 }
//                    XYPoint { x: 4.1; y: 3.3 }
                }
            }



            Button {
                id: buttonInterpolate
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5
//                anchors.right: textAreaLU.left
//                anchors.rightMargin: 5
//                anchors.top: textFieldW.top
                text: qsTr("Решить")

                onClicked: {
                    furieInterpolator.calculate()
                    var X = furieInterpolator.getXout()
                    var Y = furieInterpolator.getYout()

                    lineInterpolated.clear()
                    for (var i = 0; i < X.length; i++){

                        lineInterpolated.append(X[i], Y[i])
                        //lineInterpolated.
                    }
//                    textAreaFurie.text = furieInterpolator.getSolution()

                }
            }
        }
    }
}



/*##^##
Designer {
    D{i:6;anchors_height:142;anchors_x:45;anchors_y:32}D{i:8;anchors_y:40}D{i:7;anchors_x:228;anchors_y:48}
}
##^##*/
