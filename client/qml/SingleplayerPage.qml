import QtQuick 2.3
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.2

FocusScope {
    Text {
        id: titleLabel
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        text: "Singleplayer"
        color: "white"
        font.pointSize: 50
    }

    ColumnLayout {
        anchors.centerIn: parent
        Button {
            id: startButton
            text: "Start"
            Layout.alignment: Qt.AlignRight
            onClicked: {
                stackView.push(Qt.resolvedUrl("GamePage.qml"))
                barbelScene.startSinglePlayerSession();
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

