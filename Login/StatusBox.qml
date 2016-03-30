import QtQuick 2.3
import QtQuick.Layouts 1.1

Item {
    Rectangle {
        width: 320
        height: 320

        GridLayout {
            anchors.fill: parent
            rows: 2
            columns: 5

            Text {
                text: "Netzwerk"
                Layout.row: 0
                Layout.column: 0
            }

            Text {
                text: "IP-Adresse"
                Layout.row: 1
                Layout.column: 0
            }

            Text {
                text: "Netzmaske"
                Layout.row: 2
                Layout.column: 0
            }

            Text {
                text: "Gateway"
                Layout.row: 3
                Layout.column: 0
            }

            Text {
                text: "IP Vergabe"
                Layout.row: 4
                Layout.column: 0
            }
        }
    }
}
