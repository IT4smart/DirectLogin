import QtQuick 2.3

Item {
    width: 320
    height: 200

    Column {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 2

        Text {
            id: timeText

            text: Date().toLocaleTimeString(Qt.locale("de_DE"), "hh:mm")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
            width: parent.width
            height: 128

            color: "white"
            font.pixelSize: 120;font.family: "Futura"
        }

        Text {
            id: dateText

            text: Date().toLocaleDateString(Qt.locale("de_DE"), "d. MMM yyyy")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
            style: Text.Normal
            width: parent.width
            height: 72

            color: "white"
            font.pixelSize: 64
            font.family: "Futura"
        }
    }

    function timeChanged() {
        var date = new Date;
        timeText.text = date.toLocaleTimeString(Qt.locale("de_DE"), "hh:mm")
        dateText.text = date.toLocaleDateString(Qt.locale("de_DE"), "d. MMM yyyy")
    }

    Timer {
        interval: 500
        running: true
        repeat: true;
        onTriggered: timeChanged()
    }
}

