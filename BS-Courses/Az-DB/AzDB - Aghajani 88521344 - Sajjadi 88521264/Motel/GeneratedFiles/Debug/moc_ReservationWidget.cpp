/****************************************************************************
** Meta object code from reading C++ file 'ReservationWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ReservationWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ReservationWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ReservationWidget_t {
    QByteArrayData data[16];
    char stringdata[292];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ReservationWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ReservationWidget_t qt_meta_stringdata_ReservationWidget = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 10),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 7),
QT_MOC_LITERAL(4, 38, 11),
QT_MOC_LITERAL(5, 50, 18),
QT_MOC_LITERAL(6, 69, 10),
QT_MOC_LITERAL(7, 80, 10),
QT_MOC_LITERAL(8, 91, 20),
QT_MOC_LITERAL(9, 112, 15),
QT_MOC_LITERAL(10, 128, 16),
QT_MOC_LITERAL(11, 145, 30),
QT_MOC_LITERAL(12, 176, 39),
QT_MOC_LITERAL(13, 216, 22),
QT_MOC_LITERAL(14, 239, 25),
QT_MOC_LITERAL(15, 265, 25)
    },
    "ReservationWidget\0showResult\0\0reserve\0"
    "fillTransCB\0searchReservations\0"
    "updateRoom\0searchRoom\0updateDateIndicators\0"
    "searchPassenger\0ClearStyleSheets\0"
    "HighlightSearchPassengerFields\0"
    "HighlightSearchReservationHistoryFields\0"
    "HighlightReserveFields\0HighlightSearchRoomFields\0"
    "HighlightUpdateRoomFields\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ReservationWidget[] = {

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
       1,    0,   84,    2, 0x0a,
       3,    0,   85,    2, 0x0a,
       4,    0,   86,    2, 0x0a,
       5,    0,   87,    2, 0x0a,
       6,    0,   88,    2, 0x0a,
       7,    0,   89,    2, 0x0a,
       8,    0,   90,    2, 0x0a,
       9,    0,   91,    2, 0x0a,
      10,    0,   92,    2, 0x0a,
      11,    0,   93,    2, 0x0a,
      12,    0,   94,    2, 0x0a,
      13,    0,   95,    2, 0x0a,
      14,    0,   96,    2, 0x0a,
      15,    0,   97,    2, 0x0a,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ReservationWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ReservationWidget *_t = static_cast<ReservationWidget *>(_o);
        switch (_id) {
        case 0: _t->showResult(); break;
        case 1: _t->reserve(); break;
        case 2: _t->fillTransCB(); break;
        case 3: _t->searchReservations(); break;
        case 4: _t->updateRoom(); break;
        case 5: _t->searchRoom(); break;
        case 6: _t->updateDateIndicators(); break;
        case 7: _t->searchPassenger(); break;
        case 8: _t->ClearStyleSheets(); break;
        case 9: _t->HighlightSearchPassengerFields(); break;
        case 10: _t->HighlightSearchReservationHistoryFields(); break;
        case 11: _t->HighlightReserveFields(); break;
        case 12: _t->HighlightSearchRoomFields(); break;
        case 13: _t->HighlightUpdateRoomFields(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ReservationWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ReservationWidget.data,
      qt_meta_data_ReservationWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *ReservationWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ReservationWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ReservationWidget.stringdata))
        return static_cast<void*>(const_cast< ReservationWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ReservationWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
