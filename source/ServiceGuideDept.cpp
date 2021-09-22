#include "../inc/ServiceGuideDept.h"
#include "../public/Cache.h"
#include "../inc/FramePage.h"
#include <QDateTime>
#include <QDomDocument>

static const int pageRecordCount = 16;

ServiceGuideDept::ServiceGuideDept()
{
    //detailPage = new ServiceGuideGetByUrlDetail();
    //UILogic::AllInstance().append(detailPage);
}


bool ServiceGuideDept::Init()
{
    if(!UILogic::Init())
        return false;
    uiGuideList.append(UIItem("item0"));
    uiGuideList.append(UIItem("item1"));
    uiGuideList.append(UIItem("item2"));
    uiGuideList.append(UIItem("item3"));
    uiGuideList.append(UIItem("item4"));
    uiGuideList.append(UIItem("item5"));
    uiGuideList.append(UIItem("item6"));
    uiGuideList.append(UIItem("item7"));
    uiGuideList.append(UIItem("item8"));
    uiGuideList.append(UIItem("item9"));
    uiGuideList.append(UIItem("item10"));
    uiGuideList.append(UIItem("item11"));
    uiGuideList.append(UIItem("item12"));
    uiGuideList.append(UIItem("item13"));
    uiGuideList.append(UIItem("item14"));
    uiGuideList.append(UIItem("item15"));

    return true;
}

void ServiceGuideDept::Show(Record& vdata)
{

    //QString baseUrl="http://localhost:8142/services/WsItemZS/GetAllDept";
    QString baseUrl=(const char*)vdata["baseUrl"];
    QNetworkRequest request;
    request.setUrl(QUrl(baseUrl));
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    // 发送请求
    QNetworkReply *pReplay = manager->get(request);
    // 开启一个局部的事件循环，等待响应结束，退出
    QEventLoop eventLoop;
    QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();
    // 获取响应信息
    QByteArray bytes = pReplay->readAll();
    //qDebug() <<"bytes："<< bytes;

    //处理结果xml开始
    QString xml = QString(bytes);
    //qDebug()<<"xml:"<<xml;
//    QString str1 = xml.mid(xml.indexOf("[")+1);
//    //qDebug()<<"str1:"<<str1;
//    QStringList str2 = str1.split("]", QString::SkipEmptyParts);
//    //qDebug()<<">>>>>depts:"<<str2[0];
//    depts=str2[0];

    //新方法
    Record result,record;
    result["Succ"] = 0;
    QDomDocument doc;
    doc.setContent(xml);

    QDomElement root = doc.documentElement();
    QDomElement ele = root.firstChildElement();
    QByteArray resEle = ele.text().toUtf8();
    if(ele.tagName() == "ns:return") {
        record.FromString(resEle.data(), resEle.size());
    }

    guideList=record;
    qDebug() << "办事指南信息返回Size" <<record.Size();
    //
    totalPage = (guideList.Size() + pageRecordCount - 1) / pageRecordCount;
    ShowPage(0);

    UIPage()->setVisible(true);
}
bool ServiceGuideDept::SplitUrl(const QString& urlForSp, QString& host, int& port, QString& url) {
    host = urlForSp.mid(urlForSp.indexOf("//") + 2);
    if(host.contains(":")) {
        int b = host.indexOf(":") + 1;
        int e = host.indexOf("/", b) + 1;
        if(e <= 0) return false;
        QString strPort = host.mid(b, e - b - 1);
        port = strPort.toInt();
        url = host.mid(e - 1);
        host = host.left(b - 1);
    } else {
        port = 80;
        int e = host.indexOf("/") + 1;
        if(e <= 0) return false;
        url = host.mid(e - 1);
        host = host.left(e - 1);
    }
    return true;
}
QByteArray ServiceGuideDept::HttpPost(const QString& host, int port, const QString& url,const QByteArray& postDat, const QString& contentType) {
    static QByteArray resultErr;
    QTcpSocket socket;
    socket.connectToHost(host, port);
    if(!socket.waitForConnected(10000)) return resultErr;

    QString req =   "POST %1 HTTP/1.0\r\n"
                    "Content-Type: %2\r\n"
                    "Host: %3:%4\r\n"
                    "Content-Length: %5\r\n"
                    "Accept: */*\r\n\r\n";
    QByteArray send = req.arg(url).arg(contentType).arg(host).arg(port).arg(postDat.size()).toUtf8() + postDat;

    //发送命令
    if(socket.write(send) <= 0) return resultErr;
    if(!socket.waitForBytesWritten(10000)) return resultErr;

    int index = 0;
    QByteArray json;
    //重试三次读回返头
    for(int i = 0; i < 3; i++) {
        if(socket.bytesAvailable() <= 0)
            socket.waitForReadyRead(10000);
        json += socket.readAll();
        index = json.indexOf("\n{");
        if(index > 0) break;
    }
    //只记录失败的请求
    if(index <= 0) {
        qDebug() << "HTTP请求失败，读不到内容放弃操作:" << json;
        return resultErr;
    }

    int size = GetHttpContentLength(json, index);
    //有可能取不到HTTP内容长度...
    if(size == 0) size = 0x8000000;
    int reTry = 0;
    while(json.length() < size + index - 1) {
        if(socket.bytesAvailable() <= 0)
            socket.waitForReadyRead(5000);
        QByteArray read = socket.readAll();
        if(read.length() == 0 && reTry++ > 10) break;
        json += read;
    }
    return json.mid(index + 1);
}

int ServiceGuideDept::GetHttpContentLength(const QByteArray& httpData, int httpHeadLen) {
    QByteArray head = httpData.left(httpHeadLen).toUpper();
    int lenOff = head.indexOf("CONTENT-LENGTH:");
    if(lenOff < 0) return 0;
    lenOff += strlen("CONTENT-LENGTH:");
    QByteArray lenByte = head.mid(lenOff, head.indexOf('\n', lenOff) - lenOff);
    if(lenByte[lenByte.length() - 1] == '\r') lenByte.remove(lenByte.length() - 1, 1);
    return lenByte.toInt();
}


void ServiceGuideDept::SetGuideGridValue(int index, Record value)
{
    if(index < 0 || index >= uiGuideList.size())
        return;

    if(value.GetType() != DataType::Object)
    {
        uiGuideList[index]->setProperty("visible", false);
    }
    else
    {
        QQuickItem* curGrid = uiGuideList[index];
        QQuickItem* find = curGrid->findChild<QQuickItem*>("deptName");
        QString deptName(value["deptName"]);
        if(find) find->setProperty("text", deptName);

        QString deptCode(value["deptCode"]);
        find = curGrid->findChild<QQuickItem*>("deptCode");
        if(find) find->setProperty("text", deptCode);

        uiGuideList[index]->setProperty("visible", true);
    }
}

void ServiceGuideDept::ShowPage(int page)
{
    for (int i = 0; i < pageRecordCount; i++)
        SetGuideGridValue(i, "");

    page = qMax(0, page);
    page = qMin(totalPage - 1, page);

    if(page >= 0)
    {
        int index = 0;
        for (int i = page * pageRecordCount; i < (page + 1) * pageRecordCount && i < (int)guideList.Size(); i++)
        {
            SetGuideGridValue(index++, guideList[i]);
        }
        currentPage = page;
    }

    UIItem("mousePrev")->setEnabled(page <= 0 ? false : true);
    UIItem("imgPrev")->setOpacity(page <= 0 ? 0.3 : 1);

    UIItem("mouseNext")->setEnabled(page >= totalPage - 1 ? false : true);
    UIItem("imgNext")->setOpacity(page >= totalPage - 1 ? 0.3 : 1);
}

//void ServiceGuideDept::guideListClick(int index)
//{
//    if(index < 0 || index >= (int)guideList.Size() || guideList[index].GetType() != DataType::Object)
//        return;

//    UIPage()->setVisible(false);
//    detailPage->Show(guideList[currentPage * pageRecordCount + index]["id"]);
//}

void ServiceGuideDept::Hide()
{
    //detailPage->Hide();
    UILogic::Hide();
}

void ServiceGuideDept::nextPageClick()
{
    ShowPage(currentPage + 1);
}

void ServiceGuideDept::prevPageClick()
{
    ShowPage(currentPage - 1);
}


