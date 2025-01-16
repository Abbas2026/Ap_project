#ifndef CURRENTPRICE_H
#define CURRENTPRICE_H

#include <QMainWindow>
#include "CoinGeckoAPI.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void fetchCoinDetails();
    void fetchCurrentPrices();
    void updateResult(const QJsonObject &data);

    void on_detailsButton_clicked();

    void on_priceButton_clicked();

private:
    Ui::MainWindow *ui;
    CoinGeckoAPI api;
};

#endif // CURRENTPRICE_H
