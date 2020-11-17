#pragma execution_character_set("utf-8")

#include "videopanel.h"
#include "qevent.h"
#include "qmenu.h"
#include "qlayout.h"
#include "qlabel.h"
#include "qtimer.h"
#include "qdebug.h"

VideoPanel::VideoPanel(QWidget *parent) : QWidget(parent)
{
    this->initControl();
    this->initForm();
    this->initMenu();
    this->show_video_all();
//    QTimer::singleShot(1000, this, SLOT(play_video_all()));
}

bool VideoPanel::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        VideoWidget *widget = (VideoWidget *) watched;
        if (!videoMax) {
            videoMax = true;
            hide_video_all();
            gridLayout->addWidget(widget, 0, 0);
            widget->setVisible(true);
        } else {
            videoMax = false;
            show_video_all();
        }
        widget->setFocus();
    } else if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = (QMouseEvent *)event;
        if (mouseEvent->button() == Qt::RightButton) {
            videoMenu->exec(QCursor::pos());
        }
    }
    return QWidget::eventFilter(watched, event);
}

QSize VideoPanel::sizeHint() const
{
    return QSize(800, 600);
}

QSize VideoPanel::minimumSizeHint() const
{
    return QSize(80, 60);
}

void VideoPanel::initControl()
{
    gridLayout = new QGridLayout;
    gridLayout->setSpacing(1);
    gridLayout->setMargin(0);
    gridLayout->setObjectName("gridLayout");
    this->setLayout(gridLayout);
}

void VideoPanel::initForm()
{
    //设置样式表
    QStringList qss;
    qss.append("QFrame{border:2px solid #000000;}");
//    qss.append("FFmpegWidget{border:2px solid #000000;}");
//    qss.append("FFmpegWidget:focus{border:2px solid #00BB9E;}");
    this->setStyleSheet(qss.join(""));
    videoMax = false;
    videoMenu = new QMenu(this);
    videoCount = 4;
    rightclickSt = true;
    videoType = "1_4";
    for (int i = 0; i < videoCount; i++) {
        btnSt.append(false);
        VideoWidget *widget = new VideoWidget;
        widget->setObjectName(QString("video%1").arg(i + 1));
        widget->installEventFilter(this);
        widget->setFocusPolicy(Qt::StrongFocus);
        widget->setBgText(QString("通道%1").arg(i + 1));
//        widget->setStyleSheet(QString::fromUtf8("border:1px solid #000000;"));
//        widget->setFlowEnable(false);
//        widget->setAlignment(Qt::AlignCenter);
        //二选一可以选择显示文字,也可以选择显示背景图片
//        widget->setText(QString("通道 %1").arg(i + 1));
        //widget->setPixmap(QPixmap(":/bg_novideo.png"));
        widgets.append(widget);
    }
}

void VideoPanel::initMenu()
{
//    QAction *actionPlay;        //播放动作
//    QAction *actionPause;       //暂停动作
//    QAction *actionStop;        //停止动作
    QAction *actionAllPlay = new QAction("全部播放", videoMenu);
    connect(actionAllPlay, SIGNAL(triggered(bool)), this, SLOT(allPlay()));
    QAction *actionAllStop = new QAction("全部停止", videoMenu);
    connect(actionAllStop, SIGNAL(triggered(bool)), this, SLOT(allStop()));
    QAction *actionPlay = new QAction("播放", videoMenu);
    connect(actionPlay, SIGNAL(triggered(bool)), this, SLOT(play()));
    QAction *actionPause = new QAction("暂停", videoMenu);
    connect(actionPause, SIGNAL(triggered(bool)), this, SLOT(pause()));
    QAction *actionStop = new QAction("停止", videoMenu);
    connect(actionStop, SIGNAL(triggered(bool)), this, SLOT(stop()));
    if(rightclickSt) {
        videoMenu->addAction(actionAllPlay);
        videoMenu->addAction(actionAllStop);
    }
    videoMenu->addAction(actionPlay);
    videoMenu->addAction(actionPause);
    videoMenu->addAction(actionStop);
//    videoMenu->addSeparator();
//    videoMenu->addAction("截图当前视频", this, SLOT(snapshot_video_one()));
//    videoMenu->addAction("截图所有视频", this, SLOT(snapshot_video_all()));
//    videoMenu->addSeparator();
//    QMenu *menu4 = videoMenu->addMenu("切换到4画面");
//    menu4->addAction("通道1-通道4", this, SLOT(show_video_4()));
//    menu4->addAction("通道5-通道8", this, SLOT(show_video_4()));
//    menu4->addAction("通道9-通道12", this, SLOT(show_video_4()));
//    menu4->addAction("通道13-通道16", this, SLOT(show_video_4()));
//    QMenu *menu6 = videoMenu->addMenu("切换到6画面");
//    menu6->addAction("通道1-通道6", this, SLOT(show_video_6()));
//    menu6->addAction("通道6-通道11", this, SLOT(show_video_6()));
//    menu6->addAction("通道11-通道16", this, SLOT(show_video_6()));
//    QMenu *menu8 = videoMenu->addMenu("切换到8画面");
//    menu8->addAction("通道1-通道8", this, SLOT(show_video_8()));
//    menu8->addAction("通道9-通道16", this, SLOT(show_video_8()));
//    QMenu *menu9 = videoMenu->addMenu("切换到9画面");
//    menu9->addAction("通道1-通道9", this, SLOT(show_video_9()));
//    menu9->addAction("通道8-通道16", this, SLOT(show_video_9()));
//    QMenu *menu13 = videoMenu->addMenu("切换到13画面");
//    menu13->addAction("通道1-通道13", this, SLOT(show_video_13()));
//    menu13->addAction("通道4-通道16", this, SLOT(show_video_13()));
//    videoMenu->addAction("切换到16画面", this, SLOT(show_video_16()));
//    videoMenu->addAction("切换到25画面", this, SLOT(show_video_25()));
//    videoMenu->addAction("切换到36画面", this, SLOT(show_video_36()));
//    videoMenu->addAction("切换到64画面", this, SLOT(show_video_64()));
}

void VideoPanel::full()
{
    if (actionFull->text() == "切换全屏模式") {
        emit fullScreen(true);
        actionFull->setText("切换正常模式");
    } else {
        emit fullScreen(false);
        actionFull->setText("切换全屏模式");
    }
    //执行全屏处理
}

void VideoPanel::poll()
{
    if (actionPoll->text() == "启动轮询视频") {
        actionPoll->setText("停止轮询视频");
    } else {
        actionPoll->setText("启动轮询视频");
    }
    //执行轮询处理
}

void VideoPanel::play_video_all()
{
}

void VideoPanel::snapshot_video_one()
{
}

void VideoPanel::snapshot_video_all()
{
}

void VideoPanel::setRightclickSt(bool sts)
{
    this->rightclickSt = sts;
    videoMenu->clear();
    initMenu();
}

void VideoPanel::show_video_all()
{
    if (videoType == "1_4") {
        change_video_4(0);
    } else if (videoType == "5_8") {
        change_video_4(4);
    } else if (videoType == "9_12") {
        change_video_4(8);
    } else if (videoType == "13_16") {
        change_video_4(12);
    } else if (videoType == "1_6") {
        change_video_6(0);
    } else if (videoType == "6_11") {
        change_video_6(5);
    } else if (videoType == "11_16") {
        change_video_6(10);
    } else if (videoType == "1_8") {
        change_video_8(0);
    } else if (videoType == "9_16") {
        change_video_8(8);
    } else if (videoType == "1_9") {
        change_video_9(0);
    } else if (videoType == "8_16") {
        change_video_9(7);
    } else if (videoType == "1_13") {
        change_video_13(0);
    } else if (videoType == "4_16") {
        change_video_13(3);
    } else if (videoType == "1_16") {
        change_video_16(0);
    } else if (videoType == "1_25") {
        change_video_25(0);
    } else if (videoType == "1_36") {
        change_video_36(0);
    } else if (videoType == "1_64") {
        change_video_64(0);
    }
}

void VideoPanel::show_video_4()
{
    videoMax = false;
    QString videoType;
    int index = 0;
    QAction *action = (QAction *)sender();
    QString name = action->text();
    if (name == "通道1-通道4") {
        index = 0;
        videoType = "1_4";
    } else if (name == "通道5-通道8") {
        index = 4;
        videoType = "5_8";
    } else if (name == "通道9-通道12") {
        index = 8;
        videoType = "9_12";
    } else if (name == "通道13-通道16") {
        index = 12;
        videoType = "13_16";
    }
    if (this->videoType != videoType) {
        this->videoType = videoType;
        change_video_4(index);
    }
}

void VideoPanel::show_video_6()
{
    videoMax = false;
    QString videoType;
    int index = 0;
    QAction *action = (QAction *)sender();
    QString name = action->text();
    if (name == "通道1-通道6") {
        index = 0;
        videoType = "1_6";
    } else if (name == "通道6-通道11") {
        index = 5;
        videoType = "6_11";
    } else if (name == "通道11-通道16") {
        index = 10;
        videoType = "11_16";
    }
    if (this->videoType != videoType) {
        this->videoType = videoType;
        change_video_6(index);
    }
}

void VideoPanel::show_video_8()
{
    videoMax = false;
    QString videoType;
    int index = 0;
    QAction *action = (QAction *)sender();
    QString name = action->text();
    if (name == "通道1-通道8") {
        index = 0;
        videoType = "1_8";
    } else if (name == "通道9-通道16") {
        index = 8;
        videoType = "9_16";
    }
    if (this->videoType != videoType) {
        this->videoType = videoType;
        change_video_8(index);
    }
}

void VideoPanel::show_video_9()
{
    videoMax = false;
    QString videoType;
    int index = 0;
    QAction *action = (QAction *)sender();
    QString name = action->text();
    if (name == "通道1-通道9") {
        index = 0;
        videoType = "1_9";
    } else if (name == "通道8-通道16") {
        index = 7;
        videoType = "8_16";
    }
    if (this->videoType != videoType) {
        this->videoType = videoType;
        change_video_9(index);
    }
}

void VideoPanel::show_video_13()
{
    QString videoType;
    int index = 0;
    QAction *action = (QAction *)sender();
    QString name = action->text();
    if (name == "通道1-通道13") {
        index = 0;
        videoType = "1_13";
    } else if (name == "通道4-通道16") {
        index = 3;
        videoType = "4_16";
    }
    if (this->videoType != videoType) {
        this->videoType = videoType;
        change_video_13(index);
    }
}

void VideoPanel::show_video_16()
{
    videoMax = false;
    QString videoType;
    int index = 0;
    videoType = "1_16";
    if (this->videoType != videoType) {
        this->videoType = videoType;
        change_video_16(index);
    }
}

void VideoPanel::show_video_25()
{
    videoMax = false;
    QString videoType;
    int index = 0;
    videoType = "1_25";
    if (this->videoType != videoType) {
        this->videoType = videoType;
        change_video_25(index);
    }
}

void VideoPanel::show_video_36()
{
    videoMax = false;
    QString videoType;
    int index = 0;
    videoType = "1_36";
    if (this->videoType != videoType) {
        this->videoType = videoType;
        change_video_36(index);
    }
}

void VideoPanel::show_video_64()
{
    videoMax = false;
    QString videoType;
    int index = 0;
    videoType = "1_64";
    if (this->videoType != videoType) {
        this->videoType = videoType;
        change_video_64(index);
    }
}

void VideoPanel::hide_video_all()
{
    for (int i = 0; i < videoCount; i++) {
        gridLayout->removeWidget(widgets.at(i));
        widgets.at(i)->setVisible(false);
    }
}

void VideoPanel::change_video(int index, int flag)
{
    int count = 0;
    int row = 0;
    int column = 0;
    for (int i = 0; i < videoCount; i++) {
        if (i >= index) {
            gridLayout->addWidget(widgets.at(i), row, column);
            widgets.at(i)->setVisible(true);
            count++;
            column++;
            if (column == flag) {
                row++;
                column = 0;
            }
        }
        if (count == (flag * flag)) {
            break;
        }
    }
}

void VideoPanel::change_video_4(int index)
{
    hide_video_all();
    change_video(index, 2);
}

void VideoPanel::change_video_6(int index)
{
    hide_video_all();
    if (index == 0) {
        gridLayout->addWidget(widgets.at(0), 0, 0, 2, 2);
        gridLayout->addWidget(widgets.at(1), 0, 2, 1, 1);
        gridLayout->addWidget(widgets.at(2), 1, 2, 1, 1);
        gridLayout->addWidget(widgets.at(3), 2, 2, 1, 1);
        gridLayout->addWidget(widgets.at(4), 2, 1, 1, 1);
        gridLayout->addWidget(widgets.at(5), 2, 0, 1, 1);
        for (int i = 0; i < 6; i++) {
            widgets.at(i)->setVisible(true);
        }
    } else if (index == 5) {
        gridLayout->addWidget(widgets.at(5), 0, 0, 2, 2);
        gridLayout->addWidget(widgets.at(6), 0, 2, 1, 1);
        gridLayout->addWidget(widgets.at(7), 1, 2, 1, 1);
        gridLayout->addWidget(widgets.at(8), 2, 2, 1, 1);
        gridLayout->addWidget(widgets.at(9), 2, 1, 1, 1);
        gridLayout->addWidget(widgets.at(10), 2, 0, 1, 1);
        for (int i = 5; i < 11; i++) {
            widgets.at(i)->setVisible(true);
        }
    } else if (index == 10) {
        gridLayout->addWidget(widgets.at(10), 0, 0, 2, 2);
        gridLayout->addWidget(widgets.at(11), 0, 2, 1, 1);
        gridLayout->addWidget(widgets.at(12), 1, 2, 1, 1);
        gridLayout->addWidget(widgets.at(13), 2, 2, 1, 1);
        gridLayout->addWidget(widgets.at(14), 2, 1, 1, 1);
        gridLayout->addWidget(widgets.at(15), 2, 0, 1, 1);
        for (int i = 10; i < 16; i++) {
            widgets.at(i)->setVisible(true);
        }
    }
}

void VideoPanel::change_video_8(int index)
{
    hide_video_all();
    if (index == 0) {
        gridLayout->addWidget(widgets.at(0), 0, 0, 3, 3);
        gridLayout->addWidget(widgets.at(1), 0, 3, 1, 1);
        gridLayout->addWidget(widgets.at(2), 1, 3, 1, 1);
        gridLayout->addWidget(widgets.at(3), 2, 3, 1, 1);
        gridLayout->addWidget(widgets.at(4), 3, 3, 1, 1);
        gridLayout->addWidget(widgets.at(5), 3, 2, 1, 1);
        gridLayout->addWidget(widgets.at(6), 3, 1, 1, 1);
        gridLayout->addWidget(widgets.at(7), 3, 0, 1, 1);
        for (int i = 0; i < 8; i++) {
            widgets.at(i)->setVisible(true);
        }
    } else if (index == 8) {
        gridLayout->addWidget(widgets.at(8), 0, 0, 3, 3);
        gridLayout->addWidget(widgets.at(9), 0, 3, 1, 1);
        gridLayout->addWidget(widgets.at(10), 1, 3, 1, 1);
        gridLayout->addWidget(widgets.at(11), 2, 3, 1, 1);
        gridLayout->addWidget(widgets.at(12), 3, 3, 1, 1);
        gridLayout->addWidget(widgets.at(13), 3, 2, 1, 1);
        gridLayout->addWidget(widgets.at(14), 3, 1, 1, 1);
        gridLayout->addWidget(widgets.at(15), 3, 0, 1, 1);
        for (int i = 8; i < 16; i++) {
            widgets.at(i)->setVisible(true);
        }
    }
}

void VideoPanel::change_video_9(int index)
{
    hide_video_all();
    change_video(index, 3);
}

void VideoPanel::change_video_13(int index)
{
    hide_video_all();
    if (index == 0) {
        gridLayout->addWidget(widgets.at(0), 0, 0, 1, 1);
        gridLayout->addWidget(widgets.at(1), 0, 1, 1, 1);
        gridLayout->addWidget(widgets.at(2), 0, 2, 1, 1);
        gridLayout->addWidget(widgets.at(3), 0, 3, 1, 1);
        gridLayout->addWidget(widgets.at(4), 1, 0, 1, 1);
        gridLayout->addWidget(widgets.at(5), 2, 0, 1, 1);
        gridLayout->addWidget(widgets.at(6), 1, 1, 2, 2);
        gridLayout->addWidget(widgets.at(7), 1, 3, 1, 1);
        gridLayout->addWidget(widgets.at(8), 2, 3, 1, 1);
        gridLayout->addWidget(widgets.at(9), 3, 0, 1, 1);
        gridLayout->addWidget(widgets.at(10), 3, 1, 1, 1);
        gridLayout->addWidget(widgets.at(11), 3, 2, 1, 1);
        gridLayout->addWidget(widgets.at(12), 3, 3, 1, 1);
        for (int i = 0; i < 13; i++) {
            widgets.at(i)->setVisible(true);
        }
    } else if (index == 3) {
        gridLayout->addWidget(widgets.at(3), 0, 0, 1, 1);
        gridLayout->addWidget(widgets.at(4), 0, 1, 1, 1);
        gridLayout->addWidget(widgets.at(5), 0, 2, 1, 1);
        gridLayout->addWidget(widgets.at(6), 0, 3, 1, 1);
        gridLayout->addWidget(widgets.at(7), 1, 0, 1, 1);
        gridLayout->addWidget(widgets.at(8), 2, 0, 1, 1);
        gridLayout->addWidget(widgets.at(9), 1, 1, 2, 2);
        gridLayout->addWidget(widgets.at(10), 1, 3, 1, 1);
        gridLayout->addWidget(widgets.at(11), 2, 3, 1, 1);
        gridLayout->addWidget(widgets.at(12), 3, 0, 1, 1);
        gridLayout->addWidget(widgets.at(13), 3, 1, 1, 1);
        gridLayout->addWidget(widgets.at(14), 3, 2, 1, 1);
        gridLayout->addWidget(widgets.at(15), 3, 3, 1, 1);
        for (int i = 3; i < 16; i++) {
            widgets.at(i)->setVisible(true);
        }
    }
}

void VideoPanel::change_video_16(int index)
{
    hide_video_all();
    change_video(index, 4);
}

void VideoPanel::change_video_25(int index)
{
    hide_video_all();
    change_video(index, 5);
}

void VideoPanel::change_video_36(int index)
{
    hide_video_all();
    change_video(index, 6);
}

void VideoPanel::change_video_64(int index)
{
    hide_video_all();
    change_video(index, 8);
}

void VideoPanel::pressed(int childIndex)
{
    if(urls.count() <= 0) {
        return ;
    }
    if(!btnSt.at(childIndex)) {
//        url = QString("http://ivi.bupt.edu.cn/hls/cctv%1.m3u8").arg(childIndex + 1);
        widgets.at(childIndex)->setUrl(urls.at(childIndex));
        widgets.at(childIndex)->open();
        btnSt[childIndex] = true;
    } else {
        widgets.at(childIndex)->close();
        btnSt[childIndex] = false;
    }
    qDebug("childIndex:%d", childIndex);
    qDebug("url:%s", qUtf8Printable(urls.at(childIndex)));
    qDebug("btnSt[%d]:%d", childIndex, btnSt.at(childIndex));
}

void VideoPanel::play()
{
    if(urls.count() <= 0) {
        return ;
    }
    for (int i = 0; i < widgets.count(); i++) {
        if( widgets.at(i)->hasFocus()) {
            widgets.at(i)->setUrl(urls.at(i));
            widgets.at(i)->open();
            btnSt[i] = true;
        }
    }
}

void VideoPanel::pause()
{
    for (int i = 0; i < widgets.count(); i++) {
        if( widgets.at(i)->hasFocus()) {
            widgets.at(i)->pause();
        }
    }
}

void VideoPanel::stop()
{
    for (int i = 0; i < widgets.count(); i++) {
        if( widgets.at(i)->hasFocus()) {
            widgets.at(i)->close();
            btnSt[i] = false;
        }
    }
}

void VideoPanel::allPlay()
{
    if(urls.count() <= 0) {
        return ;
    }
    for (int i = 0; i < widgets.count(); i++) {
        widgets.at(i)->setUrl(urls.at(i));
        widgets.at(i)->open();
        btnSt[i] = true;
    }
}

void VideoPanel::allStop()
{
    for (int i = 0; i < widgets.count(); i++) {
        widgets.at(i)->close();
        btnSt[i] = false;
    }
}

void VideoPanel::setUrls(QStringList urls)
{
    this->urls = urls;
}
