import QtQuick 2.3

BorderImage {
    width: 1005
    height: 630
    source: "images/cjwtbg.png"

    Image {
        objectName: "imgPre"
        x: 32
        y: 440
        width: 27
        height: 72
        source: "images/xzuobutton.png"

        MouseArea {
            objectName: "mousePre"
            width: 27
            height: 72
            onClicked: QuestionPage.prevPageClick()
        }
    }

    Image {
        objectName: "imgNext"
        x: 943
        y: 440
        width: 27
        height: 78
        source: "images/xyaobutton.png"

        MouseArea {
            objectName: "mouseNext"
            width: 27
            height: 78
            onClicked: QuestionPage.nextPageClick()
        }
    }

    Text {
        objectName: "tbTitle"
        x: 303
        y: 82
        width: 597
        height: 55
        color: "#214c90"
        style: Text.Sunken
        font.family: "黑体"
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 22
    }

    Item {
        objectName: "tbGrid"
        x: 212
        y: 160
        width: 688
        height: 226
        clip: true
        Text {
            objectName: "tbContent"
            width: parent.width
            color: "#214c90"
            font.family: "黑体"
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            font.pixelSize: 15
        }
        Image {
            objectName: "imgContent"
            width: parent.width
            clip: false
            fillMode: Image.PreserveAspectFit
            smooth: true
        }
        MouseArea {
            width: parent.width
            height: parent.height
            property int downX: 0
            property int downY: 0
            onPressed: { downX = mouse.x; downY = mouse.y; }
            onPositionChanged:  QuestionPage.dragMove(mouse.x - downX, mouse.y - downY);
        }
    }

    MouseArea {
        x: 71
        y: 429
        width: 198
        height: 103
        onClicked: QuestionPage.questionListClick(0);
        Text {
            objectName: "qlist1"
            color: "#214c90"
            font.family: "黑体"
            clip: true
            width: parent.width
            height: parent.height
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            font.pixelSize: 18
        }
    }

    MouseArea {
        x: 291
        y: 429
        width: 198
        height: 103
        onClicked: QuestionPage.questionListClick(1);
        Text {
            objectName: "qlist2"
            color: "#214c90"
            font.family: "黑体"
            clip: true
            width: parent.width
            height: parent.height
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            font.pixelSize: 18
        }
    }

    MouseArea {
        x: 510
        y: 429
        width: 198
        height: 103
        onClicked: QuestionPage.questionListClick(2);
        Text {
            objectName: "qlist3"
            color: "#214c90"
            font.family: "黑体"
            clip: true
            width: parent.width
            height: parent.height
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            font.pixelSize: 18
        }
    }

    MouseArea {
        x: 730
        y: 429
        width: 198
        height: 103
        onClicked: QuestionPage.questionListClick(3);
        Text {
            objectName: "qlist4"
            color: "#214c90"
            font.family: "黑体"
            clip: true
            width: parent.width
            height: parent.height
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            font.pixelSize: 18
        }
    }
}
