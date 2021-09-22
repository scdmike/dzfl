import QtQuick 2.3

BorderImage {
    id: borderImage1
    width: 1179
    height: 603
    source: "images/nyk.png"
    onVisibleChanged: if(visible) ServiceInfo.resumeScroll()

    Image {
        objectName: "image_gov_d"
        x: 406
        y: -411
        width: 178
        height: 135
        visible: false
        source: "images/dy.png"
    }

    Image {
        objectName: "image_gov_t"
        x: 453
        y: -397
        width: 117
        height: 117
        visible: false
        source: "images/ty.png"
    }

    Image {
        objectName: "image_gov_p"
        x: 453
        y: -397
        width: 117
        height: 117
        visible: false
    }
    Image {
        id:returnbg
        x: 1074
        y: 610
        width: 105
        height: 46
        smooth: true
        visible: false
        source: "images/lfhnew.png"
        MouseArea {
            width: parent.width
            height: parent.height
            onClicked: {
                returnbg.visible=false
                showbtn2.visible=false
                showbtn4.visible=false
                showbtn3.visible=false
            }
        }
    }


    Image {
        x: 437
        y: 383
        z:1
        width: 150
        height: 130
        source: "images/showbtn2.png"
        MouseArea {
            width: 150
            height: 130
            onClicked: {
                returnbg.visible=true
                showbtn2.visible=true
            }
        }
    }
    Image {
        id:showbtn2
        x: 0
        y: 0
        z:2
        visible: false
        width: 1180
        height: 606
        source: "images/showbtn2.jpg"

    }

    Image {
        x: 617
        y: 383
        z:1
        width: 150
        height: 130
        source: "images/showbtn3.png"
        MouseArea {
            width: 150
            height: 130
            onClicked: {
                returnbg.visible=true
                showbtn3.visible=true
            }
        }
    }
    Image {
        id:showbtn3
        x: 0
        y: 0
        z:2
        visible: false
        width: 1180
        height: 606
        source: "images/showbtn3.jpg"
        Text {
            objectName: "Responsibility"
            x: 23
            y: 83
            width: 1132
            height: 497
            text: ""
            font.family: "微软雅黑"
            wrapMode: Text.WrapAnywhere
            font.pixelSize: 20
        }
    }

    Item {
        x: 795
        y: 383
        z:1
        width: 150
        height: 130
        Image {
            smooth: true
            anchors.fill: parent
            source: "images/showbtn1.png"
            MouseArea {
                width: parent.width
                height: parent.height
                onClicked: {
                    FramePage.returnClick();
                    FramePage.guideClick();
                }
            }
        }

        Image {
            objectName: "actGuide"
            smooth: true
            anchors.fill: parent
            source: "images/showbtn1.png"
        }
    }

    Image {
        x: 977
        y: 383
        z:1
        width: 150
        height: 130
        source: "images/showbtn4.png"
        MouseArea {
            width: 150
            height: 130
            onClicked: {
                returnbg.visible=true
                showbtn4.visible=true
            }
        }
    }
    Image {
        id:showbtn4
        x: 0
        y: 0
        z:2
        visible: false
        width: 1180
        height: 606
        source: "images/showbtn4.jpg"

    }

    ProjectNameGrid {
        x: 544
        y: 55
        width: 455
        height: 304
        objectName: "projGrid"
    }

    Item {
        objectName: "grid_info"
        x: 572
        y: 94
        width: 399
        height: 395
        visible: true
        //clip: true

        Image {
            x: 91
            y: 41
            width: 233
            height: 129
            source: "images/blr.png"
        }

        Text {
            objectName: "serviceID"
            x: 91
            y: 41
            width: 233
            height: 129
            color: "#ffffff"
            text: ""
            font.family: "微软雅黑"
            horizontalAlignment: Text.AlignHCenter   //中间对齐
            verticalAlignment:   Text.AlignVCenter  //中间对齐
            font.bold: true
            style: Text.Raised
            font.pixelSize: 50
        }

        Text {
            objectName: "projectName"
            x: 119
            y: -392
            width: 178
            height: 28
            color: "#415122"
            text: "x"
            verticalAlignment: Text.AlignVCenter
            font.family: "微软雅黑"
            style: Text.Raised
            font.bold: true
            font.pixelSize: 28
        }

        Text {
            objectName: "sex"
            x: 119
            y: -354
            width: 178
            color: "#415122"
            text: "x"
            font.bold: true
            style: Text.Sunken
            font.family: "微软雅黑"
            font.pixelSize: 28
        }

        Text {
            objectName: "personPhone"
            x: 119
            y: -316
            width: 178
            color: "#415122"
            text: "x"
            font.bold: true
            style: Text.Sunken
            font.family: "微软雅黑"
            font.pixelSize: 30
            visible: false
        }
        Text {

            x: -27
            y: 208
            width: 178
            text: "办理业务："
            //font.bold: true
            style: Text.Sunken
            font.family: "微软雅黑"
            font.pixelSize: 30
            horizontalAlignment: Text.AlignRight //右对齐
            //visible: false
        }

        Text {
            objectName: "accBizName"
            x: 151
            y: 208
            width: 178
            height: 40
            text: "x"
            style: Text.Sunken
            font.family: "微软雅黑"
            font.pixelSize: 30
            horizontalAlignment: Text.AlignLeft    //左对齐
            //visible: false
        }



        ScrollMessagePage {
            objectName: "acceptName"
            x: 162
            y: 148
            width: 229
            height: 28
            color: "#415122"
            fontBold: true
            style: Text.Sunken
            fontSize: 26
        }
    }

    Image {
        objectName: "userImage"
        x: 102
        y: 55
        width: 205
        height: 269
        smooth: true
        fillMode: Image.Stretch
        asynchronous: true
    }
    Rectangle {
        x: 102
        y: 55
        width: 205
        height: 269
        color: "#00000000"
        //border.color: "#221e1e"
    }

    Text {
        objectName: "userName"
        x: 201
        y: 383
        width: 120
        height: 22
        text: ""
        verticalAlignment: Text.AlignVCenter
        font.family: "微软雅黑"
        font.pixelSize: 30
    }

    Text {
        objectName: "userID"
        x: 201
        y: 431
        width: 120
        height: 22
        verticalAlignment: Text.AlignVCenter
        font.family: "微软雅黑"
        font.pixelSize: 30
    }

    Text {
        objectName: "phone1"
        x: 201
        y: 909
        width: 138
        text: ""
        verticalAlignment: Text.AlignVCenter
        style: Text.Sunken
        font.bold: true
        font.family: "微软雅黑"
        font.pixelSize: 22
    }

    Text {
        objectName: "phone2"
        x: 201
        y: 483
        width: 120
        height: 22
        text: ""
        verticalAlignment: Text.AlignVCenter
        font.family: "微软雅黑"
        font.pixelSize: 30
    }

    Item {
        id: serviceMessage
        x: 53
        y: -411
        width: 316
        height: 173

        Text {
            id: text1
            x: 15
            y: 13
            color: "#165da3"
            text: "服务寄语："
            style: Text.Sunken
            font.bold: true
            font.family: "微软雅黑"
            font.pixelSize: 32
        }

        Text {
            objectName: "message"
            x: 65
            y: 63
            width: 230
            height: 81
            color: "#165da3"
            text: ""
            style: Text.Raised
            smooth: true
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            font.pixelSize: 22
        }
    }

    Text {
        x: 105
        y: 374
        text: "姓名 ："
        font.family: "微软雅黑"
        font.pixelSize: 30
    }

    Text {
        x: 105
        y: 422
        text: "工号 ："
        font.family: "微软雅黑"
        font.pixelSize: 30
    }

    Text {
        x: 91
        y: 909
        color: "#165da3"
        text: "咨询电话:"
        font.family: "微软雅黑"
        font.pixelSize: 22
    }

    Text {
        objectName: "tbPhone"
        x: 105
        y: 474
        text: "电话 ："
        font.family: "微软雅黑"
        font.pixelSize: 30
    }



    Image {
        objectName: "img_ty"
        x: 649
        y: -411
        width: 145
        height: 30
        visible: false
        source: "images/tyfwg.png"
    }

    Image {
        objectName: "img_dy"
        x: 649
        y: -411
        width: 145
        height: 30
        visible: false
        source: "images/dyfwg.png"
    }

    ServiceStar {
        objectName: "serviceStar"
        x: 53
        y: -223
        visible: false

    }

    ModifyPersonInfo {
        objectName: "modifyPersonInfo"
        property int showTime: 10
        x: -1560
        y: -11
        visible: false
    }
}
