/****************************************************************************
** Meta object code from reading C++ file 'bin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../test/Bin/bin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Bin_t {
    QByteArrayData data[10];
    char stringdata0[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Bin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Bin_t qt_meta_stringdata_Bin = {
    {
QT_MOC_LITERAL(0, 0, 3), // "Bin"
QT_MOC_LITERAL(1, 4, 10), // "AddPeerLan"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 10), // "AddPeerWan"
QT_MOC_LITERAL(4, 27, 11), // "AddPeerNick"
QT_MOC_LITERAL(5, 39, 10), // "DeletePeer"
QT_MOC_LITERAL(6, 50, 11), // "GetNickname"
QT_MOC_LITERAL(7, 62, 15), // "QList<QString>&"
QT_MOC_LITERAL(8, 78, 4), // "nick"
QT_MOC_LITERAL(9, 83, 4) // "Test"

    },
    "Bin\0AddPeerLan\0\0AddPeerWan\0AddPeerNick\0"
    "DeletePeer\0GetNickname\0QList<QString>&\0"
    "nick\0Test"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Bin[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    1,   48,    2, 0x0a /* Public */,
       9,    0,   51,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,

       0        // eod
};

void Bin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Bin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->AddPeerLan(); break;
        case 1: _t->AddPeerWan(); break;
        case 2: _t->AddPeerNick(); break;
        case 3: _t->DeletePeer(); break;
        case 4: _t->GetNickname((*reinterpret_cast< QList<QString>(*)>(_a[1]))); break;
        case 5: _t->Test(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Bin::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Bin.data,
    qt_meta_data_Bin,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Bin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Bin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Bin.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Bin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
