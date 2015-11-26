#include "a2dpsource.h"

#include <QDebug>

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
A2DPSourceThread::A2DPSourceThread()
{

    //Get org.bluez ManagedObjects
    qDBusRegisterMetaType<InterfaceList>();
    qDBusRegisterMetaType<ManagedObjectList>();

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

        foreach (InterfaceList ifzList, m_mapBluezObjects) {
            qDebug()<<" Keys: "<<ifzList.keys();
        }

        sleep(4);

    }

}
