/****************************************************************************
** Meta object code from reading C++ file 'msgrectangle.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/msgrectangle.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'msgrectangle.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSMsgRectangleENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMsgRectangleENDCLASS = QtMocHelpers::stringData(
    "MsgRectangle",
    "QML.Element",
    "auto",
    "isLeftChanged",
    "",
    "colorChanged",
    "colorChange",
    "isLeftChange",
    "isLeft",
    "color"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMsgRectangleENDCLASS_t {
    uint offsetsAndSizes[20];
    char stringdata0[13];
    char stringdata1[12];
    char stringdata2[5];
    char stringdata3[14];
    char stringdata4[1];
    char stringdata5[13];
    char stringdata6[12];
    char stringdata7[13];
    char stringdata8[7];
    char stringdata9[6];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMsgRectangleENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMsgRectangleENDCLASS_t qt_meta_stringdata_CLASSMsgRectangleENDCLASS = {
    {
        QT_MOC_LITERAL(0, 12),  // "MsgRectangle"
        QT_MOC_LITERAL(13, 11),  // "QML.Element"
        QT_MOC_LITERAL(25, 4),  // "auto"
        QT_MOC_LITERAL(30, 13),  // "isLeftChanged"
        QT_MOC_LITERAL(44, 0),  // ""
        QT_MOC_LITERAL(45, 12),  // "colorChanged"
        QT_MOC_LITERAL(58, 11),  // "colorChange"
        QT_MOC_LITERAL(70, 12),  // "isLeftChange"
        QT_MOC_LITERAL(83, 6),  // "isLeft"
        QT_MOC_LITERAL(90, 5)   // "color"
    },
    "MsgRectangle",
    "QML.Element",
    "auto",
    "isLeftChanged",
    "",
    "colorChanged",
    "colorChange",
    "isLeftChange",
    "isLeft",
    "color"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMsgRectangleENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       1,   14, // classinfo
       4,   16, // methods
       2,   44, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // classinfo: key, value
       1,    2,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   40,    4, 0x06,    3 /* Public */,
       5,    0,   41,    4, 0x06,    4 /* Public */,
       6,    0,   42,    4, 0x04,    5 /* Private */,
       7,    0,   43,    4, 0x04,    6 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       8, QMetaType::Bool, 0x00015003, uint(0), 0,
       9, QMetaType::QColor, 0x00015003, uint(1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject MsgRectangle::staticMetaObject = { {
    QMetaObject::SuperData::link<QQuickPaintedItem::staticMetaObject>(),
    qt_meta_stringdata_CLASSMsgRectangleENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMsgRectangleENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_metaTypeArray<
        // property 'isLeft'
        bool,
        // property 'color'
        QColor,
        // Q_OBJECT / Q_GADGET
        MsgRectangle,
        // method 'isLeftChanged'
        void,
        // method 'colorChanged'
        void,
        // method 'colorChange'
        void,
        // method 'isLeftChange'
        void
    >,
    nullptr
} };

void MsgRectangle::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MsgRectangle *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->isLeftChanged(); break;
        case 1: _t->colorChanged(); break;
        case 2: _t->colorChange(); break;
        case 3: _t->isLeftChange(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MsgRectangle::*)();
            if (_t _q_method = &MsgRectangle::isLeftChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MsgRectangle::*)();
            if (_t _q_method = &MsgRectangle::colorChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MsgRectangle::*)();
            if (_t _q_method = &MsgRectangle::colorChange; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MsgRectangle::*)();
            if (_t _q_method = &MsgRectangle::isLeftChange; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    } else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<MsgRectangle *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->_isLeft; break;
        case 1: *reinterpret_cast< QColor*>(_v) = _t->_color; break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<MsgRectangle *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0:
            if (_t->_isLeft != *reinterpret_cast< bool*>(_v)) {
                _t->_isLeft = *reinterpret_cast< bool*>(_v);
                Q_EMIT _t->isLeftChanged();
            }
            break;
        case 1:
            if (_t->_color != *reinterpret_cast< QColor*>(_v)) {
                _t->_color = *reinterpret_cast< QColor*>(_v);
                Q_EMIT _t->colorChanged();
            }
            break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_a;
}

const QMetaObject *MsgRectangle::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MsgRectangle::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMsgRectangleENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QQuickPaintedItem::qt_metacast(_clname);
}

int MsgRectangle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QQuickPaintedItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void MsgRectangle::isLeftChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MsgRectangle::colorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MsgRectangle::colorChange()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MsgRectangle::isLeftChange()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
