import QtQuick 2.3
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.2
import Qt.labs.settings 1.0

FocusScope {
    Text {
        id: titleLabel
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        text: "Settings"
        color: "white"
        font.pointSize: 50
    }

    Settings {
        category: "Settings"
    }

    ColumnLayout {
        anchors.centerIn: parent

        Button {
            id: backButton
            text: "Back"
            Layout.alignment: Qt.AlignCenter
            onClicked: {
                stackView.pop();
            }
        }
    }
}

