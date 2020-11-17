#ifndef FRMLOGIN_H
#define FRMLOGIN_H

#include <QWidget>

namespace Ui
{
    class frmLogin;
}

class frmLogin : public QWidget
{
    Q_OBJECT

public:
    explicit frmLogin(QWidget *parent = nullptr);
    ~frmLogin();

protected:
    bool eventFilter(QObject *watched, QEvent *event);


private slots:
    void initForm();
    void initStyle();

private slots:
    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();

    void on_pushButton_clicked();

private:
    Ui::frmLogin *ui;
};

#endif // FRMLOGIN_H
