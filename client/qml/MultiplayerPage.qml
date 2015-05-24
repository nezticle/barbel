import QtQuick 2.3
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.2

FocusScope {
    Text {
        id: titleLabel
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        text: "Multiplayer"
        color: "white"
        font.pointSize: 50
    }

    ColumnLayout {
        anchors.centerIn: parent

        Button {
            id: singlePlayerModeButton
            text: "Join"
            Layout.alignment: Qt.AlignCenter
            onClicked: {
                stackView.push(Qt.resolvedUrl("JoinMultiplayerPage.qml"));
            }
        }
        Button {
            id: multiPlayerButton
            text: "Host"
            Layout.alignment: Qt.AlignCenter
            onClicked: {
                stackView.push(Qt.resolvedUrl("HostMultiplayerPage.qml"));
            }
        }
        Button {
            id: settingsButton
            text: "Back"
            Layout.alignment: Qt.AlignCenter
            onClicked: {
                stackView.pop();
            }
        }
    }
}

