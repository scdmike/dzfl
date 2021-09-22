import QtQuick 2.3

BorderImage {
    width: 1005
    height: 630
    source: "images/bg2.png"

    Image {
        objectName: "imgPrev"
        x: 4
        y: 284
        width: 27
        height: 72
        source: "images/xyaobutton.png"

        MouseArea {
            objectName: "mousePrev"
            width: 27
            height: 72
            onClicked: ServiceGuideOtherXM.prevPageClick()
        }
    }

    Image {
        objectName: "imgNext"
        x: 973
        y: 284
        width: 27
        height: 72
        source: "images/xzuobutton.png"

        MouseArea {
            objectName: "mouseNext"
            width: 27
            height: 72
            onClicked: ServiceGuideOtherXM.nextPageClick()
        }
    }

    Image {
        objectName: "item0"
        x: 42
        y: 24
        width: 450
        height: 175
        source: "images/guidebuttonXM.png"

        MouseArea {
            width: 450
            height: 175
            onClicked: ServiceGuideOtherXM.guideListClick(0)
        }

        Text {
            objectName: "tbName"
            x: 124
            y: 18
            width: 307
            height: 68
            color: "#508cc9"
            style: Text.Sunken
            smooth: true
            clip: true
            font.family: "黑体"
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 18
        }

        Text {
            objectName: "tbSn"
            x: 124
            y: 94
            width: 307
            height: 20
            color: "#88b0da"
            style: Text.Sunken
            clip: true
            font.family: "黑体"
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 13
        }

        Text {
            objectName: "tbTime"
            x: 124
            y: 134
            width: 307
            height: 13
            color: "#6b9ed1"
            clip: true
            font.family: "黑体"
            font.pixelSize: 13
        }
    }

    Image {
        objectName: "item1"
        x: 515
        y: 24
        width: 450
        height: 175
        MouseArea {
            width: 450
            height: 175
            onClicked: ServiceGuideOtherXM.guideListClick(1)
        }
        Text {
            objectName: "tbName"
            x: 124
            y: 18
            width: 307
            height: 68
            color: "#508cc9"
            style: Text.Sunken
            smooth: true
            clip: true
            font.family: "黑体"
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 18
        }

        Text {
            objectName: "tbSn"
            x: 124
            y: 94
            width: 307
            height: 20
            color: "#88b0da"
            style: Text.Sunken
            clip: true
            font.family: "黑体"
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 13
        }

        Text {
            objectName: "tbTime"
            x: 124
            y: 134
            width: 307
            height: 13
            color: "#6b9ed1"
            clip: true
            font.family: "黑体"
            font.pixelSize: 13
        }
        source: "images/guidebuttonXM.png"
    }

    Image {
        objectName: "item2"
        x: 42
        y: 226
        width: 450
        height: 175
        MouseArea {
            width: 450
            height: 175
            onClicked: ServiceGuideOtherXM.guideListClick(2)
        }
        Text {
            objectName: "tbName"
            x: 124
            y: 18
            width: 307
            height: 68
            color: "#508cc9"
            style: Text.Sunken
            smooth: true
            clip: true
            font.family: "黑体"
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 18
        }

        Text {
            objectName: "tbSn"
            x: 124
            y: 94
            width: 307
            height: 20
            color: "#88b0da"
            style: Text.Sunken
            clip: true
            font.family: "黑体"
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 13
        }

        Text {
            objectName: "tbTime"
            x: 124
            y: 134
            width: 307
            height: 13
            color: "#6b9ed1"
            clip: true
            font.family: "黑体"
            font.pixelSize: 13
        }
        source: "images/guidebuttonXM.png"
    }

    Image {
        objectName: "item3"
        x: 515
        y: 226
        width: 450
        height: 175
        MouseArea {
            width: 450
            height: 175
            onClicked: ServiceGuideOtherXM.guideListClick(3)
        }
        Text {
            objectName: "tbName"
            x: 124
            y: 18
            width: 307
            height: 68
            color: "#508cc9"
            style: Text.Sunken
            smooth: true
            clip: true
            font.family: "黑体"
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 18
        }

        Text {
            objectName: "tbSn"
            x: 124
            y: 94
            width: 307
            height: 20
            color: "#88b0da"
            style: Text.Sunken
            clip: true
            font.family: "黑体"
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 13
        }

        Text {
            objectName: "tbTime"
            x: 124
            y: 134
            width: 307
            height: 13
            color: "#6b9ed1"
            clip: true
            font.family: "黑体"
            font.pixelSize: 13
        }
        source: "images/guidebuttonXM.png"
    }

    Image {
        objectName: "item4"
        x: 42
        y: 427
        width: 450
        height: 175
        MouseArea {
            width: 450
            height: 175
            onClicked: ServiceGuideOtherXM.guideListClick(4)
        }
        Text {
            objectName: "tbName"
            x: 124
            y: 18
            width: 307
            height: 68
            color: "#508cc9"
            style: Text.Sunken
            smooth: true
            clip: true
            font.family: "黑体"
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 18
        }

        Text {
            objectName: "tbSn"
            x: 124
            y: 94
            width: 307
            height: 20
            color: "#88b0da"
            style: Text.Sunken
            clip: true
            font.family: "黑体"
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 13
        }

        Text {
            objectName: "tbTime"
            x: 124
            y: 134
            width: 307
            height: 13
            color: "#6b9ed1"
            clip: true
            font.family: "黑体"
            font.pixelSize: 13
        }
        source: "images/guidebuttonXM.png"
    }

    Image {
        objectName: "item5"
        x: 515
        y: 427
        width: 450
        height: 175
        MouseArea {
            width: 450
            height: 175
            onClicked: ServiceGuideOtherXM.guideListClick(5)
        }
        Text {
            objectName: "tbName"
            x: 124
            y: 18
            width: 307
            height: 68
            color: "#508cc9"
            style: Text.Sunken
            smooth: true
            clip: true
            font.family: "黑体"
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 18
        }

        Text {
            objectName: "tbSn"
            x: 124
            y: 94
            width: 307
            height: 20
            color: "#88b0da"
            style: Text.Sunken
            clip: true
            font.family: "黑体"
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 13
        }

        Text {
            objectName: "tbTime"
            x: 124
            y: 134
            width: 307
            height: 13
            color: "#6b9ed1"
            clip: true
            font.family: "黑体"
            font.pixelSize: 13
        }
        source: "images/guidebuttonXM.png"
    }
}
