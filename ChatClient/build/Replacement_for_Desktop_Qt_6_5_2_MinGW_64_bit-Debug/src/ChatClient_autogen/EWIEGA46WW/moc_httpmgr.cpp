/****************************************************************************
** Meta object code from reading C++ file 'httpmgr.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/httpmgr.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'httpmgr.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSHttpMgrENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSHttpMgrENDCLASS = QtMocHelpers::stringData(
    "HttpMgr",
    "QML.Element",
    "auto",
    "signalShowInfo",
    "",
    "signalShowError",
    "signalConnectTcp",
    "ServerInfo",
    "signalHttpFinish",
    "ReqId",
    "id",
    "res",
    "ErrorCodes",
    "err",
    "slotHttpFinish",
    "onLoginButtonClicked",
    "usr",
    "pwd",
    "onRegisterButtonClicked",
    "email",
    "confirm_pwd",
    "varify_code",
    "onResetButtonClicked",
    "new_pwd",
    "onGetVarifyCodeButtonClicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSHttpMgrENDCLASS_t {
    uint offsetsAndSizes[50];
    char stringdata0[8];
    char stringdata1[12];
    char stringdata2[5];
    char stringdata3[15];
    char stringdata4[1];
    char stringdata5[16];
    char stringdata6[17];
    char stringdata7[11];
    char stringdata8[17];
    char stringdata9[6];
    char stringdata10[3];
    char stringdata11[4];
    char stringdata12[11];
    char stringdata13[4];
    char stringdata14[15];
    char stringdata15[21];
    char stringdata16[4];
    char stringdata17[4];
    char stringdata18[24];
    char stringdata19[6];
    char stringdata20[12];
    char stringdata21[12];
    char stringdata22[21];
    char stringdata23[8];
    char stringdata24[29];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSHttpMgrENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSHttpMgrENDCLASS_t qt_meta_stringdata_CLASSHttpMgrENDCLASS = {
    {
        QT_MOC_LITERAL(0, 7),  // "HttpMgr"
        QT_MOC_LITERAL(8, 11),  // "QML.Element"
        QT_MOC_LITERAL(20, 4),  // "auto"
        QT_MOC_LITERAL(25, 14),  // "signalShowInfo"
        QT_MOC_LITERAL(40, 0),  // ""
        QT_MOC_LITERAL(41, 15),  // "signalShowError"
        QT_MOC_LITERAL(57, 16),  // "signalConnectTcp"
        QT_MOC_LITERAL(74, 10),  // "ServerInfo"
        QT_MOC_LITERAL(85, 16),  // "signalHttpFinish"
        QT_MOC_LITERAL(102, 5),  // "ReqId"
        QT_MOC_LITERAL(108, 2),  // "id"
        QT_MOC_LITERAL(111, 3),  // "res"
        QT_MOC_LITERAL(115, 10),  // "ErrorCodes"
        QT_MOC_LITERAL(126, 3),  // "err"
        QT_MOC_LITERAL(130, 14),  // "slotHttpFinish"
        QT_MOC_LITERAL(145, 20),  // "onLoginButtonClicked"
        QT_MOC_LITERAL(166, 3),  // "usr"
        QT_MOC_LITERAL(170, 3),  // "pwd"
        QT_MOC_LITERAL(174, 23),  // "onRegisterButtonClicked"
        QT_MOC_LITERAL(198, 5),  // "email"
        QT_MOC_LITERAL(204, 11),  // "confirm_pwd"
        QT_MOC_LITERAL(216, 11),  // "varify_code"
        QT_MOC_LITERAL(228, 20),  // "onResetButtonClicked"
        QT_MOC_LITERAL(249, 7),  // "new_pwd"
        QT_MOC_LITERAL(257, 28)   // "onGetVarifyCodeButtonClicked"
    },
    "HttpMgr",
    "QML.Element",
    "auto",
    "signalShowInfo",
    "",
    "signalShowError",
    "signalConnectTcp",
    "ServerInfo",
    "signalHttpFinish",
    "ReqId",
    "id",
    "res",
    "ErrorCodes",
    "err",
    "slotHttpFinish",
    "onLoginButtonClicked",
    "usr",
    "pwd",
    "onRegisterButtonClicked",
    "email",
    "confirm_pwd",
    "varify_code",
    "onResetButtonClicked",
    "new_pwd",
    "onGetVarifyCodeButtonClicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSHttpMgrENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       1,   14, // classinfo
       9,   16, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // classinfo: key, value
       1,    2,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       3,    1,   70,    4, 0x06,    1 /* Public */,
       5,    1,   73,    4, 0x06,    3 /* Public */,
       6,    1,   76,    4, 0x06,    5 /* Public */,
       8,    3,   79,    4, 0x06,    7 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      14,    3,   86,    4, 0x0a,   11 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      15,    2,   93,    4, 0x02,   15 /* Public */,
      18,    5,   98,    4, 0x02,   18 /* Public */,
      22,    4,  109,    4, 0x02,   24 /* Public */,
      24,    1,  118,    4, 0x02,   29 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, 0x80000000 | 7,    4,
    QMetaType::Void, 0x80000000 | 9, QMetaType::QString, 0x80000000 | 12,   10,   11,   13,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 9, QMetaType::QString, 0x80000000 | 12,   10,   11,   13,

 // methods: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   16,   17,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   16,   19,   17,   20,   21,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   16,   19,   23,   21,
    QMetaType::Void, QMetaType::QString,   19,

       0        // eod
};

Q_CONSTINIT const QMetaObject HttpMgr::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSHttpMgrENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSHttpMgrENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_metaTypeArray<
        // Q_OBJECT / Q_GADGET
        HttpMgr,
        // method 'signalShowInfo'
        void,
        QString,
        // method 'signalShowError'
        void,
        QString,
        // method 'signalConnectTcp'
        void,
        ServerInfo,
        // method 'signalHttpFinish'
        void,
        ReqId,
        QString,
        ErrorCodes,
        // method 'slotHttpFinish'
        void,
        ReqId,
        QString,
        ErrorCodes,
        // method 'onLoginButtonClicked'
        void,
        const QString &,
        const QString &,
        // method 'onRegisterButtonClicked'
        void,
        const QString &,
        const QString &,
        const QString &,
        const QString &,
        const QString &,
        // method 'onResetButtonClicked'
        void,
        const QString &,
        const QString &,
        const QString &,
        const QString &,
        // method 'onGetVarifyCodeButtonClicked'
        void,
        const QString &
    >,
    nullptr
} };

void HttpMgr::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HttpMgr *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->signalShowInfo((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->signalShowError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->signalConnectTcp((*reinterpret_cast< std::add_pointer_t<ServerInfo>>(_a[1]))); break;
        case 3: _t->signalHttpFinish((*reinterpret_cast< std::add_pointer_t<ReqId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<ErrorCodes>>(_a[3]))); break;
        case 4: _t->slotHttpFinish((*reinterpret_cast< std::add_pointer_t<ReqId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<ErrorCodes>>(_a[3]))); break;
        case 5: _t->onLoginButtonClicked((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 6: _t->onRegisterButtonClicked((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[5]))); break;
        case 7: _t->onResetButtonClicked((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4]))); break;
        case 8: _t->onGetVarifyCodeButtonClicked((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (HttpMgr::*)(QString );
            if (_t _q_method = &HttpMgr::signalShowInfo; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (HttpMgr::*)(QString );
            if (_t _q_method = &HttpMgr::signalShowError; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (HttpMgr::*)(ServerInfo );
            if (_t _q_method = &HttpMgr::signalConnectTcp; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (HttpMgr::*)(ReqId , QString , ErrorCodes );
            if (_t _q_method = &HttpMgr::signalHttpFinish; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *HttpMgr::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HttpMgr::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSHttpMgrENDCLASS.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "std::enable_shared_from_this<HttpMgr>"))
        return static_cast< std::enable_shared_from_this<HttpMgr>*>(this);
    return QObject::qt_metacast(_clname);
}

int HttpMgr::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void HttpMgr::signalShowInfo(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void HttpMgr::signalShowError(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void HttpMgr::signalConnectTcp(ServerInfo _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void HttpMgr::signalHttpFinish(ReqId _t1, QString _t2, ErrorCodes _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
