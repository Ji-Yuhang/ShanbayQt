#ifndef SHANBAY_H
#define SHANBAY_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QWebView>
#include <QNetworkReply>
#include <QString>
#include <QMap>
#include "json.h"

struct ShanbayWord {
    QString status_code;
    QString msg;
    QMap<QString, QVariant> data;

    // data:
    QMap<QString, QVariant> en_definitions;
    QMap<QString, QVariant> cn_definition;
    QString id;
    QString retention;
    QString definition;
    QString target_retention;
    QMap<QString, QVariant> en_definition;
    QString learning_id;
    QString content;
    QString pronunciation;
    QString audio;
    QString uk_audio;
    QString us_audio;
};
class Shanbay : public QObject
{
    Q_OBJECT
public:
    explicit Shanbay(QObject *parent = 0);

    // sync get word information, timeout 5000 ms
    ShanbayWord syncGetWord(const QString& word,bool* ok,int timeout = 5000);

signals:

public slots:
};

#endif // SHANBAY_H
