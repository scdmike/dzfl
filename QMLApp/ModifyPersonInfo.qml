import QtQuick 2.3

BorderImage {
    width: 1005
    height: 630
    source: "images/nyk_b.png"
    id: modifyPage

    Item {
        objectName: "updatePhoneMsg"
        x: 62
        y: 53
        width: 385
        height: 451
        Text {
            color: "#e64a1e"
            font.bold: true
            style: Text.Normal
            font.family: "黑体"
            font.pixelSize: 80
            width: parent.width
            height: 80
            text: "温馨提示\n"
            horizontalAlignment: Text.AlignHCenter
        }
        Text {
            y: 120
            width: parent.width
            color: "#e64a1e"
            font.bold: false
            text: "一、为保证窗口服务公正透\n" +
                  "明，整个服务过程有录音、\n" +
                  "录像进行记录\n" +
                  "二、请核对您的个人信息是\n" +
                  "否准确\n" +
                  "三、服务结束后请您对窗口\n" +
                  "服务进行评价，可以在此评\n" +
                  "价器上点击，也可以在取号\n" +
                  "机上操作，以当天最后一次\n" +
                  "评价为准"
            style: Text.Normal
            font.family: "黑体"
            font.pixelSize: 32
        }
    }

    Item {
        x: 520
        y: 42
        width: 466
        height: 566

        Text {
            x: 18
            y: 22
            text: "办事人姓名:"
            font.pixelSize: 32
            font.family: "黑体"
            font.bold: true
        }
        Text {
            objectName: "modUserName"
            x: 251
            y: 22
            font.pixelSize: 32
            font.family: "楷体"
        }

        Image {
            x: 18
            y: 62
            width: 431
            height: 498
            source: "images/sjjp_b.png"

            TextInput {
                objectName: "tbOutput"
                id: tbOutput
                x: 169
                y: 102
                width: 180
                height: 32
                cursorVisible: true
                selectionColor: "#e8671d"
                font.family: "黑体"
                font.pixelSize: 32
            }


            MouseArea {
                x: 184
                y: 351
                width: 57
                height: 59
                enabled: modifyPage.visible
                onClicked: {
                    ServiceInfo.stopTimer();
                    var i = tbOutput.selectionStart;
                    tbOutput.text = tbOutput.text.substring(0, i) + "0" + tbOutput.text.substring(i);
                    tbOutput.select(i + 1, i + 1);
                }
            }


            MouseArea {
                x: 113
                y: 146
                width: 57
                height: 59
                enabled: modifyPage.visible
                onClicked: {
                    ServiceInfo.stopTimer();
                    var i = tbOutput.selectionStart;
                    tbOutput.text = tbOutput.text.substring(0, i) + "1" + tbOutput.text.substring(i);
                    tbOutput.select(i + 1, i + 1);
                }
            }


            MouseArea {
                x: 183
                y: 147
                width: 57
                height: 59
                enabled: modifyPage.visible
                onClicked: {
                    ServiceInfo.stopTimer();
                    var i = tbOutput.selectionStart;
                    tbOutput.text = tbOutput.text.substring(0, i) + "2" + tbOutput.text.substring(i);
                    tbOutput.select(i + 1, i + 1);
                }
            }

            MouseArea {
                x: 255
                y: 147
                width: 57
                height: 59
                enabled: modifyPage.visible
                onClicked: {
                    ServiceInfo.stopTimer();
                    var i = tbOutput.selectionStart;
                    tbOutput.text = tbOutput.text.substring(0, i) + "3" + tbOutput.text.substring(i);
                    tbOutput.select(i + 1, i + 1);
                }
            }

            MouseArea {
                x: 112
                y: 213
                width: 57
                height: 59
                enabled: modifyPage.visible
                onClicked: {
                    ServiceInfo.stopTimer();
                    var i = tbOutput.selectionStart;
                    tbOutput.text = tbOutput.text.substring(0, i) + "4" + tbOutput.text.substring(i);
                    tbOutput.select(i + 1, i + 1);
                }
            }

            MouseArea {
                x: 184
                y: 213
                width: 57
                height: 59
                enabled: modifyPage.visible
                onClicked: {
                    ServiceInfo.stopTimer();
                    var i = tbOutput.selectionStart;
                    tbOutput.text = tbOutput.text.substring(0, i) + "5" + tbOutput.text.substring(i);
                    tbOutput.select(i + 1, i + 1);
                }
            }

            MouseArea {
                x: 254
                y: 213
                width: 57
                height: 59
                enabled: modifyPage.visible
                onClicked: {
                    ServiceInfo.stopTimer();
                    var i = tbOutput.selectionStart;
                    tbOutput.text = tbOutput.text.substring(0, i) + "6" + tbOutput.text.substring(i);
                    tbOutput.select(i + 1, i + 1);
                }
            }

            MouseArea {
                x: 113
                y: 283
                width: 57
                height: 59
                enabled: modifyPage.visible
                onClicked: {
                    ServiceInfo.stopTimer();
                    var i = tbOutput.selectionStart;
                    tbOutput.text = tbOutput.text.substring(0, i) + "7" + tbOutput.text.substring(i);
                    tbOutput.select(i + 1, i + 1);
                }
            }

            MouseArea {
                x: 184
                y: 283
                width: 57
                height: 59
                enabled: modifyPage.visible
                onClicked: {
                    ServiceInfo.stopTimer();
                    var i = tbOutput.selectionStart;
                    tbOutput.text = tbOutput.text.substring(0, i) + "8" + tbOutput.text.substring(i);
                    tbOutput.select(i + 1, i + 1);
                }
            }

            MouseArea {
                x: 255
                y: 283
                width: 57
                height: 59
                enabled: modifyPage.visible
                onClicked: {
                    ServiceInfo.stopTimer();
                    var i = tbOutput.selectionStart;
                    tbOutput.text = tbOutput.text.substring(0, i) + "9" + tbOutput.text.substring(i);
                    tbOutput.select(i + 1, i + 1);
                }
            }

            MouseArea {
                x: 113
                y: 351
                width: 57
                height: 59
                enabled: modifyPage.visible
                onClicked: {
                    ServiceInfo.stopTimer();
                    var a = tbOutput.text;
                    var i = tbOutput.selectionStart;
                    if(a.length > 1) {
                        a = a.substring(0, i - 1).concat(a.substring(i));
                        tbOutput.text = a;
                        tbOutput.select(i - 1, i - 1);
                    } else if(i == 1 && tbOutput.text.length == 1) {
                        tbOutput.text = "";
                    }
                }
            }

            MouseArea {
                x: 255
                y: 351
                width: 57
                height: 59
                enabled: modifyPage.visible
                onClicked: {
                    ServiceInfo.stopTimer();
                    TelWindow.savePhone(tbOutput.text);
                    modifyPage.visible = false;
                }
            }
        }
    }
}
