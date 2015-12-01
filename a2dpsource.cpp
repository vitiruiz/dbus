#include "a2dpsource.h"

#include <QDebug>

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
A2DPSourceThread::A2DPSourceThread()
{

    //Get org.bluez ManagedObjects
    qDBusRegisterMetaType<InterfaceList>();
    qDBusRegisterMetaType<ManagedObjectList>();

    //Connect to property changes

//    org.freedesktop.DBus.Properties.PropertiesChanged (STRING interface_name,
//                                                       DICT<STRING,VARIANT> changed_properties,
//                                                       ARRAY<STRING> invalidated_properties);

    QDBusConnection::systemBus().connect("org.bluez", "", "org.freedesktop.DBus.Properties", "PropertiesChanged",
                         this, SLOT(onPropertyChanged(QDBusMessage)));


    QDBusMessage msg = QDBusMessage::createMethodCall("org.bluez", "/", "org.freedesktop.DBus.ObjectManager", "GetManagedObjects");
    QDBusMessage reply = QDBusConnection::systemBus().call(msg);

    qDebug()<<"Type:     "<<reply.type();
    qDebug()<<"Signaute: "<<reply.signature();

    QDBusArgument arg = reply.arguments().at(0).value<QDBusArgument>();
    arg >> m_mapBluezObjects;


}



//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
void A2DPSourceThread::run()
{

    while (true) {
        qDebug()<<"Trying to conect";

        QList<QDBusObjectPath> objPathList = m_mapBluezObjects.keys();
        foreach (QDBusObjectPath objPath, objPathList) {
            InterfaceList ifzList = m_mapBluezObjects[objPath];

            if(ifzList.keys().contains(DEVICE_IFZ))
            {
                connect(objPath.path());
            }
        }

        sleep(4);

    }

}



//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
void A2DPSourceThread::connect(QString path)
{
    qDebug()<<" Trying to connect to: "<<path;

//    org.bluez
//    Interface	org.bluez.Device1
//    Object path	[variable prefix]/{hci0,hci1,...}/dev_XX_XX_XX_XX_XX_XX

    QDBusMessage msg = QDBusMessage::createMethodCall("org.bluez", path, "org.bluez.Device1", "Connect");
    QDBusMessage reply = QDBusConnection::systemBus().call(msg);

    qDebug()<<" Reply:"<<reply;

}



//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
void A2DPSourceThread::onPropertyChanged(QDBusMessage msg)
{
    qDebug() << "Adapter properties changed:" << msg;



}



//void Bluez5BtAdapter::startDiscovery() {
//    qDebug("Starting discovery...");
//    QDBusInterface adapter("org.bluez", _adapterPath, "org.bluez.Adapter1", QDBusConnection::systemBus());
//    adapter.call("StartDiscovery");
//}

//void Bluez5BtAdapter::stopDiscovery() {
//    qDebug("Stopping discovery...");
//    QDBusInterface adapter("org.bluez", _adapterPath, "org.bluez.Adapter1", QDBusConnection::systemBus());
//    adapter.call("StopDiscovery");
//}
