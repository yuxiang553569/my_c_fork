/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Fri Sep 4 15:12:02 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      34,   11,   11,   11, 0x08,
      55,   11,   11,   11, 0x08,
      76,   11,   11,   11, 0x08,
      99,   11,   11,   11, 0x08,
     118,   11,   11,   11, 0x08,
     140,   11,   11,   11, 0x08,
     161,   11,   11,   11, 0x08,
     183,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_rightbtn_clicked()\0"
    "on_downbtn_clicked()\0on_leftbtn_clicked()\0"
    "on_didownbtn_clicked()\0on_upbtn_clicked()\0"
    "on_pausebtn_clicked()\0on_overbtn_clicked()\0"
    "on_startbtn_clicked()\0timerOut()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

const QMetaObject *MainWindow::metaObject() const
{
    return &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_rightbtn_clicked(); break;
        case 1: on_downbtn_clicked(); break;
        case 2: on_leftbtn_clicked(); break;
        case 3: on_didownbtn_clicked(); break;
        case 4: on_upbtn_clicked(); break;
        case 5: on_pausebtn_clicked(); break;
        case 6: on_overbtn_clicked(); break;
        case 7: on_startbtn_clicked(); break;
        case 8: timerOut(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
