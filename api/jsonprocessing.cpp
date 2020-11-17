#include "jsonprocessing.h"
#include <QCoreApplication>
#include <QHttpPart>
#include <QDebug>
#include <QElapsedTimer>
#include <QTimer>
#include <QEventLoop>
jsonProcessing::jsonProcessing(QObject *parent) : QObject(parent)
{
}

jsonProcessing::~jsonProcessing()
{
}

bool jsonProcessing::postHttpRequest(QUrl url, QJsonObject obj, QByteArray &requestData)
{
    QNetworkRequest request;
    QNetworkAccessManager* naManager = new QNetworkAccessManager(this);
//    QObject::connect(naManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    request.setUrl(url);
    QByteArray byte_array = QJsonDocument(obj).toJson();
//    qDebug() << "byte_array:" << byte_array;
    QNetworkReply *reply = naManager->post(request, byte_array);
    QEventLoop l;
    //一旦服务器返回 reply会发出信号
    connect(reply, &QNetworkReply::finished, &l, &QEventLoop::quit);
    l.exec();//死循环，reply发出信号，结束循环
    if(reply != nullptr && reply->error() == QNetworkReply::NoError) {
        requestData = reply->readAll();
        return true;
    } else {
        qDebug("请求失败：\0");
        return false;
    }
}


bool jsonProcessing::uploadFileForm(QUrl url, QJsonObject obj, QByteArray &requestData)
{
    QNetworkRequest request;
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QNetworkAccessManager* naManager = new QNetworkAccessManager(this);
//    QObject::connect(naManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
    QHttpPart fileUploadfile;
    fileUploadfile.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"fileUploadfile\";filename=\"" + obj.value("fileName").toString() + "\""));
    QFile *file = new QFile(obj.value("fileUploadfile").toString());
    if(!file->open(QIODevice::ReadOnly)) {
        return false;
    }
    fileUploadfile.setBodyDevice(file);
    file->setParent(multiPart);
    QHttpPart table_name;
    table_name.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"table_name\""));
    table_name.setBody(obj.value("table_name").toString().toUtf8());
    QHttpPart user_id;
    user_id.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"user_id\""));
    user_id.setBody(obj.value("user_id").toString().toUtf8());
    QHttpPart table_desc;
    table_desc.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"table_desc\""));
    table_desc.setBody(obj.value("table_desc").toString().toUtf8());
    QHttpPart user_name;
    user_name.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"user_name\""));
    user_name.setBody( obj.value("user_name").toString().toUtf8());
    QHttpPart project_id;
    project_id.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"project_id\""));
    project_id.setBody(obj.value("project_id").toString().toUtf8());
    multiPart->append(table_name);
    multiPart->append(user_id);
    multiPart->append(table_desc);
    multiPart->append(user_name);
    multiPart->append(project_id);
    multiPart->append(fileUploadfile);
    request.setUrl(url);
    QNetworkReply *reply = naManager->post(request, multiPart);
    multiPart->setParent(reply);
    QEventLoop l;
    //一旦服务器返回 reply会发出信号
    connect(reply, &QNetworkReply::finished, &l, &QEventLoop::quit);
    l.exec();//死循环，reply发出信号，结束循环
    if(reply != nullptr && reply->error() == QNetworkReply::NoError) {
        requestData = reply->readAll();
        return true;
    } else {
        qDebug("请求失败：\0")  ;
        return false;
    }
}

void jsonProcessing::requestFinished(QNetworkReply* reply)
{
//    QByteArray a = "{\"success\":true,\"message\":\"\xE7\x99\xBB\xE5\xBD\x95\xE6\x88\x90\xE5\x8A\x9F\",\"user\":{\"id\":\"cab9135025654ad2a517a81f85c2e6d8\",\"name\":\"\xE6\x98\x8E\xE5\x8D\x8E\",\"loginName\":\"\xE6\x98\x8E\xE5\x8D\x8E\"}}";
//    QByteArray b = "{\"success\":false,\"errorMessage\":\"\xE5\xAF\x86\xE7\xA0\x81\xE8\xBE\x93\xE5\x85\xA5\xE6\x9C\x89\xE8\xAF\xAF\"}";
    QByteArray bytes = reply->readAll();
//    qDebug() << "bytes:" << bytes;
    // 获取http状态码
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCode.isValid()) {
        qDebug() << "status code=" << statusCode.toInt();
    }
    QNetworkReply::NetworkError err = reply->error();
    if(err != QNetworkReply::NoError) {
        qDebug() << "Failed: " << reply->errorString().toUtf8();
        QByteArray Failed = "{'success':false,'errorMessage':'网络异常！'}";
        emit parsingJson(Failed);
    } else {
        // 获取返回内容
        emit parsingJson(bytes);
    }
}
#if 0
void jsonProcessing::parsingJson(QByteArray bytearray)
{
    QJsonParseError jsonErr;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(bytearray, &jsonErr);
    if(jsonErr.error != QJsonParseError::NoError) {
        qDebug() << QString::fromLocal8Bit("Json解析失败:");
    }
    QJsonObject root_Obj = jsonDoc.object();
    bool success = root_Obj.value("success").toBool();
    if(success) {
        qDebug() << "success:" << success;
        QJsonValue table_Vaule = root_Obj.value("table");
        QJsonValue fieldTable_Vaule = root_Obj.value("fieldTable");
        if(table_Vaule.isArray()) {
            for(int idy = 0; idy < fieldLabel.count(); idy++) {
                model->setHorizontalHeaderItem(idy, new QStandardItem(fieldLabel[idy]));
            }
            for(int idx = 0; idx < table_Vaule.toArray().count(); idx++) {
                QJsonObject data_Obj = table_Vaule.toArray().at(idx).toObject();
                for(int i = 0; i < fieldName.count(); i++) {
                    model->setItem(idx,  i,  new QStandardItem(data_Obj.value(fieldName[i]).toString()));
                    labelData << data_Obj.value(fieldName[i]).toString();
                }
                idLabelData << data_Obj.value("id").toString();
            }
            booleanVal = true;
            qDebug() << "idLabelData：" << idLabelData;
            qDebug() << "LabelData：" << labelData;
        } else if(fieldTable_Vaule.isArray()) {
            for(int idx = 8; idx < fieldTable_Vaule.toArray().count(); idx++) {
                QJsonObject data_Obj = fieldTable_Vaule.toArray().at(idx).toObject();
                fieldName << data_Obj.value("field_name").toString();
                fieldLabel << data_Obj.value("field_label").toString();
            }
            titleDesc = root_Obj.value("table_desc").toString();
            qDebug() << "fieldName：" << fieldName;
            qDebug() << "fieldLabel：" << fieldLabel;
            qDebug() << "titleDesc：" << titleDesc;
            booleanVal = true;
        }
    } else {
        booleanVal = false;
        qDebug() << "success:" << success;
    }
    return ;
}
#endif

