import QtQuick 2.3

BorderImage {
    width: 1005
    height: 630
    source: "images/bg2.png"
    Item {
        objectName: "tbGrid"
        x: 35
        y: 44
        width: 936
        height: 546
        clip: true

        MouseArea {
            width: parent.width
            height: parent.height
            property int downX: 0
            property int downY: 0
            onPressed: { downX = mouse.x; downY = mouse.y; }
            onPositionChanged:  HonestPage.dragMove(mouse.x - downX, mouse.y - downY);
        }

        Text {
            objectName: "t1"
            width: parent.width
            height: parent.height
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            font.family: "宋体"
            font.bold: true
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 38
        }
    }
}
