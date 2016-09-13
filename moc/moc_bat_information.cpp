/****************************************************************************
** Meta object code from reading C++ file 'bat_information.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../main/ui/bat_information.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bat_information.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_bat_information_t {
    QByteArrayData data[5];
    char stringdata0[58];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_bat_information_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_bat_information_t qt_meta_stringdata_bat_information = {
    {
QT_MOC_LITERAL(0, 0, 15), // "bat_information"
QT_MOC_LITERAL(1, 16, 11), // "change_moni"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 13), // "change_equinf"
QT_MOC_LITERAL(4, 43, 14) // "change_billinf"

    },
    "bat_information\0change_moni\0\0change_equinf\0"
    "change_billinf"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_bat_information[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void bat_information::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        bat_information *_t = static_cast<bat_information *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->change_moni(); break;
        case 1: _t->change_equinf(); break;
        case 2: _t->change_billinf(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject bat_information::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_bat_information.data,
      qt_meta_data_bat_information,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *bat_information::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *bat_information::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_bat_information.stringdata0))
        return static_cast<void*>(const_cast< bat_information*>(this));
    return QWidget::qt_metacast(_clname);
}

int bat_information::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
