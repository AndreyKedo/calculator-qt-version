import QtQuick 2.12
import QtQuick.Controls 2.4
import com.vm.main 1.0

ApplicationWindow {
    property bool isHistory: false
    visible: true
    minimumWidth: 320
    minimumHeight: 380
    title: qsTr("Калькулятор")

    DataContext {
        id: vm
    }

    Item {
        id: row
        width: parent.width
        height: parent.height / 4

        ListView {
            clip: true
            visible: isHistory
            anchors.left: historyButton.right
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            height: 46
            snapMode: ListView.SnapOneItem
            delegate: Text {
                width: Text.contentWidth
                height: Text.contentHeight
                font.pixelSize: 40
                text: modelData
            }
        }

        Text {
            visible: !isHistory
            anchors.right: parent.right
            anchors.left: historyButton.right
            height: parent.height
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            text: vm.expression.length !== 0 ? vm.expression.replace(
                                                   '_', '-') : "Выражение"
            wrapMode: Text.WrapAnywhere
            font.pixelSize: 26
        }

        Button {
            id: historyButton
            anchors.left: parent.left
            height: parent.height
            width: Button.implicitContentWidth
            text: "История"
            font.pixelSize: 14
            onClicked: {
                isHistory ? isHistory = false : isHistory = true
            }
            background: Rectangle {
                color: historyButton.hovered ? "#8d8d8d" : "#e6e6e6"
                opacity: 0.5
            }
        }
    }

    Grid {
        width: parent.width
        anchors.top: row.bottom
        anchors.bottom: parent.bottom
        columns: 4
        rows: 5

        Repeater {
            model: ['(', ')', '±', 'C', '7', '8', '9', '+', '4', '5', '6', '-', '1', '2', '3', '×', '.', '0', '=', '÷']
            Button {
                id: contr
                width: parent.width / 4
                height: parent.height / 5
                text: modelData
                antialiasing: true
                font.pixelSize: 18
                onClicked: {
                    isHistory = false
                    if (text >= '0' && text <= '9') {
                        vm.numberButton(text)
                    }
                    switch (text) {
                    case '×':
                        vm.operationButton('*')
                        break
                    case '÷':
                        vm.operationButton('/')
                        break
                    case '±':
                        vm.operationButton('_')
                        break
                    case 'C':
                        vm.clearButton()
                        break
                    case '=':
                        vm.calcButton()
                        break
                    default:
                        if (!(text >= '0' && text <= '9'))
                            vm.operationButton(text)
                    }
                }
                background: Rectangle {
                    color: contr.down ? "#8d8d8d" : "#e6e6e6"
                    border.width: 1 / 2
                    border.color: "#727272"
                }
            }
        }
    }
}
