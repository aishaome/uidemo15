#ifndef BUSINESSPROCESSING_H
#define BUSINESSPROCESSING_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardItemModel>
#include <QCoreApplication>
#include <QFile>
class businessProcessing : public QObject
{
    Q_OBJECT
public:
    explicit businessProcessing(QObject *parent = nullptr);
    ~businessProcessing();
    QStringList loginData(QJsonObject obj);
    QStringList addData(QJsonObject obj);
    QStringList editData(QJsonObject obj);
    QStringList deleteData(QJsonObject obj);
    QStandardItemModel *updateData(QJsonObject obj);
    QStandardItemModel *queryData(QJsonObject obj, QJsonObject sql);
    QStringList importData(QJsonObject obj);
    QString exportData(QJsonObject obj);
    QStringList getFieldName();
    QStringList getfieldLabel();
    QStringList getIdLabelData();
    QString getTitleDesc();
    QString getUserName();
    QStringList editPass(QJsonObject obj);
    QJsonArray getJsonBySql(QJsonObject obj);
    QStringList exceteSql(QJsonObject obj);

private slots:
    void Sleep(int msec);
    void editJson(QByteArray bytearray);
    void updateJson(QByteArray bytearray);
    void exportJson(QByteArray bytearray);

private:
    QJsonArray jsonArray;
    QStringList fieldLabel;
    QStringList fieldName;
    QStringList labelData;
    QStringList idLabelData;
    QString titleDesc;
    QStandardItemModel *model;
    QStandardItemModel *queryModel;
    QStringList status;
    QString filePath;
    QString userName;


signals:

};

#endif // BUSINESSPROCESSING_H
