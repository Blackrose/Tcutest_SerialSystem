/****************************************************************************
** Meta object code from reading C++ file 'charging_monitoring.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../main/ui/charging_monitoring.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'charging_monitoring.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Charging_monitoring_t {
    QByteArrayData data[11];
    char stringdata0[143];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Charging_monitoring_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Charging_monitoring_t qt_meta_stringdata_Charging_monitoring = {
    {
QT_MOC_LITERAL(0, 0, 19), // "Charging_monitoring"
QT_MOC_LITERAL(1, 20, 7), // "set_soc"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 11), // "change_moni"
QT_MOC_LITERAL(4, 41, 13), // "change_equinf"
QT_MOC_LITERAL(5, 55, 13), // "change_batinf"
QT_MOC_LITERAL(6, 69, 14), // "change_billinf"
QT_MOC_LITERAL(7, 84, 10), // "change_end"
QT_MOC_LITERAL(8, 95, 24), // "Charging_monitoring_hide"
QT_MOC_LITERAL(9, 120, 11), // "change_main"
QT_MOC_LITERAL(10, 132, 10) // "slot_timer"

    },
    "Charging_monitoring\0set_soc\0\0change_moni\0"
    "change_equinf\0change_batinf\0change_billinf\0"
    "change_end\0Charging_monitoring_hide\0"
    "change_main\0slot_timer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Charging_monitoring[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x0a /* Public */,
       4,    0,   61,    2, 0x0a /* Public */,
       5,    0,   62,    2, 0x0a /* Public */,
       6,    0,   63,    2, 0x0a /* Public */,
       7,    0,   64,    2, 0x0a /* Public */,
       8,    0,   65,    2, 0x0a /* Public */,
       9,    0,   66,    2, 0x0a /* Public */,
      10,    0,   67,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
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

void Charging_monitoring::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Charging_monitoring *_t = static_cast<Charging_monitoring *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->set_soc(); break;
        case 1: _t->change_moni(); break;
        case 2: _t->change_equinf(); break;
        case 3: _t->change_batinf(); break;
        case 4: _t->change_billinf(); break;
        case 5: _t->change_end(); break;
        case 6: _t->Charging_monitoring_hide(); break;
        case 7: _t->change_main(); break;
        case 8: _t->slot_timer(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Charging_monitoring::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Charging_monitoring.data,
      qt_meta_data_Charging_monitoring,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Charging_monitoring::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Charging_monitoring::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Charging_monitoring.stringdata0))
        return static_cast<void*>(const_cast< Charging_monitoring*>(this));
    return QWidget::qt_metacast(_clname);
}

int Charging_monitoring::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
