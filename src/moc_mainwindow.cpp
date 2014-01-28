/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      37,   35,   11,   11, 0x0a,
      57,   35,   11,   11, 0x0a,
      82,   80,   11,   11, 0x0a,
     106,  104,   11,   11, 0x0a,
     126,  124,   11,   11, 0x0a,
     149,  147,   11,   11, 0x0a,
     173,  147,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0setTimeMode(mode_type)\0n\0"
    "setNumberEdges(int)\0setNumberVertices(int)\0"
    "t\0setTimeLabel(time_t*)\0i\0setSliderMax(int)\0"
    "r\0setUbiRadius(double)\0v\0"
    "sliderValueChanged(int)\0"
    "snapshotSpinBoxValueChanged(int)\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->setTimeMode((*reinterpret_cast< mode_type(*)>(_a[1]))); break;
        case 1: _t->setNumberEdges((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setNumberVertices((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setTimeLabel((*reinterpret_cast< time_t*(*)>(_a[1]))); break;
        case 4: _t->setSliderMax((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setUbiRadius((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->sliderValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->snapshotSpinBoxValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
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
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
