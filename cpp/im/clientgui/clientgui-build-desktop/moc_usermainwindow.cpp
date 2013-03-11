/****************************************************************************
** Meta object code from reading C++ file 'usermainwindow.h'
**
** Created: Tue Jun 14 11:20:42 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../clientgui/usermainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'usermainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UserMainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   16,   15,   15, 0x05,
      65,   41,   15,   15, 0x05,
     108,  101,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
     148,  136,   15,   15, 0x08,
     202,   15,   15,   15, 0x08,
     230,   15,   15,   15, 0x08,
     248,   15,   15,   15, 0x08,
     271,   41,   15,   15, 0x08,
     306,  101,   15,   15, 0x08,
     333,   16,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_UserMainWindow[] = {
    "UserMainWindow\0\0op\0analyseCmdSignal(int)\0"
    "username_userno_p,msstr\0"
    "analyseMessageSignal(char*,QString)\0"
    "op,str\0showInfoSignal(int,QString)\0"
    "item,column\0"
    "on_treeWidget_itemDoubleClicked(QTreeWidgetItem*,int)\0"
    "actionModifyUserinfoSlots()\0"
    "actionExitSlots()\0actionAddFriendSlots()\0"
    "analyseMessageSlots(char*,QString)\0"
    "showInfoSlots(int,QString)\0"
    "analyseCmdSlots(int)\0"
};

const QMetaObject UserMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_UserMainWindow,
      qt_meta_data_UserMainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UserMainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UserMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UserMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UserMainWindow))
        return static_cast<void*>(const_cast< UserMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int UserMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: analyseCmdSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: analyseMessageSignal((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: showInfoSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: on_treeWidget_itemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: actionModifyUserinfoSlots(); break;
        case 5: actionExitSlots(); break;
        case 6: actionAddFriendSlots(); break;
        case 7: analyseMessageSlots((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: showInfoSlots((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 9: analyseCmdSlots((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void UserMainWindow::analyseCmdSignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UserMainWindow::analyseMessageSignal(char * _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void UserMainWindow::showInfoSignal(int _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
