#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QWidget>
#include "tablebutton.h"
#include <QSettings>

class QPushButton;
class QTableView;
class QStandardItemModel;
namespace Ui
{
    class frmMain;
}

class frmMain : public QWidget
{
    Q_OBJECT

public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();
public slots:
    void initForm();
protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::frmMain *ui;
    QList<QPushButton *> btns;
    tableButton *tableview;
    tableButton *tableview_2;
    QSettings *configIniWrite;
    QList<QString> doorCollection;  //门集合
    int doorNum;                    //门编号
    QList<bool> btnSts;                //按钮状态
    int fromCount;
    bool modifySts;
//    QStandardItemModel *model;


private slots:
    void initStyle();
    void initBtn();
    void initTableWidget();
    void buttonClick();
    void Sleep(int msec);
    QStandardItemModel *getLocalData();
    void logout();
private slots:
    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_clicked();
    void on_pushButton_20_clicked();
    void on_pushButton_42_clicked();
    void on_pushButton_43_clicked();
    void on_pushButton_41_clicked();
    void on_pushButton_44_clicked();
    void on_pushButton_22_clicked();
    void on_pushButton_21_clicked();
    void on_pushButton_25_clicked();
    void on_pushButton_26_clicked();
    void on_pushButton_27_clicked();
    void on_pushButton_40_clicked();
    void on_pushButton_24_clicked();
    void on_pushButton_28_clicked();
    void on_pushButton_29_clicked();
    void on_pushButton_30_clicked();
    void on_pushButton_31_clicked();
    void on_pushButton_32_clicked();
    void on_pushButton_33_clicked();
    void on_pushButton_34_clicked();
    void on_pushButton_35_clicked();
    void on_pushButton_36_clicked();
    void on_pushButton_39_clicked();
    void on_pushButton_23_clicked();
    void on_pushButton_16_clicked();
    void on_pushButton_19_clicked();
    void on_pushButton_18_clicked();
    void on_pushButton_17_clicked();
    void on_radioButton_10_clicked(bool checked);
    void on_radioButton_15_clicked(bool checked);
    void on_pushButton_47_clicked();
    void on_pushButton_46_clicked();
    void on_pushButton_48_clicked();
    void on_pushButton_45_clicked();
};

#endif // FRMMAIN_H
