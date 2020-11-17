#pragma execution_character_set("utf-8")
#include "frmmain.h"
#include "frmlogin.h"
#include "ui_frmmain.h"
#include "quiwidget.h"
#include <QDebug>
#include <QUuid>

extern QString project_id;
extern QStringList table_name;
extern QString user;
extern QString title;
extern QString version;
extern QString companyName;
frmMain::frmMain(QWidget *parent) : QWidget(parent), ui(new Ui::frmMain)
{
    ui->setupUi(this);
//    this->initStyle();
    this->initBtn();
    this->initForm();
    this->initTableWidget();
    QUIHelper::setFormInCenter(this);
}

frmMain::~frmMain()
{
    delete ui;
    delete configIniWrite;
    delete tableview;
    delete tableview_2;
}

bool frmMain::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->widgetTitle) {
        if (event->type() == QEvent::MouseButtonDblClick) {
            on_btnMenu_Max_clicked();
        }
    }
    return QWidget::eventFilter(watched, event);
}


void frmMain::buttonClick()
{
    QPushButton *btn = (QPushButton *)sender();
    for (int i = 0; i < btns.count(); i++) {
        btns.at(i)->setChecked(btns.at(i) == btn);
    }
    if(btns.indexOf(btn) == 0) {
        ui->stackedWidgetMain->setCurrentIndex(9);
    } else if(btns.indexOf(btn) == 1) {
        ui->stackedWidgetMain->setCurrentIndex(10);
    } else if(btns.indexOf(btn) == 2) {
        ui->stackedWidgetMain->setCurrentIndex(1);
    } else if(btns.indexOf(btn) == 3) {
        ui->stackedWidgetMain->setCurrentIndex(11);
    } else if(btns.indexOf(btn) == 4) {
        ui->stackedWidgetMain->setCurrentIndex(5);
    } else if(btns.indexOf(btn) == 5) {
        ui->stackedWidgetMain->setCurrentIndex(6);
    } else if(btns.indexOf(btn) == 6) {
        ui->stackedWidgetMain->setCurrentIndex(8);
    } else if(btns.indexOf(btn) == 7) {
        logout();
    }
}


void frmMain::initForm()
{
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    ui->labTitle->setText(title + version);
    this->setWindowTitle(ui->labTitle->text());
    ui->label_223->setText("软件名称：" + title);
    ui->label_4->setText("软件名称：" + title);
    ui->label_224->setText("软件版本：" + version);
    ui->label_28->setText("软件版本：" + version);
    ui->widgetTitle->installEventFilter(this);
    ui->widgetBtn->setProperty("flag", "btn");
    tableview = new tableButton(project_id, table_name[0], ui->tableView);
    ui->groupBox_10->setTitle(tableview->updateData());
//    tableview_2 = new tableButton(project_id, table_name[1], ui->tableView_2);
//    ui->groupBox_11->setTitle(tableview_2->updateData());
    configIniWrite = new QSettings("configuration.ini", QSettings::IniFormat);
    //摄像机地址加载
    QStringList urls;
    urls << "http://ivi.bupt.edu.cn/hls/cctv1.m3u8";
    urls << "http://ivi.bupt.edu.cn/hls/cctv2.m3u8";
    urls << "http://ivi.bupt.edu.cn/hls/cctv3.m3u8";
    urls << "http://ivi.bupt.edu.cn/hls/cctv4.m3u8";
    ui->widget_4->setUrls(urls);
    ui->widget_5->setUrls(urls);
    ui->widget_5->setRightclickSt(false);
//    ui->videoPlayback->setTextCh1();
    ui->stackedWidgetMain->setCurrentIndex(0);
}


void frmMain::initStyle()
{
    QStringList qss;
    //全局无焦点虚边框,全局文字颜色,全局字号
//    qss.append(QString("*{outline:0px;color:#ABD6FF;font:%1pt;}").arg(12));
    qss.append(QString("QLabel#labTitle{font:%1pt;}").arg(14));
    qss.append(QString("QWidget[flag=\"check\"] QAbstractButton{font:%1pt;}").arg(15));
    //主界面顶部栏
    qss.append("QWidget#widgetTitle{background:qlineargradient"
               "(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 #0973AB,stop:1 #098DCE);}"
               "QToolButton::menu-indicator{image:None;}");
    //主界面顶部左上角logo
    qss.append("QLabel#labLogo{image:url(:/image/logo.png);}");
    ui->labLogo->setMinimumWidth(100);
    //主界面顶部标题流线型背景
    qss.append("QLabel#labTitle{border-image:url(:/image/bg_title.png);}");
    //主界面顶部右上角
    qss.append("QWidget#widgetMenu QAbstractButton{"
               "border:0px solid #FF0000;}");
    qss.append("QWidget#widgetMenu QAbstractButton:hover,"
               "QWidget#widgetMenu QAbstractButton:pressed{"
               "background:#067DB8;}");
#if 0
    //主界面
    qss.append("QWidget#widgetMain{background-color:rgba(29,34,40,220);}");
    //主界面堆栈窗体
    qss.append("QWidget#stackedWidgetMain{background-color:rgba(29,34,40,240);}");
    //操作按钮面板
    qss.append("QAbstractButton{background-color:rgba(29,34,40,255);}");
    qss.append("QAbstractButton{"
               "border-radius:5px;border:none;color:#F7F7F7;"
               "background-color:rgba(56,60,69,255);}");
    qss.append("QAbstractButton:hover,"
               "QAbstractButton:pressed{"
               "border:2px solid #03C5ED;"
               "background-color:rgba(24,189,155,100);}");
    //右下角操作按钮面板
    qss.append("QWidget[flag=\"arming\"]{background-color:rgba(29,34,40,230);}");
    qss.append("QWidget[flag=\"arming\"] QAbstractButton{"
               "border-radius:5px;border:none;color:#F7F7F7;"
               "background-color:rgba(9,115,171,255);}");
    qss.append("QWidget[flag=\"arming\"] QAbstractButton:hover,"
               "QWidget[flag=\"arming\"] QAbstractButton:pressed{"
               "border:2px solid #03C5ED;"
               "background-color:rgba(37,116,221,100);}");
    //返回按钮样式,所有子界面共用
    qss.append("QWidget[flag=\"return\"] QAbstractButton{"
               "background-color:rgba(7,48,73,100);"
               "border-radius:5px;border:2px solid #03C5ED;}");
    qss.append("QWidget[flag=\"return\"] QAbstractButton:hover,"
               "QWidget[flag=\"return\"] QAbstractButton:pressed{"
               "background-color:rgba(24,189,155,100);}");
    //按钮复选框样式
    qss.append("QWidget[flag=\"check\"] QAbstractButton{"
               "border-image:url(:/image/btn_check_off1.png);}");
    qss.append("QWidget[flag=\"check\"] QAbstractButton:checked{"
               "border-image:url(:/image/btn_check_on1.png);}");
    //表格样式,所有子界面共用
    qss.append("QTableView{background-color:rgba(16,44,56,150);border:1px solid #617D90;"
               "selection-background-color:rgba(0,187,226,100);"
               "alternate-background-color:rgba(49,88,105,150);"
               "selection-color:#FFFFFF;gridline-color:#517DA5;}");
    //表格头部样式,所有子界面共用
    qss.append(QString("QHeaderView::section,QTableCornerButton:section{"
                       "font:%1pt;background:#102C38;border:1px solid #617D90;}").arg(14));
    //滑块条样式
    qss.append("QSlider::groove:horizontal{background:rgba(29,34,56,150);"
               "height:16px;border-radius:8px;}"
               "QSlider::add-page:horizontal{background:rgba(29,34,56,150);"
               "height:16px;border-radius:8px;}"
               "QSlider::sub-page:horizontal{background:rgba(37,156,210,150);"
               "height:16px;border-radius:8px;}"
               "QSlider::handle:horizontal{width:30px;margin-top:-7px;"
               "margin-bottom:-7px;border-radius:14px;"
               "background:qradialgradient(spread:pad,cx:0.5,cy:0.5,"
               "radius:0.5,fx:0.5,fy:0.5,stop:0.6 #FFFFFF,stop:0.8 rgba(250,250,250,100));}");
    //滚动条样式
    qss.append("QScrollBar:vertical{background:rgba(150,150,150,100);padding:0px;border-radius:10px;min-width:20px;max-width:20px;}"
               "QScrollBar::handle:vertical{background:#617D90;min-height:120px;border-radius:10px;}"
               "QScrollBar::handle:vertical:hover{background:#1ABC9C;}"
               "QScrollBar::handle:vertical:pressed{background:#1ABC9C;}"
               "QScrollBar::add-page:vertical{background:none;}"
               "QScrollBar::sub-page:vertical{background:none;}"
               "QScrollBar::add-line:vertical{background:none;}"
               "QScrollBar::sub-line:vertical{background:none;}");
#endif
    qApp->setStyleSheet(qss.join(""));
}

void frmMain::initBtn()
{
    QString color = "#F7F7F7";
    int iconSize = 20;
    int iconWidth = 40;
    int iconHeight = 30;
    QFont btnFont(QUIConfig::FontName, QUIConfig::FontSize + 4);
    QList<QChar> pixChar;
    pixChar << 0xf03d << 0xf16a << 0xf010 << 0xf13e;
    pixChar << 0xf085 << 0xf007 << 0xf073 << 0xf08b;
    QStringList btnNm;
    btnNm << "视频监控" << "视频回放" << "日志查询" << "门禁管理"
          << "系统设置" << "用户管理" << "关于软件" << "用户注销";
    btns << ui->btn1 << ui->btn2 << ui->btn3 << ui->btn4 ;
    btns << ui->btn5 << ui->btn6 << ui->btn7 << ui->btn8 ;
    for (int i = 0; i < btns.count(); i++) {
        if (i >= 8) {
            iconWidth = 30;
        }
        QPixmap pix = IconHelper::Instance()->getPixmap(color, pixChar.at(i), iconSize, iconWidth, iconHeight);
        QPushButton *btn = btns.at(i);
        btn->setText(btnNm.at(i));
        btn->setIconSize(QSize(iconWidth, iconHeight));
        btn->setIcon(QIcon(pix));
        btn->setFont(btnFont);
        btn->setText(btn->text() + " ");
        connect(btn, SIGNAL(pressed()), this, SLOT(buttonClick()));
    }
}

void frmMain::initTableWidget()
{
//    connect(ui->navListView, SIGNAL(pressed(int)), ui->widget_4, SLOT(pressed(int)));
    QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy4.setHorizontalStretch(0);
    sizePolicy4.setVerticalStretch(0);
    sizePolicy4.setHeightForWidth(ui->dateTimeEdit->sizePolicy().hasHeightForWidth());
    ui->dateTimeEdit->setSizePolicy(sizePolicy4);
    ui->dateTimeEdit->setCalendarPopup(true);
    sizePolicy4.setHeightForWidth(ui->dateTimeEdit_2->sizePolicy().hasHeightForWidth());
    ui->dateTimeEdit_2->setSizePolicy(sizePolicy4);
    ui->dateTimeEdit_2->setCalendarPopup(true);
    ui->dateTimeEdit->setDate(QDate::currentDate());
    ui->dateTimeEdit_2->setDate(QDate::currentDate().addDays(1));
    ui->dateTimeEdit->calendarWidget()->setGridVisible(true);
    ui->dateTimeEdit_2->calendarWidget()->setGridVisible(true);
    ui->dateTimeEdit->calendarWidget()->setLocale(QLocale::Chinese);
    ui->dateTimeEdit_2->calendarWidget()->setLocale(QLocale::Chinese);
    doorCollection << "外门" << "内门1" << "内门2" << "内门3" << "内门4" << "内门5";
    doorNum = 0;
    fromCount = 1;
    int tmp =  configIniWrite->value("fromCount/fromCount").toInt();
    if(tmp > 0) {
        fromCount = tmp;
    }
    qDebug("fromCount:%d", fromCount);
    btnSts = {false, false, false, false, false, false
              , false, false, false, false, false, false
             };
    ui->tableView_4->setModel(getLocalData());
    ui->tableView_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->stackedWidget->setCurrentIndex(0);
}

void frmMain::logout()
{
    int ret =  QUIWidget::showMessageBoxQuestion("确定要注销登录？");
    if(ret) {
        frmLogin *f_login = new frmLogin;
        f_login->show();
        this->hide();
    } else {
    }
}

void frmMain::on_btnMenu_Min_clicked()
{
    showMinimized();
}

void frmMain::on_btnMenu_Max_clicked()
{
    static bool max = false;
    static QRect location = this->geometry();
    if (max) {
        this->setGeometry(location);
    } else {
        location = this->geometry();
        this->setGeometry(qApp->desktop()->availableGeometry());
    }
    this->setProperty("canMove", max);
    max = !max;
}

void frmMain::on_btnMenu_Close_clicked()
{
    exit(0);
}


void frmMain::on_pushButton_2_clicked()
{
    int result = tableview->addData();
    if(result) {
        tableview->updateData();
    }
}

void frmMain::on_pushButton_5_clicked()
{
    QString  data = tableview->updateData();
    if(!data.isNull()) {
        QUIWidget::showMessageBoxInfo("更新完成!", 3);
        ui->groupBox_10->setTitle(data);
    } else {
        QUIWidget::showMessageBoxInfo("更新失败!", 3);
    }
}

void frmMain::on_pushButton_3_clicked()
{
    int result = tableview->editData();
    if(result) {
        tableview->updateData();
    }
}
void frmMain::on_pushButton_4_clicked()
{
    int result = tableview->deleteData();
    if(result) {
        tableview->updateData();
    }
}
void frmMain::on_pushButton_7_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save", ui->groupBox_10->title(),
                       tr("Excel Files (*.xls)"));
    if (filePath.isEmpty()) {
        QUIWidget::showMessageBoxError("导出失败!", 3) ;
        return;
    }
    tableview->exportData(filePath);
}




void frmMain::on_pushButton_6_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "打开", "",
                       tr("Excel Files (*.xls)"));
    if (filePath.isEmpty()) {
        QUIWidget::showMessageBoxError("导入失败!", 3) ;
        return;
    }
    int result = tableview->importData(filePath);
    if(result) {
        tableview->updateData();
    }
}

void frmMain::on_pushButton_8_clicked()
{
    int result = tableview_2->addData();
    if(result) {
        tableview->updateData();
    }
}

void frmMain::on_pushButton_9_clicked()
{
    int result = tableview_2->editData();
    if(result) {
        tableview->updateData();
    }
}

void frmMain::on_pushButton_10_clicked()
{
    int result = tableview_2->deleteData();
    if(result) {
        tableview->updateData();
    }
}

void frmMain::on_pushButton_11_clicked()
{
    if(!tableview_2->updateData().isNull()) {
        QUIWidget::showMessageBoxInfo("更新完成!", 3);
    } else {
        QUIWidget::showMessageBoxInfo("更新失败!", 3);
    }
}

void frmMain::on_pushButton_13_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save", ui->groupBox_11->title(),
                       tr("Excel Files (*.xls)"));
    if (filePath.isEmpty()) {
        QUIWidget::showMessageBoxError("导出失败!", 3) ;
        return;
    }
    tableview_2->exportData(filePath);
}

void frmMain::on_pushButton_12_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "打开", "",
                       tr("Excel Files (*.xls)"));
    if (filePath.isEmpty()) {
        QUIWidget::showMessageBoxError("导入失败!", 3) ;
        return;
    }
    int result = tableview_2->importData(filePath);
    if(result) {
        tableview->updateData();
    }
}

void frmMain::on_pushButton_clicked()
{
    tableview->editPass(ui->oldPassword->text(), ui->password->text(), ui->confirmPassword->text());
}


void frmMain::on_pushButton_20_clicked()
{
    int result = tableview->conditionQuery();
    if(result) {
        QUIHelper::showMessageBoxInfo("查询成功!", 3);
    } else {
        QUIHelper::showMessageBoxError("查询失败!", 3);
    }
}

void frmMain::on_pushButton_42_clicked()
{
    if(doorNum <= 0) {
        doorNum = 5;
    }
    ui->label_18->setText(QString("%1/6").arg(doorNum + 1));
    ui->pushButton_41->setText(doorCollection.at(doorNum));
    --doorNum;
}

void frmMain::on_pushButton_43_clicked()
{
    if(doorNum >= 5) {
        doorNum = 0;
    }
    ui->label_18->setText(QString("%1/6").arg(doorNum + 1));
    ui->pushButton_41->setText(doorCollection.at(doorNum));
    ++doorNum;
}

void frmMain::on_pushButton_41_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->label_20->setStyleSheet(QString::fromUtf8("border-image: url(:/image/authoring.png);background: transparent;"));
    ui->label_21->setStyleSheet("color: rgb(25, 118, 180);\nfont: 75 18pt '微软雅黑';");
    ui->label_21->setText("正在审核中……");
    Sleep(3000);
    ui->label_20->setStyleSheet(QString::fromUtf8("border-image: url(:/image/authorok.png);background: transparent;"));
    ui->label_21->setStyleSheet("color: rgb(1, 246, 15);\nfont: 75 18pt '微软雅黑';");
    ui->label_21->setText("审核成功");
}

void frmMain::on_pushButton_44_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void frmMain::on_pushButton_22_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void frmMain::on_pushButton_21_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void frmMain::on_pushButton_25_clicked()
{
    ++fromCount;
    modifySts = true;
    ui->stackedWidget->setCurrentIndex(1);
    qDebug("fromCount:%d", fromCount);
}

void frmMain::on_pushButton_26_clicked()
{
    int row = ui->tableView_4->currentIndex().row();
    QModelIndex index = ui->tableView_4->model()->index(row, 0); //选中行第一列的内容
    QString user_num = ui->tableView_4->model()->data(index).toString();
    qDebug("user_num：%s", qUtf8Printable(user_num));
    QString user_name = configIniWrite->value(qUtf8Printable(QString("%1/name").arg(user_num))).toString();
    QString user_pass = configIniWrite->value(qUtf8Printable(QString("%1/pass").arg(user_num))).toString();
    btnSts[0] = !configIniWrite->value(qUtf8Printable(QString("%1/btn1").arg(user_num))).toBool();
    btnSts[1] = !configIniWrite->value(qUtf8Printable(QString("%1/btn2").arg(user_num))).toBool();
    btnSts[2] = !configIniWrite->value(qUtf8Printable(QString("%1/btn3").arg(user_num))).toBool();
    btnSts[3] = !configIniWrite->value(qUtf8Printable(QString("%1/btn4").arg(user_num))).toBool();
    btnSts[4] = !configIniWrite->value(qUtf8Printable(QString("%1/btn5").arg(user_num))).toBool();
    btnSts[5] = !configIniWrite->value(qUtf8Printable(QString("%1/btn6").arg(user_num))).toBool();
    btnSts[6] = !configIniWrite->value(qUtf8Printable(QString("%1/btn7").arg(user_num))).toBool();
    btnSts[7] = !configIniWrite->value(qUtf8Printable(QString("%1/btn8").arg(user_num))).toBool();
    btnSts[8] = !configIniWrite->value(qUtf8Printable(QString("%1/btn9").arg(user_num))).toBool();
    btnSts[9] = !configIniWrite->value(qUtf8Printable(QString("%1/btn10").arg(user_num))).toBool();
    ui->lineEdit_2->setText(user_num);
    ui->lineEdit_3->setText(user_name);
    ui->lineEdit_4->setText(user_pass);
    ui->lineEdit_5->setText(user_pass);
    on_pushButton_24_clicked();
    on_pushButton_28_clicked();
    on_pushButton_29_clicked();
    on_pushButton_30_clicked();
    on_pushButton_31_clicked();
    on_pushButton_32_clicked();
    on_pushButton_33_clicked();
    on_pushButton_34_clicked();
    on_pushButton_35_clicked();
    on_pushButton_36_clicked();
    modifySts = false;
    ui->stackedWidget->setCurrentIndex(1);
    qDebug("fromCount:%d", fromCount);
}

void frmMain::on_pushButton_27_clicked()
{
    int row = ui->tableView_4->currentIndex().row();
//    QModelIndex index = ui->tableView_4->model()->index(row, 0); //选中行第一列的内容
//    QString user_num = ui->tableView_4->model()->data(index).toString();
    --fromCount;
    configIniWrite->setValue("fromCount/fromCount", fromCount);
    configIniWrite->remove(qUtf8Printable(QString("table/%1").arg(row)));
    ui->tableView_4->setModel(getLocalData());
    ui->tableView_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    qDebug("fromCount:%d", fromCount);
}

void frmMain::Sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime ) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void frmMain::on_pushButton_40_clicked()
{
    QString user_num;
    QString user_name;
    QString user_pass;
    if(ui->lineEdit_2->text() == "") {
        QUIHelper::showMessageBoxInfo("请填写用户编号!", 3);
        return ;
    } else if(ui->lineEdit_3->text() == "") {
        QUIHelper::showMessageBoxInfo("请填写用户名称!", 3);
        return ;
    } else if(ui->lineEdit_4->text() == "") {
        QUIHelper::showMessageBoxInfo("请填写用户密码!", 3);
        return ;
    } else if(ui->lineEdit_5->text() == "") {
        QUIHelper::showMessageBoxInfo("请填写确认密码!", 3);
        return ;
    } else if(ui->lineEdit_5->text() != ui->lineEdit_4->text()) {
        QUIHelper::showMessageBoxInfo("用户密码和确认吗密码不一致!", 3);
        return ;
    }
    user_num = ui->lineEdit_2->text();
    user_name = ui->lineEdit_3->text();
    user_pass = ui->lineEdit_4->text();
    if(modifySts) {
        configIniWrite->setValue(qUtf8Printable(QString("table/%1").arg(fromCount)), user_num);
    }
    configIniWrite->setValue(qUtf8Printable(QString("%1/num").arg(user_num)), user_num);
    configIniWrite->setValue(qUtf8Printable(QString("%1/name").arg(user_num)), user_name);
    configIniWrite->setValue(qUtf8Printable(QString("%1/pass").arg(user_num)), user_pass);
    configIniWrite->setValue(qUtf8Printable(QString("%1/btn1").arg(user_num)), btnSts[0]);
    configIniWrite->setValue(qUtf8Printable(QString("%1/btn2").arg(user_num)), btnSts[1]);
    configIniWrite->setValue(qUtf8Printable(QString("%1/btn3").arg(user_num)), btnSts[2]);
    configIniWrite->setValue(qUtf8Printable(QString("%1/btn4").arg(user_num)), btnSts[3]);
    configIniWrite->setValue(qUtf8Printable(QString("%1/btn5").arg(user_num)), btnSts[4]);
    configIniWrite->setValue(qUtf8Printable(QString("%1/btn6").arg(user_num)), btnSts[5]);
    configIniWrite->setValue(qUtf8Printable(QString("%1/btn7").arg(user_num)), btnSts[6]);
    configIniWrite->setValue(qUtf8Printable(QString("%1/btn8").arg(user_num)), btnSts[7]);
    configIniWrite->setValue(qUtf8Printable(QString("%1/btn9").arg(user_num)), btnSts[8]);
    configIniWrite->setValue(qUtf8Printable(QString("%1/btn10").arg(user_num)), btnSts[9]);
    configIniWrite->setValue(qUtf8Printable(QString("%1/btn11").arg(user_num)), btnSts[10]);
    configIniWrite->setValue(qUtf8Printable(QString("%1/btn12").arg(user_num)), btnSts[11]);
    configIniWrite->setValue("fromCount/fromCount", fromCount);
    ui->tableView_4->setModel(getLocalData());
    ui->tableView_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->stackedWidget->setCurrentIndex(0);
    return ;
}

void frmMain::on_pushButton_24_clicked()
{
    if(!btnSts.at(0)) {
        ui->pushButton_24->setStyleSheet(QString::fromUtf8("border-image: url(:/image/btn_check_on2.png);"));
        btnSts[0] = true;
    } else {
        ui->pushButton_24->setStyleSheet(QString::fromUtf8("border-image: url(:/image/btn_check_off1.png);"));
        btnSts[0] = false;
    }
}

void frmMain::on_pushButton_28_clicked()
{
    if(!btnSts.at(1)) {
        ui->pushButton_28->setStyleSheet(QString::fromUtf8("border-image: url(:/image/btn_check_on2.png);"));
        btnSts[1] = true;
    } else {
        ui->pushButton_28->setStyleSheet(QString::fromUtf8("border-image: url(:/image/btn_check_off1.png);"));
        btnSts[1] = false;
    }
}

void frmMain::on_pushButton_29_clicked()
{
    if(!btnSts.at(2)) {
        ui->pushButton_29->setStyleSheet(QString::fromUtf8("border-image: url(:/image/btn_check_on2.png);"));
        btnSts[2] = true;
    } else {
        ui->pushButton_29->setStyleSheet(QString::fromUtf8("border-image: url(:/image/btn_check_off1.png);"));
        btnSts[2] = false;
    }
}

void frmMain::on_pushButton_30_clicked()
{
    if(!btnSts.at(3)) {
        ui->pushButton_30->setStyleSheet(QString::fromUtf8("border-image: url(:/image/btn_check_on2.png);"));
        btnSts[3] = true;
    } else {
        ui->pushButton_30->setStyleSheet(QString::fromUtf8("border-image: url(:/image/btn_check_off1.png);"));
        btnSts[3] = false;
    }
}

void frmMain::on_pushButton_31_clicked()
{
    if(!btnSts.at(4)) {
        ui->pushButton_31->setStyleSheet(QString::fromUtf8("border-image: url(:/image/btn_check_on1.png);"));
        btnSts[4] = true;
    } else {
        ui->pushButton_31->setStyleSheet(QString::fromUtf8("border-image: url(:/image/btn_check_off1.png);"));
        btnSts[4] = false;
    }
}

void frmMain::on_pushButton_32_clicked()
{
    if(!btnSts.at(5)) {
        ui->pushButton_32->setStyleSheet(QString::fromUtf8("border-image: url(:/image/btn_check_on1.png);"));
        btnSts[5] = true;
    } else {
        ui->pushButton_32->setStyleSheet(QString::fromUtf8("border-image: url(:/image/btn_check_off1.png);"));
        btnSts[5] = false;
    }
}

void frmMain::on_pushButton_33_clicked()
{
    if(!btnSts.at(6)) {
        ui->pushButton_33->setStyleSheet(QString::fromUtf8("border-image: url(:/image/btn_check_on1.png);"));
        btnSts[6] = true;
    } else {
        ui->pushButton_33->setStyleSheet(QString::fromUtf8("border-image: url(:/image/btn_check_off1.png);"));
        btnSts[6] = false;
    }
}

void frmMain::on_pushButton_34_clicked()
{
    if(!btnSts.at(7)) {
        ui->pushButton_34->setStyleSheet(QString::fromUtf8("border-image: url(:/image/btn_check_on1.png);"));
        btnSts[7] = true;
    } else {
        ui->pushButton_34->setStyleSheet(QString::fromUtf8("border-image: url(:/image/btn_check_off1.png);"));
        btnSts[7] = false;
    }
}

void frmMain::on_pushButton_35_clicked()
{
    if(!btnSts.at(8)) {
        ui->pushButton_35->setStyleSheet(QString::fromUtf8("border-image: url(:/image/btn_check_on1.png);"));
        btnSts[8] = true;
    } else {
        ui->pushButton_35->setStyleSheet(QString::fromUtf8("border-image: url(:/image/btn_check_off1.png);"));
        btnSts[8] = false;
    }
}

void frmMain::on_pushButton_36_clicked()
{
    if(!btnSts.at(9)) {
        ui->pushButton_36->setStyleSheet(QString::fromUtf8("border-image: url(:/image/btn_check_on1.png);"));
        btnSts[9] = true;
    } else {
        ui->pushButton_36->setStyleSheet(QString::fromUtf8("border-image: url(:/image/btn_check_off1.png);"));
        btnSts[9] = false;
    }
}

QStandardItemModel *frmMain::getLocalData()
{
    int userCount = 0;
    QString user_name;
    QList<QString> userNames;
    QList<QString> userLabels;
    QList<QString> userAuthority;
    userAuthority << "用户" << "日志" << "设置" << "监控";
    userLabels << "num" << "name" << "btn1" << "btn2" << "btn3" << "btn4";
    userCount = configIniWrite->value("fromCount/fromCount").toInt();
    for (int i = 0; i < userCount; i++) {
        userNames << configIniWrite->value(qUtf8Printable(QString("table/%1").arg(1))).toString();
    }
//    qDebug("userNames:%s", qUtf8Printable(userNames));
    QStringList fromTableName = {"用户编号", "用户名称", "用户权限"};
    QStandardItemModel *m_model = new QStandardItemModel;
    m_model->setHorizontalHeaderLabels(fromTableName);
    for(int i = 0; i < userCount; i++) {
        QString user_authority = "";
        user_name = configIniWrite->value(qUtf8Printable(QString("table/%1").arg(i))).toString();
        m_model->setItem(i, 0, new QStandardItem(
                             configIniWrite->value(
                                 qUtf8Printable(QString("%1/%2")
                                                .arg(user_name).arg(userLabels.at(0)))).toString()));
        m_model->setItem(i, 1, new QStandardItem(
                             configIniWrite->value(
                                 qUtf8Printable(QString("%1/%2")
                                                .arg(user_name).arg(userLabels.at(1)))).toString()));
        if(configIniWrite->value(qUtf8Printable(QString("%1/%2").arg(user_name).arg(userLabels.at(2)))).toBool()) {
            user_authority += "监控";
        }
        if(configIniWrite->value(qUtf8Printable(QString("%1/%2").arg(user_name).arg(userLabels.at(3)))).toBool()) {
            user_authority += "/设置";
        }
        if(configIniWrite->value(qUtf8Printable(QString("%1/%2").arg(user_name).arg(userLabels.at(4)))).toBool()) {
            user_authority += "/日志";
        }
        if(configIniWrite->value(qUtf8Printable(QString("%1/%2").arg(user_name).arg(userLabels.at(5)))).toBool()) {
            user_authority += "/用户";
        }
        if(user_authority.mid(0, 1) == "/") {
            user_authority = user_authority.mid(1);
        }
        m_model->setItem(i, 2, new QStandardItem(user_authority));
    }
    return m_model;
}

void frmMain::on_pushButton_39_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void frmMain::on_pushButton_23_clicked()
{
    int tmp = configIniWrite->value("fromCount/fromCount").toInt();
    if(tmp > 0) {
        fromCount = tmp;
    }
    ui->tableView_4->setModel(getLocalData());
    ui->tableView_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    qDebug("fromCount:%d", fromCount);
}

void frmMain::on_pushButton_16_clicked()
{
    QString datetm = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    ui->listWidget->addItem(datetm);
    VideoCh::VideoData data1, data2, data3, data4;
    data1.startX = 30;
    data1.length = 150;
    data2.startX = 200;
    data2.length = 50;
    data3.startX = 280;
    data3.length = 100;
    ui->videoPlayback->setDatas1(QList<VideoCh::VideoData>() << data1 << data2 << data3);
    data4.startX = 30;
    data4.length = 380;
    ui->videoPlayback->setDatas2(QList<VideoCh::VideoData>() << data4);
    ui->videoPlayback->setDatas3(QList<VideoCh::VideoData>() << data4);
    ui->videoPlayback->setDatas4(QList<VideoCh::VideoData>() << data4);
}

void frmMain::on_pushButton_19_clicked()
{
    ui->listWidget->clear();
}

void frmMain::on_pushButton_18_clicked()
{
//    int index = ui->listWidget->currentIndex();
    QList<QListWidgetItem*> list = ui->listWidget->selectedItems();
    if(list.size() == 0) {
        return;
    }
    QListWidgetItem* sel = list[0];
    if (sel) {
        int r = ui->listWidget->row(sel);
        ui->listWidget->takeItem(r);
    }
}

void frmMain::on_pushButton_17_clicked()
{
    QString filepath = QFileDialog::getSaveFileName(this, tr("选择文件路径"), "videoPlayback.wmv", tr("视频文件(*.mp4 *.wmv *.avi)"));
    if(filepath.isNull()) {
        return ;
    }
    QFile::copy("videoPlayback.wmv", filepath);
}

void frmMain::on_radioButton_10_clicked(bool checked)
{
    QString ip = "192.168.1.125";
    QString ip1 = "255.255.255.0";
    QString ip2 = "192.168.1.1";
    QString ip3 = "192.168.1.1";
    if(checked == true) {
        ui->lineEdit_9->setText(ip);
        ui->lineEdit_17->setText(ip1);
        ui->lineEdit_18->setText(ip2);
        ui->lineEdit_20->setText(ip3);
    }
}

void frmMain::on_radioButton_15_clicked(bool checked)
{
    if(checked) {
        ui->lineEdit_9->clear();
        ui->lineEdit_18->clear();
        ui->lineEdit_17->clear();
        ui->lineEdit_20->clear();
    }
}

void frmMain::on_pushButton_47_clicked()
{
    ui->stackedWidgetMain->setCurrentIndex(7);
}

void frmMain::on_pushButton_46_clicked()
{
    QUIHelper::showMessageBoxInfo("信息修改成功!", 3);
}

void frmMain::on_pushButton_48_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("选择图像文件"), "", tr("图像文件(*.jpg *.png *.bmp)"));
    if(filePath.isNull()) {
        return ;
    }
    ui->pushButton_48->setStyleSheet(QString::fromUtf8("border-image: url(%1);background: transparent;").arg(filePath));
}

void frmMain::on_pushButton_45_clicked()
{
    QUIHelper::showMessageBoxInfo("设置成功!", 3);
}
