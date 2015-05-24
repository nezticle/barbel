import QtQuick 2.3
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.2
import Qt.labs.settings 1.0

FocusScope {
    Text {
        id: titleLabel
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        text: "Host Multiplayer"
        color: "white"
        font.pointSize: 50
    }

    Settings {
        category: "HostMultiplayer"
        property alias port: portField.text
    }

    ColumnLayout {
        anchors.centerIn: parent

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
            text: "Host Game"
            enabled: portField.text != ""
            Layout.alignment: Qt.AlignRight
            onClicked: {
                barbelScene.hostMultiPlayerSession(portField.text);
                stackView.push(Qt.resolvedUrl("GamePage.qml"))
            }
        }

        Button {
            id: settingsButton
            text: "Back"
            Layout.alignment: Qt.AlignRight
            onClicked: {
                stackView.pop();
            }
        }
    }
}

