#ifndef WITHDRAWAL_H
#define WITHDRAWAL_H

#include <QWidget>

namespace Ui {
class withdrawal;
}

class withdrawal : public QWidget
{
    Q_OBJECT

public:
    explicit withdrawal(QWidget *parent = nullptr);
    ~withdrawal();
    void applyStyles();

private slots:
    void on_radiobtc_clicked();

    void on_radioirt_clicked();

    void on_radioeth_clicked();

    void on_radiotrx_clicked();

    void on_radiousdt_clicked();

    void on_Dashboard_btn_clicked();

    void on_Mywallets_btn_clicked();

    void on_Profile_btn_clicked();

    void on_withdrawal_coin_clicked();

private:
    Ui::withdrawal *ui;
};

#endif // WITHDRAWAL_H
