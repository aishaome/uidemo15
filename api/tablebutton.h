
#ifndef TABLEBUTTON_H
#define TABLEBUTTON_H

#include <QObject>
class QTableView;
class tableButton : public QObject
{
    Q_OBJECT
public:
    explicit tableButton(QString projectId = nullptr, QString tableName = nullptr, QTableView *tableView = nullptr, QObject *parent = nullptr);
    ~tableButton();

signals:
public:



public Q_SLOTS:
    void setUserName(QString &userName);
    QString getUserName();
    QString getProjectName();
    bool addData();
    bool editData();
    bool deleteData();
    bool exportData(QString &filePath);
    bool importData(QString &filePath);
    QString updateData();
    bool login(QString login_name, QString password);
    bool editPass(QString oldPassword, QString password, QString confirmPassword);
    bool conditionQuery();
    QString getSqlDate();
private slots:
    QList <int> requestRowId(QTableView *tableView);
    QStringList retrieveData(QTableView *tableView);
    bool downloadFileFromURL(const QString &url, const QString &filePath, int timeout = -1);

private:
    QStringList fieldName;
    QStringList fieldLabel;
    QStringList idLabelData;
    QStringList selectedId;
    QString table_desc;
    QString strId;
    QString project_id;
    QString table_name;
    QTableView *tableview;
    QString projectName;
    QString user_name;

};


#endif // TABLEBUTTON_H
