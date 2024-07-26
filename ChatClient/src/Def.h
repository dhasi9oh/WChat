#ifndef DEF_H
#define DEF_H

#include <QObject>
#include <QtQml/qqml.h>

namespace ChatUIModeType {

    Q_NAMESPACE

    //聊天界面几种模式
    enum ChatUIMode{
        SearchMode = 0x0000, //搜索模式
        ChatMode = 0x0001, //聊天模式
        ContactMode = 0x0002, //联系模式
    };

    Q_ENUM_NS(ChatUIMode)
    QML_NAMED_ELEMENT(ChatUIModeType)

};


#endif // DEF_H
