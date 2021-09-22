import QtQuick 2.3

BorderImage {
    width: 1280
    height: 800
    source: "images/bg.png"

    //中心图标
    Image {
        x: 15
        y: 714
        width: 91
        height: 52
        source: "images/logo.png"
    }

    //禁用按钮
    DisableButton {
        objectName: "disableButton"
    }

    //滚动消息
    ScrollMessage {
        objectName: "scrollmsg"
        x: 615
        y: 978
    }


    Image {
        x: 697
        y: 315
        width: 260
        height: 205
        source: "images/zt.png"
    }

    Text {
        objectName: "CenterName"
        x: 400
        y: 976
        color: "#c8e6e6"
        font.bold: true
        font.family: "黑体"
        font.pixelSize: 21
    }
    //展示用户信息部分st
    Image {
        objectName: "userImage"
        x: 152
        y: 177
        width: 205
        height: 269
        smooth: true
        fillMode: Image.Stretch
        asynchronous: true
    }
    Rectangle {
        x: 152
        y: 177
        width: 205
        height: 269
        color: "#00000000"
        //border.color: "#221e1e"
    }
    Text {
        x: 155
        y: 496
        text: "姓名 ："
        font.family: "微软雅黑"
        font.pixelSize: 30
    }

    Text {
        x: 155
        y: 544
        text: "工号 ："
        font.family: "微软雅黑"
        font.pixelSize: 30
    }

    Text {
        objectName: "tbPhone"
        x: 155
        y: 596
        text: "电话 ："
        font.family: "微软雅黑"
        font.pixelSize: 30
    }
    Text {
        objectName: "userName"
        x: 252
        y: 505
        width: 120
        height: 22
        text: ""
        verticalAlignment: Text.AlignVCenter
       font.family: "微软雅黑"
        font.pixelSize: 30
    }

    Text {
        objectName: "userID"
        x: 252
        y: 553
        width: 120
        height: 22
        verticalAlignment: Text.AlignVCenter
        font.family: "微软雅黑"
        font.pixelSize: 30
    }

    Text {
        objectName: "phone2"
        x: 252
        y: 605
        width: 120
        height: 22
        text: ""
        verticalAlignment: Text.AlignVCenter
        font.family: "微软雅黑"
        font.pixelSize: 30
    }

    //end
}
