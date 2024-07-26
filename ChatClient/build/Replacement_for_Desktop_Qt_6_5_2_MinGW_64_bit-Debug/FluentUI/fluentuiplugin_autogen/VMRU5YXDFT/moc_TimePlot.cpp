/****************************************************************************
** Meta object code from reading C++ file 'TimePlot.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../FluentUI/qmlcustomplot/TimePlot.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TimePlot.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSQmlQCustomPlotSCOPETimePlotENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSQmlQCustomPlotSCOPETimePlotENDCLASS = QtMocHelpers::stringData(
    "QmlQCustomPlot::TimePlot",
    "QML.Element",
    "auto",
    "plotTimeRangeInMillisecondsChanged",
    "",
    "setTimeFormat",
    "format",
    "addCurrentTimeValue",
    "name",
    "value",
    "addCurrentTimeValues",
    "values",
    "plotTimeRangeInMilliseconds"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSQmlQCustomPlotSCOPETimePlotENDCLASS_t {
    uint offsetsAndSizes[26];
    char stringdata0[25];
    char stringdata1[12];
    char stringdata2[5];
    char stringdata3[35];
    char stringdata4[1];
    char stringdata5[14];
    char stringdata6[7];
    char stringdata7[20];
    char stringdata8[5];
    char stringdata9[6];
    char stringdata10[21];
    char stringdata11[7];
    char stringdata12[28];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSQmlQCustomPlotSCOPETimePlotENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSQmlQCustomPlotSCOPETimePlotENDCLASS_t qt_meta_stringdata_CLASSQmlQCustomPlotSCOPETimePlotENDCLASS = {
    {
        QT_MOC_LITERAL(0, 24),  // "QmlQCustomPlot::TimePlot"
        QT_MOC_LITERAL(25, 11),  // "QML.Element"
        QT_MOC_LITERAL(37, 4),  // "auto"
        QT_MOC_LITERAL(42, 34),  // "plotTimeRangeInMillisecondsCh..."
        QT_MOC_LITERAL(77, 0),  // ""
        QT_MOC_LITERAL(78, 13),  // "setTimeFormat"
        QT_MOC_LITERAL(92, 6),  // "format"
        QT_MOC_LITERAL(99, 19),  // "addCurrentTimeValue"
        QT_MOC_LITERAL(119, 4),  // "name"
        QT_MOC_LITERAL(124, 5),  // "value"
        QT_MOC_LITERAL(130, 20),  // "addCurrentTimeValues"
        QT_MOC_LITERAL(151, 6),  // "values"
        QT_MOC_LITERAL(158, 27)   // "plotTimeRangeInMilliseconds"
    },
    "QmlQCustomPlot::TimePlot",
    "QML.Element",
    "auto",
    "plotTimeRangeInMillisecondsChanged",
    "",
    "setTimeFormat",
    "format",
    "addCurrentTimeValue",
    "name",
    "value",
    "addCurrentTimeValues",
    "values",
    "plotTimeRangeInMilliseconds"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSQmlQCustomPlotSCOPETimePlotENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       1,   14, // classinfo
       4,   16, // methods
       1,   54, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // classinfo: key, value
       1,    2,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       3,    1,   40,    4, 0x06,    2 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       5,    1,   43,    4, 0x02,    4 /* Public */,
       7,    2,   46,    4, 0x02,    6 /* Public */,
      10,    1,   51,    4, 0x02,    9 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    4,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::Double,    8,    9,
    QMetaType::Void, QMetaType::QVariantMap,   11,

 // properties: name, type, flags
      12, QMetaType::Int, 0x00015003, uint(0), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QmlQCustomPlot::TimePlot::staticMetaObject = { {
    QMetaObject::SuperData::link<BasePlot::staticMetaObject>(),
    qt_meta_stringdata_CLASSQmlQCustomPlotSCOPETimePlotENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSQmlQCustomPlotSCOPETimePlotENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_metaTypeArray<
        // property 'plotTimeRangeInMilliseconds'
        int,
        // Q_OBJECT / Q_GADGET
        TimePlot,
        // method 'plotTimeRangeInMillisecondsChanged'
        void,
        int,
        // method 'setTimeFormat'
        void,
        const QString &,
        // method 'addCurrentTimeValue'
        void,
        const QString &,
        double,
        // method 'addCurrentTimeValues'
        void,
        QVariantMap
    >,
    nullptr
} };

void QmlQCustomPlot::TimePlot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TimePlot *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->plotTimeRangeInMillisecondsChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->setTimeFormat((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->addCurrentTimeValue((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2]))); break;
        case 3: _t->addCurrentTimeValues((*reinterpret_cast< std::add_pointer_t<QVariantMap>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TimePlot::*)(int );
            if (_t _q_method = &TimePlot::plotTimeRangeInMillisecondsChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    } else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<TimePlot *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->plotTimeRangeInMilliseconds(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<TimePlot *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->set_plotTimeRangeInMilliseconds(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *QmlQCustomPlot::TimePlot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QmlQCustomPlot::TimePlot::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSQmlQCustomPlotSCOPETimePlotENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return BasePlot::qt_metacast(_clname);
}

int QmlQCustomPlot::TimePlot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasePlot::qt_metacall(_c, _id, _a);
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
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void QmlQCustomPlot::TimePlot::plotTimeRangeInMillisecondsChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
