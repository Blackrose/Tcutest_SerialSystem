/****************************************************************************
** Meta object code from reading C++ file 'Emter_window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qcom/Emter_window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Emter_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EmterWindow_t {
    QByteArrayData data[21];
    char stringdata0[416];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EmterWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EmterWindow_t qt_meta_stringdata_EmterWindow = {
    {
QT_MOC_LITERAL(0, 0, 11), // "EmterWindow"
QT_MOC_LITERAL(1, 12, 30), // "on_actionWriteToFile_triggered"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 28), // "on_actionCleanPort_triggered"
QT_MOC_LITERAL(4, 73, 27), // "on_actionLoadfile_triggered"
QT_MOC_LITERAL(5, 101, 28), // "on_delayspinBox_valueChanged"
QT_MOC_LITERAL(6, 130, 22), // "on_actionAdd_triggered"
QT_MOC_LITERAL(7, 153, 23), // "on_actionExit_triggered"
QT_MOC_LITERAL(8, 177, 23), // "on_actionSave_triggered"
QT_MOC_LITERAL(9, 201, 22), // "on_obocheckBox_clicked"
QT_MOC_LITERAL(10, 224, 29), // "on_actionClearBytes_triggered"
QT_MOC_LITERAL(11, 254, 24), // "on_actionClose_triggered"
QT_MOC_LITERAL(12, 279, 23), // "on_actionOpen_triggered"
QT_MOC_LITERAL(13, 303, 21), // "on_clearUpBtn_clicked"
QT_MOC_LITERAL(14, 325, 21), // "on_sendmsgBtn_clicked"
QT_MOC_LITERAL(15, 347, 9), // "readMyCom"
QT_MOC_LITERAL(16, 357, 7), // "sendMsg"
QT_MOC_LITERAL(17, 365, 12), // "changedIndex"
QT_MOC_LITERAL(18, 378, 5), // "index"
QT_MOC_LITERAL(19, 384, 15), // "changeaddrIndex"
QT_MOC_LITERAL(20, 400, 15) // "changeadirIndex"

    },
    "EmterWindow\0on_actionWriteToFile_triggered\0"
    "\0on_actionCleanPort_triggered\0"
    "on_actionLoadfile_triggered\0"
    "on_delayspinBox_valueChanged\0"
    "on_actionAdd_triggered\0on_actionExit_triggered\0"
    "on_actionSave_triggered\0on_obocheckBox_clicked\0"
    "on_actionClearBytes_triggered\0"
    "on_actionClose_triggered\0"
    "on_actionOpen_triggered\0on_clearUpBtn_clicked\0"
    "on_sendmsgBtn_clicked\0readMyCom\0sendMsg\0"
    "changedIndex\0index\0changeaddrIndex\0"
    "changeadirIndex"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EmterWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x08 /* Private */,
       3,    0,  105,    2, 0x08 /* Private */,
       4,    0,  106,    2, 0x08 /* Private */,
       5,    1,  107,    2, 0x08 /* Private */,
       6,    0,  110,    2, 0x08 /* Private */,
       7,    0,  111,    2, 0x08 /* Private */,
       8,    0,  112,    2, 0x08 /* Private */,
       9,    0,  113,    2, 0x08 /* Private */,
      10,    0,  114,    2, 0x08 /* Private */,
      11,    0,  115,    2, 0x08 /* Private */,
      12,    0,  116,    2, 0x08 /* Private */,
      13,    0,  117,    2, 0x08 /* Private */,
      14,    0,  118,    2, 0x08 /* Private */,
      15,    0,  119,    2, 0x08 /* Private */,
      16,    0,  120,    2, 0x08 /* Private */,
      17,    1,  121,    2, 0x08 /* Private */,
      19,    1,  124,    2, 0x08 /* Private */,
      20,    1,  127,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::Int,   18,

       0        // eod
};

void EmterWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EmterWindow *_t = static_cast<EmterWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_actionWriteToFile_triggered(); break;
        case 1: _t->on_actionCleanPort_triggered(); break;
        case 2: _t->on_actionLoadfile_triggered(); break;
        case 3: _t->on_delayspinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_actionAdd_triggered(); break;
        case 5: _t->on_actionExit_triggered(); break;
        case 6: _t->on_actionSave_triggered(); break;
        case 7: _t->on_obocheckBox_clicked(); break;
        case 8: _t->on_actionClearBytes_triggered(); break;
        case 9: _t->on_actionClose_triggered(); break;
        case 10: _t->on_actionOpen_triggered(); break;
        case 11: _t->on_clearUpBtn_clicked(); break;
        case 12: _t->on_sendmsgBtn_clicked(); break;
        case 13: _t->readMyCom(); break;
        case 14: _t->sendMsg(); break;
        case 15: _t->changedIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->changeaddrIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->changeadirIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject EmterWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_EmterWindow.data,
      qt_meta_data_EmterWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *EmterWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EmterWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_EmterWindow.stringdata0))
        return static_cast<void*>(const_cast< EmterWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int EmterWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
