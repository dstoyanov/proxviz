/****************************************************************************
** Meta object code from reading C++ file 'modedialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "modedialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModeDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      31,   11,   11,   11, 0x08,
      55,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ModeDialog[] = {
    "ModeDialog\0\0setMode(mode_type)\0"
    "realTimeButtonPressed()\0loadButtonPressed()\0"
};

void ModeDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModeDialog *_t = static_cast<ModeDialog *>(_o);
        switch (_id) {
        case 0: _t->setMode((*reinterpret_cast< mode_type(*)>(_a[1]))); break;
        case 1: _t->realTimeButtonPressed(); break;
        case 2: _t->loadButtonPressed(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModeDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModeDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ModeDialog,
      qt_meta_data_ModeDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModeDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModeDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModeDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModeDialog))
        return static_cast<void*>(const_cast< ModeDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ModeDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ModeDialog::setMode(mode_type _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
