import QtQuick 2.3

BorderImage {
    width: 1280
    height: 800
    source: "images/bg.png"

    BorderImage {
        id: grid1
        objectName: "grid1"
        x: 50
        y: 122
        width: 1179
        height: 603

        ServiceInfo {

            objectName: "ServiceInfo"
            visible: false
        }

        ServiceGuide {

            width: 1180
            height: 606
            objectName: "ServiceGuide"
            visible: true
        }

        ServiceGuideGetByUrl {
            objectName: "ServiceGuideGetByUrl"
            visible: false
        }

        ServiceGuideDetail {
            width: 1180
            height: 606
            objectName: "ServiceGuideDetail"
            visible: false
        }


        ServiceGuideOther {
            objectName: "ServiceGuideOther"
            visible: false
        }     
        ServiceGuideDetailOther {
            objectName: "ServiceGuideDetailOther"
            visible: false
        }

        QuestionPage {
            objectName: "QuestionPage"
            visible: false
        }

        Item {
            objectName: "TelWindow"
            visible: false
        }

        MediaPage {
            objectName: "MediaPage"
            visible: false
        }

        Honest {
            objectName: "HonestPage"
            visible: false
        }

        Duty {
            objectName: "DutyPage"
            visible: false
        }
    }

    Image {
        x: 965
        y: -226
        width: 155
        height: 59
        smooth: true
        source: "images/lfh.png"
        MouseArea {
            width: parent.width
            height: parent.height
            onClicked: FramePage.returnClick()
        }
    }


    Text {
        x: 973
        y: 879
        height: 16
        text: "Ver:"
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 12
    }

    Text {
        id: tbVer
        objectName: "tbVer"
        x: 1003
        y: 879
        width: 32
        height: 16
        text: "3.12"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 12
    }

    Image {
        x: -165
        y: 988
        width: 91
        height: 52
        source: "images/logo.png"
    }

    ScrollMessagePage {
        objectName: "scrollmsg"
        x: 655
        y: 918
    }

    Item {
        id: guideGridOther
        x: 311
        y: -221
        width: 155
        height: 59
        visible: false
        Image {
            anchors.fill: parent
            smooth: true
            source: "images/zjfw.png"
            MouseArea {
                anchors.fill: parent
                onClicked: FramePage.guideOtherClick()
            }
        }

        Image {
            anchors.fill: parent
            objectName: "actGuideOther"
            smooth: true
            source: "images/zjfwh.png"
        }
    }

    Item {
        id: guideXM
        x: 311
        y: -221
        width: 155
        height: 59
        visible: false
        Image {
            anchors.fill: parent
            smooth: true
            source: "images/ltzgg.png"
            MouseArea {
                anchors.fill: parent
                onClicked: FramePage.guideXMClick()
            }
        }

        Image {
            anchors.fill: parent
            objectName: "actGuideXM"
            smooth: true
            source: "images/htzgg.png"
        }
    }

    Item {
        id: guideOtherXM
        x: 667
        y: -221
        width: 155
        height: 59
        visible: false
        Image {
            anchors.fill: parent
            smooth: true
            source: "images/lzcfg.png"
            MouseArea {
                anchors.fill: parent
                onClicked: FramePage.guideOtherXMClick()
            }
        }

        Image {
            anchors.fill: parent
            objectName: "actGuideOtherXM"
            smooth: true
            source: "images/hzcfg.png"
        }
    }

    Item {
        x: -92
        y: -221
        width: 155
        height: 59
        Image {
            smooth: true
            anchors.fill: parent
            source: "images/lfwzn.png"
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
            source: "images/hfwzn.png"
        }
    }

    Item {
        x: 504
        y: 20
        width: 155
        height: 59
        visible: false
        Image {
            smooth: true
            anchors.fill: parent
            source: "images/lfwzn.png"
            MouseArea {
                width: parent.width
                height: parent.height
                onClicked: {
                    width: parent.width
                    height: parent.height
                    onClicked: FramePage.guideGetByUrlClick()
                }
            }
        }

        Image {
            objectName: "actGuideGetByUrl"
            smooth: true
            anchors.fill: parent
            source: "images/hfwzn.png"
        }
    }
    Item {
        x: 492
        y: -221
        width: 155
        height: 59
        Image {
            anchors.fill: parent
            smooth: true
            source: "images/xctp.png"
            MouseArea {
                anchors.fill: parent
                onClicked: FramePage.mediaClick()
            }
        }

        Image {
            anchors.fill: parent
            objectName: "actMedia"
            smooth: true
            source: "images/xctph.png"
        }
    }
    
    Item {
        id: questGrid
        x: 311
        y: -221
        width: 155
        height: 59
        visible: true

        Image {
            anchors.fill: parent
            smooth: true
            source: "images/lcjwt.png"
            MouseArea {
                width: parent.width
                height: parent.height
                onClicked: FramePage.questionClick()
            }
        }

        Image {
            objectName: "actQuestion"
            anchors.fill: parent
            smooth: true
            source: "images/hcjwt.png"
        }
    }
    Item {
        id: announcementGrid
        x: 667
        y: -221
        width: 155
        height: 59
        visible: false

        Image {
            anchors.fill: parent
            smooth: true
            source: "images/ltzgg.png"
            MouseArea {
                width: parent.width
                height: parent.height
                onClicked: FramePage.announcementClick()
            }
        }

        Image {
            objectName: "actAnnouncement"
            anchors.fill: parent
            smooth: true
            source: "images/htzgg.png"
        }
    }

    Item {
        x: 667
        y: -221
        width: 155
        height: 59
        visible: false

        Image {
            anchors.fill: parent
            smooth: true
            source: "images/lzgy.png"
            MouseArea {
                width: parent.width
                height: parent.height
                onClicked: FramePage.honestClick()
            }
        }

        Image {
            objectName: "actHonest"
            anchors.fill: parent
            smooth: true
            source: "images/lzgyh.png"
        }
    }

    Item {
        x: 667
        y: -221
        width: 155
        height: 59
        visible: false

        Image {
            anchors.fill: parent
            smooth: true
            source: "images/lzgy.png"
            MouseArea {
                width: parent.width
                height: parent.height
                onClicked: FramePage.dutyClick()
            }
        }

        Image {
            objectName: "actDuty"
            anchors.fill: parent
            smooth: true
            source: "images/lzgyh.png"
        }
    }

    Text {
        objectName: "CenterName"
        x: 8
        y: 1019
        width: 13
        height: 21
        color: "#c8e6e6"
        font.bold: true
        font.family: "黑体"
        font.pixelSize: 21
    }
}
