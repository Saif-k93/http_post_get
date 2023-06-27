#include "worker.h"

Worker::Worker(QObject *parent)
    : QObject{parent}
{
    QObject::connect(&manager,&QNetworkAccessManager::authenticationRequired,this,&Worker::authenticationRequired);
    QObject::connect(&manager,&QNetworkAccessManager::encrypted,this,&Worker::encrypted);
    QObject::connect(&manager,&QNetworkAccessManager::preSharedKeyAuthenticationRequired,this,&Worker::preSharedKeyAuthenticationRequired);
    QObject::connect(&manager,&QNetworkAccessManager::proxyAuthenticationRequired,this,&Worker::proxyAuthenticationRequired);
    QObject::connect(&manager,&QNetworkAccessManager::sslErrors,this,&Worker::sslErrors);
    QObject::connect(&manager,&QNetworkAccessManager::finished,this,&Worker::finished);

}

Worker::~Worker()
{
   // TODO
}

void Worker::get(QString location)
{
    qInfo() << "Geting From Server...";

    QNetworkReply* replay = manager.get(QNetworkRequest(QUrl(location)));

    QObject::connect(replay,&QNetworkReply::readyRead,this,&Worker::readyread);
}

void Worker::post(QString location, QByteArray data)
{
    qInfo() << "Posting To Server...";

    QNetworkRequest request = QNetworkRequest(QUrl(location));

    request.setHeader(QNetworkRequest::ContentTypeHeader,"test/plain");

    QNetworkReply* replay = manager.post(request,data);

    QObject::connect(replay,&QNetworkReply::readyRead,this,&Worker::readyread);
}

void Worker::authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{
    Q_UNUSED(reply);
    Q_UNUSED(authenticator);
    qInfo() << "authenticationRequired!";
}

void Worker::encrypted(QNetworkReply *reply)
{
    Q_UNUSED(reply);
    qInfo() << "encrypted!";
}

void Worker::finished(QNetworkReply *reply)
{
    qInfo() << "finished!";
    reply->deleteLater();
}

void Worker::preSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator)
{
    Q_UNUSED(reply);
    Q_UNUSED(authenticator);
    qInfo() << "preSharedKeyAuthenticationRequired!";
}

void Worker::proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{
    Q_UNUSED(proxy);
    Q_UNUSED(authenticator);
    qInfo() << "proxyAuthenticationRequired!";
}

void Worker::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    Q_UNUSED(reply);
    Q_UNUSED(errors);
    qInfo() << "Ssl Error!";
}

void Worker::readyread()
{
    qInfo() << "ReadyRead!";

    QNetworkReply* replay = qobject_cast<QNetworkReply*>(sender());

    if(replay) qInfo() << replay->readAll();

}
