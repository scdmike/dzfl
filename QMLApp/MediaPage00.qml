import QtQuick 2.3
import QtMultimedia 5.0

BorderImage {
    width: 1005
    height: 630
    source: "images/mtbj.png"

    MediaPlayer {
        objectName: "video"
        id: mediaPlayer
    }
    VideoOutput {
        x: 48
        y: 47
        width: 499
        height: 320
        source: mediaPlayer
    }

    Text {
        objectName: "pageMediaCount"
        text: "5"
    }

    property string src: ""
    onVisibleChanged: src = ""
    onSrcChanged: {
        mediaPlayer.source = src;
        if(src.length > 0)
            mediaPlayer.play();
    }

    Image {
        objectName: "imgSlt"
        x: 48
        y: 47
        width: 499
        height: 320
    }

    Image {
        objectName: "imgPre"
        x: 12
        y: 428
        width: 35
        height: 86
        source: "images/xzuobutton.png"

        MouseArea {
            objectName: "mousePre"
            width: 35
            height: 86
            onClicked: MediaPage.prevPageClick()
        }
    }

    Image {
        objectName: "imgNext"
        x: 944
        y: 431
        width: 27
        height: 78
        source: "images/xyaobutton.png"

        MouseArea {
            objectName: "mouseNext"
            width: 27
            height: 78
            onClicked: MediaPage.nextPageClick()
        }
    }

    Image {
        objectName: "play"
        x: 255
        y: 163
        width: 72
        height: 64
        source: "images/bf.png"
        MouseArea {
            width: 72
            height: 64
            onClicked: MediaPage.playClick()
        }
    }

    Text {
        objectName: "tbTitle"
        x: 590
        y: 56
        width: 338
        color: "#214c90"
        style: Text.Raised
        smooth: true
        font.family: "黑体"
        font.pixelSize: 30
    }

    Text {
        objectName: "tbContent"
        x: 605
        y: 97
        width: 338
        height: 266
        color: "#214c90"
        style: Text.Sunken
        smooth: true
        font.family: "黑体"
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        font.pixelSize: 23
    }

    Image {
        objectName: "mList_m1"
        x: 55
        y: 417
        width: 166
        height: 109
        opacity: 0.700

        MouseArea {
            width: parent.width
            height: parent.height
            onClicked: MediaPage.mediaListClick(0);
        }

        Text {
            y: 44
            width: parent.width
            height: 20
            color: "#214c90"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 20
        }
    }

    Image {
        objectName: "mList_m2"
        x: 230
        y: 417
        width: 170
        height: 109
        opacity: 0.700

        MouseArea {
            width: parent.width
            height: parent.height
            onClicked: MediaPage.mediaListClick(1);
        }

        Text {
            y: 44
            width: parent.width
            height: 20
            color: "#214c90"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 20
        }
    }

    Image {
        objectName: "mList_m3"
        x: 409
        y: 417
        width: 165
        height: 109
        opacity: 0.700

        MouseArea {
            width: parent.width
            height: parent.height
            onClicked: MediaPage.mediaListClick(2);
        }

        Text {
            y: 44
            width: parent.width
            height: 20
            color: "#214c90"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 20
        }
    }

    Image {
        objectName: "mList_m4"
        x: 587
        y: 417
        width: 168
        height: 109
        opacity: 0.700

        MouseArea {
            width: parent.width
            height: parent.height
            onClicked: MediaPage.mediaListClick(3);
        }

        Text {
            y: 44
            width: parent.width
            height: 20
            color: "#214c90"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 20
        }
    }

    Image {
        objectName: "mList_m5"
        x: 763
        y: 417
        width: 168
        height: 109
        opacity: 0.700

        MouseArea {
            width: parent.width
            height: parent.height
            onClicked: MediaPage.mediaListClick(4);
        }

        Text {
            y: 44
            width: parent.width
            height: 20
            color: "#214c90"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 20
        }
    }

}
