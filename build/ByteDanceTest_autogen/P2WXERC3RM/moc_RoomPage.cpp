/****************************************************************************
** Meta object code from reading C++ file 'RoomPage.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../pages/RoomPage.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RoomPage.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN8RoomPageE_t {};
} // unnamed namespace

template <> constexpr inline auto RoomPage::qt_create_metaobjectdata<qt_meta_tag_ZN8RoomPageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "RoomPage",
        "leaveRoomRequested",
        "",
        "shareScreenRequested",
        "stopShareRequested",
        "grabShareRequested",
        "grabShareResponded",
        "granted",
        "micToggleRequested",
        "enabled",
        "onMemberListReceived",
        "roomId",
        "QList<MemberEntry>",
        "members",
        "onMemberJoined",
        "name",
        "isSharing",
        "onMemberLeft",
        "onShareStarted",
        "onShareStopped",
        "onShareRejected",
        "reason",
        "onGrabRequested",
        "fromName",
        "onGrabResult"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'leaveRoomRequested'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'shareScreenRequested'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'stopShareRequested'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'grabShareRequested'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'grabShareResponded'
        QtMocHelpers::SignalData<void(bool)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 7 },
        }}),
        // Signal 'micToggleRequested'
        QtMocHelpers::SignalData<void(bool)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 9 },
        }}),
        // Slot 'onMemberListReceived'
        QtMocHelpers::SlotData<void(const QString &, const QList<MemberEntry> &)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 11 }, { 0x80000000 | 12, 13 },
        }}),
        // Slot 'onMemberJoined'
        QtMocHelpers::SlotData<void(const QString &, const QString &, bool)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 11 }, { QMetaType::QString, 15 }, { QMetaType::Bool, 16 },
        }}),
        // Slot 'onMemberLeft'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 11 }, { QMetaType::QString, 15 },
        }}),
        // Slot 'onShareStarted'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 11 }, { QMetaType::QString, 15 },
        }}),
        // Slot 'onShareStopped'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 11 }, { QMetaType::QString, 15 },
        }}),
        // Slot 'onShareRejected'
        QtMocHelpers::SlotData<void(const QString &)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 21 },
        }}),
        // Slot 'onGrabRequested'
        QtMocHelpers::SlotData<void(const QString &)>(22, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 23 },
        }}),
        // Slot 'onGrabResult'
        QtMocHelpers::SlotData<void(bool, const QString &)>(24, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 7 }, { QMetaType::QString, 23 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<RoomPage, qt_meta_tag_ZN8RoomPageE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject RoomPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8RoomPageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8RoomPageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN8RoomPageE_t>.metaTypes,
    nullptr
} };

void RoomPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<RoomPage *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->leaveRoomRequested(); break;
        case 1: _t->shareScreenRequested(); break;
        case 2: _t->stopShareRequested(); break;
        case 3: _t->grabShareRequested(); break;
        case 4: _t->grabShareResponded((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 5: _t->micToggleRequested((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 6: _t->onMemberListReceived((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QList<MemberEntry>>>(_a[2]))); break;
        case 7: _t->onMemberJoined((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[3]))); break;
        case 8: _t->onMemberLeft((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 9: _t->onShareStarted((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 10: _t->onShareStopped((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 11: _t->onShareRejected((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 12: _t->onGrabRequested((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 13: _t->onGrabResult((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (RoomPage::*)()>(_a, &RoomPage::leaveRoomRequested, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (RoomPage::*)()>(_a, &RoomPage::shareScreenRequested, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (RoomPage::*)()>(_a, &RoomPage::stopShareRequested, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (RoomPage::*)()>(_a, &RoomPage::grabShareRequested, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (RoomPage::*)(bool )>(_a, &RoomPage::grabShareResponded, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (RoomPage::*)(bool )>(_a, &RoomPage::micToggleRequested, 5))
            return;
    }
}

const QMetaObject *RoomPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RoomPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8RoomPageE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int RoomPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void RoomPage::leaveRoomRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void RoomPage::shareScreenRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void RoomPage::stopShareRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void RoomPage::grabShareRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void RoomPage::grabShareResponded(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void RoomPage::micToggleRequested(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}
QT_WARNING_POP
