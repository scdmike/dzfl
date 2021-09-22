import QtQuick 2.3
import QtMultimedia 5.3

BorderImage {
    width: 1280
    height: 800
    source: "images/bg.png"

    //中心图标
    Image {
        x: 25
        y: 846
        width: 91
        height: 52
        source: "images/logo.png"
    }

    //禁用按钮
    DisableButton {
        objectName: "disableButton"
    }

    //滚动消息
    ScrollMessagePage {
        objectName: "scrollmsg"
        x: 853
        y: 876
    }

    Image {
        x: 48
        y: 121
        width: 1185
        height: 608
        source: "Intro.png"
    }

    Text {
        objectName: "CenterName"
        x: 396
        y: 877
        width: 50
        height: 21
        color: "#c8e6e6"
        font.bold: true
        font.family: "黑体"
        font.pixelSize: 21
    }
}
