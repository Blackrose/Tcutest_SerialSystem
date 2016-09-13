/****************************************************************************
** Meta object code from reading C++ file 'test_manual.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../main/test_manual.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'test_manual.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_test_Manual_t {
    QByteArrayData data[10];
    char stringdata0[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_test_Manual_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_test_Manual_t qt_meta_stringdata_test_Manual = {
    {
QT_MOC_LITERAL(0, 0, 11), // "test_Manual"
QT_MOC_LITERAL(1, 12, 9), // "slot_hide"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 9), // "slot_card"
QT_MOC_LITERAL(4, 33, 10), // "slot_emter"
QT_MOC_LITERAL(5, 44, 11), // "slot_canbus"
QT_MOC_LITERAL(6, 56, 8), // "slot_gps"
QT_MOC_LITERAL(7, 65, 9), // "slot_gprs"
QT_MOC_LITERAL(8, 75, 12), // "slot_network"
QT_MOC_LITERAL(9, 88, 10) // "slot_touch"

    },
    "test_Manual\0slot_hide\0\0slot_card\0"
    "slot_emter\0slot_canbus\0slot_gps\0"
    "slot_gprs\0slot_network\0slot_touch"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_test_Manual[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    0,   60,    2, 0x0a /* Public */,
       9,    0,   61,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void test_Manual::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        test_Manual *_t = static_cast<test_Manual *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_hide(); break;
        case 1: _t->slot_card(); break;
        case 2: _t->slot_emter(); break;
        case 3: _t->slot_canbus(); break;
        case 4: _t->slot_gps(); break;
        case 5: _t->slot_gprs(); break;
        case 6: _t->slot_network(); break;
        case 7: _t->slot_touch(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject test_Manual::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_test_Manual.data,
      qt_meta_data_test_Manual,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *test_Manual::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *test_Manual::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_test_Manual.stringdata0))
        return static_cast<void*>(const_cast< test_Manual*>(this));
    return QWidget::qt_metacast(_clname);
}

int test_Manual::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
