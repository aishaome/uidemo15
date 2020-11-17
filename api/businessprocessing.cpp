#include "businessprocessing.h"
#include "jsonprocessing.h"
#include <qdebug.h>

businessProcessing::businessProcessing(QObject *parent) : QObject(parent)
{
    model = new QStandardItemModel();
}

businessProcessing::~businessProcessing()
{
    delete model;
}

QStringList businessProcessing::loginData(QJsonObject obj)
{
    QByteArray requestData;
    QUrl url("http://api.cqbrh.com/api/business/login");
    jsonProcessing* json = new jsonProcessing();
    json->postHttpRequest(url, obj, requestData);
//    QObject::connect(json, SIGNAL(parsingJson(QByteArray)), this, SLOT(editJson(QByteArray)));
    editJson(requestData);
    Sleep(500);
    return status;
}

void businessProcessing::Sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime ) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void businessProcessing::editJson(QByteArray bytearray)
{
    status.clear();
    QJsonParseError jsonErr;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(bytearray, &jsonErr);
    if(jsonErr.error != QJsonParseError::NoError) {
        qDebug() << QString::fromLocal8Bit("Json解析失败:");
    }
    QJsonObject root_Obj = jsonDoc.object();
    bool success = root_Obj.value("success").toBool();
    if(success) {
        qDebug() << "success:" << success;
        status << "1";
        status << root_Obj.value("message").toString();
        if(root_Obj.value("table").isArray()) {
            jsonArray = root_Obj.value("table").toArray();
        }
    } else {
        qDebug() << "success:" << success;
        status << "0";
        status << root_Obj.value("errorMessage").toString();
    }
    return ;
}

QStandardItemModel* businessProcessing::updateData(QJsonObject obj)
{
    QByteArray requestData;
    QUrl url1("http://api.cqbrh.com/api/business/getTableFiled");
    QUrl url2("http://api.cqbrh.com/api/business/getJsonByTable");
    jsonProcessing* json = new jsonProcessing();
    json->postHttpRequest(url1, obj, requestData);
//    QObject::connect(json, SIGNAL(parsingJson(QByteArray)), this, SLOT(updateJson(QByteArray)));
    updateJson(requestData);
    Sleep(250);
    qDebug("Sleep:200");
    json->postHttpRequest(url2, obj, requestData);
    updateJson(requestData);
    Sleep(250);
    qDebug("Sleep:250");
    return model;
}

void businessProcessing::updateJson(QByteArray bytearray)
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
                if(userName == "") {
                    userName = data_Obj.value("user_name").toString();
                }
            }
//            qDebug() << "userName" << userName;
//            qDebug() << "LabelData：" << labelData;
        } else if(fieldTable_Vaule.isArray()) {
            for(int idx = 8; idx < fieldTable_Vaule.toArray().count(); idx++) {
                QJsonObject data_Obj = fieldTable_Vaule.toArray().at(idx).toObject();
                fieldName << data_Obj.value("field_name").toString();
                fieldLabel << data_Obj.value("field_label").toString();
            }
            titleDesc = root_Obj.value("table_desc").toString();
//            qDebug() << "fieldName：" << fieldName;
//            qDebug() << "fieldLabel：" << fieldLabel;
//            qDebug() << "titleDesc：" << titleDesc;
        }
    } else {
        qDebug() << "success:" << success;
    }
    return ;
}

QStringList businessProcessing::getFieldName()
{
    return fieldName;
}

QStringList businessProcessing::getfieldLabel()
{
    return fieldLabel;
}

QStringList businessProcessing::getIdLabelData()
{
    return idLabelData;
}

QString businessProcessing::getTitleDesc()
{
    return titleDesc;
}

QString businessProcessing::getUserName()
{
    return userName;
}

QStringList businessProcessing::addData(QJsonObject obj)
{
    QByteArray requestData;
    QUrl url("http://api.cqbrh.com/api/business/saveForm");
    jsonProcessing* json = new jsonProcessing();
    json->postHttpRequest(url, obj, requestData);
//    QObject::connect(json, SIGNAL(parsingJson(QByteArray)), this, SLOT(editJson(QByteArray)));
    editJson(requestData);
    Sleep(250);
    qDebug("Sleep:250");
    return status;
}

QStringList businessProcessing::deleteData(QJsonObject obj)
{
    QByteArray requestData;
    QUrl url("http://api.cqbrh.com/api/business/delete");
    jsonProcessing* json = new jsonProcessing();
    json->postHttpRequest(url, obj, requestData);
//    QObject::connect(json, SIGNAL(parsingJson(QByteArray)), this, SLOT(editJson(QByteArray)));
    editJson(requestData);
    Sleep(250);
    qDebug("Sleep:250");
    return status;
}

QString businessProcessing::exportData(QJsonObject obj)
{
    QByteArray requestData;
    QUrl url("http://api.cqbrh.com/api/business/export");
    jsonProcessing* json = new jsonProcessing();
    json->postHttpRequest(url, obj, requestData);
//    QObject::connect(json, SIGNAL(parsingJson(QByteArray)), this, SLOT(exportJson(QByteArray)));
    exportJson(requestData);
    Sleep(250);
    qDebug("Sleep:250");
    return filePath;
}

void businessProcessing::exportJson(QByteArray bytearray)
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
        filePath = root_Obj.value("domainPath").toString();
//        qDebug() << "addStatus:" + loginStatus;
    } else {
        qDebug() << "success:" << success;
//        status = root_Obj.value("errorMessage").toString();
//        qDebug() << "addStatus:" + loginStatus;
    }
    return ;
}


QStringList businessProcessing::importData(QJsonObject obj)
{
    QByteArray requestData;
    QUrl url("http://api.cqbrh.com/api/business/import");
    jsonProcessing* json = new jsonProcessing();
    json->uploadFileForm(url, obj, requestData);
//    QObject::connect(json, SIGNAL(parsingJson(QByteArray)), this, SLOT(editJson(QByteArray)));
    editJson(requestData);
    Sleep(250);
    qDebug("Sleep:250");
    return status;
}

QStringList businessProcessing::editPass(QJsonObject obj)
{
    QByteArray requestData;
    QUrl url("http://api.cqbrh.com/api/business/update");
    jsonProcessing* json = new jsonProcessing();
    json->postHttpRequest(url, obj, requestData);
//    QObject::connect(json, SIGNAL(parsingJson(QByteArray)), this, SLOT(editJson(QByteArray)));
    editJson(requestData);
    Sleep(250);
    qDebug("Sleep:250");
    return status;
}

QJsonArray businessProcessing::getJsonBySql(QJsonObject obj)
{
    QByteArray requestData;
    QUrl url("http://api.cqbrh.com/api/business/getJsonBySql");
    jsonProcessing* json = new jsonProcessing();
    json->postHttpRequest(url, obj, requestData);
//    QObject::connect(json, SIGNAL(parsingJson(QByteArray)), this, SLOT(editJson(QByteArray)));
    editJson(requestData);
    Sleep(250);
    qDebug("Sleep:250");
    return jsonArray;
}

QStringList businessProcessing::exceteSql(QJsonObject obj)
{
    QByteArray requestData;
    QUrl url("http://api.cqbrh.com/api/business/exceteSql");
    jsonProcessing* json = new jsonProcessing();
    json->postHttpRequest(url, obj, requestData);
//    QObject::connect(json, SIGNAL(parsingJson(QByteArray)), this, SLOT(editJson(QByteArray)));
    editJson(requestData);
    Sleep(250);
    qDebug("Sleep:250");
    return status;
}

QStandardItemModel *businessProcessing::queryData(QJsonObject obj, QJsonObject sql)
{
    QByteArray requestData;
    QUrl url1("http://api.cqbrh.com/api/business/getTableFiled");
    QUrl url2("http://api.cqbrh.com/api/business/getJsonBySql");
    jsonProcessing* json = new jsonProcessing();
    json->postHttpRequest(url1, obj, requestData);
//    QObject::connect(json, SIGNAL(parsingJson(QByteArray)), this, SLOT(updateJson(QByteArray)));
    updateJson(requestData);
    Sleep(250);
    qDebug("Sleep:200");
    json->postHttpRequest(url2, sql, requestData);
    updateJson(requestData);
    Sleep(250);
    qDebug("Sleep:250");
    return model;
}


