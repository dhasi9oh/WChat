/****************************************************************************
** Meta object code from reading C++ file 'tcpmgr.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/tcpmgr.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcpmgr.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSTcpMgrENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSTcpMgrENDCLASS = QtMocHelpers::stringData(
    "TcpMgr",
    "QML.Element",
    "auto",
    "signalConnectSuccess",
    "",
    "bsuccess",
    "signalSendData",
    "ReqId",
    "reqId",
    "data",
    "signalSwichChatdlg",
    "signalLoginFailed",
    "signalFriendApply",
    "from_id",
    "name",
    "desc",
    "signalAddAuthFriend",
    "uid",
    "nick",
    "icon",
    "sex",
    "signalAuthRsp",
    "slotTcpConnect",
    "ServerInfo",
    "slotSendData"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSTcpMgrENDCLASS_t {
    uint offsetsAndSizes[50];
    char stringdata0[7];
    char stringdata1[12];
    char stringdata2[5];
    char stringdata3[21];
    char stringdata4[1];
    char stringdata5[9];
    char stringdata6[15];
    char stringdata7[6];
    char stringdata8[6];
    char stringdata9[5];
    char stringdata10[19];
    char stringdata11[18];
    char stringdata12[18];
    char stringdata13[8];
    char stringdata14[5];
    char stringdata15[5];
    char stringdata16[20];
    char stringdata17[4];
    char stringdata18[5];
    char stringdata19[5];
    char stringdata20[4];
    char stringdata21[14];
    char stringdata22[15];
    char stringdata23[11];
    char stringdata24[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSTcpMgrENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSTcpMgrENDCLASS_t qt_meta_stringdata_CLASSTcpMgrENDCLASS = {
    {
        QT_MOC_LITERAL(0, 6),  // "TcpMgr"
        QT_MOC_LITERAL(7, 11),  // "QML.Element"
        QT_MOC_LITERAL(19, 4),  // "auto"
        QT_MOC_LITERAL(24, 20),  // "signalConnectSuccess"
        QT_MOC_LITERAL(45, 0),  // ""
        QT_MOC_LITERAL(46, 8),  // "bsuccess"
        QT_MOC_LITERAL(55, 14),  // "signalSendData"
        QT_MOC_LITERAL(70, 5),  // "ReqId"
        QT_MOC_LITERAL(76, 5),  // "reqId"
        QT_MOC_LITERAL(82, 4),  // "data"
        QT_MOC_LITERAL(87, 18),  // "signalSwichChatdlg"
        QT_MOC_LITERAL(106, 17),  // "signalLoginFailed"
        QT_MOC_LITERAL(124, 17),  // "signalFriendApply"
        QT_MOC_LITERAL(142, 7),  // "from_id"
        QT_MOC_LITERAL(150, 4),  // "name"
        QT_MOC_LITERAL(155, 4),  // "desc"
        QT_MOC_LITERAL(160, 19),  // "signalAddAuthFriend"
        QT_MOC_LITERAL(180, 3),  // "uid"
        QT_MOC_LITERAL(184, 4),  // "nick"
        QT_MOC_LITERAL(189, 4),  // "icon"
        QT_MOC_LITERAL(194, 3),  // "sex"
        QT_MOC_LITERAL(198, 13),  // "signalAuthRsp"
        QT_MOC_LITERAL(212, 14),  // "slotTcpConnect"
        QT_MOC_LITERAL(227, 10),  // "ServerInfo"
        QT_MOC_LITERAL(238, 12)   // "slotSendData"
    },
    "TcpMgr",
    "QML.Element",
    "auto",
    "signalConnectSuccess",
    "",
    "bsuccess",
    "signalSendData",
    "ReqId",
    "reqId",
    "data",
    "signalSwichChatdlg",
    "signalLoginFailed",
    "signalFriendApply",
    "from_id",
    "name",
    "desc",
    "signalAddAuthFriend",
    "uid",
    "nick",
    "icon",
    "sex",
    "signalAuthRsp",
    "slotTcpConnect",
    "ServerInfo",
    "slotSendData"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSTcpMgrENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       1,   14, // classinfo
       9,   16, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // classinfo: key, value
       1,    2,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       3,    1,   70,    4, 0x06,    1 /* Public */,
       6,    2,   73,    4, 0x06,    3 /* Public */,
      10,    0,   78,    4, 0x06,    6 /* Public */,
      11,    1,   79,    4, 0x06,    7 /* Public */,
      12,    3,   82,    4, 0x06,    9 /* Public */,
      16,    5,   89,    4, 0x06,   13 /* Public */,
      21,    5,  100,    4, 0x06,   19 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      22,    1,  111,    4, 0x0a,   25 /* Public */,
      24,    2,  114,    4, 0x0a,   27 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, 0x80000000 | 7, QMetaType::QString,    8,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString,   13,   14,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,   17,   14,   18,   19,   20,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,   17,   14,   18,   19,   20,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 23,    4,
    QMetaType::Void, 0x80000000 | 7, QMetaType::QString,    8,    9,

       0        // eod
};

Q_CONSTINIT const QMetaObject TcpMgr::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSTcpMgrENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSTcpMgrENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_metaTypeArray<
        // Q_OBJECT / Q_GADGET
        TcpMgr,
        // method 'signalConnectSuccess'
        void,
        bool,
        // method 'signalSendData'
        void,
        ReqId,
        QString,
        // method 'signalSwichChatdlg'
        void,
        // method 'signalLoginFailed'
        void,
        int,
        // method 'signalFriendApply'
        void,
        int,
        QString,
        QString,
        // method 'signalAddAuthFriend'
        void,
        int,
        QString,
        QString,
        QString,
        int,
        // method 'signalAuthRsp'
        void,
        int,
        QString,
        QString,
        QString,
        int,
        // method 'slotTcpConnect'
        void,
        ServerInfo,
        // method 'slotSendData'
        void,
        ReqId,
        QString
    >,
    nullptr
} };

void TcpMgr::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TcpMgr *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->signalConnectSuccess((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->signalSendData((*reinterpret_cast< std::add_pointer_t<ReqId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 2: _t->signalSwichChatdlg(); break;
        case 3: _t->signalLoginFailed((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->signalFriendApply((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 5: _t->signalAddAuthFriend((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5]))); break;
        case 6: _t->signalAuthRsp((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5]))); break;
        case 7: _t->slotTcpConnect((*reinterpret_cast< std::add_pointer_t<ServerInfo>>(_a[1]))); break;
        case 8: _t->slotSendData((*reinterpret_cast< std::add_pointer_t<ReqId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TcpMgr::*)(bool );
            if (_t _q_method = &TcpMgr::signalConnectSuccess; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TcpMgr::*)(ReqId , QString );
            if (_t _q_method = &TcpMgr::signalSendData; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TcpMgr::*)();
            if (_t _q_method = &TcpMgr::signalSwichChatdlg; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (TcpMgr::*)(int );
            if (_t _q_method = &TcpMgr::signalLoginFailed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (TcpMgr::*)(int , QString , QString );
            if (_t _q_method = &TcpMgr::signalFriendApply; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (TcpMgr::*)(int , QString , QString , QString , int );
            if (_t _q_method = &TcpMgr::signalAddAuthFriend; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (TcpMgr::*)(int , QString , QString , QString , int );
            if (_t _q_method = &TcpMgr::signalAuthRsp; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject *TcpMgr::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TcpMgr::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSTcpMgrENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TcpMgr::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void TcpMgr::signalConnectSuccess(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TcpMgr::signalSendData(ReqId _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TcpMgr::signalSwichChatdlg()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void TcpMgr::signalLoginFailed(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void TcpMgr::signalFriendApply(int _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void TcpMgr::signalAddAuthFriend(int _t1, QString _t2, QString _t3, QString _t4, int _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void TcpMgr::signalAuthRsp(int _t1, QString _t2, QString _t3, QString _t4, int _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
