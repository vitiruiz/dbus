TEMPLATE = app

QT += qml quick widgets dbus bluetooth

DEFINES += QT_BLUEZ_BLUETOOTH

SOURCES += main.cpp \
    a2dpsource.cpp \
    settings.cpp \
    bluetooth/qbluetooth.cpp \
    bluetooth/qbluetoothaddress.cpp \
    bluetooth/qbluetoothdevicediscoveryagent.cpp \
    bluetooth/qbluetoothdevicediscoveryagent_bluez.cpp \
    bluetooth/qbluetoothdeviceinfo.cpp \
    bluetooth/qbluetoothhostinfo.cpp \
    bluetooth/qbluetoothlocaldevice.cpp \
    bluetooth/qbluetoothlocaldevice_bluez.cpp \
    bluetooth/qbluetoothserver.cpp \
    bluetooth/qbluetoothserver_bluez.cpp \
    bluetooth/qbluetoothservicediscoveryagent.cpp \
    bluetooth/qbluetoothservicediscoveryagent_bluez.cpp \
    bluetooth/qbluetoothserviceinfo.cpp \
    bluetooth/qbluetoothserviceinfo_bluez.cpp \
    bluetooth/qbluetoothsocket.cpp \
    bluetooth/qbluetoothsocket_bluez.cpp \
    bluetooth/qbluetoothtransfermanager.cpp \
    bluetooth/qbluetoothtransferreply.cpp \
    bluetooth/qbluetoothtransferreply_bluez.cpp \
    bluetooth/qbluetoothtransferrequest.cpp \
    bluetooth/qbluetoothuuid.cpp \
    bluetooth/qlowenergycharacteristic.cpp \
    bluetooth/qlowenergycontroller.cpp \
    bluetooth/qlowenergycontroller_bluez.cpp \
    bluetooth/qlowenergydescriptor.cpp \
    bluetooth/qlowenergyservice.cpp \
    bluetooth/qlowenergyserviceprivate.cpp \
    bluetooth/bluez/adapter.cpp \
    bluetooth/bluez/adapter1_bluez5.cpp \
    bluetooth/bluez/agent.cpp \
    bluetooth/bluez/bluez5_helper.cpp \
    bluetooth/bluez/device.cpp \
    bluetooth/bluez/device1_bluez5.cpp \
    bluetooth/bluez/hcimanager.cpp \
    bluetooth/bluez/manager.cpp \
    bluetooth/bluez/obex_agent.cpp \
    bluetooth/bluez/obex_client.cpp \
    bluetooth/bluez/obex_client1_bluez5.cpp \
    bluetooth/bluez/obex_manager.cpp \
    bluetooth/bluez/obex_objectpush1_bluez5.cpp \
    bluetooth/bluez/obex_transfer.cpp \
    bluetooth/bluez/obex_transfer1_bluez5.cpp \
    bluetooth/bluez/objectmanager.cpp \
    bluetooth/bluez/profile1.cpp \
    bluetooth/bluez/properties.cpp \
    bluetooth/bluez/service.cpp \
    bluetooth/bluez/servicemap.cpp


RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    a2dpsource.h \
    settings.h \
    bluetooth/qbluetooth.h \
    bluetooth/qbluetoothaddress.h \
    bluetooth/qbluetoothaddress_p.h \
    bluetooth/qbluetoothdevicediscoveryagent.h \
    bluetooth/qbluetoothdevicediscoveryagent_p.h \
    bluetooth/qbluetoothdeviceinfo.h \
    bluetooth/qbluetoothdeviceinfo_p.h \
    bluetooth/qbluetoothglobal.h \
    bluetooth/qbluetoothhostinfo.h \
    bluetooth/qbluetoothhostinfo_p.h \
    bluetooth/qbluetoothlocaldevice.h \
    bluetooth/qbluetoothlocaldevice_p.h \
    bluetooth/qbluetoothserver.h \
    bluetooth/qbluetoothserver_p.h \
    bluetooth/qbluetoothservicediscoveryagent.h \
    bluetooth/qbluetoothservicediscoveryagent_p.h \
    bluetooth/qbluetoothserviceinfo.h \
    bluetooth/qbluetoothserviceinfo_p.h \
    bluetooth/qbluetoothsocket.h \
    bluetooth/qbluetoothsocket_p.h \
    bluetooth/qbluetoothtransfermanager.h \
    bluetooth/qbluetoothtransferreply.h \
    bluetooth/qbluetoothtransferreply_bluez_p.h \
    bluetooth/qbluetoothtransferreply_p.h \
    bluetooth/qbluetoothtransferrequest.h \
    bluetooth/qbluetoothtransferrequest_p.h \
    bluetooth/qbluetoothuuid.h \
    bluetooth/qlowenergycharacteristic.h \
    bluetooth/qlowenergycontroller.h \
    bluetooth/qlowenergycontroller_p.h \
    bluetooth/qlowenergydescriptor.h \
    bluetooth/qlowenergyservice.h \
    bluetooth/qlowenergyserviceprivate_p.h \
    bluetooth/qprivatelinearbuffer_p.h \
    bluetooth/bluez/adapter1_bluez5_p.h \
    bluetooth/bluez/adapter_p.h \
    bluetooth/bluez/agent_p.h \
    bluetooth/bluez/bluez5_helper_p.h \
    bluetooth/bluez/bluez_data_p.h \
    bluetooth/bluez/device1_bluez5_p.h \
    bluetooth/bluez/device_p.h \
    bluetooth/bluez/hcimanager_p.h \
    bluetooth/bluez/manager_p.h \
    bluetooth/bluez/obex_agent_p.h \
    bluetooth/bluez/obex_client1_bluez5_p.h \
    bluetooth/bluez/obex_client_p.h \
    bluetooth/bluez/obex_manager_p.h \
    bluetooth/bluez/obex_objectpush1_bluez5_p.h \
    bluetooth/bluez/obex_transfer1_bluez5_p.h \
    bluetooth/bluez/obex_transfer_p.h \
    bluetooth/bluez/objectmanager_p.h \
    bluetooth/bluez/profile1_p.h \
    bluetooth/bluez/properties_p.h \
    bluetooth/bluez/servicemap_p.h \
    bluetooth/bluez/service_p.h \
    bt_defines.h

DISTFILES += \
    bluetooth/bluez/org.bluez.Adapter1.xml \
    bluetooth/bluez/org.bluez.Agent.xml \
    bluetooth/bluez/org.bluez.all.xml \
    bluetooth/bluez/org.bluez.Client1.xml \
    bluetooth/bluez/org.bluez.Device.xml \
    bluetooth/bluez/org.bluez.Device1.xml \
    bluetooth/bluez/org.bluez.Manager.xml \
    bluetooth/bluez/org.bluez.obex.ObjectPush1.xml \
    bluetooth/bluez/org.bluez.obex.Transfer1.xml \
    bluetooth/bluez/org.bluez.ProfileManager1.xml \
    bluetooth/bluez/org.bluez.Service.xml \
    bluetooth/bluez/org.freedesktop.dbus.objectmanager.xml \
    bluetooth/bluez/org.freedesktop.dbus.properties.xml \
    bluetooth/bluez/org.openobex.agent.xml \
    bluetooth/bluez/org.openobex.all.xml \
    bluetooth/bluez/org.openobex.client.xml \
    bluetooth/bluez/org.openobex.transfer.xml

