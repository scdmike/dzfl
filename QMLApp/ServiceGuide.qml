import QtQuick 2.3

BorderImage {
    width: 1180
    height: 606
    source: "images/blsx-bg.png"

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

    Image {
        objectName: "imgPrev"
        x: -33
        y: 284
        width: 69
        height: 69
        source: "images/xyaobutton.png"

        MouseArea {
            objectName: "mousePrev"
            width: 69
            height: 69
            onClicked: ServiceGuide.prevPageClick()
        }
    }

    Image {
        objectName: "imgNext"
        x: 1145
        y: 284
        width: 69
        height: 69
        source: "images/xzuobutton.png"

        MouseArea {
            objectName: "mouseNext"
            width: 69
            height: 69
            onClicked: ServiceGuide.nextPageClick()
        }
    }

    Image {
        objectName: "item0"
        x: 44
        y: 92
        width: 516
        height: 150
        source: "images/guidebutton.png"

        MouseArea {
            width: 516
            height: 150
            onClicked: ServiceGuide.guideListClick(0)
        }

        Text {
            objectName: "tbName"
            x: 123
            y: 15
            width: 341
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
            x: 123
            y: 84
            width: 341
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
            x: 123
            y: 117
            width: 341
            height: 13
            color: "#6b9ed1"
            clip: true
            font.family: "黑体"
            font.pixelSize: 13
        }
    }

    Image {
        objectName: "item1"
        x: 623
        y: 92
        width: 516
        height: 150
        MouseArea {
            width: 516
            height: 150
            onClicked: ServiceGuide.guideListClick(1)
        }
        Text {
            objectName: "tbName"
            x: 123
            y: 15
            width: 341
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
            x: 123
            y: 84
            width: 341
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
            x: 123
            y: 117
            width: 341
            height: 13
            color: "#6b9ed1"
            clip: true
            font.family: "黑体"
            font.pixelSize: 13
        }
        source: "images/guidebutton.png"
    }

    Image {
        objectName: "item2"
        x: 44
        y: 257
        width: 516
        height: 150
        MouseArea {
            width: 516
            height: 150
            onClicked: ServiceGuide.guideListClick(2)
        }
        Text {
            objectName: "tbName"
            x: 123
            y: 15
            width: 341
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
            x: 123
            y: 84
            width: 341
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
            x: 123
            y: 117
            width: 341
            height: 13
            color: "#6b9ed1"
            clip: true
            font.family: "黑体"
            font.pixelSize: 13
        }
        source: "images/guidebutton.png"
    }

    Image {
        objectName: "item3"
        x: 623
        y: 257
        width: 516
        height: 150
        MouseArea {
            width: 516
            height: 150
            onClicked: ServiceGuide.guideListClick(3)
        }
        Text {
            objectName: "tbName"
            x: 123
            y: 15
            width: 341
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
            x: 123
            y: 84
            width: 341
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
            x: 123
            y: 117
            width: 341
            height: 13
            color: "#6b9ed1"
            clip: true
            font.family: "黑体"
            font.pixelSize: 13
        }
        source: "images/guidebutton.png"
    }

    Image {
        objectName: "item4"
        x: 44
        y: 428
        width: 516
        height: 150
        MouseArea {
            width: 516
            height: 150
            onClicked: ServiceGuide.guideListClick(4)
        }
        Text {
            objectName: "tbName"
            x: 123
            y: 15
            width: 341
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
            x: 123
            y: 84
            width: 341
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
            x: 123
            y: 117
            width: 341
            height: 13
            color: "#6b9ed1"
            clip: true
            font.family: "黑体"
            font.pixelSize: 13
        }
        source: "images/guidebutton.png"
    }

    Image {
        objectName: "item5"
        x: 623
        y: 428
        width: 516
        height: 150
        MouseArea {
            width: 516
            height: 150
            onClicked: ServiceGuide.guideListClick(5)
        }
        Text {
            objectName: "tbName"
            x: 123
            y: 15
            width: 341
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
            x: 123
            y: 84
            width: 341
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
            x: 123
            y: 117
            width: 341
            height: 13
            color: "#6b9ed1"
            clip: true
            font.family: "黑体"
            font.pixelSize: 13
        }
        source: "images/guidebutton.png"
    }
}
