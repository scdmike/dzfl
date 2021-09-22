import QtQuick 2.3

BorderImage {
    width: 1180
    height: 606
    source: "images/guidebg.png"

    Image {
        x: 1074
        y: 610
        width: 105
        height: 46
        smooth: true
        source: "images/lfhnew.png"
        MouseArea {
            width: parent.width
            height: parent.height
            onClicked: FramePage.returnClick()
        }
    }

    Text {
        objectName: "tbName"
        x: 345
        y: 39
        width: 590
        height: 67
        color: "#0000ff"
        text: ""
        style: Text.Sunken
        font.family: "黑体"
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 25
    }

    MouseArea {
        x: 55
        y: 149
        width: 167
        height: 60
        onClicked: ServiceGuideDetail.btnClick(0)
    }

    Image {
        objectName: "btn0"
        x: 55
        y: 149
        width: 167
        height: 60
        source: "images/spyj.png"
    }

    MouseArea {
        x: 55
        y: 208
        width: 167
        height: 60
        onClicked: ServiceGuideDetail.btnClick(1)
    }
    Image {
        objectName: "btn1"
        x: 55
        y: 208
        width: 167
        height: 60
        source: "images/sqtj.png"
    }

    MouseArea {
        x: 55
        y: 266
        width: 167
        height: 60
        onClicked: ServiceGuideDetail.btnClick(2)
    }
    Image {
        objectName: "btn2"
        x: 55
        y: 266
        width: 167
        height: 60
        source: "images/sbzl.png"
    }

    MouseArea {
        x: 55
        y: 325
        width: 167
        height: 60
        onClicked: ServiceGuideDetail.btnClick(3)
    }
    Image {
        objectName: "btn3"
        x: 55
        y: 325
        width: 167
        height: 60
        source: "images/spcx.png"
    }

    Item {
        objectName: "tbGrid"
        x: 315
        y: 170
        width: 650
        height: 346
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
            onPositionChanged:  ServiceGuideDetail.dragMove(mouse.x - downX, mouse.y - downY);
        }
    }
}
