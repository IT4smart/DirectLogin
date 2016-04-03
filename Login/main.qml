import QtQuick 2.3
import QtQuick.Window 2.2

Window {
    visible: true
    visibility: "FullScreen"

    Connections {
        target: access
        onLoginDone: {
            if (!loginBool) {
                message_item.visible = true
                message_timer.start()
            }
        }
    }

    Timer {
        id: message_timer
        interval: 2000
        running: true
        repeat: false
        onTriggered: {
            message_item.visible = false
        }
    }

    Image {
        id: backgroundImage

        width: parent.width
        height: parent.height

        anchors.fill: parent
        anchors.centerIn: parent

        source: "./Amsterdam.jpg"

        Item {
            id: leftItem

            anchors.left: parent.left
            anchors.top: parent.top

            width: parent.width * (2/3)
            height: parent.height

            LoginBox {
                id: loginbox
                objectName: "myLoginBox"

                anchors.centerIn: parent
            }
        }

        Item {
            id: rightItem

            anchors.right: parent.right
            anchors.top: parent.top

            width: (parent.width * (1/3))
            height: parent.height

            Image {
                id: logo

                anchors.right: parent.right
                anchors.top: parent.top

                anchors.topMargin: 16
                anchors.rightMargin: 16

                width: parent.width-16

                fillMode: Image.Stretch
                source: "./logo.jpg"
            }

            Clock {
                id: clock

                anchors.right: parent.right
                anchors.bottom: parent.bottom

                anchors.bottomMargin: 16
                anchors.rightMargin: 16
            }
        }
    }

    Item {
        id: message_item
        visible: false

        anchors.left: backgroundImage.left
        anchors.top: backgroundImage.top

        width: 328
        height: 128

        Rectangle {
            id: message_rec

            anchors.fill: parent
            anchors.centerIn: parent

            anchors.margins: 16
            radius: 16

            color: "white"
            opacity: 0.85

            border.color: "red"
            border.width: 3

            Text {
                id: message_text

                anchors.centerIn: message_rec
                anchors.fill: message_rec

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text:"Login"
                color: "red"
                font.pixelSize: 48
                font.family: "Futura"
            }
        }
    }
}
