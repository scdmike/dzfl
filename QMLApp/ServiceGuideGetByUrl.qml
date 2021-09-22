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
            onClicked: ServiceGuideGetByUrl.prevPageClick()
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
            onClicked: ServiceGuideGetByUrl.nextPageClick()
        }
    }



    Image {
        objectName: "item0"
        x: -54
        y: 18
        width: 450
        height: 175

        Image {
            objectName: "itemurl"
            x: 142
            y: 0
            z:1
            width: 167
            height: 159

        }

        Text {
            objectName: "tbName"
            x: 108
            y: 159
            width: 234
            height: 36
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
    }

    Image {
        objectName: "item1"
        x: 278
        y: 18
        width: 450
        height: 175

        Image {
            objectName: "itemurl"
            x: 142
            y: 0
            z:1
            width: 167
            height: 159

        }

        Text {
            objectName: "tbName"
            x: 108
            y: 159
            width: 234
            height: 36
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
    }

    Image {
        objectName: "item2"
        x: 634
        y: 18
        width: 450
        height: 175

        Image {
            objectName: "itemurl"
            x: 142
            y: 0
            z:1
            width: 167
            height: 159

        }

        Text {
            objectName: "tbName"
            x: 108
            y: 159
            width: 234
            height: 36
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
    }

    Image {
        objectName: "item3"
        x: -59
        y: 217
        width: 450
        height: 175

        Image {
            objectName: "itemurl"
            x: 142
            y: 0
            z:1
            width: 167
            height: 159

        }

        Text {
            objectName: "tbName"
            x: 108
            y: 159
            width: 234
            height: 36
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
    }

    Image {
        objectName: "item4"
        x: 278
        y: 217
        width: 450
        height: 175

        Image {
            objectName: "itemurl"
            x: 142
            y: 0
            z:1
            width: 167
            height: 159

        }

        Text {
            objectName: "tbName"
            x: 108
            y: 159
            width: 234
            height: 36
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
    }

    Image {
        objectName: "item5"
        x: 278
        y: 415
        width: 450
        height: 175

        Image {
            objectName: "itemurl"
            x: 142
            y: 0
            z:1
            width: 167
            height: 159

        }

        Text {
            objectName: "tbName"
            x: 108
            y: 159
            width: 234
            height: 36
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
    }
    Image {
        objectName: "item6"
        x: 634
        y: 211
        width: 450
        height: 175

        Image {
            objectName: "itemurl"
            x: 142
            y: 0
            z:1
            width: 167
            height: 159

        }

        Text {
            objectName: "tbName"
            x: 108
            y: 159
            width: 234
            height: 36
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
    }
    Image {
        objectName: "item7"
        x: -59
        y: 415
        width: 450
        height: 175

        Image {
            objectName: "itemurl"
            x: 142
            y: 0
            z:1
            width: 167
            height: 159

        }

        Text {
            objectName: "tbName"
            x: 108
            y: 159
            width: 234
            height: 36
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
    }
    Image {
        objectName: "item8"
        x: 634
        y: 415
        width: 450
        height: 175

        Image {
            objectName: "itemurl"
            x: 142
            y: 0
            z:1
            width: 167
            height: 159

        }

        Text {
            objectName: "tbName"
            x: 108
            y: 159
            width: 234
            height: 36
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
    }
}
