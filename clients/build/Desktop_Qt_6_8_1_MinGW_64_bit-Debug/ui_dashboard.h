/********************************************************************************
** Form generated from reading UI file 'dashboard.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DASHBOARD_H
#define UI_DASHBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dashboard
{
public:
    QWidget *widget;
    QPushButton *currentprice_btn;
    QPushButton *Mywallets_btn;
    QPushButton *Dashboard_btn;
    QPushButton *market_btn;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QTextEdit *textEdit;
    QPushButton *Transmission_btn;
    QPushButton *Profile_btn;
    QPushButton *Authentication_btn;
    QPushButton *backButton;
    QPushButton *deposit_btn;
    QPushButton *withdrawal_btn;
    QPushButton *easyexchange_btn;
    QPushButton *backButton_2;

    void setupUi(QWidget *dashboard)
    {
        if (dashboard->objectName().isEmpty())
            dashboard->setObjectName("dashboard");
        dashboard->resize(1278, 904);
        dashboard->setMinimumSize(QSize(1278, 904));
        dashboard->setMaximumSize(QSize(1278, 904));
        dashboard->setStyleSheet(QString::fromUtf8("background-color:#d9d8d4  ;"));
        widget = new QWidget(dashboard);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 0, 1278, 904));
        widget->setMinimumSize(QSize(1278, 904));
        widget->setMaximumSize(QSize(1278, 904));
        widget->setStyleSheet(QString::fromUtf8("background-color:#d9d8d4  ;"));
        currentprice_btn = new QPushButton(widget);
        currentprice_btn->setObjectName("currentprice_btn");
        currentprice_btn->setGeometry(QRect(1030, 630, 221, 41));
        currentprice_btn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        currentprice_btn->setStyleSheet(QString::fromUtf8("border:none;\n"
"color: rgb(0, 0, 0);\n"
"font: 28pt \"Bangers\";\n"
"letter-spacing: 1px;"));
        Mywallets_btn = new QPushButton(widget);
        Mywallets_btn->setObjectName("Mywallets_btn");
        Mywallets_btn->setGeometry(QRect(1050, 280, 171, 41));
        Mywallets_btn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        Mywallets_btn->setStyleSheet(QString::fromUtf8("border:none;\n"
"color: rgb(0, 0, 0);\n"
"font: 28pt \"Bangers\";\n"
"letter-spacing: 1px;"));
        Dashboard_btn = new QPushButton(widget);
        Dashboard_btn->setObjectName("Dashboard_btn");
        Dashboard_btn->setGeometry(QRect(1040, 210, 191, 41));
        Dashboard_btn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        Dashboard_btn->setStyleSheet(QString::fromUtf8("border:none;\n"
"font: 28pt \"Bangers\";\n"
"color: #c97940;\n"
"\n"
""));
        market_btn = new QPushButton(widget);
        market_btn->setObjectName("market_btn");
        market_btn->setGeometry(QRect(1050, 420, 171, 41));
        market_btn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        market_btn->setStyleSheet(QString::fromUtf8("border:none;\n"
"color: rgb(0, 0, 0);\n"
"font: 28pt \"Bangers\";\n"
"letter-spacing: 1px;"));
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setEnabled(true);
        label->setGeometry(QRect(0, 0, 1021, 921));
        label->setStyleSheet(QString::fromUtf8(""));
        label->setPixmap(QPixmap(QString::fromUtf8("image/\330\267\330\261\330\255 \331\204\331\210\332\257\331\210 \330\250\330\261\330\247\333\214 \330\265\330\261\330\247\331\201\333\214 \330\250\331\207 \330\247\330\263\331\205 heliacal.png")));
        label->setScaledContents(true);
        label->setWordWrap(false);
        label->setIndent(-1);
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");
        label_2->setEnabled(false);
        label_2->setGeometry(QRect(1020, 130, 251, 71));
        label_2->setStyleSheet(QString::fromUtf8("           border: none;  \n"
"color: #344b90;\n"
"background-color: #d9d8d4;\n"
"font: 22pt \"Rubik Wet Paint\";\n"
"letter-spacing: -2px;\n"
"word-spacing: 3px;\n"
""));
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");
        label_3->setEnabled(true);
        label_3->setGeometry(QRect(1020, 0, 251, 151));
        label_3->setPixmap(QPixmap(QString::fromUtf8("E:/Downloads/logo for a currency exchange named heliacal (1).png")));
        label_3->setScaledContents(true);
        label_3->setIndent(-6);
        textEdit = new QTextEdit(widget);
        textEdit->setObjectName("textEdit");
        textEdit->setEnabled(false);
        textEdit->setGeometry(QRect(60, 790, 104, 51));
        Transmission_btn = new QPushButton(widget);
        Transmission_btn->setObjectName("Transmission_btn");
        Transmission_btn->setGeometry(QRect(1030, 560, 221, 41));
        Transmission_btn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        Transmission_btn->setStyleSheet(QString::fromUtf8("border:none;\n"
"color: rgb(0, 0, 0);\n"
"font: 28pt \"Bangers\";\n"
"letter-spacing: 1px;"));
        Profile_btn = new QPushButton(widget);
        Profile_btn->setObjectName("Profile_btn");
        Profile_btn->setGeometry(QRect(1030, 350, 211, 41));
        Profile_btn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        Profile_btn->setStyleSheet(QString::fromUtf8("border:none;\n"
"color: rgb(0, 0, 0);\n"
"font: 28pt \"Bangers\";\n"
"letter-spacing: 1px;"));
        Authentication_btn = new QPushButton(widget);
        Authentication_btn->setObjectName("Authentication_btn");
        Authentication_btn->setGeometry(QRect(1030, 700, 231, 41));
        Authentication_btn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        Authentication_btn->setStyleSheet(QString::fromUtf8("border:none;\n"
"color: #4fee93;\n"
"font: 28pt \"Bangers\";\n"
"letter-spacing: -1px;"));
        backButton = new QPushButton(widget);
        backButton->setObjectName("backButton");
        backButton->setEnabled(true);
        backButton->setGeometry(QRect(30, 820, 161, 41));
        backButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        backButton->setStyleSheet(QString::fromUtf8("          background-color: #BF360C;\n"
"            color: white;\n"
"            border-radius: 10px;\n"
"            font-size: 16px;\n"
"           border: none;  "));
        deposit_btn = new QPushButton(widget);
        deposit_btn->setObjectName("deposit_btn");
        deposit_btn->setGeometry(QRect(1060, 770, 171, 41));
        deposit_btn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        deposit_btn->setStyleSheet(QString::fromUtf8("border:none;\n"
"color: rgb(0, 0, 0);\n"
"font: 28pt \"Bangers\";\n"
"letter-spacing: 1px;"));
        withdrawal_btn = new QPushButton(widget);
        withdrawal_btn->setObjectName("withdrawal_btn");
        withdrawal_btn->setGeometry(QRect(1040, 840, 201, 41));
        withdrawal_btn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        withdrawal_btn->setStyleSheet(QString::fromUtf8("border:none;\n"
"color: rgb(0, 0, 0);\n"
"font: 28pt \"Bangers\";\n"
"letter-spacing: 1px;"));
        easyexchange_btn = new QPushButton(widget);
        easyexchange_btn->setObjectName("easyexchange_btn");
        easyexchange_btn->setGeometry(QRect(1060, 490, 151, 41));
        easyexchange_btn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        easyexchange_btn->setStyleSheet(QString::fromUtf8("border:none;\n"
"color: rgb(0, 0, 0);\n"
"font: 28pt \"Bangers\";\n"
"letter-spacing: -1px;"));
        backButton_2 = new QPushButton(widget);
        backButton_2->setObjectName("backButton_2");
        backButton_2->setEnabled(true);
        backButton_2->setGeometry(QRect(30, 20, 161, 41));
        backButton_2->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        backButton_2->setStyleSheet(QString::fromUtf8("          background-color: rgb(85, 0, 127);\n"
"            color: white;\n"
"            border-radius: 10px;\n"
"            font-size: 16px;\n"
"           border: none;  "));
        textEdit->raise();
        currentprice_btn->raise();
        Mywallets_btn->raise();
        Dashboard_btn->raise();
        market_btn->raise();
        label_2->raise();
        label_3->raise();
        label->raise();
        Transmission_btn->raise();
        Profile_btn->raise();
        Authentication_btn->raise();
        backButton->raise();
        deposit_btn->raise();
        withdrawal_btn->raise();
        easyexchange_btn->raise();
        backButton_2->raise();

        retranslateUi(dashboard);

        QMetaObject::connectSlotsByName(dashboard);
    } // setupUi

    void retranslateUi(QWidget *dashboard)
    {
        dashboard->setWindowTitle(QCoreApplication::translate("dashboard", "HELIACAL EXCHANGE", nullptr));
        currentprice_btn->setText(QCoreApplication::translate("dashboard", "Current price", nullptr));
        Mywallets_btn->setText(QCoreApplication::translate("dashboard", "My wallets", nullptr));
        Dashboard_btn->setText(QCoreApplication::translate("dashboard", "Dashboard", nullptr));
        market_btn->setText(QCoreApplication::translate("dashboard", "market", nullptr));
#if QT_CONFIG(accessibility)
        label->setAccessibleDescription(QString());
#endif // QT_CONFIG(accessibility)
        label->setText(QString());
        label_2->setText(QCoreApplication::translate("dashboard", "heliacal exchange", nullptr));
        label_3->setText(QString());
        Transmission_btn->setText(QCoreApplication::translate("dashboard", "Transmission", nullptr));
        Profile_btn->setText(QCoreApplication::translate("dashboard", "Profile", nullptr));
        Authentication_btn->setText(QCoreApplication::translate("dashboard", "Authentication", nullptr));
        backButton->setText(QCoreApplication::translate("dashboard", "log out", nullptr));
        deposit_btn->setText(QCoreApplication::translate("dashboard", "Deposit ", nullptr));
        withdrawal_btn->setText(QCoreApplication::translate("dashboard", " withdrawal", nullptr));
        easyexchange_btn->setText(QCoreApplication::translate("dashboard", " Exchange", nullptr));
        backButton_2->setText(QCoreApplication::translate("dashboard", "guideline", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dashboard: public Ui_dashboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DASHBOARD_H
