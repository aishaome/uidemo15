#pragma execution_character_set("utf-8")
#include "tablebutton.h"
#include "businessprocessing.h"
#include "quiwidget.h"
#include <QUuid>

tableButton::tableButton(QString projectId, QString tableName, QTableView *tableView,  QObject *parent) :
    QObject(parent), project_id(projectId), table_name(tableName), tableview(tableView)
{
}

tableButton::~tableButton()
{
}

bool tableButton::addData()
{
    bool ok;
    QStringList mdates;
    businessProcessing *bus = new businessProcessing();
    QString strId = QUuid::createUuid().toString();
    strId = strId.remove("{").remove("}").remove("-");
    QJsonArray plot_array;
    for(int i = 0; i < 6; i++) {
        mdates << QString::fromLocal8Bit("请输入%1").arg(fieldLabel[i]);
    }
    QStringList vals = QUIWidget::showInputBoxs(0, ok, mdates, mdates, 6);
    if(ok) {
        for(int i = 0; i < 6; i++) {
            QJsonObject form;
            form.insert("name", fieldName[i]);
            form.insert("value", vals[i]);
            plot_array.append(form);
        }
        if(user_name == "") {
            getUserName();
        }
        QJsonObject obj;
        obj.insert("id", strId);
        obj.insert("project_id", project_id);
        obj.insert("table_name", table_name);
        obj.insert("user_id", project_id);
        obj.insert("user_name", user_name);
        obj.insert("form", plot_array);
        qDebug("obj:%s", QJsonDocument(obj).toJson());
        QStringList addStatus = bus->addData(obj);
        qDebug() << addStatus;
        if(QString(addStatus[0]).toInt()) {
            QUIWidget::showMessageBoxInfo("添加成功!", 3);
            return true;
        } else {
            QUIWidget::showMessageBoxError("添加失败!", 3);
            return false;
        }
    }
    return false;
}
bool tableButton::editData()
{
    bool ok;
    QStringList mdates;
    int row = tableview ->currentIndex().row();
    if(row < 0) {
        QUIWidget::showMessageBoxError("请在表中操作!", 3);
        return false;
    }
    QStringList mtatle = retrieveData(tableview);
    qDebug() << "mtatle:" << mtatle;
    businessProcessing *bus = new businessProcessing();
    QString strId = idLabelData[row];
    QJsonArray plot_array;
    for(int i = 0; i < 6; i++) {
        mdates << QString::fromLocal8Bit("请输入%1").arg(fieldLabel[i]);
    }
    QStringList vals = QUIWidget::showInputBoxs(1, ok, mdates, mtatle, 6);
    if(ok) {
        for(int i = 0; i < 6; i++) {
            QJsonObject form;
            form.insert("name", fieldName[i]);
            form.insert("value", vals[i]);
            plot_array.append(form);
        }
        if(user_name == "") {
            getUserName();
        }
        QJsonObject obj;
        obj.insert("id", strId);
        obj.insert("project_id", project_id);
        obj.insert("table_name", table_name);
        obj.insert("user_id", project_id);
        obj.insert("user_name", user_name);
        obj.insert("form", plot_array);
        qDebug("obj:%s", QJsonDocument(obj).toJson());
        QStringList addStatus = bus->addData(obj);
        qDebug() << "addStatus:" << addStatus;
        if(QString(addStatus[0]).toInt()) {
            QUIWidget::showMessageBoxInfo("编辑成功!", 3);
            return true;
        } else {
            QUIWidget::showMessageBoxError("编辑失败!", 3);
            return false;
        }
    }
    return false;
}
bool tableButton::deleteData()
{
    businessProcessing *bus = new businessProcessing();
    QList<int> indexs = requestRowId(tableview);
    if(indexs.count() <= 0) {
        QUIWidget::showMessageBoxError("请选择需要删除的数据", 3);
        return false;
    }
    QString ids;
    foreach (int index, indexs) {
        ids = ids + QString("%1,").arg(idLabelData[index]);
    }
    QJsonObject obj;
    QStringList msg;
    obj.insert("project_id", project_id);
    obj.insert("table_name", table_name);
    obj.insert("ids", ids);
//    qDebug() << "ids:" << ids;
//    qDebug() << "obj:" << obj;
    int ret = QUIWidget::showMessageBoxQuestion("是否删除所选的数据");
    if(ret) {
        msg = bus->deleteData(obj);
//        qDebug() << "msg:" << msg;
        if(QString(msg[0]).toInt()) {
            QUIWidget::showMessageBoxInfo(msg[1], 3);
            return true;
        } else {
            QUIWidget::showMessageBoxError(msg[1], 3);
            return false;
        }
    } else {
        return false;
    }
    return false;
}
QString tableButton::updateData()
{
    businessProcessing *bus = new businessProcessing();
    QJsonObject obj;
    obj.insert("table_name", table_name);
    obj.insert("project_id", project_id);
    tableview->setModel(bus->updateData(obj));
    tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    fieldName = bus->getFieldName();
    fieldLabel = bus->getfieldLabel();
    idLabelData = bus->getIdLabelData();
    table_desc = bus->getTitleDesc();
    user_name = bus->getUserName();
    return table_desc;
}
bool tableButton::importData(QString &filePath)
{
    businessProcessing *bus = new businessProcessing();
    QFileInfo fileInfo(filePath);
    QString fileName = fileInfo.fileName();
    if(user_name == "") {
        getUserName();
    }
    QJsonObject obj;
    obj.insert("table_name", table_name);
    obj.insert("project_id", project_id);
    obj.insert("table_desc", table_desc);
    obj.insert("user_id", project_id);
    obj.insert("user_name", user_name);
    obj.insert("fileName", fileName);
    obj.insert("fileUploadfile", filePath);
//    qDebug() << "obj:" << obj;
    QStringList msg = bus->importData(obj);
//    qDebug() << "msg:" << msg;
    if(QString(msg[0]).toInt()) {
        QUIWidget::showMessageBoxInfo(QString("数据导入成功").arg(QString(msg[1]).toInt()), 3);
        return true;
    } else {
        QUIWidget::showMessageBoxError("数据导入失败!", 3);
        return false;
    }
}
bool tableButton::exportData(QString &filePath)
{
    businessProcessing *bus = new businessProcessing();
    QJsonObject obj;
    obj.insert("project_id", project_id);
    obj.insert("table_name", table_name);
    qDebug("obj:%s", QJsonDocument(obj).toJson());
    QString addStatus = bus->exportData(obj);
    qDebug("addStatus:%s", qUtf8Printable(addStatus));
    if(addStatus == "") {
        QUIWidget::showMessageBoxError("数据导出失败!", 3);
        return false;
    }
    if(downloadFileFromURL(addStatus, filePath, 500)) {
        QUIWidget::showMessageBoxInfo("数据导出成功!", 3);
        return true;
    } else {
        QUIWidget::showMessageBoxError("数据导出失败!", 3);
        return false;
    }
}

QList<int> tableButton::requestRowId(QTableView *tableView)
{
    QItemSelectionModel *selections = tableView->selectionModel();
    QModelIndexList selected = selections->selectedIndexes();
    QMap <int, int> rowMap;
    foreach (QModelIndex index, selected) {
        rowMap.insert(index.row(), 0);
    }
    return rowMap.keys();
}

QStringList tableButton::retrieveData(QTableView *tableView)
{
    QStringList tableData;
    QAbstractItemModel *tmpmodel = tableView->model();
    int row =  tableView->currentIndex().row();
    for(int i = 0; i < 6; i++) {
        QModelIndex index = tmpmodel->index(row, i);
        tableData << tmpmodel->data(index).toString();
    }
    return tableData;
}

bool tableButton::downloadFileFromURL(const QString &url, const QString &filePath, int timeout)
{
    QFile f(filePath);
    if (!f.open(QIODevice::WriteOnly)) {
        return false;
    }
    QNetworkAccessManager m;
    QNetworkRequest req;
    req.setUrl(QUrl(url));
    QNetworkReply *reply = m.get(req);
    QEventLoop loop;
    QTimer t;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    QObject::connect(reply, &QNetworkReply::downloadProgress,
    [ =, &f, &t]() {
        f.write(reply->readAll());
        if (t.isActive()) {
            t.start(timeout);
        }
    });
    if (timeout > 0) {
        QObject::connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
        t.start(timeout);
    }
    loop.exec();
    if (reply->error() != QNetworkReply::NoError) {
        return false;
    }
    f.close();
    delete reply;
    return true;
}

bool tableButton::login(QString login_name, QString password)
{
    businessProcessing *bus = new businessProcessing();
    QJsonObject obj;
    if(login_name == "" || password == "") {
        QUIWidget::showMessageBoxError("请将账号和密码填写完成!", 3);
        return false;
    }
    obj.insert("project_id", project_id);
    obj.insert("login_name", login_name);
    obj.insert("password", password);
    QStringList msg = bus->loginData(obj);
    if(!QString(msg[0]).toInt()) {
        QUIWidget::showMessageBoxError(msg[1], 3);
        return false;
    }
    return true;
}

bool tableButton::editPass(QString oldPassword, QString password, QString confirmPassword)
{
    businessProcessing *bus = new businessProcessing();
    QJsonObject obj;
    obj.insert("oldPassword", oldPassword);
    obj.insert("password", password);
    obj.insert("confirmPassword", confirmPassword);
    obj.insert("userId", project_id);
    QStringList msg = bus->editPass(obj);
    if(QString(msg[0]).toInt()) {
        QUIWidget::showMessageBoxInfo("密码修改成功!", 3);
        return true;
    } else {
        QUIWidget::showMessageBoxError(msg[1], 3);
        return false;
    }
    return false;
}

QString tableButton::getUserName()
{
    businessProcessing *bus = new businessProcessing();
    QJsonObject obj;
    QString sql = QString("SELECT name FROM cms_platform_user WHERE id='%1'").arg(project_id);
    obj.insert("sql", sql);
    QJsonArray userNameArray = bus->getJsonBySql(obj);
    qDebug() << "userNameArray:" << userNameArray;
    user_name = userNameArray.at(0).toObject().value("name").toString();
    return user_name;
}

QString tableButton::getProjectName()
{
    businessProcessing *bus = new businessProcessing();
    QJsonObject obj;
    QString sql = QString("SELECT title FROM cms_platform_project WHERE id='%1'").arg(project_id);
    obj.insert("sql", sql);
    QJsonArray userNameArray = bus->getJsonBySql(obj);
    qDebug() << "projectName:" << userNameArray;
    projectName = userNameArray.at(0).toObject().value("title").toString();
    return projectName;
}

void tableButton::setUserName(QString &userName)
{
    user_name = userName;
}

bool tableButton::conditionQuery()
{
    bool ok;
    QStringList mdates;
    for(int i = 0; i < 6; i++) {
        mdates << QString::fromLocal8Bit("请输入%1").arg(fieldLabel[i]);
    }
    QStringList vals = QUIWidget::showInputBoxs(0, ok, mdates, mdates, 6);
    if(ok) {
        QString strSql = QString("SELECT * FROM %1 WHERE project_id = '%2' ")
                         .arg(table_name).arg(project_id);
        if(vals.at(0) != "") {
            vals[0] = QString(" AND %1 LIKE '%%2%'").arg(fieldName[0]).arg(vals.at(0));
        }
        if(vals.at(1) != "") {
            vals[1] = QString(" AND %1 LIKE '%%2%'").arg(fieldName[1]).arg(vals.at(1));
        }
        if(vals.at(2) != "") {
            vals[2] = QString(" AND %1 LIKE '%%2%'").arg(fieldName[2]).arg(vals.at(2));
        }
        if(vals.at(3) != "") {
            vals[3] = QString(" AND %1 LIKE '%%2%'").arg(fieldName[3]).arg(vals.at(3));
        }
        if(vals.at(4) != "") {
            vals[4] = QString(" AND %1 LIKE '%%2%'").arg(fieldName[4]).arg(vals.at(4));
        }
        if(vals.at(5) != "") {
            vals[5] = QString(" AND %1 LIKE '%%2%'").arg(fieldName[5]).arg(vals.at(5));
        }
        strSql = strSql + vals.at(0) + vals.at(1) + vals.at(2) + vals.at(3) + vals.at(4) + vals.at(5);
        qDebug("strSql:%s", qUtf8Printable(strSql));
        businessProcessing *bus = new businessProcessing();
        QJsonObject obj;
        obj.insert("table_name", table_name);
        obj.insert("project_id", project_id);
        QJsonObject sql;
        sql.insert("sql", strSql);
        tableview->setModel(bus->queryData(obj, sql));
        tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
//    tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        tableview->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
//    int width = tableview->width();
//    qDebug() << "width:" << width;
        tableview->horizontalHeader()->setMinimumSectionSize(195);
//    tableview->verticalHeader()->setMinimumSectionSize(100);
        return true;
    }
    return false;
}

QString tableButton::getSqlDate()
{
    QString strSql = QString("SELECT * FROM %1 WHERE project_id = '%2' ")
                     .arg(table_name).arg(project_id);
    businessProcessing *bus = new businessProcessing();
    QJsonObject obj;
    obj.insert("table_name", table_name);
    obj.insert("project_id", project_id);
    QJsonObject sql;
    sql.insert("sql", strSql);
    tableview->setModel(bus->queryData(obj, sql));
    tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
//    tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableview->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
//    int width = tableview->width();
//    qDebug() << "width:" << width;
    tableview->horizontalHeader()->setMinimumSectionSize(195);
//    tableview->verticalHeader()->setMinimumSectionSize(100);
    fieldName = bus->getFieldName();
    fieldLabel = bus->getfieldLabel();
    idLabelData = bus->getIdLabelData();
    table_desc = bus->getTitleDesc();
    user_name = bus->getUserName();
    return table_desc;
}
