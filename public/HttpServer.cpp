#include "../inc/HttpServer.h"
#include "../public/Cache.h"

void HttpClient::Logic() {


    const char* GResult =	"HTTP/1.1 200 OK\r\n"
                            "Server: Dzfl\r\n"
                            "Access-Control-Allow-Origin: *\r\n"
                            "Cache-Control: no-cache, no-store, max-age=0, must-revalidate\r\n"
                            "Content-Type: text/html\r\n"
                            "Content-Length: 2\r\n\r\nOK";

    char *http_end, vdata[10000], *cmd_head, *tmp;
    //测试代码
    if((http_end = strstr(buf, "\r\n")) != NULL || (http_end = strstr(buf, "\n")) != NULL) {
        mySleep(300);

        tmp = strchr(buf, '\n');

        if(tmp == NULL) { Close(); return; }

        *tmp = 0; tmp -= 9; //跳过HTTP/1.1
        for(char* tran = buf; tran < tmp; tran++) {
            if(strstr(buf, "APPRAISENEWHCP")||strstr(buf, "SHOWQRCODE")||strstr(buf, "APPRAISEHCP")||strstr(buf, "FACEPICTURE")||strstr(buf, "AUTHORIZEFILE")){
                *tran =(ushort)*tran;
            }else{
                *tran = QChar::toUpper((ushort)*tran);
            }
        }
        cmd_head = tmp;
        for(; cmd_head > buf && *cmd_head != '/'; cmd_head--);
        if(cmd_head == buf) { Close(); return; }

        cmd_head++;
        memset(vdata, 0, sizeof(vdata));       
        //返回
        socket->write(GResult, strlen(GResult));
        socket->waitForBytesWritten();
        socket->close();
    }
}

void HttpClient::OnTimer() {
    //评价状态检查是否评价结束
    if(AppraiseLock) return;

    char AResult[0x1000];
    sprintf(AResult,
        "HTTP/1.1 200 OK\r\n"
        "Server: Inspur\r\n"
        "Access-Control-Allow-Origin: *\r\n"
        "Cache-Control: no-cache, no-store, max-age=0, must-revalidate\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %d\r\n\r\n%s",
        strlen(AppraiseResult), AppraiseResult);

    socket->write(AResult, strlen(AResult));
    socket->waitForBytesWritten();
    socket->close();
    timer.stop();
}

char* HttpClient::GetParam(const char* str, const char* key) {
    static char value[10000];
    char* fkey = (char*)strstr(str, key);
    if(fkey == NULL)
        return NULL;
    int klen = strlen(key);
    if(fkey[klen] != '=')
        return NULL;
    char* vstart = fkey + klen + 1;
    char* vend = strchr(fkey + klen + 1, '&');
    memset(value, 0, sizeof(value));
    if(vend == NULL)
        vend = strchr(fkey + klen + 1, ' ');
    if(vend == NULL)
        vend = vstart;
    memcpy(value, vstart, vend - vstart);

    //处理UTF8转义字符串
    if(strcmp(value, "%") >= 0)
        strcpy(value, QString(QByteArray::fromPercentEncoding(value)).toLocal8Bit());
    return value;
}
