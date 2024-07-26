/****************************************************************************
** Meta object code from reading C++ file 'Def.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/Def.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Def.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSChatUIModeTypeENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSChatUIModeTypeENDCLASS = QtMocHelpers::stringData(
    "ChatUIModeType",
    "QML.Element",
    "ChatUIMode",
    "SearchMode",
    "ChatMode",
    "ContactMode"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSChatUIModeTypeENDCLASS_t {
    uint offsetsAndSizes[12];
    char stringdata0[15];
    char stringdata1[12];
    char stringdata2[11];
    char stringdata3[11];
    char stringdata4[9];
    char stringdata5[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSChatUIModeTypeENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSChatUIModeTypeENDCLASS_t qt_meta_stringdata_CLASSChatUIModeTypeENDCLASS = {
    {
        QT_MOC_LITERAL(0, 14),  // "ChatUIModeType"
        QT_MOC_LITERAL(15, 11),  // "QML.Element"
        QT_MOC_LITERAL(27, 10),  // "ChatUIMode"
        QT_MOC_LITERAL(38, 10),  // "SearchMode"
        QT_MOC_LITERAL(49, 8),  // "ChatMode"
        QT_MOC_LITERAL(58, 11)   // "ContactMode"
    },
    "ChatUIModeType",
    "QML.Element",
    "ChatUIMode",
    "SearchMode",
    "ChatMode",
    "ContactMode"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSChatUIModeTypeENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       1,   14, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   16, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // classinfo: key, value
       1,    0,

 // enums: name, alias, flags, count, data
       2,    2, 0x0,    3,   21,

 // enum data: key, value
       3, uint(ChatUIModeType::SearchMode),
       4, uint(ChatUIModeType::ChatMode),
       5, uint(ChatUIModeType::ContactMode),

       0        // eod
};

Q_CONSTINIT const QMetaObject ChatUIModeType::staticMetaObject = { {
    nullptr,
    qt_meta_stringdata_CLASSChatUIModeTypeENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSChatUIModeTypeENDCLASS,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSChatUIModeTypeENDCLASS_t,
        // enum 'ChatUIMode'
        QtPrivate::TypeAndForceComplete<ChatUIModeType::ChatUIMode, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<void, std::true_type>
    >,
    nullptr
} };

QT_WARNING_POP
