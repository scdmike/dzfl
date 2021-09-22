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

        Grid {
            objectName: "tbContent"
            width: parent.width
            columns: 1
            flow: Grid.TopToBottom
            Text {
                objectName: "t0"
                width: parent.width
                height: 50
                font.family: "华文隶书"
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 38
            }
            Text {
                objectName: "c0"
                width: parent.width
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                font.pixelSize: 25
            }

            Text {
                width: parent.width
                height: 100
            }

            Text {
                objectName: "t1"
                width: parent.width
                height: 50
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                font.family: "华文隶书"
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 38
            }
            Text {
                objectName: "c1"
                width: parent.width
                font.pixelSize: 25
            }
        }
    }
}
