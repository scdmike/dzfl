import QtQuick 2.3

Item {
    visible: true
    width: 1920
    height: 1280
    transformOrigin: Item.TopLeft
    property real sx: 1.5         //width/1024=2
    property real sy: 1.6      //height/768=2

    Intro {
        visible: true
        objectName: "IntroPage"
        transform: Scale { xScale: sx; yScale: sy}
    }

    Appraise {
        visible: false
        objectName: "AppraisePage"
        transform: Scale { xScale: sx; yScale: sy}
    }

    AppraiseConfirm {
        visible: false
        objectName: "AppraiseConfirm"
        transform: Scale { xScale: sx; yScale: sy}
    }

    AppraiseDetail {
        visible: false
        objectName: "AppraiseDetail"
        transform: Scale { xScale: sx; yScale: sy}
    }

    AppraiseFinish {
        objectName: "AppraiseFinish"
        visible: false
        transform: Scale { xScale: sx; yScale: sy}
    }

    PausePage {
        objectName: "PausePage"
        visible: false
        transform: Scale { xScale: sx; yScale: sy}
    }

    Frame {
        objectName: "FramePage"
        visible: false
        transform: Scale { xScale: sx; yScale: sy}
    }

    CaptureView {
        objectName: "CaptureView"
        visible: false
        property int scale: 0
        transform: Scale { xScale: sx; yScale: sy}
    }
}
