#include "form.h"
#include "ui_form.h"
#include "client.h"
#include <QDebug>
#include <QRegularExpression>
#include <QMessageBox>
#include "signin.h"
#include "dashboard.h"
#include <QWidget>
#include <QLineEdit>
#include <QKeyEvent>
#include <QList>

form::form(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::form)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon());
    client = new Client(this);
    connect(client, &Client::registrationSuccessful, this, &form::onRegistrationSuccessful);
    QList<QLineEdit*> lineEdits = {ui->lineEditEmail, ui->lineEditName, ui->lineEditPassword, ui->confirmpassword, ui->lineEditPhone, ui->invitationcode};

    for (int i = 0; i < lineEdits.size() - 1; ++i) {
        connect(lineEdits[i], &QLineEdit::returnPressed, this, [=]() { lineEdits[i + 1]->setFocus(); });
    }
    QList<QLineEdit*> lineEdits1 = {ui->lineEditEmail, ui->lineEditName, ui->lineEditPassword, ui->confirmpassword, ui->lineEditPhone, ui->invitationcode};

    for (QLineEdit* lineEdit : lineEdits1) {
        lineEdit->installEventFilter(this);
    }

}
form::~form()
{
    delete ui;
}
bool isValidEmail(const QString &email)
{
    QRegularExpression regex(R"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z]{2,3}$)");
    return regex.match(email).hasMatch();
}
bool isValidPassword(const QString &password) {
    if (password.length() < 8) {
        return false;
    }
    QRegularExpression hasUpperCase("[A-Z]");
    QRegularExpression hasLowerCase("[a-z]");
    QRegularExpression hasDigit("\\d");

    return hasUpperCase.match(password).hasMatch() &&
           hasLowerCase.match(password).hasMatch() &&
           hasDigit.match(password).hasMatch();
}
void form::on_pushButton_clicked()
{
    QString email = ui->lineEditEmail->text();
    QString password = ui->lineEditPassword->text();
    QString name = ui->lineEditName->text();
    QString copassword = ui->confirmpassword->text();
    QString phone = ui->lineEditPhone->text();
    if(email.isEmpty()){ QMessageBox::warning(this, "error", "Please enter your email");return;}
    if(password.isEmpty()){ QMessageBox::warning(this, "error", "Please enter your password");return;}
    if(name.isEmpty()){ QMessageBox::warning(this, "error", "Please enter your username");return;}

    if (!isValidEmail(email)) {
        QMessageBox::warning(this, "warning", "The email is invalid. Please enter a valid email");
        return;
    }

    if (!isValidPassword(password)) {
        QMessageBox::warning(this, "warning", "The password is invalid. The password must be at least 8 Characters long, including one Uppercase Letter, one Lowercase Letter, and one Number.");
        return;
    }
    if (password!=copassword){
        QMessageBox::warning(this, "warning", "the password and its repetition are not the same.");
        return;
    }
    Client::globalEmail = email;
    emit sendCredentials(email, password, name, phone);
}

void form::displayServerResponse(const QString &response)
{
    if (response.contains("error")) {
        QMessageBox::warning(this, "error", response);
    }
}
void form::onRegistrationSuccessful() {
    qDebug() << "Registration was successful!";
    this->hide();
    extern Client client;
    Client::warname=10;
    client.getuserprofile();
    dashboard *da = new dashboard();

    connect(da, &dashboard::backToFormRequested, this, [this]() {
        this->show();
    });
    da->show();
    da->hide();
}
void form::loginSuccessful() {
    this->hide();
    extern Client client;
    Client::warname=10;
    client.getuserprofile();
    dashboard *da = new dashboard();

    connect(da, &dashboard::backToFormRequested, this, [this]() {
        this->show();
    });
    extern Client client;
    connect(&client, &Client::receivedMessagetodash, da, &dashboard::ServerResponse);
    da->show();
    da->hide();
}
void form::on_pushButton_gosignin_clicked()
{
    this->hide();
    signin *sign = new signin();
    sign->setAttribute(Qt::WA_DeleteOnClose);
    extern Client client;
    QObject::connect(sign, &signin::sendservertologin, &client, &Client::sendservertologin);
    connect(sign, &signin::backToFormRequested, this, [this]() {
        this->show();
    });
    extern Client client;
    connect(&client, &Client::receivedMessagetosign, sign, &signin::Responsetosignin);
    connect(&client, &Client::triggerSigninSlot, sign, &signin::closewindow);
    sign->show();
}
void form::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    ui->lineEditEmail->setFocus();
}

bool form::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        QLineEdit *currentLineEdit = qobject_cast<QLineEdit*>(obj);

        if (currentLineEdit) {
            QList<QLineEdit*> lineEdits = {ui->lineEditEmail, ui->lineEditName, ui->lineEditPassword, ui->confirmpassword, ui->lineEditPhone, ui->invitationcode};
            int index = lineEdits.indexOf(currentLineEdit);

            if (keyEvent->key() == Qt::Key_Down) {
                if (index < lineEdits.size() - 1) {
                    lineEdits[index + 1]->setFocus();
                    return true;
                }
            } else if (keyEvent->key() == Qt::Key_Up) {
                if (index > 0) {
                    lineEdits[index - 1]->setFocus();
                    return true;
                }
            }
        }
    }
    return QWidget::eventFilter(obj, event);
}

