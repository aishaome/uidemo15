#ifndef JSONPROCESSING_H
#define JSONPROCESSING_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>    //加载网络请求头文件
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include "qreplytimeout.h"
class jsonProcessing : public QObject
{
    Q_OBJECT
public:
    explicit jsonProcessing(QObject *parent = nullptr);
    ~jsonProcessing();

public Q_SLOTS:
    bool postHttpRequest(QUrl url, QJsonObject obj, QByteArray &requestData); //请求远程数据库
    void requestFinished(QNetworkReply* reply); //解析JSON
    bool uploadFileForm(QUrl url,  QJsonObject obj, QByteArray &requestData);
Q_SIGNALS:
    void parsingJson(QByteArray bytearray);

};

#endif // JSONPROCESSING_H
