import QtQuick 2.3
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.2
import Qt.labs.settings 1.0

FocusScope {
    Text {
        id: titleLabel
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        text: "Join Multiplayer"
        color: "white"
        font.pointSize: 50
    }

    Settings {
        category: "JoinMultiplayer"
        property alias host: ipField.text
        property alias port: portField.text
    }

    ColumnLayout {
        anchors.centerIn: parent
        RowLayout {
            Layout.alignment: Qt.AlignRight
            Text {
                text: "Host or IP address:"
                color: "white"
            }
            TextField {
                id: ipField
                placeholderText: "127.0.0.1"
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignRight
            Text {
                text: qsTr("Port")
                color: "white"
            }
            TextField {
                id: portField
                text: "54540"
            }
        }

        Button {
            id: joinButton
            text: "Join Game"
            enabled: portField.text != "" && ipField.text != ""
            Layout.alignment: Qt.AlignRight
            onClicked: {
                barbelScene.joinMultiPlayerSession(ipField.text, portField.text);
                stackView.push(Qt.resolvedUrl("GamePage.qml"))
            }
        }

        Button {
            id: backButton
            text: "Back"
            Layout.alignment: Qt.AlignRight
            onClicked: {
                stackView.pop();
            }
        }
    }
}

