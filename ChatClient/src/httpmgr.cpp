#include "httpmgr.h"

void HttpMgr::slotHttpFinish(ReqId id, QString res, ErrorCodes err)
{
    if(err != ErrorCodes::SUCCESS){
        emit signalShowError(tr("网络请求错误"));
        return;
    }

    // 解析 JSON 字符串,res需转化为QByteArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    //json解析错误
    if(jsonDoc.isNull()){
        emit signalShowError(tr("json解析错误"));
        return;
    }

    //json解析错误
    if(!jsonDoc.isObject()){
        emit signalShowError(tr("json解析错误"));
        return;
    }

    //调用对应的逻辑,根据id回调。
    m_handlers[id](jsonDoc.object());
}

HttpMgr::~HttpMgr()
{
}

Q_INVOKABLE void HttpMgr::onLoginButtonClicked(const QString& email, const QString& pwd)
{
    QJsonObject json_obj;
    json_obj["email"] = email;
    json_obj["passwd"] = xorString(pwd);
    postHttpReq(QUrl(gate_url_prefix + "/user_login"),
        json_obj, ReqId::ID_LOGIN_USER);
}

Q_INVOKABLE void HttpMgr::onRegisterButtonClicked(const QString& usr, const QString& email, const QString& pwd, const QString& confirm_pwd, const QString& varify_code)
{
    QJsonObject json_obj;
    json_obj["user"] = usr;
    json_obj["email"] = email;
    json_obj["passwd"] = xorString(pwd);
    json_obj["sex"] = 0;

    json_obj["nick"] = usr;
    json_obj["confirm"] = xorString(confirm_pwd);
    json_obj["varifycode"] = varify_code;
    postHttpReq(QUrl(gate_url_prefix + "/user_register"),
        json_obj, ReqId::ID_REG_USER);
}

Q_INVOKABLE void HttpMgr::onResetButtonClicked(const QString& usr, const QString& email, const QString& new_pwd, const QString& varify_code)
{
    QJsonObject json_obj;
    json_obj["user"] = usr;
    json_obj["email"] = email;
    json_obj["passwd"] = xorString(new_pwd);
    json_obj["varifycode"] = varify_code;
    postHttpReq(QUrl(gate_url_prefix + "/reset_pwd"),
        json_obj, ReqId::ID_RESET_PWD);
}

Q_INVOKABLE void HttpMgr::onGetVarifyCodeButtonClicked(const QString& email)
{
    QJsonObject json_obj;
    json_obj["email"] = email;
    postHttpReq(QUrl(gate_url_prefix + "/get_varifycode"),
        json_obj, ReqId::ID_GET_VARIFY_CODE);

}

HttpMgr::HttpMgr()
{
    //连接http请求和完成信号，信号槽机制保证队列消费
    connect(this, &HttpMgr::signalHttpFinish, this, &HttpMgr::slotHttpFinish);
}

void HttpMgr::initHandle()
{
    //注册获取验证码回包逻辑
    m_handlers.insert(ReqId::ID_GET_VARIFY_CODE, [this](QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            emit signalShowError(tr("参数错误"));
            return;
        }
        auto email = jsonObj["email"].toString();
        emit signalShowInfo(tr("验证码已发送到邮箱，注意查收"));
        qDebug()<< "email is " << email ;
    });

    //注册注册用户回包逻辑
    m_handlers.insert(ReqId::ID_REG_USER, [this](QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            emit signalShowError(tr("参数错误"));
            return;
        }
        auto email = jsonObj["email"].toString();
        emit signalShowInfo(tr("用户注册成功"));
        qDebug()<< "email is " << email ;
        qDebug()<< "user uuid is " <<  jsonObj["uid"].toString();
    });

    //注册重置密码回包逻辑
    m_handlers.insert(ReqId::ID_RESET_PWD, [this](QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            emit signalShowError(tr("参数错误"));
            return;
        }
        auto email = jsonObj["email"].toString();
        emit signalShowInfo(tr("重置成功,点击返回登录"));
        qDebug()<< "email is " << email ;
        qDebug()<< "user uuid is " <<  jsonObj["uuid"].toString();
    });

    //注册获取登录回包逻辑
    m_handlers.insert(ReqId::ID_LOGIN_USER, [this](QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            emit signalShowError(tr("参数错误"));
            return;
        }
        auto email = jsonObj["email"].toString();

        //发送信号通知tcpMgr发送长链接
        ServerInfo si;
        si.Uid = jsonObj["uid"].toInt();
        si.Host = jsonObj["host"].toString();
        si.Port = jsonObj["port"].toString();
        si.Token = jsonObj["token"].toString();

        auto info = UsrMgr::Instance()->getUsrInfo();
        info._uid = si.Uid;
        UsrMgr::Instance()->setUsrInfo(info);
        UsrMgr::Instance()->setToken(si.Token);

        qDebug()<< "email is " << email << " uid is " << si.Uid <<" host is "
                 << si.Host << " Port is " << si.Port << " Token is " << si.Token;
        emit signalConnectTcp(si);
    });
}

void HttpMgr::postHttpReq(QUrl url, QJsonObject json, ReqId req_id)
{
    //创建一个HTTP POST请求，并设置请求头和请求体
    QByteArray data = QJsonDocument(json).toJson();
    //通过url构造请求
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));
    //发送请求，并处理响应, 获取自己的智能指针，构造伪闭包并增加智能指针引用计数
    auto self = shared_from_this();
    QNetworkReply* reply = m_manager.post(request, data);
    //设置信号和槽等待发送完成
    QObject::connect(reply, &QNetworkReply::finished, [reply, self, req_id]() {
        //处理错误的情况
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << reply->errorString();
            //发送信号通知完成
            emit self->signalHttpFinish(req_id, "", ErrorCodes::ERR_NETWORK);
            reply->deleteLater();
            return;
        }

        //无错误则读回请求
        QString res = reply->readAll();

        //发送信号通知完成
        emit self->signalHttpFinish(req_id, res, ErrorCodes::SUCCESS);
        reply->deleteLater();
        });
}
