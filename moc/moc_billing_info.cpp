/****************************************************************************
** Meta object code from reading C++ file 'billing_info.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../main/ui/billing_info.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'billing_info.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Billing_info_t {
    QByteArrayData data[5];
    char stringdata0[54];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Billing_info_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Billing_info_t qt_meta_stringdata_Billing_info = {
    {
QT_MOC_LITERAL(0, 0, 12), // "Billing_info"
QT_MOC_LITERAL(1, 13, 11), // "change_moni"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 13), // "change_equinf"
QT_MOC_LITERAL(4, 40, 13) // "change_batinf"

    },
    "Billing_info\0change_moni\0\0change_equinf\0"
    "change_batinf"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Billing_info[] = {

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

void Billing_info::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Billing_info *_t = static_cast<Billing_info *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->change_moni(); break;
        case 1: _t->change_equinf(); break;
        case 2: _t->change_batinf(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Billing_info::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Billing_info.data,
      qt_meta_data_Billing_info,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Billing_info::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Billing_info::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Billing_info.stringdata0))
        return static_cast<void*>(const_cast< Billing_info*>(this));
    return QWidget::qt_metacast(_clname);
}

int Billing_info::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
