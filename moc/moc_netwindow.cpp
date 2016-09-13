/****************************************************************************
** Meta object code from reading C++ file 'netwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../network/netwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'netwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NetWindow_t {
    QByteArrayData data[20];
    char stringdata0[205];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NetWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NetWindow_t qt_meta_stringdata_NetWindow = {
    {
QT_MOC_LITERAL(0, 0, 9), // "NetWindow"
QT_MOC_LITERAL(1, 10, 11), // "sel_changed"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 4), // "text"
QT_MOC_LITERAL(4, 28, 7), // "toggled"
QT_MOC_LITERAL(5, 36, 1), // "b"
QT_MOC_LITERAL(6, 38, 13), // "on_ok_clicked"
QT_MOC_LITERAL(7, 52, 17), // "refreshInterfaces"
QT_MOC_LITERAL(8, 70, 13), // "refreship_inf"
QT_MOC_LITERAL(9, 84, 11), // "readConfigs"
QT_MOC_LITERAL(10, 96, 12), // "writeConfigs"
QT_MOC_LITERAL(11, 109, 5), // "state"
QT_MOC_LITERAL(12, 115, 4), // "dhcp"
QT_MOC_LITERAL(13, 120, 13), // "proc_finished"
QT_MOC_LITERAL(14, 134, 4), // "code"
QT_MOC_LITERAL(15, 139, 15), // "on_ping_clicked"
QT_MOC_LITERAL(16, 155, 15), // "on_stop_clicked"
QT_MOC_LITERAL(17, 171, 16), // "on_clear_clicked"
QT_MOC_LITERAL(18, 188, 6), // "result"
QT_MOC_LITERAL(19, 195, 9) // "slot_hide"

    },
    "NetWindow\0sel_changed\0\0text\0toggled\0"
    "b\0on_ok_clicked\0refreshInterfaces\0"
    "refreship_inf\0readConfigs\0writeConfigs\0"
    "state\0dhcp\0proc_finished\0code\0"
    "on_ping_clicked\0on_stop_clicked\0"
    "on_clear_clicked\0result\0slot_hide"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NetWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x0a /* Public */,
       4,    1,   87,    2, 0x0a /* Public */,
       6,    0,   90,    2, 0x0a /* Public */,
       7,    0,   91,    2, 0x0a /* Public */,
       8,    0,   92,    2, 0x0a /* Public */,
       9,    0,   93,    2, 0x0a /* Public */,
      10,    0,   94,    2, 0x0a /* Public */,
      11,    1,   95,    2, 0x0a /* Public */,
      13,    1,   98,    2, 0x0a /* Public */,
      15,    0,  101,    2, 0x0a /* Public */,
      16,    0,  102,    2, 0x0a /* Public */,
      17,    0,  103,    2, 0x0a /* Public */,
      18,    0,  104,    2, 0x0a /* Public */,
      19,    0,  105,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void NetWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NetWindow *_t = static_cast<NetWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sel_changed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_ok_clicked(); break;
        case 3: _t->refreshInterfaces(); break;
        case 4: _t->refreship_inf(); break;
        case 5: _t->readConfigs(); break;
        case 6: _t->writeConfigs(); break;
        case 7: _t->state((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->proc_finished((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_ping_clicked(); break;
        case 10: _t->on_stop_clicked(); break;
        case 11: _t->on_clear_clicked(); break;
        case 12: _t->result(); break;
        case 13: _t->slot_hide(); break;
        default: ;
        }
    }
}

const QMetaObject NetWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_NetWindow.data,
      qt_meta_data_NetWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NetWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NetWindow.stringdata0))
        return static_cast<void*>(const_cast< NetWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int NetWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
