/****************************************************************************
** Meta object code from reading C++ file 'RoomClient.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../network/RoomClient.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RoomClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.3. It"
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
struct qt_meta_tag_ZN10RoomClientE_t {};
} // unnamed namespace

template <> constexpr inline auto RoomClient::qt_create_metaobjectdata<qt_meta_tag_ZN10RoomClientE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "RoomClient",
        "connected",
        "",
        "disconnected",
        "errorOccurred",
        "error",
        "memberListReceived",
        "roomId",
        "QList<MemberEntry>",
        "members",
        "memberJoined",
        "name",
        "isSharing",
        "memberLeft",
        "shareStarted",
        "shareStopped",
        "shareRejected",
        "reason",
        "grabRequested",
        "fromName",
        "grabResult",
        "granted"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'connected'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'disconnected'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'errorOccurred'
        QtMocHelpers::SignalData<void(const QString &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 5 },
        }}),
        // Signal 'memberListReceived'
        QtMocHelpers::SignalData<void(const QString &, const QList<MemberEntry> &)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 7 }, { 0x80000000 | 8, 9 },
        }}),
        // Signal 'memberJoined'
        QtMocHelpers::SignalData<void(const QString &, const QString &, bool)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 7 }, { QMetaType::QString, 11 }, { QMetaType::Bool, 12 },
        }}),
        // Signal 'memberLeft'
        QtMocHelpers::SignalData<void(const QString &, const QString &)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 7 }, { QMetaType::QString, 11 },
        }}),
        // Signal 'shareStarted'
        QtMocHelpers::SignalData<void(const QString &, const QString &)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 7 }, { QMetaType::QString, 11 },
        }}),
        // Signal 'shareStopped'
        QtMocHelpers::SignalData<void(const QString &, const QString &)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 7 }, { QMetaType::QString, 11 },
        }}),
        // Signal 'shareRejected'
        QtMocHelpers::SignalData<void(const QString &)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 17 },
        }}),
        // Signal 'grabRequested'
        QtMocHelpers::SignalData<void(const QString &)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 19 },
        }}),
        // Signal 'grabResult'
        QtMocHelpers::SignalData<void(bool, const QString &)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 21 }, { QMetaType::QString, 19 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<RoomClient, qt_meta_tag_ZN10RoomClientE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject RoomClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10RoomClientE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10RoomClientE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10RoomClientE_t>.metaTypes,
    nullptr
} };

void RoomClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<RoomClient *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->disconnected(); break;
        case 2: _t->errorOccurred((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->memberListReceived((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QList<MemberEntry>>>(_a[2]))); break;
        case 4: _t->memberJoined((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[3]))); break;
        case 5: _t->memberLeft((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 6: _t->shareStarted((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 7: _t->shareStopped((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 8: _t->shareRejected((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->grabRequested((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 10: _t->grabResult((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (RoomClient::*)()>(_a, &RoomClient::connected, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (RoomClient::*)()>(_a, &RoomClient::disconnected, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (RoomClient::*)(const QString & )>(_a, &RoomClient::errorOccurred, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (RoomClient::*)(const QString & , const QList<MemberEntry> & )>(_a, &RoomClient::memberListReceived, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (RoomClient::*)(const QString & , const QString & , bool )>(_a, &RoomClient::memberJoined, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (RoomClient::*)(const QString & , const QString & )>(_a, &RoomClient::memberLeft, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (RoomClient::*)(const QString & , const QString & )>(_a, &RoomClient::shareStarted, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (RoomClient::*)(const QString & , const QString & )>(_a, &RoomClient::shareStopped, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (RoomClient::*)(const QString & )>(_a, &RoomClient::shareRejected, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (RoomClient::*)(const QString & )>(_a, &RoomClient::grabRequested, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (RoomClient::*)(bool , const QString & )>(_a, &RoomClient::grabResult, 10))
            return;
    }
}

const QMetaObject *RoomClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RoomClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10RoomClientE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int RoomClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void RoomClient::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void RoomClient::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void RoomClient::errorOccurred(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void RoomClient::memberListReceived(const QString & _t1, const QList<MemberEntry> & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1, _t2);
}

// SIGNAL 4
void RoomClient::memberJoined(const QString & _t1, const QString & _t2, bool _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1, _t2, _t3);
}

// SIGNAL 5
void RoomClient::memberLeft(const QString & _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1, _t2);
}

// SIGNAL 6
void RoomClient::shareStarted(const QString & _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1, _t2);
}

// SIGNAL 7
void RoomClient::shareStopped(const QString & _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1, _t2);
}

// SIGNAL 8
void RoomClient::shareRejected(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 8, nullptr, _t1);
}

// SIGNAL 9
void RoomClient::grabRequested(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 9, nullptr, _t1);
}

// SIGNAL 10
void RoomClient::grabResult(bool _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 10, nullptr, _t1, _t2);
}
QT_WARNING_POP
