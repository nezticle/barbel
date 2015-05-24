/*
 * Copyright (c) 2015 Andy Nichols
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.3
import QtGraphicalEffects 1.0
import com.bsquask.Barbel 1.0
import Qt.labs.settings 1.0

Window {
    id: window
    visible: true
    width: 1280
    height: 720
    title: "Barbel"
    color: "black"

    Settings {
        property alias x: window.x
        property alias y: window.y
        property alias width: window.width
        property alias height: window.height
    }

    BarbelSceneViewItem {
        id: viewport
        anchors.fill: parent
        scene: barbelScene
    }

    BarbelScene {
        id: barbelScene
        viewportSize: Qt.size(viewport.width, viewport.height)
    }

    StackView {
        id: stackView
        anchors.fill: parent

        initialItem: Qt.resolvedUrl("StartPage.qml")
    }
}
