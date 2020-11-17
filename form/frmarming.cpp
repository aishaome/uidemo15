#include "frmarming.h"
#include "ui_frmarming.h"
#include "quiwidget.h"

frmArming *frmArming::self = NULL;
frmArming *frmArming::Instance()
{
    if (!self) {
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        if (!self) {
            self = new frmArming;
        }
    }

    return self;
}

frmArming::frmArming(QWidget *parent) : QWidget(parent), ui(new Ui::frmArming)
{
    ui->setupUi(this);
    this->initForm();
    this->initPanel();
}

frmArming::~frmArming()
{
    delete ui;
}

void frmArming::initForm()
{
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    this->setWindowTitle("选择防区子系统");

    ui->widgetSubsystem->setProperty("flag", "check");
    ui->widgetDefence->setProperty("flag", "check");
    ui->widgetReturn->setProperty("flag", "return");

    QList<QPushButton *> btns = ui->widgetSubsystem->findChildren<QPushButton *>();
    foreach (QPushButton *btn, btns) {
        btn->setCheckable(true);
    }

    btns = ui->widgetDefence->findChildren<QPushButton *>();
    foreach (QPushButton *btn, btns) {
        btn->setCheckable(true);
    }

    QString qss = "border:none;background-color:rgba(29,34,40,220);";
    ui->widgetSubsystem->setStyleSheet(qss);
    ui->widgetDefence->setStyleSheet(qss);
}

void frmArming::initPanel()
{
    //加载设备面板
    qDeleteAll(frms);
    frms.clear();

    for (int i = 0; i < 35; i++) {
        QPushButton *frm = new QPushButton;
        frm->setText(QString("防区%1").arg(i + 10, 3, 10, QChar('0')));
        frm->setFixedHeight(50);
        frm->setMinimumWidth(100);
        frm->setCheckable(true);
        frms.append(frm);
    }

    ui->widgetDefence->setAutoWidth(true);
    ui->widgetDefence->setWidget(frms, 5);
    ui->widgetDefence->setMargin(9);
    ui->widgetDefence->setSpace(6);
}

void frmArming::on_btnOk_clicked()
{
    //执行对应的动作
    this->close();
}

void frmArming::on_btnCancel_clicked()
{
    this->close();
}
