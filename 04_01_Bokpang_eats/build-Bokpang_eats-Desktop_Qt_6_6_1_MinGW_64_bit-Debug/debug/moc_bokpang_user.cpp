/****************************************************************************
** Meta object code from reading C++ file 'bokpang_user.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../bokpang_eats/bokpang_user.h"
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bokpang_user.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSBokpang_userENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSBokpang_userENDCLASS = QtMocHelpers::stringData(
    "Bokpang_user",
    "signal_newMessage",
    "",
    "signal_newID",
    "on_categoribtn_clicked",
    "on_shopbtn1_clicked",
    "showmenu",
    "str",
    "on_shopbtn2_clicked",
    "on_shopbtn3_clicked",
    "on_shopbtn4_clicked",
    "startbtn_clicked",
    "slotdebugmessage",
    "receiveclidata",
    "on_VoC_pbtn_clicked",
    "on_send_pbtn_clicked",
    "slot_read_sock",
    "slot_displaymsg",
    "on_id_double_chk_pbtn_clicked",
    "checkID",
    "on_ph_double_chk_pbtn_clicked",
    "checkPH",
    "on_email_double_chk_pbtn_clicked",
    "checkEMAIL",
    "on_signupbtn__clicked",
    "on_find_pw_pbtn_2_clicked",
    "on_find_id_pbtn_2_clicked",
    "on_login_pbtn_clicked",
    "on_find_id_pbtn_clicked",
    "on_find_pw_pbtn_clicked",
    "on_sign_up_pbtn_clicked",
    "on_pushButton_clicked",
    "page_basket_pbtn_enable",
    "basket_back_pbtn_clicked",
    "menu_pbtn_1_clicked",
    "menu_pbtn_2_clicked",
    "menu_pbtn_3_clicked",
    "menu_pbtn_4_clicked",
    "basket_order_pbtn_clicked",
    "on_basket_back_pbtn_2_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSBokpang_userENDCLASS_t {
    uint offsetsAndSizes[80];
    char stringdata0[13];
    char stringdata1[18];
    char stringdata2[1];
    char stringdata3[13];
    char stringdata4[23];
    char stringdata5[20];
    char stringdata6[9];
    char stringdata7[4];
    char stringdata8[20];
    char stringdata9[20];
    char stringdata10[20];
    char stringdata11[17];
    char stringdata12[17];
    char stringdata13[15];
    char stringdata14[20];
    char stringdata15[21];
    char stringdata16[15];
    char stringdata17[16];
    char stringdata18[30];
    char stringdata19[8];
    char stringdata20[30];
    char stringdata21[8];
    char stringdata22[33];
    char stringdata23[11];
    char stringdata24[22];
    char stringdata25[26];
    char stringdata26[26];
    char stringdata27[22];
    char stringdata28[24];
    char stringdata29[24];
    char stringdata30[24];
    char stringdata31[22];
    char stringdata32[24];
    char stringdata33[25];
    char stringdata34[20];
    char stringdata35[20];
    char stringdata36[20];
    char stringdata37[20];
    char stringdata38[26];
    char stringdata39[30];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSBokpang_userENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSBokpang_userENDCLASS_t qt_meta_stringdata_CLASSBokpang_userENDCLASS = {
    {
        QT_MOC_LITERAL(0, 12),  // "Bokpang_user"
        QT_MOC_LITERAL(13, 17),  // "signal_newMessage"
        QT_MOC_LITERAL(31, 0),  // ""
        QT_MOC_LITERAL(32, 12),  // "signal_newID"
        QT_MOC_LITERAL(45, 22),  // "on_categoribtn_clicked"
        QT_MOC_LITERAL(68, 19),  // "on_shopbtn1_clicked"
        QT_MOC_LITERAL(88, 8),  // "showmenu"
        QT_MOC_LITERAL(97, 3),  // "str"
        QT_MOC_LITERAL(101, 19),  // "on_shopbtn2_clicked"
        QT_MOC_LITERAL(121, 19),  // "on_shopbtn3_clicked"
        QT_MOC_LITERAL(141, 19),  // "on_shopbtn4_clicked"
        QT_MOC_LITERAL(161, 16),  // "startbtn_clicked"
        QT_MOC_LITERAL(178, 16),  // "slotdebugmessage"
        QT_MOC_LITERAL(195, 14),  // "receiveclidata"
        QT_MOC_LITERAL(210, 19),  // "on_VoC_pbtn_clicked"
        QT_MOC_LITERAL(230, 20),  // "on_send_pbtn_clicked"
        QT_MOC_LITERAL(251, 14),  // "slot_read_sock"
        QT_MOC_LITERAL(266, 15),  // "slot_displaymsg"
        QT_MOC_LITERAL(282, 29),  // "on_id_double_chk_pbtn_clicked"
        QT_MOC_LITERAL(312, 7),  // "checkID"
        QT_MOC_LITERAL(320, 29),  // "on_ph_double_chk_pbtn_clicked"
        QT_MOC_LITERAL(350, 7),  // "checkPH"
        QT_MOC_LITERAL(358, 32),  // "on_email_double_chk_pbtn_clicked"
        QT_MOC_LITERAL(391, 10),  // "checkEMAIL"
        QT_MOC_LITERAL(402, 21),  // "on_signupbtn__clicked"
        QT_MOC_LITERAL(424, 25),  // "on_find_pw_pbtn_2_clicked"
        QT_MOC_LITERAL(450, 25),  // "on_find_id_pbtn_2_clicked"
        QT_MOC_LITERAL(476, 21),  // "on_login_pbtn_clicked"
        QT_MOC_LITERAL(498, 23),  // "on_find_id_pbtn_clicked"
        QT_MOC_LITERAL(522, 23),  // "on_find_pw_pbtn_clicked"
        QT_MOC_LITERAL(546, 23),  // "on_sign_up_pbtn_clicked"
        QT_MOC_LITERAL(570, 21),  // "on_pushButton_clicked"
        QT_MOC_LITERAL(592, 23),  // "page_basket_pbtn_enable"
        QT_MOC_LITERAL(616, 24),  // "basket_back_pbtn_clicked"
        QT_MOC_LITERAL(641, 19),  // "menu_pbtn_1_clicked"
        QT_MOC_LITERAL(661, 19),  // "menu_pbtn_2_clicked"
        QT_MOC_LITERAL(681, 19),  // "menu_pbtn_3_clicked"
        QT_MOC_LITERAL(701, 19),  // "menu_pbtn_4_clicked"
        QT_MOC_LITERAL(721, 25),  // "basket_order_pbtn_clicked"
        QT_MOC_LITERAL(747, 29)   // "on_basket_back_pbtn_2_clicked"
    },
    "Bokpang_user",
    "signal_newMessage",
    "",
    "signal_newID",
    "on_categoribtn_clicked",
    "on_shopbtn1_clicked",
    "showmenu",
    "str",
    "on_shopbtn2_clicked",
    "on_shopbtn3_clicked",
    "on_shopbtn4_clicked",
    "startbtn_clicked",
    "slotdebugmessage",
    "receiveclidata",
    "on_VoC_pbtn_clicked",
    "on_send_pbtn_clicked",
    "slot_read_sock",
    "slot_displaymsg",
    "on_id_double_chk_pbtn_clicked",
    "checkID",
    "on_ph_double_chk_pbtn_clicked",
    "checkPH",
    "on_email_double_chk_pbtn_clicked",
    "checkEMAIL",
    "on_signupbtn__clicked",
    "on_find_pw_pbtn_2_clicked",
    "on_find_id_pbtn_2_clicked",
    "on_login_pbtn_clicked",
    "on_find_id_pbtn_clicked",
    "on_find_pw_pbtn_clicked",
    "on_sign_up_pbtn_clicked",
    "on_pushButton_clicked",
    "page_basket_pbtn_enable",
    "basket_back_pbtn_clicked",
    "menu_pbtn_1_clicked",
    "menu_pbtn_2_clicked",
    "menu_pbtn_3_clicked",
    "menu_pbtn_4_clicked",
    "basket_order_pbtn_clicked",
    "on_basket_back_pbtn_2_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSBokpang_userENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      37,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  236,    2, 0x06,    1 /* Public */,
       3,    0,  239,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    0,  240,    2, 0x08,    4 /* Private */,
       5,    0,  241,    2, 0x08,    5 /* Private */,
       6,    1,  242,    2, 0x08,    6 /* Private */,
       8,    0,  245,    2, 0x08,    8 /* Private */,
       9,    0,  246,    2, 0x08,    9 /* Private */,
      10,    0,  247,    2, 0x08,   10 /* Private */,
      11,    0,  248,    2, 0x08,   11 /* Private */,
      12,    1,  249,    2, 0x08,   12 /* Private */,
      13,    0,  252,    2, 0x08,   14 /* Private */,
      14,    0,  253,    2, 0x08,   15 /* Private */,
      15,    0,  254,    2, 0x08,   16 /* Private */,
      16,    0,  255,    2, 0x08,   17 /* Private */,
      17,    1,  256,    2, 0x08,   18 /* Private */,
      18,    0,  259,    2, 0x08,   20 /* Private */,
      19,    0,  260,    2, 0x08,   21 /* Private */,
      20,    0,  261,    2, 0x08,   22 /* Private */,
      21,    0,  262,    2, 0x08,   23 /* Private */,
      22,    0,  263,    2, 0x08,   24 /* Private */,
      23,    0,  264,    2, 0x08,   25 /* Private */,
      24,    0,  265,    2, 0x08,   26 /* Private */,
      25,    0,  266,    2, 0x08,   27 /* Private */,
      26,    0,  267,    2, 0x08,   28 /* Private */,
      27,    0,  268,    2, 0x08,   29 /* Private */,
      28,    0,  269,    2, 0x08,   30 /* Private */,
      29,    0,  270,    2, 0x08,   31 /* Private */,
      30,    0,  271,    2, 0x08,   32 /* Private */,
      31,    0,  272,    2, 0x08,   33 /* Private */,
      32,    0,  273,    2, 0x08,   34 /* Private */,
      33,    0,  274,    2, 0x08,   35 /* Private */,
      34,    0,  275,    2, 0x08,   36 /* Private */,
      35,    0,  276,    2, 0x08,   37 /* Private */,
      36,    0,  277,    2, 0x08,   38 /* Private */,
      37,    0,  278,    2, 0x08,   39 /* Private */,
      38,    0,  279,    2, 0x08,   40 /* Private */,
      39,    0,  280,    2, 0x08,   41 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
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

Q_CONSTINIT const QMetaObject Bokpang_user::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSBokpang_userENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSBokpang_userENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSBokpang_userENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Bokpang_user, std::true_type>,
        // method 'signal_newMessage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'signal_newID'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_categoribtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_shopbtn1_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showmenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_shopbtn2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_shopbtn3_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_shopbtn4_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startbtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slotdebugmessage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'receiveclidata'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_VoC_pbtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_send_pbtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_read_sock'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_displaymsg'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_id_double_chk_pbtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'checkID'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_ph_double_chk_pbtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'checkPH'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_email_double_chk_pbtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'checkEMAIL'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_signupbtn__clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_find_pw_pbtn_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_find_id_pbtn_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_login_pbtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_find_id_pbtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_find_pw_pbtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_sign_up_pbtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'page_basket_pbtn_enable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'basket_back_pbtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'menu_pbtn_1_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'menu_pbtn_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'menu_pbtn_3_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'menu_pbtn_4_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'basket_order_pbtn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_basket_back_pbtn_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Bokpang_user::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Bokpang_user *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->signal_newMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->signal_newID(); break;
        case 2: _t->on_categoribtn_clicked(); break;
        case 3: _t->on_shopbtn1_clicked(); break;
        case 4: _t->showmenu((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->on_shopbtn2_clicked(); break;
        case 6: _t->on_shopbtn3_clicked(); break;
        case 7: _t->on_shopbtn4_clicked(); break;
        case 8: _t->startbtn_clicked(); break;
        case 9: _t->slotdebugmessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 10: _t->receiveclidata(); break;
        case 11: _t->on_VoC_pbtn_clicked(); break;
        case 12: _t->on_send_pbtn_clicked(); break;
        case 13: _t->slot_read_sock(); break;
        case 14: _t->slot_displaymsg((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 15: _t->on_id_double_chk_pbtn_clicked(); break;
        case 16: _t->checkID(); break;
        case 17: _t->on_ph_double_chk_pbtn_clicked(); break;
        case 18: _t->checkPH(); break;
        case 19: _t->on_email_double_chk_pbtn_clicked(); break;
        case 20: _t->checkEMAIL(); break;
        case 21: _t->on_signupbtn__clicked(); break;
        case 22: _t->on_find_pw_pbtn_2_clicked(); break;
        case 23: _t->on_find_id_pbtn_2_clicked(); break;
        case 24: _t->on_login_pbtn_clicked(); break;
        case 25: _t->on_find_id_pbtn_clicked(); break;
        case 26: _t->on_find_pw_pbtn_clicked(); break;
        case 27: _t->on_sign_up_pbtn_clicked(); break;
        case 28: _t->on_pushButton_clicked(); break;
        case 29: _t->page_basket_pbtn_enable(); break;
        case 30: _t->basket_back_pbtn_clicked(); break;
        case 31: _t->menu_pbtn_1_clicked(); break;
        case 32: _t->menu_pbtn_2_clicked(); break;
        case 33: _t->menu_pbtn_3_clicked(); break;
        case 34: _t->menu_pbtn_4_clicked(); break;
        case 35: _t->basket_order_pbtn_clicked(); break;
        case 36: _t->on_basket_back_pbtn_2_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Bokpang_user::*)(QString );
            if (_t _q_method = &Bokpang_user::signal_newMessage; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Bokpang_user::*)();
            if (_t _q_method = &Bokpang_user::signal_newID; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *Bokpang_user::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Bokpang_user::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSBokpang_userENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Bokpang_user::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 37)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 37;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 37)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 37;
    }
    return _id;
}

// SIGNAL 0
void Bokpang_user::signal_newMessage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Bokpang_user::signal_newID()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
