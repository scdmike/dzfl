#include "../inc/ServiceGuideXM.h"
#include "../inc/ServiceGuideDetailXM.h"
#include "../public/Cache.h"

static const int pageRecordCount = 6;

ServiceGuideXM::ServiceGuideXM()
{
    detailPage = new ServiceGuideDetailXM();
    UILogic::AllInstance().append(detailPage);
}

ServiceGuideOtherXM::ServiceGuideOtherXM()
{
    detailPage = new ServiceGuideDetailOtherXM();
    UILogic::AllInstance().append(detailPage);
}

bool ServiceGuideXM::Init()
{
    if(!UILogic::Init())
        return false;
    uiGuideList.append(UIItem("item0"));
    uiGuideList.append(UIItem("item1"));
    uiGuideList.append(UIItem("item2"));
    uiGuideList.append(UIItem("item3"));
    uiGuideList.append(UIItem("item4"));
    uiGuideList.append(UIItem("item5"));

    return true;
}

void ServiceGuideXM::Show(Record& vdata)
{
    Q_UNUSED(vdata);
    detailPage->Hide();

    Record cmd;
    cmd["cmd"] = "GetInfoListByTypeCode";
    cmd["typeCode"] = "tzgg";
    guideList = CacheInstance.ServiceDoCommand(cmd.ToString())["Record"];
    totalPage = (guideList.Size() + pageRecordCount - 1) / pageRecordCount;
    ShowPage(0);

    UIPage()->setVisible(true);
}

void ServiceGuideOtherXM::Show(Record& vdata)
{
    Q_UNUSED(vdata);
    //关闭政策法规内容页
    detailPage->Hide();

    Record cmd;
    cmd["cmd"]      = "GetInfoListByTypeCodeDeptName";
    cmd["typeCode"] = (const char*)vdata["typeCode"];
    cmd["deptName"] = (const char*)vdata["deptName"];
    guideList = CacheInstance.ServiceDoCommand(cmd.ToString())["Record"];
    totalPage = (guideList.Size() + pageRecordCount - 1) / pageRecordCount;
    ShowPage(0);

    UIPage()->setVisible(true);
}

void ServiceGuideXM::SetGuideGridValue(int index, Record value)
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
        QString guideName(value["Title"]);
        if(guideName.length() > 45)
            guideName = guideName.left(44) + "...";
        if(find) find->setProperty("text", guideName);

        find = curGrid->findChild<QQuickItem*>("tbSn");
        if(find) find->setProperty("text", QString(value["DeptName"]));

        find = curGrid->findChild<QQuickItem*>("tbTime");
        if(find) find->setProperty("text", QString(value["UpdateDate"]).replace("<br>", "\n"));

        uiGuideList[index]->setProperty("visible", true);
    }
}

void ServiceGuideXM::ShowPage(int page)
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

void ServiceGuideXM::guideListClick(int index)
{
    if(index < 0 || index >= (int)guideList.Size() || guideList[index].GetType() != DataType::Object)
        return;

    UIPage()->setVisible(false);
    detailPage->Show(guideList[currentPage * pageRecordCount + index]["ID"]);
}

void ServiceGuideXM::Hide()
{
    detailPage->Hide();
    UILogic::Hide();
}

void ServiceGuideXM::nextPageClick()
{
    ShowPage(currentPage + 1);
}

void ServiceGuideXM::prevPageClick()
{
    ShowPage(currentPage - 1);
}

