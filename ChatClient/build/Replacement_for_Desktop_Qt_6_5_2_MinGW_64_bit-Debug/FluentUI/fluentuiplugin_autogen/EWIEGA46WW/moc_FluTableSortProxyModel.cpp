/****************************************************************************
** Meta object code from reading C++ file 'FluTableSortProxyModel.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../FluentUI/FluTableSortProxyModel.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FluTableSortProxyModel.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSFluTableSortProxyModelENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSFluTableSortProxyModelENDCLASS = QtMocHelpers::stringData(
    "FluTableSortProxyModel",
    "QML.Element",
    "modelChanged",
    "",
    "getRow",
    "rowIndex",
    "setRow",
    "val",
    "insertRow",
    "removeRow",
    "rows",
    "setComparator",
    "QJSValue",
    "comparator",
    "setFilter",
    "filter",
    "model"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSFluTableSortProxyModelENDCLASS_t {
    uint offsetsAndSizes[34];
    char stringdata0[23];
    char stringdata1[12];
    char stringdata2[13];
    char stringdata3[1];
    char stringdata4[7];
    char stringdata5[9];
    char stringdata6[7];
    char stringdata7[4];
    char stringdata8[10];
    char stringdata9[10];
    char stringdata10[5];
    char stringdata11[14];
    char stringdata12[9];
    char stringdata13[11];
    char stringdata14[10];
    char stringdata15[7];
    char stringdata16[6];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSFluTableSortProxyModelENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSFluTableSortProxyModelENDCLASS_t qt_meta_stringdata_CLASSFluTableSortProxyModelENDCLASS = {
    {
        QT_MOC_LITERAL(0, 22),  // "FluTableSortProxyModel"
        QT_MOC_LITERAL(23, 11),  // "QML.Element"
        QT_MOC_LITERAL(35, 12),  // "modelChanged"
        QT_MOC_LITERAL(48, 0),  // ""
        QT_MOC_LITERAL(49, 6),  // "getRow"
        QT_MOC_LITERAL(56, 8),  // "rowIndex"
        QT_MOC_LITERAL(65, 6),  // "setRow"
        QT_MOC_LITERAL(72, 3),  // "val"
        QT_MOC_LITERAL(76, 9),  // "insertRow"
        QT_MOC_LITERAL(86, 9),  // "removeRow"
        QT_MOC_LITERAL(96, 4),  // "rows"
        QT_MOC_LITERAL(101, 13),  // "setComparator"
        QT_MOC_LITERAL(115, 8),  // "QJSValue"
        QT_MOC_LITERAL(124, 10),  // "comparator"
        QT_MOC_LITERAL(135, 9),  // "setFilter"
        QT_MOC_LITERAL(145, 6),  // "filter"
        QT_MOC_LITERAL(152, 5)   // "model"
    },
    "FluTableSortProxyModel",
    "QML.Element",
    "modelChanged",
    "",
    "getRow",
    "rowIndex",
    "setRow",
    "val",
    "insertRow",
    "removeRow",
    "rows",
    "setComparator",
    "QJSValue",
    "comparator",
    "setFilter",
    "filter",
    "model"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSFluTableSortProxyModelENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       1,   14, // classinfo
       7,   16, // methods
       1,   83, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // classinfo: key, value
       1,    0,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       2,    0,   58,    3, 0x06,    2 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       4,    1,   59,    3, 0x02,    3 /* Public */,
       6,    2,   62,    3, 0x02,    5 /* Public */,
       8,    2,   67,    3, 0x02,    8 /* Public */,
       9,    2,   72,    3, 0x02,   11 /* Public */,
      11,    1,   77,    3, 0x02,   14 /* Public */,
      14,    1,   80,    3, 0x02,   16 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::QVariant, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::QVariant,    5,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::QVariant,    5,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,   10,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   15,

 // properties: name, type, flags
      16, QMetaType::QVariant, 0x00015003, uint(0), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject FluTableSortProxyModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QSortFilterProxyModel::staticMetaObject>(),
    qt_meta_stringdata_CLASSFluTableSortProxyModelENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSFluTableSortProxyModelENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_metaTypeArray<
        // property 'model'
        QVariant,
        // Q_OBJECT / Q_GADGET
        FluTableSortProxyModel,
        // method 'modelChanged'
        void,
        // method 'getRow'
        QVariant,
        int,
        // method 'setRow'
        void,
        int,
        const QVariant &,
        // method 'insertRow'
        void,
        int,
        const QVariant &,
        // method 'removeRow'
        void,
        int,
        int,
        // method 'setComparator'
        void,
        const QJSValue &,
        // method 'setFilter'
        void,
        const QJSValue &
    >,
    nullptr
} };

void FluTableSortProxyModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FluTableSortProxyModel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->modelChanged(); break;
        case 1: { QVariant _r = _t->getRow((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->setRow((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QVariant>>(_a[2]))); break;
        case 3: _t->insertRow((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QVariant>>(_a[2]))); break;
        case 4: _t->removeRow((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 5: _t->setComparator((*reinterpret_cast< std::add_pointer_t<QJSValue>>(_a[1]))); break;
        case 6: _t->setFilter((*reinterpret_cast< std::add_pointer_t<QJSValue>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QJSValue >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QJSValue >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FluTableSortProxyModel::*)();
            if (_t _q_method = &FluTableSortProxyModel::modelChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    } else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<FluTableSortProxyModel *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QVariant*>(_v) = _t->_model; break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<FluTableSortProxyModel *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0:
            if (_t->_model != *reinterpret_cast< QVariant*>(_v)) {
                _t->_model = *reinterpret_cast< QVariant*>(_v);
                Q_EMIT _t->modelChanged();
            }
            break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *FluTableSortProxyModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FluTableSortProxyModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSFluTableSortProxyModelENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QSortFilterProxyModel::qt_metacast(_clname);
}

int FluTableSortProxyModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSortFilterProxyModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void FluTableSortProxyModel::modelChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
