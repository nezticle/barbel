import QtQuick 2.3
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.2
import com.bsquask.Barbel 1.0

FocusScope {
    id: gamePage

    state: "CONNECTING"

    Connections {
        target: barbelScene
        onConnectionStateChanged: {
            if (connectionState == BarbelScene.ConnectingState) {
                gamePage.state = "CONNECTING"
            } else if (connectionState == BarbelScene.ConnectedState) {
                gamePage.state = "LOADING"
            } else if (connectionState == BarbelScene.DisconnectedState) {
                gamePage.state = "DISCONNECTING"
            } else if (connectionState == BarbelScene.ErrorState) {
                gamePage.state = "ERROR"
            }
        }
    }

    Rectangle {
        id: loadingScreen
        color: "purple"
        anchors.fill: parent

        ColumnLayout {
            anchors.centerIn: parent

            ProgressBar {
                id: loadingProgress
                Layout.alignment: Qt.AlignCenter
            }
            Text {
                id: statusLabel
                Layout.alignment: Qt.AlignCenter
                text: "Connecting..."
                color: "white"
            }
        }
    }

    Item {
        id: menuAndHUD
        visible: false
        anchors.fill: parent
    }

    states: [
        State {
            name: "CONNECTING"
            PropertyChanges {
                target: loadingScreen
                opacity: 1.0
            }
            PropertyChanges {
                target: statusLabel
                text: "Connecting..."
            }
            PropertyChanges {
                target: loadingProgress
                opacity: 0.0
            }
            PropertyChanges {
                target: menuAndHUD
                visible: false
            }
        },
        State {
            name: "LOADING"
            PropertyChanges {
                target: loadingScreen
                opacity: 1.0
            }
            PropertyChanges {
                target: statusLabel
                text: "Loading..."
            }
            PropertyChanges {
                target: loadingProgress
                opacity: 1.0
            }
            PropertyChanges {
                target: menuAndHUD
                visible: false
            }
        },
        State {
            name: "PLAYING"
            PropertyChanges {
                target: loadingScreen
                opacity: 0.0
            }
            PropertyChanges {
                target: statusLabel
                text: ""
            }
            PropertyChanges {
                target: loadingProgress
                opacity: 0.0
            }
            PropertyChanges {
                target: menuAndHUD
                visible: true
            }
        },
        State {
            name: "ERROR"
            PropertyChanges {
                target: loadingScreen
                opacity: 1.0
            }
            PropertyChanges {
                target: statusLabel
                text: barbelScene.errorString
            }
            PropertyChanges {
                target: loadingProgress
                opacity: 0.0
            }
            PropertyChanges {
                target: menuAndHUD
                visible: false
            }
        },
        State {
            name: "DISCONNECTING"
            PropertyChanges {
                target: loadingScreen
                opacity: 1.0
            }
            PropertyChanges {
                target: statusLabel
                text: "Disconnected..."
            }
            PropertyChanges {
                target: loadingProgress
                opacity: 0.0
            }
            PropertyChanges {
                target: menuAndHUD
                visible: false
            }
        }
    ]
}

