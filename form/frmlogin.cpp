#pragma execution_character_set("utf-8")
#include "frmlogin.h"
#include "ui_frmlogin.h"
#include "quiwidget.h"
#include "frmmain.h"

extern QString project_id;
extern QStringList table_name;
extern QString title;
extern QString version;
extern QString companyName;

frmLogin::frmLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmLogin)
{
    ui->setupUi(this);
    this->initForm();
//    this->initStyle();
    QUIHelper::setFormInCenter(this);
}

frmLogin::~frmLogin()
{
    delete ui;
}

bool frmLogin::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->widgetTitle) {
        if (event->type() == QEvent::MouseButtonDblClick) {
            on_btnMenu_Max_clicked();
        }
    }
    return QWidget::eventFilter(watched, event);
}

void frmLogin::initForm()
{
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    ui->labTitle->setText(title + version);
    this->setWindowTitle(ui->labTitle->text());
    ui->widgetTitle->installEventFilter(this);
}


void frmLogin::initStyle()
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

void frmLogin::on_btnMenu_Min_clicked()
{
    this->showMinimized();
}

void frmLogin::on_btnMenu_Close_clicked()
{
    exit(0);
}

void frmLogin::on_btnMenu_Max_clicked()
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

void frmLogin::on_pushButton_clicked()
{
    QString user = ui->lineEdit->text();
    QString pass = ui->lineEdit_2->text();
    tableButton *tabtn = new tableButton(project_id, table_name[0]);
    frmMain *show_f = new frmMain;
    if(tabtn->login(user, pass)) {
        show_f->show();
        this->hide();
    }
}
