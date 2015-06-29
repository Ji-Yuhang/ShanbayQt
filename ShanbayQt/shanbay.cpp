#include "shanbay.h"
#include <QEventLoop>
#include <QTimer>
Shanbay::Shanbay(QObject *parent) : QObject(parent)
{

}

ShanbayWord Shanbay::syncGetWord(const QString& word, bool *ok, int timeout)
{
    *ok = false;
    QString encodeWord = word;
    encodeWord = word.trimmed();
    encodeWord.replace(" ", "%20");
    QString url = QString("https://api.shanbay.com/bdc/search/?word=%1").arg(encodeWord);
    QNetworkRequest request;
    QString codeurl = "https://api.shanbay.com/oauth2/token/?client_id=a589ef972d26fa87d58b&client_secret=fdab01830d958dd4022e06611153839cab1c2cf2&grant_type=authorization_code&code=WllzU1ZtrMJNw1fyEEWI4LuEg9yTXN&redirect_uri=https://api.shanbay.com/oauth2/auth/success/";
    request.setUrl(QUrl(url));
//    QString tokenStr = QString("Bearer %1").arg(token_);
//    request.setRawHeader("Authorization",tokenStr.toUtf8());

    QNetworkAccessManager manager;
    QNetworkReply* reply =  manager.get(request);
    QEventLoop loop;
    QTimer timer;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), &loop, SLOT(quit()));
    QTimer::singleShot(timeout, &loop, SLOT(quit()));
    int r = loop.exec();
    ShanbayWord wordinfo;
    if (reply->error() == QNetworkReply::NoError && reply->isFinished()) {
        *ok = true;
        QByteArray block = reply->readAll();
        bool jsonOk = false;
        QtJson::JsonObject json = QtJson::parse(block, jsonOk).toMap();
        if (!jsonOk) {
            *ok = false;
            return wordinfo;
        }
        if (json["msg"] != "SUCCESS" || json.contains("data")) {
            *ok = false;
            return wordinfo;
        }
        wordinfo.status_code = json["status_code"].toString();
        wordinfo.msg = json["msg"].toString();
        wordinfo.data = json["data"].toMap();
        QMap<QString, QVariant> dataMap = wordinfo.data;
        wordinfo.en_definitions = dataMap["en_definitions"].toMap();
        wordinfo.cn_definition = dataMap["cn_definition"].toMap();
        wordinfo.id = dataMap["id"].toString();
        wordinfo.retention = dataMap["retention"].toInt();
        wordinfo.definition = dataMap["definition"].toString();
        wordinfo.target_retention = dataMap["target_retention"].toString();
        wordinfo.en_definition = dataMap["en_definition"].toMap();
        wordinfo.learning_id = dataMap["learning_id"].toString();
        wordinfo.content = dataMap["content"].toString();
        wordinfo.pronunciation = dataMap["pronunciation"].toString();
        wordinfo.audio = dataMap["audio"].toString();
        wordinfo.uk_audio = dataMap["uk_audio"].toString();
        wordinfo.us_audio = dataMap["us_audio"].toString();
        /*
        {
            "msg": "SUCCESS",
            "status_code": 0,
            "data": {
                "en_definitions": {},
                "uk_audio": "http://media.shanbay.com/audio/uk/go_to.mp3",
                "conent_id": 236557,
                "cn_definition": {
                    "pos": "",
                    "defn": "v.转到,定位"
                },
                "num_sense": 0,
                "content_type": "vocabulary",
                "id": 236557,
                "definition": " v.转到,定位",
                "content_id": 236557,
                "en_definition": {},
                "object_id": 236557,
                "content": "go to",
                "pron": "",
                "pronunciation": "",
                "audio": "http://media.shanbay.com/audio/us/go_to.mp3",
                "us_audio": "http://media.shanbay.com/audio/us/go_to.mp3"
            }

        }
*/

        return wordinfo;


    } else {
        *ok = false;
        return wordinfo;
    }



}

