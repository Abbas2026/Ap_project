#include "server.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QJsonArray>
#include <QFile>

Server::Server(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);

    connect(server, &QTcpServer::newConnection, this, &Server::newConnection);
}

void Server::startServer(quint16 port)
{
    if (server->listen(QHostAddress::Any, port)) {
        qDebug() << "Server started on port" << port;
    } else {
        qDebug() << "Failed to start server:" << server->errorString();
    }
}

void Server::newConnection()
{
    QTcpSocket *newClient = server->nextPendingConnection();
    clientSockets.append(newClient);

    qDebug() << "New client connected. Total clients:" << clientSockets.size();

    connect(newClient, &QTcpSocket::readyRead, this, &Server::readClientMessage);
    connect(newClient, &QTcpSocket::disconnected, this, &Server::clientDisconnected);
}

void Server::readClientMessage()
{
    QTcpSocket *senderClient = qobject_cast<QTcpSocket*>(sender());
    if (!senderClient)
        return;

    QByteArray data = senderClient->readAll();


    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) {
        senderClient->write("Invalid data format");
        return;
    }

    QJsonObject json = doc.object();


    QString email = json["email"].toString();
    QString password = json["password"].toString();
    QString name = json["name"].toString();
    QString address = json["address"].toString();
    QString phone = json["phone"].toString();

    qDebug() << "Received email:" << email;
    qDebug() << "Received password:" << password;
    qDebug() << "Received name:" << name;
    qDebug() << "Received address:" << address;
    qDebug() << "Received phone:" << phone;

    if (json["type"].toString() == "forgot_password") {
        QString email = json["email"].toString();
        QString username = json["username"].toString();

        QJsonObject user = loadUserData(email);
        if (user["name"].toString() == username) {
            senderClient->write("Password forgotten confirmed");
        } else {
            senderClient->write("ایمیل یا نام کاربری نادرست است");
        }
        return;
    }
    else if (json["type"] == "createwallet") {
        qDebug()<< json["type"];

        QString email = json["email"].toString();
        QJsonArray words = json["words"].toArray();

        if (email.isEmpty() || words.isEmpty()) {
            senderClient->write("Missing data");
            return;
        }

        // ذخیره اطلاعات در فایل
        saveWalletData(email, words);

        senderClient->write("Wallet created successfully");
        return;
    }
    else if (json["type"]  == "RecoveryRequest") {
        handleRecoveryRequest(json, senderClient);
        return;
    }

    if (!email.isEmpty() && !password.isEmpty()) {
        if (name.isEmpty() && address.isEmpty() && phone.isEmpty()) {

            if (isValidCredentials(email, password)) {
                senderClient->write("Login successful");
            }
            else {
                senderClient->write("خطا: نام کاربری یا رمز عبور اشتباه است");

            }
        }
        else{
            if (isEmailRegistered(email)) {
                senderClient->write("این ایمیل قبلاً ثبت شده است");
            }else if (isNameRegistered(name)) {
                senderClient->write("این نام کاربری قبلاً ثبت شده است");
            }
            else {

                saveCredentials(email, password, name, address, phone);
                senderClient->write("ready");
            }
        }
    }
    else if (!email.isEmpty()) {
        getUserDataByEmail(email, senderClient);
    } else {
        senderClient->write("ایمیل ارسال نشده است");
    }
}

void Server::clientDisconnected()
{
    QTcpSocket *disconnectedClient = qobject_cast<QTcpSocket*>(sender());
    if (!disconnectedClient)
        return;

    clientSockets.removeAll(disconnectedClient);
    disconnectedClient->deleteLater();

    qDebug() << "Client disconnected. Remaining clients:" << clientSockets.size();
}

bool Server::isEmailRegistered(const QString &email)
{
    QFile file("users.json");

    if (!file.exists()) {
        qDebug() << "File users.json does not exist. Creating new file.";
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Unable to create users.json file.";
            return false;
        }
        QJsonObject rootObject;
        QJsonArray usersArray;
        rootObject["users"] = usersArray;
        QJsonDocument doc(rootObject);
        file.write(doc.toJson());
        file.close();
        return false;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Unable to open users file for reading.";
        return false;
    }

    QByteArray fileData = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(fileData);
    QJsonArray usersArray = doc.object()["users"].toArray();


    for (const QJsonValue &userValue : usersArray) {
        QJsonObject userObj = userValue.toObject();
        if (userObj["email"].toString() == email) {
            return true;
        }
    }
    return false;
}

void Server::saveCredentials(const QString &email, const QString &password, const QString &name, const QString &address, const QString &phone)
{
    QFile file("users.json");

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Unable to open users file for writing.";
        return;
    }

    QByteArray fileData = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(fileData);
    QJsonObject rootObject = doc.object();
    QJsonArray usersArray = rootObject["users"].toArray();


    QJsonObject newUser;
    newUser["email"] = email;
    newUser["password"] = password;
    newUser["name"] = name;
    newUser["address"] = address;
    newUser["phone"] = phone;
    usersArray.append(newUser);


    rootObject["users"] = usersArray;


    doc.setObject(rootObject);

    file.resize(0);
    QTextStream out(&file);
    out << doc.toJson(QJsonDocument::Indented);
    file.close();

    qDebug() << "User credentials saved to file.";
}

QJsonObject Server::loadUserData(const QString &email)
{
    QFile file("users.json");


    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Unable to open users file for reading.";
        return QJsonObject();
    }

    QByteArray fileData = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(fileData);


    if (doc.isNull()) {
        qDebug() << "Failed to parse the JSON file.";
        return QJsonObject();
    }



    QJsonArray usersArray = doc.object()["users"].toArray();

    if (usersArray.isEmpty()) {
        qDebug() << "No users found in the file.";
        return QJsonObject();
    }


    for (const QJsonValue &userValue : usersArray) {
        QJsonObject userObj = userValue.toObject();
        if (userObj["email"].toString() == email) {
            qDebug() << "User found: " << userObj;
            return userObj;
        }
    }

    qDebug() << "User with email" << email << "not found.";
    return QJsonObject();
}


void Server::sendUserData(QTcpSocket *client, const QString &email)
{
    QJsonObject userData = loadUserData(email);

    if (userData.isEmpty()) {
        client->write("User data not found");
        return;
    }

    QJsonObject response;
    response["email"] = userData["email"];
    response["name"] = userData["name"];
    response["address"] = userData["address"];
    response["phone"] = userData["phone"];
    response["status"] = "success";

    QJsonDocument doc(response);
    client->write(doc.toJson());
    qDebug() << "User data sent to client.";
}

void Server::getUserDataByEmail(const QString &email, QTcpSocket *client)
{
    QJsonObject userData = loadUserData(email);

    if (userData.isEmpty()) {
        client->write("User data not found");
        return;
    }

    QJsonObject response;
    response["email"] = userData["email"];
    response["name"] = userData["name"];
    response["address"] = userData["address"];
    response["phone"] = userData["phone"];
    response["status"] = "success";

    QJsonDocument doc(response);
    client->write(doc.toJson());
    qDebug() << "User data sent to client.";
}
bool Server::isValidCredentials(const QString &email, const QString &password)
{
    QFile file("users.json");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Unable to open users file for reading.";
        return false;
    }

    QByteArray fileData = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(fileData);

    if (doc.isNull()) {
        qDebug() << "Failed to parse the JSON file.";
        return false;
    }

    QJsonArray usersArray = doc.object()["users"].toArray();
    for (const QJsonValue &userValue : usersArray) {

        QJsonObject userObj = userValue.toObject();
        if (userObj["email"].toString() == email &&
            userObj["password"].toString() == password) {
            return true;
        }
    }

    return false;
}
bool Server::isNameRegistered(const QString &name) {
    QFile file("users.json");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Unable to open users file for reading.";
        return false;
    }

    QByteArray fileData = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(fileData);
    QJsonArray usersArray = doc.object()["users"].toArray();

    for (const QJsonValue &userValue : usersArray) {
        QJsonObject userObj = userValue.toObject();
        if (userObj["name"].toString() == name) {
            return true;
        }
    }
    return false;
}
void Server::saveWalletData(const QString &email, const QJsonArray &words) {
    QFile file("wallets.json");

    QJsonDocument doc;
    QJsonObject rootObject;

    if (file.exists()) {
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QByteArray fileData = file.readAll();
            doc = QJsonDocument::fromJson(fileData);
            rootObject = doc.object();
            file.close();
        }
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Unable to open wallets file for writing.";
        return;
    }

    QJsonArray walletsArray = rootObject["wallets"].toArray();

    QJsonObject newWallet;
    newWallet["email"] = email;
    newWallet["words"] = words;
    walletsArray.append(newWallet);

    rootObject["wallets"] = walletsArray;
    doc.setObject(rootObject);

    file.resize(0);
    QTextStream out(&file);
    out << doc.toJson(QJsonDocument::Indented);
    file.close();

    qDebug() << "Wallet data saved.";
}
void handleRecoveryRequest(const QJsonObject &request, QTcpSocket *clientSocket)
{
    QString email = request["email"].toString();
    QFile file("wallets.json");

    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        file.close();

        if (doc.isObject()) {
            QJsonObject wallets = doc.object();
            if (wallets.contains(email)) {
                QJsonObject wallet = wallets[email].toObject();
                QJsonArray words = wallet["words"].toArray();
                QJsonArray indexes = wallet["indexes"].toArray();

                QJsonObject response;
                response["type"] = "recoverywallet";
                response["words"] = words;
                response["indexes"] = indexes;

                QJsonDocument responseDoc(response);
                clientSocket->write(responseDoc.toJson());
                return;
            }
        }
    }

    // اگر ایمیل یافت نشد
    QJsonObject response;
    response["type"] = "RecoveryRequest";
    response["error"] = "Email not found";
    QJsonDocument responseDoc(response);
    clientSocket->write(responseDoc.toJson());
}
void Server::handleRecoveryRequest(const QJsonObject &request, QTcpSocket *clientSocket)
{
    QString email = request["email"].toString();
    QFile file("wallets.json");

    if (file.open(QIODevice::ReadOnly)) {
        QByteArray fileData = file.readAll();
        qDebug() << "File contents:" << fileData;
        QJsonDocument doc = QJsonDocument::fromJson(fileData);
        file.close();

        if (doc.isObject()) {
            QJsonArray walletsArray = doc.object()["wallets"].toArray();
            for (const QJsonValue &walletValue : walletsArray) {
                QJsonObject walletObj = walletValue.toObject();
                if (walletObj["email"].toString() == email) {
                    // ایمیل پیدا شد، کلمات و ایندکس‌ها را ارسال می‌کنیم
                    QJsonArray wordsArray = walletObj["words"].toArray();

                    QJsonArray words;
                    QJsonArray indexes;

                    for (const QJsonValue &wordValue : wordsArray) {
                        QJsonObject wordObj = wordValue.toObject();
                        words.append(wordObj["word"].toString());
                        indexes.append(wordObj["index"].toInt());
                    }

                    QJsonObject response;
                    response["type"] = "RecoveryRequest";
                    response["words"] = words;
                    response["indexes"] = indexes;

                    QJsonDocument responseDoc(response);
                    clientSocket->write(responseDoc.toJson());
                    return;
                }
            }
        }
    }

    // اگر ایمیل پیدا نشد
    QJsonObject response;
    response["type"] = "recoverywallet";
    response["error"] = "Email not found";
    QJsonDocument responseDoc(response);
    clientSocket->write(responseDoc.toJson());
}
