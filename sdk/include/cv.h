#ifndef CV_H
#define CV_H

#include <QWidget>
#include <QLabel>
class CV : public QWidget
{
    Q_OBJECT

public:
    CV(QWidget *parent = 0);
    void setText(QString data);
private:
    QLabel *label;
};

#endif // CV_H
