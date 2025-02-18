#include "signin.h"
#include "ui_signin.h"
#include "form.h"
#include <QDebug>
#include "client.h"
#include <QMessageBox>

signin::signin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::signin)
{
    ui->setupUi(this);
    connect(ui->pushButton_gosignin, &QPushButton::clicked, this, &signin::on_pushButton_gosignin_clicked);

    ui->lineEditEmail_sign_2->setVisible(false);
    ui->lineEditName_sign->setVisible(false);
    ui->label_email_sign_2->setVisible(false);
    ui->label_name_sign->setVisible(false);
    ui->forgotbtnsend->setVisible(false);


    QList<QLineEdit*> lineEdits = {ui->lineEditEmail_sign, ui->lineEditPassword_sign};

    for (int i = 0; i < lineEdits.size() - 1; ++i) {
        connect(lineEdits[i], &QLineEdit::returnPressed, this, [=]() { lineEdits[i + 1]->setFocus(); });
    }
}

signin::~signin()
{
    delete ui;
}

void signin::on_pushButton_gosignin_clicked()
{

    emit backToFormRequested();
    this->close();
}



void signin::on_login_button_clicked()
{
    QString email = ui->lineEditEmail_sign->text();
    QString password = ui->lineEditPassword_sign->text();

    if (email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "erre", "Please enter your email and username");
        return;
    }

    Client::globalEmail = email;

    emit sendservertologin(email, password);
}
void signin::Responsetosignin(const QString &response)
{

    QMessageBox::warning(this, "warning", response);



}

void signin::on_forgot_password_clicked()
{
    ui->lineEditEmail_sign_2->setVisible(true);
    ui->lineEditName_sign->setVisible(true);
    ui->label_email_sign_2->setVisible(true);
    ui->label_name_sign->setVisible(true);
    ui->forgotbtnsend->setVisible(true);

}


void signin::on_forgotbtnsend_clicked()
{
    QString email = ui->lineEditEmail_sign_2->text();
    QString username = ui->lineEditName_sign->text();

    if (email.isEmpty() || username.isEmpty()) {
        QMessageBox::warning(this, "error", "Please enter your email and username.");
        return;
    }
    extern Client client;
    client.sendForgotPasswordRequest(email, username);
}
void signin:: closewindow(){
    this->close();
}
void signin::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    ui->lineEditEmail_sign->setFocus();
}
