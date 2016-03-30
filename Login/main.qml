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
        interval: 3000
        running: true
        repeat: false
        onTriggered: message_item.visible = false
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
            anchors.margins: 32

            width: (parent.width * (1/3)) - 32
            height: parent.height-64

            Image {
                id: logo

                anchors.right: parent.right
                anchors.top: parent.top

                fillMode: Image.PreserveAspectFit
                source: "./logo.jpg"
            }

            Clock {
                id: clock

                anchors.right: parent.right
                anchors.bottom: parent.bottom
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
            opacity: 0.86


            Text {
                id: message_text

                anchors.centerIn: message_rec
                anchors.fill: message_rec

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text:"Login failed"
                color: "red"
                font.pixelSize: 48
                font.family: "Futura"
            }
        }
    }
}
