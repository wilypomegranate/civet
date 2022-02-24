import QtQuick 2.15
import QtQuick.Window 2.2
import QtMultimedia 5.15

Window {
    width: 1920
    height: 1080
    visible: true

    Rectangle {
        color: "black"
        anchors.fill: parent
        MediaPlayer {
            id: mediaplayer
            source: "gst-pipeline: udpsrc retrieve-sender-address=false port=5000 caps = \"application/x-rtp, media=video, clock-rate=90000, encoding-name=H264, packetization-mode=1, payload=96, seqnum-offset=19489, timestamp-offset=3505589453, ssrc=1918278934, a-framerate=50\" ! rtph264depay ! decodebin ! autovideosink"
            /* source: "gst-pipeline: videotestsrc ! autovideosink" */
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
            event.accepted = true
        }
        focus: playArea.containsMouse
        MouseArea {
            property var oldMouseX: playArea.mouseX
            property var oldMouseY: playArea.mouseY
            property var leftClick: false
            property var allowChange: true
            id: playArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.BlankCursor
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
                    _mouseClient.sendMovement(deltaX, deltaY, leftClick);
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
                    _mouseClient.sendMovement(0, 0, leftClick)
                }
            }
            onReleased: function (event) {
                if (event.button == Qt.LeftButton) {
                    leftClick = false;
                    _mouseClient.sendMovement(0, 0, leftClick)
                }
            }
        }
        }

    }

}
