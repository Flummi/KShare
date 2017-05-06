#include "ioutils.hpp"
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

namespace ioutils {
QNetworkAccessManager networkManager;
}

void ioutils::getJson(
    QUrl target, QList<QPair<QString, QString>> headers,
    std::function<void(QJsonDocument, QNetworkReply *)> callback) {
  QNetworkRequest req(target);
  for (auto header : headers) {
    req.setRawHeader(header.first.toUtf8(), header.second.toUtf8());
  }
  QNetworkReply *reply = networkManager.get(req);
  QObject::connect(reply, &QNetworkReply::finished, [reply, callback] {
    callback(QJsonDocument::fromJson(reply->readAll()), reply);
    reply->deleteLater();
  });
}

void ioutils::postJson(
    QUrl target, QList<QPair<QString, QString>> headers, QByteArray body,
    std::function<void(QJsonDocument, QNetworkReply *)> callback) {
  QNetworkRequest req(target);
  for (auto header : headers) {
    req.setRawHeader(header.first.toUtf8(), header.second.toUtf8());
  }
  QNetworkReply *reply = networkManager.post(req, body);
  QObject::connect(reply, &QNetworkReply::finished, [reply, callback] {
    callback(QJsonDocument::fromJson(reply->readAll()), reply);
    delete reply;
  });
}

void ioutils::getData(
    QUrl target, QList<QPair<QString, QString>> headers,
    std::function<void(QByteArray, QNetworkReply *)> callback) {
  QNetworkRequest req(target);
  for (auto header : headers) {
    req.setRawHeader(header.first.toUtf8(), header.second.toUtf8());
  }
  QNetworkReply *reply = networkManager.get(req);
  QObject::connect(reply, &QNetworkReply::finished, [reply, callback] {
    callback(reply->readAll(), reply);
    delete reply;
  });
}

void ioutils::postData(
    QUrl target, QList<QPair<QString, QString>> headers, QByteArray body,
    std::function<void(QByteArray, QNetworkReply *)> callback) {
  QNetworkRequest req(target);
  for (auto header : headers) {
    req.setRawHeader(header.first.toUtf8(), header.second.toUtf8());
  }
  QNetworkReply *reply = networkManager.post(req, body);
  QObject::connect(reply, &QNetworkReply::finished, [reply, callback] {
    callback(reply->readAll(), reply);
    delete reply;
  });
}
