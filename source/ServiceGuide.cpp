#include "../inc/ServiceGuide.h"
#include "../inc/ServiceGuideDetail.h"
#include "../public/Cache.h"

//QString str = QString(CsGetConfig("办事指南每页数量"));
//int tmp = str.toInt();
//static const int pageRecordCount = str.isEmpty()?6:tmp;
static const int pageRecordCount = 6;

ServiceGuide::ServiceGuide()
{

    //qDebug()<<"办事指南每页数量:"<<tmp;
    detailPage = new ServiceGuideDetail();
    UILogic::AllInstance().append(detailPage);
}

ServiceGuideOther::ServiceGuideOther()
{
    detailPage = new ServiceGuideDetailOther();
    UILogic::AllInstance().append(detailPage);
}

bool ServiceGuide::Init()
{
    if(!UILogic::Init())
        return false;

//    for(int i=0;i<pageRecordCount;i++){

//        QString objectName = "item"+QString::number(i);

//        qDebug()<<">>>Uname"<<objectName;
//        uiGuideList.append(UIItem((const char*)objectName.toUtf8()));
//    }
    uiGuideList.append(UIItem("item0"));
    uiGuideList.append(UIItem("item1"));
    uiGuideList.append(UIItem("item2"));
    uiGuideList.append(UIItem("item3"));
    uiGuideList.append(UIItem("item4"));
    uiGuideList.append(UIItem("item5"));

    return true;
}

void ServiceGuide::Show(Record& vdata)
{
    //关闭办事指南内容页
    detailPage->Hide();

    Record cmd;
    cmd["cmd"]      = "GetDeptGuideList";
    cmd["deptName"] = (const char*)vdata["deptName"];
    cmd["deptID"]   = (const char*)vdata["deptID"];
    guideList = CacheInstance.ServiceDoCommand(cmd.ToString())["Record"];
    totalPage = (guideList.Size() + pageRecordCount - 1) / pageRecordCount;
    ShowPage(0);

    UIPage()->setVisible(true);
}

void ServiceGuideOther::Show(Record& vdata)
{
    //关闭办事指南内容页
    detailPage->Hide();

    Record cmd;
    cmd["cmd"]      = "GetDeptGuideList";
    cmd["deptName"] = (const char*)vdata["deptName"] + QString("_中介办理");
    cmd["deptID"]   = (const char*)vdata["deptID"];
    guideList = CacheInstance.ServiceDoCommand(cmd.ToString())["Record"];
    totalPage = (guideList.Size() + pageRecordCount - 1) / pageRecordCount;
    ShowPage(0);

    UIPage()->setVisible(true);
}

void ServiceGuide::SetGuideGridValue(int index, Record value)
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
        QQuickItem* find = curGrid->findChild<QQuickItem*>("tbName");
        QString guideName(value["Name"]);
        if(guideName.length() > 45)
            guideName = guideName.left(44) + "...";
        if(find) find->setProperty("text", guideName);

        find = curGrid->findChild<QQuickItem*>("tbSn");
        if(find) find->setProperty("text", QString(value["Sn"]));

        find = curGrid->findChild<QQuickItem*>("tbTime");
        if(find) find->setProperty("text", QString(value["Time"]).replace("<br>", "\n"));

        find = curGrid->findChild<QQuickItem*>("tbID");
        if(find) find->setProperty("text", QString(value["id"]).replace("<br>", "\n"));

        //根据url生成二维码//为了各程序稳定运行暂时注释
        //QByteArray  image;
        //image = QByteArray::fromBase64((const char*)value["imgData"]);
        //QString imgSource = "image://ImageStreamLoader/";
        //imgSource += QString::number((qulonglong)image.data());
        //imgSource += '#';
        //imgSource += QString::number((unsigned int)image.size());
        //imgSource += "#";
        //imgSource += QString(value["id"]).replace("<br>", "\n");
        //find = curGrid->findChild<QQuickItem*>("itemurl");
        //if(find) find->setProperty("source", imgSource);
        
        uiGuideList[index]->setProperty("visible", true);
    }
}

void ServiceGuide::ShowPage(int page)
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

void ServiceGuide::guideListClick(int index)
{
    if(index < 0 || index >= (int)guideList.Size() || guideList[index].GetType() != DataType::Object)
        return;

    UIPage()->setVisible(false);
    detailPage->Show(guideList[currentPage * pageRecordCount + index]["id"]);
}

void ServiceGuide::Hide()
{
    detailPage->Hide();
    UILogic::Hide();
}

void ServiceGuide::nextPageClick()
{
    ShowPage(currentPage + 1);
}

void ServiceGuide::prevPageClick()
{
    ShowPage(currentPage - 1);
}

