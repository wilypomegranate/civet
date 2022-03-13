import QtQuick 2.15
import QtQuick.Window 2.2
import QtMultimedia 5.15
import Qt.labs.settings 1.0

import civet.wheeldirection 1.0

Window {
    id: "window"
    width: 1920
    height: 1080
    visible: true

    Rectangle {
        color: "black"
        anchors.fill: parent
        Settings {
            id: settings
            property string url: "url"
        }
        MediaPlayer {
            id: mediaplayer
            source: settings.url
            autoPlay: true
        }

        VideoOutput {
            id: "video"
            anchors.fill: parent
            source: mediaplayer

        Keys.onPressed: {
            _keyboardClient.pressKey(event.key, event.modifiers)
            console.log("Pressed", event.key, event.modifiers)
            event.accepted = true
        }
        Keys.onReleased: {
            _keyboardClient.releaseKey(event.key, event.modifiers)
            console.log("Released", event.key, event.modifiers)
            // Handle windows modifier differently when pressed alone.
            // TODO This is most definitely a hack and needs a revisit.
            if (event.modifiers & Qt.MetaModifier && event.key == Qt.Key_Super_L) {
                _keyboardClient.pressKey(event.key, event.modifiers)
                console.log("Pressed", event.key, event.modifiers)
                _keyboardClient.releaseKey(event.key, event.modifiers)
                console.log("Released", event.key, event.modifiers)
            }
            event.accepted = true
        }
        focus: playArea.containsMouse
        MouseArea {
            property var oldMouseX: playArea.mouseX
            property var oldMouseY: playArea.mouseY
            property var leftClick: false
            property var rightClick: false
            property var middleClick: false
            property var allowChange: true
            id: playArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.BlankCursor
            acceptedButtons: Qt.LeftButton | Qt.RightButton | Qt.MiddleButton
            onPositionChanged: {
                var deltaX = playArea.mouseX - oldMouseX
                var deltaY = playArea.mouseY - oldMouseY
                /* if (deltaX < 10) { */
                /*     deltaX = parseInt(deltaX * 1.5) */
                /* } */
                /* if (deltaY < 10) { */
                /*     deltaY = parseInt(deltaY * 1.5) */
                /* } */
                // If the delta is too big, just send 127.
                if (deltaX > 127) {
                    deltaX = 127
                }
                if (deltaX < -127) {
                    deltaX = -127
                }
                if (deltaY > 127) {
                    deltaY = 127
                }
                if (deltaY < -127) {
                    deltaY = -127
                }
                /* console.log(deltaX, deltaY); */
                if (allowChange) {
                    _mouseClient.sendMovement(deltaX, deltaY, leftClick, rightClick, middleClick);
                }
                else {
                    allowChange = true
                }
                // Force the cursor to stay at the center of the screen.
                if (mouseX < 20 || mouseY < 20 || mouseX > video.width - 20 || mouseY > video.height - 20) {
                    var position = mapFromItem(video, window.x, window.y);
                    position.x += video.width / 2
                    position.y += video.height / 2
                    playArea.enabled = false
                    playArea.hoverEnabled = false
                    allowChange = false
                    _cursorMove.moveCursor(position);
                    playArea.enabled = true
                    playArea.hoverEnabled = true
                }
                oldMouseX = playArea.mouseX
                oldMouseY = playArea.mouseY
            }
            onPressed: function (event) {
                console.log(event.button)
                if (event.button == Qt.LeftButton) {
                    leftClick = true;
                }
                else if (event.button == Qt.RightButton) {
                    rightClick = true;
                }
                else if (event.button == Qt.MiddleButton) {
                    middleClick = true;
                }
                _mouseClient.sendMovement(0, 0, leftClick, rightClick, middleClick)
            }
            onReleased: function (event) {
                if (event.button == Qt.LeftButton) {
                    leftClick = false;
                }
                else if (event.button == Qt.RightButton) {
                    rightClick = false;
                }
                else if (event.button == Qt.MiddleButton) {
                    middleClick = false;
                }
                _mouseClient.sendMovement(0, 0, leftClick, rightClick)
            }
            onWheel: function(wheel) {
                console.log(wheel.angleDelta.y)
                if (wheel.angleDelta.y > 0) {
                    _mouseClient.sendMovement(0, 0, leftClick, rightClick, middleClick, WheelDirection.WHEEL_UP);
                }
                else if (wheel.angleDelta.y < 0) {
                    _mouseClient.sendMovement(0, 0, leftClick, rightClick, middleClick, WheelDirection.WHEEL_DOWN);
                }
                wheel.accepted = true;
            }
        }
        }

    }

}
