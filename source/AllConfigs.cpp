#include "../inc/AllConfigs.h"
#include "../inc/FramePage.h"
#include <QProcess>
#include "../inc/CommandBuffer.h"
#include <QHostInfo>
void AllConfigs::Show(Record& data)
{
    const char* vdata = (const char*)(int64_t)data;
    getConfigs();
    UIPage()->setVisible(true);
}
QString AllConfigs::appReStart()
{
    if(!SettingKeyValue["窗口工号"] .isEmpty()) {
        char vdata[100] = {0};
        strcpy(vdata, SettingKeyValue["窗口工号"].toUtf8().data());
        CmdBufInstance->ShowPage("FramePage", vdata);
    } else {
        CmdBufInstance->ShowPage("IntroPage", NULL);
    }
    return "a";

}
bool AllConfigs::Init()
{
    if(!UILogic::Init())
        return false;

    return true;
}
//上传大厅管理系统设备状态
void AllConfigs::dtglState()
{
   qDebug()<<">>>>>>>上传大厅数据";

   QString startPage = CsGetConfig("大厅管理地址");
   QStringList setting =startPage.split("|");

   if(setting.size() < 3) return ;

   QString loginName= setting[0];
   QString loginPwd = setting[1];
   QString loginUrl = setting[2];//"http://10.110.1.110:8142/web/serviceEntry"

   Record cmdLogin;
   cmdLogin["Service"] = "QueueCity.Login";
   cmdLogin["account"] = loginName;
   cmdLogin["password"]= loginPwd;

   Record loginRes=sendGetUrl( loginUrl,cmdLogin);
   if(!loginRes.Exists("token")) {
       qDebug() << "对比数据同步登录失败";
       return ;
   }
   token = (const char*)loginRes["token"];



   Record cmdBiz;

   cmdBiz["Service"]  = "OtherService.UpdateDeviceInfo";
   /*{"token":"46460A9D69B84496A527A270BF3745FE",
    "Service":"OtherService.UpdateDeviceInfo",
    "IPAddr":"191.191.191.191",
    "State":"1",
    "StateDesc":"正常",
    "Sort_order":1,
    "HostType":"CXJ",
    "FWDT_CODE":"GZ_ZWZX",
    "Location":"一楼",
    "Floor":"1",
    "SSID":"序列号"
    }
    */


   cmdBiz["token"]    = token;



   QString cip = "127.0.0.1";
   QHostInfo info = QHostInfo::fromName(QHostInfo::localHostName());

   qDebug()<<"找出一个IPv4地址即返回"<<QHostInfo::localHostName();

   // 找出一个IPv4地址即返回
   foreach(QHostAddress address,info.addresses())
   {
       qDebug()<<"开始找ip地址";
       if(address.protocol() == QAbstractSocket::IPv4Protocol)
       {
           qDebug()<<"获得呼叫器本地ip"<<address.toString();
           cip = address.toString();
       }
   }
   //10.48.18.72
   cmdBiz["IPAddr"]    = cip;
   cmdBiz["State"]    = "1";
   cmdBiz["StateDesc"]    ="正常";
   cmdBiz["Sort_order"]    =1;
   cmdBiz["HostType"]    ="PJFWQ";

   QString FWDT_CODE = CsGetConfig("大厅编码");
   QString Location = CsGetConfig("位置");
   QString Floor = CsGetConfig("楼层");
   QString SSID = CsGetConfig("序列号");

   cmdBiz["FWDT_CODE"]    = FWDT_CODE;
   cmdBiz["Location"]    = Location;
   cmdBiz["Floor"]    = Floor;
   cmdBiz["SSID"]    = SSID;

   qDebug() << "评价器上传状态访问参数 "<<cmdBiz.ToString();
   Record result  = sendGetUrl(loginUrl,cmdBiz);;
   qDebug() << "评价器上传状态返回结果 "<<result.ToString();
}

//获取所有配置项
QString AllConfigs::getAllConfigs(){
    QFile file2("config.txt");
    QString value="";
    if(file2.open(QIODevice::ReadOnly)) {
        QByteArray data = file2.readAll();
        file2.close();
        int sindex = data.indexOf('{');
        if(sindex > 0) {
            data = data.mid(sindex);
        } else if(sindex < 0) {
            data = "{}";
        }
        Record clientConfig;
        clientConfig.FromString(data, data.length());
        value = clientConfig.ToString();

        QString setts = value;
//        setts = setts.replace(QRegExp("{"), "");
//        setts = setts.replace(QRegExp("}"), "");
        setts = setts.remove(0,1);
        setts = setts.left(setts.length() - 1);

        //qDebug()<<">>>>>>>setts"<<setts;
        QStringList settsAll = setts.split(',', QString::SkipEmptyParts);
       // qDebug()<<">>>>>>>settsAllSize"<<settsAll.size();
        for(int i=0;i<settsAll.size();i++){
            QStringList sett = settsAll[0].split(':', QString::SkipEmptyParts);
            QString setKey= sett[0].replace(QRegExp("\""), "");
            QString setValue = sett[1].replace(QRegExp("\""), "");
            SettingKeyValue[setKey] = setValue;

        }
        //qDebug()<<">>>>>>>SettingKeyValue"<<SettingKeyValue.size();

    }
    return value;
}
//获取所有配置项
void AllConfigs::getConfigs(){
    QFile file2("config.txt");
    if(file2.open( QIODevice::ReadOnly)) {
        QByteArray data = file2.readAll();
        file2.close();
        int sindex = data.indexOf('{');
        if(sindex > 0) {
            data = data.mid(sindex);
        } else if(sindex < 0) {
            data = "{}";
        }
        Record clientConfig;
        clientConfig.FromString(data, data.length());

        for(int i =0; i<clientConfig.Size();i++){
            QByteArray setKey= clientConfig.keys()[i];
            QString setValue =  QString(clientConfig[setKey]);
             //qDebug()<<"setKey"<<setKey;
             //qDebug()<<"setValue"<<setValue;
            SettingKeyValue[setKey] = setValue;
            //qDebug()<<">>>>>>>SettingKeyValue"<<i<<SettingKeyValue.size();

        }
    }
}
QString AllConfigs::getAllSetting(QString array){
    getConfigs();
    QStringList sp = array.split(',', QString::SkipEmptyParts);//专题组

     Record result;
     QMap<QString,QString>::iterator it; //遍历map
     int i=0;
     int k =0;
     for(int j=0;j<sp.size();j++){
        //对已成专题的配置项优先排序
         for ( it = SettingKeyValue.begin(); it != SettingKeyValue.end(); ++it ) {
             //对已成专题的配置项优先排序
             if(sp[j].contains(it.key())){
                     if(sp[j]==it.key()){
                         result[k]["key"] = it.key();
                         result[k]["value"] = it.value();
                         result[k]["num"] = (k+1);
                         k++;
                         i++;
                     }
             }
         }

     }



     //剩下配置项载入
     for ( it = SettingKeyValue.begin(); it != SettingKeyValue.end(); ++it ) {

         if(!array.contains(it.key())){

                     result[i]["key"] = it.key();
                     result[i]["value"] = it.value();
                     result[i]["num"] = (i+1);
                     i++;

         }
     }

     //qDebug()<<">>>>>>>result"<<result.ToString();
     return result.ToString();
}

void AllConfigs::dmSaveSett(QString updatekey,QString updateValue) {

    //qDebug()<<"修改key"<<updatekey<<"的值为"<<updateValue;

    QString sett = updatekey;
    QString value = updateValue;

    QFile file2("config.txt");
    QByteArray data;
    Record clientConfig;
    if(file2.open( QIODevice::ReadOnly)) {
        data = file2.readAll();
        file2.close();
        int sindex = data.indexOf('{');
        if(sindex > 0) {
            data = data.mid(sindex);
        } else if(sindex < 0) {
            data = "{}";
        }

        clientConfig.FromString(data, data.length());

    qDebug()<<"修改参数名称"<<sett+":"+value;

    clientConfig[sett.toUtf8()] = value;
    QString e = clientConfig.ToString();
    file2.open(QIODevice::WriteOnly | QIODevice::Text);
    file2.write(e.toUtf8());
    file2.close();
    UIItem("settext")->setProperty("text", "配置项【"+updatekey+"】保存成功！");
    }
}
QString AllConfigs::dmGetSett(QString updatekey) {

  return SettingKeyValue[updatekey];

}
//展示分组数据
QString AllConfigs::getTeamSetting(QString array){

    QStringList sp = array.split(',', QString::SkipEmptyParts);//专题组

     Record result;
     QMap<QString,QString>::iterator it; //遍历map
     int i=0;
     int k =0;
     if(!array.isEmpty()){
         for(int j=0;j<sp.size();j++){
            //对已成专题的配置项优先排序
             for ( it = SettingKeyValue.begin(); it != SettingKeyValue.end(); ++it ) {
                 //对已成专题的配置项优先排序
                 if(sp[j].contains(it.key())){
                         if(sp[j]==it.key()){
                             result[k]["key"] = it.key();
                             result[k]["value"] = it.value();
                             result[k]["num"] = (k+1);
                             k++;
                             i++;
                         }
                 }
             }

         }
     }
     else{
         //剩下配置项载入
         for ( it = SettingKeyValue.begin(); it != SettingKeyValue.end(); ++it ) {

             if(!array.contains(it.key())){

                         result[i]["key"] = it.key();
                         result[i]["value"] = it.value();
                         result[i]["num"] = (i+1);
                         i++;

             }
         }

     }
     //qDebug()<<">>>>>>>result"<<result.ToString();
     return result.ToString();
}
QString AllConfigs::checkingValue(){
    QString errorKey="";

    //排队地址验证
    if(!QtPing(SettingKeyValue["服务器IP"])){
        if(errorKey!="")errorKey=errorKey+",";
        errorKey = errorKey+"服务器IP,服务器Port";
    }
    //电视机ip地址验证
    return errorKey;
}
bool AllConfigs::QtPing(const QString ip)
{
    QString res;
    // #Linux指令 "ping -s 1 -c 1 IP"
    //QString cmdstr = QString("ping -s 1 -c 1 %1")
    //      .arg(ip);

    // #Windows指令 "ping IP -n 1 -w 超时(ms)"
    QString cmdstr = QString("ping %1 -n 1 -w %2")
            .arg(ip).arg(1000);

    QProcess cmd;
    cmd.start(cmdstr);
    cmd.waitForReadyRead(1000);
    cmd.waitForFinished(1000);

    QString response = cmd.readAll();
    if (response.indexOf("TTL") == -1)
    {
        return false;
    }
    else
    {
        return true;
    }
}
//直接从大厅管理系统同步配置项
QString AllConfigs::updateConfigs() {
        //登录获取token
        QString startPage = CsGetConfig("大厅管理地址");
        QStringList setting =startPage.split("|");

        if(setting.size() < 3) return "";

        QString loginName= setting[0];
        QString loginPwd = setting[1];
        QString loginUrl = setting[2];//"http://10.110.1.110:8142/web/serviceEntry"

        Record cmdLogin;
        cmdLogin["Service"] = "QueueCity.Login";
        cmdLogin["account"] = loginName;
        cmdLogin["password"]= loginPwd;

        Record loginRes=sendGetUrl( loginUrl,cmdLogin);
        if(!loginRes.Exists("token")) {
            qDebug() << "对比数据同步登录失败";
            return "";
        }
        token = (const char*)loginRes["token"];



        Record cmdBiz;

        cmdBiz["Service"]  = "ZdSetting.GetZdSetting";


        cmdBiz["Device_type"]    = "PJFWQ";
        cmdBiz["token"]    = token;



        QString cip = "127.0.0.1";
        QHostInfo info = QHostInfo::fromName(QHostInfo::localHostName());

        qDebug()<<"找出一个IPv4地址即返回"<<QHostInfo::localHostName();

        // 找出一个IPv4地址即返回
        foreach(QHostAddress address,info.addresses())
        {
            qDebug()<<"开始找ip地址";
            if(address.protocol() == QAbstractSocket::IPv4Protocol)
            {
                qDebug()<<"获得呼叫器本地ip"<<address.toString();
                cip = address.toString();
            }
        }
        //10.48.18.72
        cmdBiz["Device_ip"]    = cip;

        qDebug() << "评价器配置项信息访问参数 "<<cmdBiz.ToString();


        Record result  = sendGetUrl(loginUrl,cmdBiz);;



        qDebug() << "评价器配置项信息返回结果 "<<result.ToString();
        if((bool)result["Succ"]==true) {
            Record Res = result["Setting"];

            qDebug()<<"所有配置项数量"<<Res.Size();
            uint r = Res.Size();

            for(uint i = 0; i < r; i++){
                QString setting_code     = (const char*)Res[i]["setting_code"];
                QString setting_value    = (const char*)Res[i]["setting_value"];
                qDebug()<<(i+1)<<"开始同步："<<setting_code<<"："<<setting_value;
                dmSaveSett(setting_code,setting_value);

            }
            qDebug()<<"修改修改缓存";
            CacheInstance.SaveConfig("评价器配置__", getAllSetting("").toUtf8());//修改缓存
        }
        return result.ToString();

}

Record AllConfigs::sendGetUrl(QString urlForSp, Record cmdBiz) {

        QString host;
        int port ;
        QString url;

       qDebug() << "访问接口 "<<cmdBiz.ToString();
        const QByteArray& postDat = cmdBiz.ToString();


        const QString& contentType = "application/json";

        //static QByteArray resultErr;
        Record resultErr;
        resultErr["Succ"] = 0;

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
        QByteArray BizResult = json.mid(index + 1);

        Record result;
        result.FromString(BizResult.data(), BizResult.size());


        qDebug() << "评价器配置项信息返回结果 "<<result.ToString();

        return result;

}
//对比程序改为从大厅管理系统
QString AllConfigs::getSetCompare() {

        //登录获取token
        QString startPage = CsGetConfig("大厅管理地址");
        //QString startPage = "dtgladmin_zd|202cb962ac59075b964b07152d234b70|http://10.110.5.22:8168/web/serviceEntry";

        QStringList setting =startPage.split("|");

        if(setting.size() < 3) return "";

        QString loginName= setting[0];
        QString loginPwd = setting[1];
        QString loginUrl = setting[2];//"http://10.110.1.110:8142/web/serviceEntry"

        Record cmdLogin;
        cmdLogin["Service"] = "QueueCity.Login";
        cmdLogin["account"] = loginName;
        cmdLogin["password"]= loginPwd;

        Record loginRes=sendGetUrl( loginUrl,cmdLogin);
        if(!loginRes.Exists("token")) {
            qDebug() << "对比数据同步登录失败";
            return "";
        }
        token = (const char*)loginRes["token"];



        Record cmdBiz;

        cmdBiz["Service"]  = "ZdSetting.GetZdSetting";


        cmdBiz["Device_type"]    = "PJFWQ";
        cmdBiz["token"]    = token;



        QString cip = "127.0.0.1";
        QHostInfo info = QHostInfo::fromName(QHostInfo::localHostName());

        qDebug()<<"找出一个IPv4地址即返回"<<QHostInfo::localHostName();

        // 找出一个IPv4地址即返回
        foreach(QHostAddress address,info.addresses())
        {
            qDebug()<<"开始找ip地址";
            if(address.protocol() == QAbstractSocket::IPv4Protocol)
            {
                qDebug()<<"获得呼叫器本地ip"<<address.toString();
                cip = address.toString();
            }
        }
        //10.48.18.72
        cmdBiz["Device_ip"]    = cip;

        qDebug() << "评价器配置项信息访问参数 "<<cmdBiz.ToString();


        Record result  = sendGetUrl(loginUrl,cmdBiz);;
        Record showResult;


        qDebug() << "评价器配置项信息返回结果 "<<result.ToString();
        if((bool)result["Succ"]==true) {
            Record Res = result["Setting"];

            qDebug()<<"所有配置项数量"<<Res.Size();
            uint r = Res.Size();
            int k = 0 ;

            //新增
            for(uint i = 0; i < r; i++){
                QString setting_code     = (const char*)Res[i]["setting_code"];
                 const char* sCode = (const char*)Res[i]["setting_code"];
                QString setting_value    = (const char*)Res[i]["setting_value"];
                //qDebug()<<(i+1)<<"开始同步："<<setting_code<<"："<<setting_value;


                QString compare = "0";


                if(SettingKeyValue[sCode]==""){
                    //如果本地没有该配置项 则定义为新增
                    showResult[k]["key"] = setting_code;
                    showResult[k]["value"] = SettingKeyValue[sCode];
                    showResult[k]["compareValue"] = setting_value;
                    showResult[k]["num"] = (k+1);
                    compare = "new";
                    showResult[k]["compare"] = compare;
                    k++;
                }else if(SettingKeyValue[sCode]==setting_value){
                    //如果本地和大厅一样则没有改变
                    compare = "same";
                }else if(SettingKeyValue[sCode]!=setting_value){
                    //如果本地和大厅不一样则证明本地与大厅不同
                    compare = "unlike";
                }
            }
            //修改
            for(uint i = 0; i < r; i++){
                QString setting_code     = (const char*)Res[i]["setting_code"];
                 const char* sCode = (const char*)Res[i]["setting_code"];
                QString setting_value    = (const char*)Res[i]["setting_value"];
                //qDebug()<<(i+1)<<"开始同步："<<setting_code<<"："<<setting_value;


                QString compare = "0";


                if(SettingKeyValue[sCode]==""){
                    //如果本地没有该配置项 则定义为新增
                    compare = "new";

                }else if(SettingKeyValue[sCode]==setting_value){
                    //如果本地和大厅一样则没有改变
                    compare = "same";

                }else if(SettingKeyValue[sCode]!=setting_value){
                    //如果本地和大厅不一样则证明本地与大厅不同
                    compare = "unlike";
                    showResult[k]["key"] = setting_code;
                    showResult[k]["value"] = SettingKeyValue[sCode];
                    showResult[k]["compareValue"] = setting_value;
                    showResult[k]["num"] = (k+1);
                    showResult[k]["compare"] = compare;
                    k++;
                }
            }
            //相同
            for(uint i = 0; i < r; i++){
                QString setting_code     = (const char*)Res[i]["setting_code"];
                const char* sCode = (const char*)Res[i]["setting_code"];
                QString setting_value    = (const char*)Res[i]["setting_value"];
                //qDebug()<<(i+1)<<"开始同步："<<setting_code<<"："<<setting_value;


                QString compare = "0";


                if(SettingKeyValue[sCode]==""){
                    //如果本地没有该配置项 则定义为新增
                    compare = "new";

                }else if(SettingKeyValue[sCode]==setting_value){
                    //如果本地和大厅一样则没有改变
                    compare = "same";
                    showResult[k]["key"] = setting_code;
                    showResult[k]["value"] = SettingKeyValue[sCode];
                    showResult[k]["compareValue"] = setting_value;
                    showResult[k]["num"] = (k+1);
                    showResult[k]["compare"] = compare;
                    k++;

                }else if(SettingKeyValue[sCode]!=setting_value){
                    //如果本地和大厅不一样则证明本地与大厅不同
                    compare = "unlike";

                }
            }



        }

        qDebug() << "评价器对比配置项结果： "<<result.ToString();
        return showResult.ToString();

}
int AllConfigs::GetHttpContentLength(const QByteArray& httpData, int httpHeadLen) {
    QByteArray head = httpData.left(httpHeadLen).toUpper();
    int lenOff = head.indexOf("CONTENT-LENGTH:");
    if(lenOff < 0) return 0;
    lenOff += strlen("CONTENT-LENGTH:");
    QByteArray lenByte = head.mid(lenOff, head.indexOf('\n', lenOff) - lenOff);
    if(lenByte[lenByte.length() - 1] == '\r') lenByte.remove(lenByte.length() - 1, 1);
    return lenByte.toInt();
}
//展示除了分组意外的其他配置项
QString AllConfigs::getOtherSetting(QString array){


     Record result;
     QMap<QString,QString>::iterator it; //遍历map
     int i=0;
     //剩下配置项载入
     for ( it = SettingKeyValue.begin(); it != SettingKeyValue.end(); ++it ) {

         if(!array.contains(it.key())){

                     result[i]["key"] = it.key();
                     result[i]["value"] = it.value();
                     result[i]["num"] = (i+1);
                     i++;

         }
     }

     return result.ToString();
}
