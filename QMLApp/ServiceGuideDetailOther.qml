import QtQuick 2.3

BorderImage {
    width: 1008
    height: 482
    source: "images/guidebg.png"

    Text {
        objectName: "tbName"
        x: 320
        y: 55
        width: 594
        height: 56
        color: "#0000ff"
        font.pointSize: 25
        style: Text.Sunken
        font.family: "黑体"
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 25
    }

    MouseArea {
        x: 69
        y: 126
        width: 162
        height: 34
        onClicked: ServiceGuideDetailOther.btnClick(0)
    }

    Image {
        objectName: "btn0"
        x: 69
        y: 126
        width: 162
        height: 34
        source: "images/spyj.png"
    }

    MouseArea {
        x: 69
        y: 161
        width: 162
        height: 34
        onClicked: ServiceGuideDetailOther.btnClick(1)
    }
    Image {
        objectName: "btn1"
        x: 69
        y: 161
        width: 162
        height: 34
        source: "images/sqtj.png"
    }

    MouseArea {
        x: 69
        y: 201
        width: 162
        height: 34
        onClicked: ServiceGuideDetailOther.btnClick(2)
    }
    Image {
        objectName: "btn2"
        x: 69
        y: 200
        width: 162
        height: 34
        source: "images/sbzl.png"
    }

    MouseArea {
        x: 69
        y: 240
        width: 162
        height: 34
        onClicked: ServiceGuideDetailOther.btnClick(3)
    }
    Image {
        objectName: "btn3"
        x: 69
        y: 239
        width: 162
        height: 34
        source: "images/spcx.png"
    }

    Item {
        objectName: "tbGrid"
        x: 259
        y: 122
        width: 665
        height: 290
        clip: true
        Text {
            objectName: "tbContent"
            width: parent.width
            style: Text.Raised
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            font.family: "黑体"
            font.pixelSize: 21
        }
        Image {
            width: parent.width
            clip: false
            fillMode: Image.PreserveAspectFit
            smooth: true
            objectName: "imgContent"
        }
        MouseArea {
            width: parent.width
            height: parent.height
            property int downX: 0
            property int downY: 0
            onPressed: { downX = mouse.x; downY = mouse.y; }
            onPositionChanged: ServiceGuideDetailOther.dragMove(mouse.x - downX, mouse.y - downY);
        }
    }
}
