import QtQuick 2.3
import QtQuick.Controls 1.4

Item {
    visible: true
    width: 640
    height: 640

    Connections {
        target: access
        onLoginDone: {
            clearText()
        }
    }

    function clearText() {
        usernameText.text = ""
        passwordText.text = ""
    }

    function checkInput() {
        if ((usernameText.text != "") && (passwordText.text != "")) {
            access.username = usernameText.text
            access.password = passwordText.text

            access.login_clicked()
        }
    }

    Rectangle {
        id: loginBox

        opacity: 0.86

        anchors.fill: parent
        radius: 16
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#58e150"
            }

            GradientStop {
                position: 1
                color: "#1475ab"
            }
        }
        border.color: "white"

        border.width: 4
    }


    Column {
        id: col

        anchors.fill: loginBox
        anchors.margins: 32
        spacing: 32

        Text {
            id: loginHeader

            anchors.margins: 16

            width: parent.width
            height: 192

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text:"Login"
            color: "white"
            font.pixelSize: 128
            font.family: "Futura"
        }

        TextField {
            id: usernameText

            width: parent.width
            height: 64

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            placeholderText: "Username"
            font.pixelSize: 48
            font.family: "Futura"
            textColor: "gray"
        }

        TextField {
            id: passwordText

            width: parent.width
            height: 64

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            placeholderText: "Password"
            echoMode: TextInput.Password
            font.pixelSize: 48
            font.family: "Futura"
            textColor: "gray"
        }

        Item {
            width: parent.width
            height: 128

            Rectangle {
                id: buttonFrame

                anchors.centerIn: parent

                width: parent.width
                height: 64
                radius: 5

                Text {
                    id: buttonText

                    anchors.centerIn: parent

                    text: "Login"
                    font.pixelSize: 48
                    font.family: "Futura"
                    color: "gray"
                }

                MouseArea {
                    id: loginMouseArea

                    anchors.fill: parent
                    hoverEnabled: true

                    onClicked: {
                        checkInput()
                    }
                }

                states: State {
                    name: "pressed"; when: loginMouseArea.pressed
                    PropertyChanges {
                        target: buttonFrame;
                        color: "gray";
                        opacity: 1
                    }
                    PropertyChanges {
                        target: buttonText;
                        color: "white";
                    }
                }
            }
        }
    }

}
