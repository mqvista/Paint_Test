import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Window 2.12

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle {
        id: rectangle

        width: 500
        height: 200
        anchors.centerIn: parent
        color: "#ffffff"
        border.width: 2
        border.color: "#66ccff"

        Text {
            id: element
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: parent.width * -0.3
            text: qsTr("Weight:")
            font.pointSize: 50
        }

        Text {
            id: element1
            anchors.left: element.right
            text: userModule.weight
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 50
        }

        Rectangle {
            id: rectangle1
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: parent.height * -0.35
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: parent.width * -0.43
            width: 40
            height: 20
            color: "#ffffff"
            radius: 20
            border.width: 4
            visible: userModule.status
        }

        TextField {
            id: textField
            width: 120
            height: 40
            text: qsTr("Text Field")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: parent.width * -0.3
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: parent.height * 0.33
            onFocusChanged: {
                if (textField.focus)
                {
                    if (textField.text == "Text Field")
                    {
                        textField.text = ""
                    }
                }
            }
        }

        Button {
            id: button
            anchors.left: textField.right
            anchors.leftMargin: 10
            anchors.verticalCenter: textField.verticalCenter

            text: qsTr("Button")
            onClicked: {
                userModule.addPaint(textField.text)
            }
        }

        BusyIndicator {
            id: busyIndicator
            anchors.left: button.right
            anchors.leftMargin: 50
            anchors.verticalCenter: button.verticalCenter
            running: userModule.status

        }
    }


}
