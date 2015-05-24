import QtQuick 2.3
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.2
import Qt.labs.settings 1.0

FocusScope {
    Text {
        id: titleLabel
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        text: "I have more barbels than a catfish."
        color: "white"
        font.pointSize: 50
    }

    Settings {
        category: "StartPage"
        property alias username: usernameField.text
    }

    ColumnLayout {
        anchors.centerIn: parent

        RowLayout {
            Layout.alignment: Qt.AlignRight
            Text {
                text: "Username:"
                color: "white"
            }

            TextField {
                id: usernameField
                placeholderText: "Username"
            }
        }
        Button {
            id: singlePlayerModeButton
            text: "Singleplayer"
            enabled: usernameField.text != '';
            Layout.alignment: Qt.AlignRight
            onClicked: {
                stackView.push(Qt.resolvedUrl("SingleplayerPage.qml"));
            }
        }
        Button {
            id: multiPlayerButton
            text: "Multiplayer"
            enabled: usernameField.text != '';
            Layout.alignment: Qt.AlignRight
            onClicked: {
                stackView.push(Qt.resolvedUrl("MultiplayerPage.qml"));
            }
        }
        Button {
            id: settingsButton
            text: "Settings"
            Layout.alignment: Qt.AlignRight
            onClicked: {
                stackView.push(Qt.resolvedUrl("SettingsPage.qml"));
            }
        }
    }
}

