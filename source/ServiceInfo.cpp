#include <QDateTime>
#include <qsound.h>
#include <QGuiApplication>
#include "../inc/ServiceInfo.h"
#include "../public/Cache.h"
#include "../inc/FramePage.h"
#include "../inc/CommandBuffer.h"
#include "../inc/HttpServer.h"


//utf-8
void ServiceInfo::HideItem()
{
   UIItem("projGrid")->setVisible(false);
//   UIItem("tbPhone")->setVisible(false);
//   UIItem("image_gov_d")->setVisible(false);
//   UIItem("img_dy")->setVisible(false);
//   UIItem("image_gov_t")->setVisible(false);
//   UIItem("img_ty")->setVisible(false);
//   UIItem("image_gov_p")->setVisible(false);
//   UIItem("img_p")->setVisible(false);
//   UIItem("image_gov_q")->setVisible(false);
//   UIItem("image_qz")->setVisible(false);
//   UIItem("grid_info")->setVisible(false);
//   UIItem("serviceStar")->setVisible(false);
//   UIItem("phone2")->setVisible(false);
//   UIItem("FRGrid")->setVisible(false);

//   UIItem("tbPhoneB")->setVisible(false);
//   UIItem("image_gov_dB")->setVisible(false);
//   UIItem("img_dyB")->setVisible(false);
//   UIItem("image_gov_tB")->setVisible(false);
//   UIItem("img_tyB")->setVisible(false);
//   UIItem("image_gov_pB")->setVisible(false);
//   UIItem("img_pB")->setVisible(false);
//   UIItem("image_gov_qB")->setVisible(false);
//   UIItem("img_qzB")->setVisible(false);
//   UIItem("grid_infoB")->setVisible(false);
//   UIItem("serviceStarB")->setVisible(false);
//   UIItem("phone2B")->setVisible(false);
//   UIItem("btnProjectPageUp")->setProperty("enabled", false);
//   UIItem("btnProjectPageDown")->setProperty("enabled", false);
//   UIItem("modifyPersonInfo")->setVisible(false);
//   UIItem("img_qn")->setVisible(false);
   servicedetailPage->Hide();
}

void ServiceInfo::LoadScrollText(ScrollMessage* box, const char* boxName, const char* field)
{
    QString project(FramePage::GetUserInfo()[field]);
    QStringList strList = project.split("<R><N>", QString::SkipEmptyParts);
    QList<QQuickItem*> subList = UIItem(boxName)->childItems();

    if(subList.size() == 0 || !UIItem(boxName)->isVisible()) return;

    for(int i = 0; i < 3; i++)
    {
        char subName[0x30];
        sprintf(subName, "%s%d", boxName, i);
        box[i].Start(this, subName);
        box[i].setText(i < strList.count() ? strList[i] : "");
        if(i < subList.count())
        {
            ((QQuickItem*)subList[i])->setProperty("fontSize", 22);
            ((QQuickItem*)subList[i])->setProperty("fontColor", "#000000");
            //((QQuickItem*)subList[i])->setProperty("fontFamily", "黑体");
        }
    }
}

void ServiceInfo::loadSecondUser()
{
    QByteArray idUser = (const char*)FramePage::GetUserInfo()["userID"];
    Record cmd;
    cmd["cmd"] = "SecondUserInfo";
    cmd["idUser"] = idUser.data();
    Record result = CacheInstance.ServiceDoCommand(cmd.ToString());
    idUser = (const char*)result["idUser"];

    if(CsGetConfig("监督电话B")[0] != 0)
    {
        UIItem("tbPhoneB")->setVisible(true);
        UIItem("phone2B")->setVisible(true);
        UIItem("phone2B")->setProperty("text", QString(CsGetConfig("监督电话B")));
    }

    result = CacheInstance.GetServiceUserInfo(idUser);
    UIItem("userNameB")->setProperty("text", QString(result["UserName"]));
    UIItem("userIDB")->setProperty("text", QString(idUser));
    UIItem("phone1B")->setProperty("text", QString(CsGetConfig(result["deptName"])));
    UIItem("deptNameB")->setProperty("text", QString(result["deptName"]));

    UIItem("userImageB")->setProperty("source", FramePage::GetUserImageUrl(idUser));

    UpdateGovFlag((const char*)result["GovRole"], 1);
}
void ServiceInfo::resumeScroll2(QString UserID,QString ServiceID)
{
    QString dturl = "http://localhost:9900/Appraise?UserID="+UserID+"&ServiceID="+ServiceID;
    qDebug() << "办事指南地址" <<dturl;

    //SplitUrl(dturl, rootHost, rootPort, rootUrl);
    //bool ServiceGuideGetByUrl::SplitUrl(const QString& urlForSp, QString& host, int& port, QString& url) {
        QString host = dturl.mid(dturl.indexOf("//") + 2);
        int port;
        Record cmdBiz;
        cmdBiz["apiv"]       = "1";
        cmdBiz["app_key"]         = "bszn";
        cmdBiz["channel"]         = "android";
         QByteArray sendBiz      = cmdBiz.ToString();
        QString url;
        if(host.contains(":")) {
            int b = host.indexOf(":") + 1;
            int e = host.indexOf("/", b) + 1;
            if(e <= 0) {}
            QString strPort = host.mid(b, e - b - 1);
            port = strPort.toInt();
            url = host.mid(e - 1);
            host = host.left(b - 1);
        } else {
            port = 80;
            int e = host.indexOf("/") + 1;
           if(e <= 0){}
            url = host.mid(e - 1);
            host = host.left(e - 1);
        }
       // return true;
    //}
        // HttpPost(rootHost, rootPort, rootUrl, sendBiz,"application/json");
       // QByteArray ServiceGuideGetByUrl::HttpPost(const QString& host, int port, const QString& url,const QByteArray& postDat, const QString& contentType) {
            static QByteArray resultErr;
            QTcpSocket socket;
            socket.connectToHost(host, port);
            if(!socket.waitForConnected(10000)) {}

            QString req =   "POST %1 HTTP/1.0\r\n"
                            "Content-Type: %2\r\n"
                            "Host: %3:%4\r\n"
                            "Content-Length: %5\r\n"
                            "Accept: */*\r\n\r\n";
            QByteArray send = req.arg(url).arg("application/json").arg(host).arg(port).arg(sendBiz.size()).toUtf8() + sendBiz;

            //发送命令
            socket.write(send);//if(socket.write(send) <= 0) {}
            socket.waitForBytesWritten(100);if(!socket.waitForBytesWritten(10000)){}

            int index = 0;
            QByteArray json;
            socket.bytesAvailable();
//            //重试三次读回返头
//            for(int i = 0; i < 3; i++) {
//                if(socket.bytesAvailable() <= 0)
//                    socket.waitForReadyRead(10000);
//                json += socket.readAll();
//                index = json.indexOf("\n{");
//                if(index > 0) break;
//            }
//            //只记录失败的请求
//            if(index <= 0) {
//                qDebug() << "HTTP请求失败，读不到内容放弃操作:" << json;
//                {}
//            }

            //int size = GetHttpContentLength(json, index);
            //
            int size;
            //int ServiceGuideGetByUrl::GetHttpContentLength(const QByteArray& httpData, int httpHeadLen) {
                QByteArray head = json.left(index).toUpper();
                int lenOff = head.indexOf("CONTENT-LENGTH:");
                if(lenOff < 0){ size = 0;}
                else{  lenOff += strlen("CONTENT-LENGTH:");
                    QByteArray lenByte = head.mid(lenOff, head.indexOf('\n', lenOff) - lenOff);
                    if(lenByte[lenByte.length() - 1] == '\r') lenByte.remove(lenByte.length() - 1, 1);
                    size = lenByte.toInt();
                }


            //}
            //
            //有可能取不到HTTP内容长度...
//            if(size == 0) size = 0x8000000;
//            int reTry = 0;
//            while(json.length() < size + index - 1) {
//                if(socket.bytesAvailable() <= 0)
//                    socket.waitForReadyRead(10);
//                QByteArray read = socket.readAll();
//                if(read.length() == 0 && reTry++ > 10) break;
//                json += read;
//            }
            //return json.mid(index + 1);
       // }

}

void ServiceInfo::resumeScroll()
{
    LoadScrollText(scWinProject, "winProjectPY", "WinProject");
    LoadScrollText(scUserProject, "userProjectPY", "Project");

    if(UIItem("projectName")->isVisible())
        scProjectName.Start(this, "projectName");

    //项目的格子不显示，不需要滚动
    if(UIItem("projGrid")->isVisible()) {
        QList<QQuickItem *> items = UIItem("project")->childItems();
        for(int i = 0; i < items.count() && i < scProjectNameList.size(); i++)
        {
            char tmp[0x20];
            sprintf(tmp, "ProjectNameGridItem%d", i);
            scProjectNameList[i]->Start(this, tmp);
        }
    }
}

ServiceInfo::ServiceInfo() {
}

void ServiceInfo::CheckModifyPage() {
    int timeOut = UIItem("modifyPersonInfo")->property("showTime").toInt();
    if(timeOut > 0) {
        Record cmd;
        cmd["cmd"] = "GetServicePID";
        cmd["ServiceID"] = serviceID;
        Record serviceInfo = CacheInstance.ServiceDoCommand(cmd.ToString());
        UIItem("modUserName")->setProperty("text", QString(serviceInfo["Name"]));
        UIItem("tbOutput")->setProperty("text", QString(serviceInfo["Phone"]));

        UIItem("modifyPersonInfo")->setVisible(true);
        timer.start(timeOut * 1000);
    } else {
        UIItem("modifyPersonInfo")->setVisible(false);
    }
}

void ServiceInfo::stopTimer() {
    timer.stop();
}

void ServiceInfo::OnTimer() {
    UIItem("modifyPersonInfo")->setVisible(false);
}

void ServiceInfo::Show(Record& vdata)
{    
    HideItem();

    UIPage()->setVisible(true);
}

void ServiceInfo::UpdateServiceMessage()
{
    //服务寄语
    Record cmd;
    cmd["cmd"] = "GetServiceMessage";
    cmd["deptID"] = FramePage::GetUserInfo()["deptID"];
    cmd["userID"] = FramePage::GetUserInfo()["userID"];
    Record value = CacheInstance.ServiceDoCommand(cmd.ToString());
    QString message(value["Message"]);
    message.replace("<R><N>", "\n");
    message.replace("\r\n", "\n");
    UIItem("message")->setProperty("text", message);
}

QString ServiceInfo::GetUserProjectGz(const QString& userid)
{
    Record cmd;
    cmd["cmd"]      = "GetUserProjec";
    cmd["UserID"]   = userid.toUtf8().data();
    if(CsGetConfig("业务按部门筛选")[0] == '1')
        cmd["deptName"] = FramePage::GetUserInfo()["deptName"];
    Record result = CacheInstance.ServiceDoCommand(cmd.ToString());
    return QString(result["Project"]);
}

void ServiceInfo::UpdateUserProject(QString project)
{
    if(project.isEmpty()) project = "综合业务";

    QQuickItem* uiProj = UIItem("project");
    if(uiProj->property("gridType").toString() == "ListView") {
        uiProj->setProperty("model", QVariant::fromValue(project.split("<R><N>", QString::SkipEmptyParts)));
        UIItem("projGrid")->setVisible(true);
    } else {
        QList<QQuickItem *> items = uiProj->childItems();
        //project可能是一个大的TextBlock,也可能是一个Grid里面包含几个滚动框
        if(items.count() == 0)          //如果是TextBlock
        {
            project.replace("<R><N>", "\n");
            UIItem("project")->setProperty("text", project);
            projectNameListPageCount = 1;
        }
        else                            //如果是一个Grid里面包含几个滚动框
        {
            GetProjectList(project);
            projectNameListPageCount = (projectNameList.count() + items.count() - 1) / items.count();
            if(scProjectNameList.empty()) {
                for(int i = 0; i < items.count(); i++)
                    scProjectNameList.append(new ScrollMessage(this));
            }
            SetScrollProjectPage(0);
        }
    }
}

void ServiceInfo::projectPageUp()
{
    SetScrollProjectPage(projectNameListCurPage - 1);
}

void ServiceInfo::projectPageDown()
{
    SetScrollProjectPage(projectNameListCurPage + 1);
}

void ServiceInfo::projectPageAlwaysDown()
{
    if(projectNameListCurPage < projectNameListPageCount - 1) {
        SetScrollProjectPage(projectNameListCurPage + 1);
    } else {
        SetScrollProjectPage(0);
    }
}

void ServiceInfo::SetScrollProjectPage(int page)
{
    QList<QQuickItem *> items = UIItem("project")->childItems();
    int index = items.count() * page;
    if(index >= projectNameList.count())
        return;

    for(int i = 0; i < items.count(); i++)
    {
        char tmp[0x20];
        sprintf(tmp, "ProjectNameGridItem%d", i);
        scProjectNameList[i]->Start(this, tmp);
        if(index + i < projectNameList.size())
            scProjectNameList[i]->setText(projectNameList[index + i]);
        else
            scProjectNameList[i]->setText("");
    }
    UIItem("projGrid")->setProperty("visible", true);

    projectNameListCurPage = page;
    UIItem("btnProjectPageUp")->setProperty("enabled", page > 0);
    UIItem("btnProjectPageDown")->setProperty("enabled",
            projectNameListCurPage < projectNameListPageCount - 1);
}

void ServiceInfo::UpdateGovFlag(const QString& gov, int user)
{

    UIItem("Text_gov_JD")->setProperty("text", (const char*)FramePage::GetUserInfo()["Quarter"]);

    if(gov == "自定义") {
        QString Photo = (const char*)FramePage::GetUserInfo()["Photo"];
        qDebug() << "自定义政务面貌:" << Photo;
        UIItem("image_gov_d")->setProperty("source", Photo);
        UIItem("image_gov_d")->setVisible(true);
    } else {
        const char* itemName[2][8] = {
            {"image_gov_d", "img_dy", "image_gov_t", "img_ty", "image_gov_p", "img_p", "image_gov_q", "image_qz"},
            {"image_gov_dB", "img_dyB", "image_gov_tB", "img_tyB", "image_gov_pB", "img_pB", "image_gov_qB", "image_qzB"}
        };

        if(gov.indexOf("青年") >= 0) {
            UIItem("img_qn")->setVisible(true); return;
        }

        if(gov.indexOf("工作者") >= 0 || gov.indexOf("标兵") >= 0) {
            UIItem("Text_gov_YG")->setProperty("text", gov); return;
        }

        if (gov.indexOf("党员") >= 0) {
            UIItem(itemName[user][0])->setVisible(true);
            UIItem(itemName[user][1])->setVisible(true);
        } else if (gov.indexOf("团员") >= 0) {
            UIItem(itemName[user][2])->setVisible(true);
            UIItem(itemName[user][3])->setVisible(true);
        } else if (gov.indexOf("群众") >= 0) {
            UIItem(itemName[user][6])->setVisible(true);
            UIItem(itemName[user][7])->setVisible(true);
        } else if(gov.length() > 0){
            QString path = "file:///" + QGuiApplication::applicationDirPath() + "/" + gov + ".png";
            qDebug() << "政务面貌图片" << path;
            UIItem(itemName[user][0])->setProperty("source", path);
            UIItem(itemName[user][0])->setVisible(true);

            path = "file:///" + QGuiApplication::applicationDirPath() + "/" + gov + "标题.png";
            qDebug() << "政务面貌标题图片" << path;
            UIItem(itemName[user][1])->setProperty("source", path);
            UIItem(itemName[user][1])->setVisible(true);
        } else {
            if(CsGetConfig("默认政治面貌图片")[0] != '\0')
                UIItem(itemName[user][4])->setProperty("source", CsGetConfig("默认政治面貌图片"));
            UIItem(itemName[user][4])->setVisible(true);
            if(CsGetConfig("默认政治面貌标题")[0] != '\0')
                UIItem(itemName[user][5])->setProperty("source", CsGetConfig("默认政治面貌标题"));
            UIItem(itemName[user][5])->setVisible(true);
            UIItem("Text_gov_YG")->setProperty("text", "");
        }

        if(UIItem("Text_gov")) UIItem("Text_gov")->setProperty("text", gov);
    }
}

void ServiceInfo::UpdateWinFlag(const QString &winHonor) {
    QStringList honorList = winHonor.split(",");
    if(honorList.size() < 1) return;

    const char* itemName[3][11] = {
        {"党员示范岗", "工人先锋号", "红旗窗口", "巾帼文明岗", "青年文明号", "月度服务标兵" ,"文明窗口", "优秀窗口", "服务标兵", "服务之星", "党员先锋岗"},
        {"image_win_dysfg", "image_win_grxfh", "image_win_hqck", "image_win_jgwmg", "image_win_qnwmh", "image_win_ydfwbb", "image_org_wmck", "image_org_yxck", "image_user_fwbb", "image_user_fwzx", "image_user_dyxfg" },
        {"image_win_dysfg_b", "image_win_grxfh_b", "image_win_hqck_b", "image_win_jgwmg_b", "image_win_qnwmh_b", "image_win_ydfwbb_b", "image_org_wmck_b", "image_org_yxck_b", "image_user_fwbb_b","image_user_fwzx_b", "image_user_dyxfg_b" }
    };

    for(int i = 0; i < 11; i++) {
         if(UIItem(itemName[1][i]) && UIItem(itemName[2][i])) {
             if(honorList.contains(itemName[0][i])) {
                 UIItem(itemName[1][i])->setVisible(true);
                 UIItem(itemName[2][i])->setVisible(false);
             } else {
                 UIItem(itemName[1][i])->setVisible(false);
                 UIItem(itemName[2][i])->setVisible(true);
             }
         }
    }
}

void ServiceInfo::UpdateServiceStar(const QString& userID, int user)
{
    Record cmd;
    cmd["cmd"] = "ServiceStar";
    cmd["UserID"] = userID.toUtf8().data();
    Record result = CacheInstance.ServiceDoCommand(cmd.ToString());

    //年度服务之星
    QString star = (const char*)result["Star"];

    Record Month = result["Record"];
    const char* itemName[] = {"serviceStar", "serviceStarB"};
    QQuickItem* starGrid = UIItem(itemName[user]);
    if(Month.Size() > 0) {
        starGrid->setVisible(true);
        char buf[32];
        for(size_t i = 0; i < Month.Size(); i++) {
            sprintf(buf, "month%d", i+1);
            SubItem(starGrid, buf)->setVisible(true);

            sprintf(buf, "tbMonth%d", i+1);
            SubItem(starGrid, buf)->setProperty("text", QString(Month[i]) + "月");
        }
    } else {
        starGrid->setVisible(false);
    }

    //番禺季度服务之星
    qDebug()<<">>>star"<<star;
    qDebug()<<">>>star2"<<(!star.isEmpty() && star[0] == '1');
    UIItem("seasonStarPY")->setVisible(!star.isEmpty() && star[0] == '1');
    cmd["cmd"] = "ServiceStarYear";
    result = CacheInstance.ServiceDoCommand(cmd.ToString());
    if(result.GetType() == DataType::Object)
        star = (const char*)result["Star"];
    else
        star = "0";
    UIItem("yearStarPY")->setVisible(!star.isEmpty() && star[0] == '1');
}

void ServiceInfo::GetProjectList(QString project) {
    if(CsGetConfig("显示办事指南事项")[0] == '1') {
        QStringList list = project.split("<R><N>", QString::SkipEmptyParts);
        if(list.size() == 0) return;

        projectNameList.clear();
        int i = 1;
        Q_FOREACH(const QString& id, list) {
            Record cmd;
            cmd["cmd"]     = "GuideContent";
            cmd["appid"]   = id.toUtf8().data();
            Record content = CacheInstance.ServiceDoCommand(cmd.ToString());
            QString applyname =  (const char*)content["applyname"];
            if(applyname != "") {
               applyname = QString("%1.%2").arg(i).arg(applyname);
               i++;
               projectNameList.append(applyname);
               idList.append(id);
            }
        }
    } else if(CsGetConfig("按部门显示办事指南事项")[0] == '1') {
        Record cmd;
        cmd["cmd"] = "GetDeptGuideList";
        cmd["deptName"] = (const char*)FramePage::GetUserInfo()["deptName"];
        Record guideList = CacheInstance.ServiceDoCommand(cmd.ToString())["Record"];
        if(guideList.Size() == 0) return;

        projectNameList.clear();
        for(size_t i = 0; i < guideList.Size(); i++) {
            projectNameList.append(QString(guideList[i]["Name"]));
            idList.append(QString(guideList[i]["id"]));
        }
    } else {
        projectNameList = project.split("<R><N>", QString::SkipEmptyParts);
    }
}


void ServiceInfo::approvalClick(int index) {
    QList<QQuickItem*> items = UIItem("project")->childItems();
    index += projectNameListCurPage * items.size();

    if(index < 0 || index >= (int)idList.size()) return;

    const QString& id = idList[index];
    Record data;
    data["id"] = id.toUtf8().data();
    UIPage()->setVisible(false);
    servicedetailPage->Show(data["id"]);
}
void ServiceInfo::showAppraise(){
        QString userID = (const char*)FramePage::GetUserInfo()["userID"];
        std::string str = userID.toStdString();
        const char* id = str.c_str();
        char Uid[1024];
        strcpy(Uid, id);
        QString strDate = QDate::currentDate().toString("yyyyMMdd");
        std::string str2 = (strDate+"_"+serviceID).toStdString();
        const char* qid = str2.c_str();
        char Qid[1024];
        strcpy(Qid, qid);
        qDebug() <<"showAppraise用户编号" <<Uid;
        qDebug() <<"showAppraise排队号" <<Qid;
        char vdata[100];
        char* value =  Uid;
        strcpy(vdata, value);
        value =  Qid;
        strcpy(vdata + 16, value);
        //CppCommand(CommandID::APPRAISE, vdata);
}

