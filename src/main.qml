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
            anchors.fill: parent
            source: mediaplayer

            MouseArea {
                property var oldMouseX: playArea.mouseX
                property var oldMouseY: playArea.mouseY
                id: playArea
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.BlankCursor
                onPositionChanged: {
                    var deltaX = playArea.mouseX - oldMouseX
                    var deltaY = playArea.mouseY - oldMouseY
                    // If the delta is too big drop it, because it's likely not right.
                    if (Math.abs(deltaX) < 100 && Math.abs(deltaY) < 100) {
                        console.log(deltaX, deltaY);
                        _mouseClient.sendMovement(deltaX, deltaY);
                    }
                    oldMouseX = playArea.mouseX
                    oldMouseY = playArea.mouseY
                }
            }
        }

    }

}
