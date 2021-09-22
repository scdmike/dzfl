import QtQuick 2.3
import QtMultimedia 5.0

BorderImage {
    width: 1005
    height: 630
    source: "images/mtbj.png"
    property int mIndex: 0

    Image {
        objectName: "imgSlt"
        x: 18
        y: 16
        width: 966
        height: 598
    }

    Text {
        objectName: "pageMediaCount"
        text: "5"
        visible: false
    }

    MouseArea {
        width: parent.width
        height: parent.height
        property int downX: 0
        onPressed: downX = mouse.x;
        onReleased: {
            if(mouse.x - 50 > downX) MediaPage.mediaListClick(MediaPage.mIndex - 1);
            else if(mouse.x + 50 < downX) MediaPage.mediaListClick(MediaPage.mIndex + 1);
        }
    }

}
