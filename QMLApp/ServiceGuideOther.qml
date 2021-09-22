import QtQuick 2.3

BorderImage {
    width: 1008
    height: 482
    source: "images/bg2.png"

    Image {
        objectName: "imgPrev"
        x: 8
        y: 205
        width: 27
        height: 72
        source: "images/xzuobutton.png"

        MouseArea {
            objectName: "mousePrev"
            width: 27
            height: 72
            onClicked: ServiceGuideOther.prevPageClick()
        }
    }

    Image {
        objectName: "imgNext"
        x: 973
        y: 205
        width: 27
        height: 72
        source: "images/xyaobutton.png"

        MouseArea {
            objectName: "mouseNext"
            width: 27
            height: 72
            onClicked: ServiceGuideOther.nextPageClick()
        }
    }

    Image {
        objectName: "item0"
        x: 46
        y: 10
        width: 450
        height: 150
        source: "images/guidebutton.png"

        MouseArea {
            anchors.fill: parent
            onClicked: ServiceGuideOther.guideListClick(0)
        }

        Text {
            objectName: "tbName"
            x: 124
            y: 9
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
            y: 80
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
            y: 114
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
        x: 509
        y: 10
        width: 450
        height: 150
        MouseArea {
            anchors.fill: parent
            onClicked: ServiceGuideOther.guideListClick(1)
        }
        Text {
            objectName: "tbName"
            x: 124
            y: 9
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
            y: 80
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
            y: 114
            width: 307
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
        x: 46
        y: 166
        width: 450
        height: 150
        MouseArea {
            anchors.fill: parent
            onClicked: ServiceGuideOther.guideListClick(2)
        }
        Text {
            objectName: "tbName"
            x: 124
            y: 9
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
            y: 80
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
            y: 114
            width: 307
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
        x: 509
        y: 166
        width: 450
        height: 150
        MouseArea {
            anchors.fill: parent
            onClicked: ServiceGuideOther.guideListClick(3)
        }
        Text {
            objectName: "tbName"
            x: 124
            y: 9
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
            y: 80
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
            y: 114
            width: 307
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
        x: 46
        y: 324
        width: 450
        height: 150
        MouseArea {
            anchors.fill: parent
            onClicked: ServiceGuideOther.guideListClick(4)
        }
        Text {
            objectName: "tbName"
            x: 124
            y: 9
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
            y: 80
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
            y: 114
            width: 307
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
        x: 509
        y: 324
        width: 450
        height: 150
        MouseArea {
            anchors.fill: parent
            onClicked: ServiceGuideOther.guideListClick(5)
        }
        Text {
            objectName: "tbName"
            x: 124
            y: 9
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
            y: 80
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
            y: 114
            width: 307
            height: 13
            color: "#6b9ed1"
            clip: true
            font.family: "黑体"
            font.pixelSize: 13
        }
        source: "images/guidebutton.png"
    }
}
