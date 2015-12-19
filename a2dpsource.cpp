#include "a2dpsource.h"

#include <QDebug>

#include "bluetooth/bluez/properties_p.h"
#include "bt_defines.h"

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
A2DPSourceThread::A2DPSourceThread()
{

    //Get org.bluez ManagedObjects
    qDBusRegisterMetaType<InterfaceList>();
    qDBusRegisterMetaType<ManagedObjectList>();




    //Get all objects
    QDBusMessage msg = QDBusMessage::createMethodCall("org.bluez", "/", "org.freedesktop.DBus.ObjectManager", "GetManagedObjects");
    QDBusMessage reply = QDBusConnection::systemBus().call(msg);

    qDebug()<<"Objects:     "<<reply;

    QDBusArgument arg = reply.arguments().at(0).value<QDBusArgument>();
    arg >> m_mapBluezObjects;


    QList<QDBusObjectPath> objPathList = m_mapBluezObjects.keys();
    foreach (QDBusObjectPath objPath, objPathList) {
        InterfaceList ifzList = m_mapBluezObjects[objPath];

        if(ifzList.keys().contains(DEVICE_IFZ))
        {
            m_lDevices.append(new OrgBluezDevice1Interface("org.bluez", objPath.path(), QDBusConnection::systemBus()));
        }
        else if(ifzList.keys().contains(OrgBluezAdapter1Interface::staticInterfaceName()))
        {
            m_pAdapter = new OrgBluezAdapter1Interface("org.bluez", objPath.path(), QDBusConnection::systemBus());
            registerEndPoint();
        }
    }

    //Connect to property changes
    OrgFreedesktopDBusPropertiesInterface* monitor = new OrgFreedesktopDBusPropertiesInterface(QStringLiteral("org.bluez"),
                                                                            "",
                                                                            QDBusConnection::systemBus(), this);
    QObject::connect(monitor, SIGNAL(PropertiesChanged(QString,QVariantMap,QStringList)),
                         this, SLOT(onPropertyChanged(QString,QVariantMap,QStringList)));


}



//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
void A2DPSourceThread::run()
{

    while (true) {
        qDebug()<<"\nTrying to conect to all devices";

        //Power on adapter
        if(!m_pAdapter->powered())
        {
            qDebug()<<" Powering on device";
            m_pAdapter->setPowered(true);
        }

        //Set discoverable
        if(!m_pAdapter->discoverable())
        {
            qDebug()<<" Showing device";
//            m_pAdapter->setDiscoverableTimeout(-1);
            m_pAdapter->setDiscoverable(true);
        }


        QList<QDBusPendingReply<> > pendReplies;

        //Request connection to all devices
        foreach (OrgBluezDevice1Interface *device, m_lDevices) {
            if(!device->connected())
            {
                qDebug()<<" Devicenot not connected "<<device->path();
                pendReplies.append( device->Connect() );
            }
        }

        foreach (QDBusPendingReply<> pendingReply, pendReplies) {
            pendingReply.waitForFinished();
            if (pendingReply.isError())
                qDebug()<<"  Connection failed: "<<pendingReply.error();
            else
                qDebug()<<"  Connection success: "<<pendingReply.reply();
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
void A2DPSourceThread::onPropertyChanged(QString interface,
                                         QVariantMap changed_properties,
                                         QStringList invalidated_properties)
{
    qDebug() << "Prop changed:"<<interface<<" -> "<<changed_properties<<" -> "<<invalidated_properties;



}


//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
void A2DPSourceThread::registerEndPoint()
{

    QDBusMessage msg = QDBusMessage::createMethodCall("org.bluez", m_pAdapter->path(), "org.bluez.Media1", "RegisterEndpoint");

    QVariantList arguments;

    QDBusObjectPath obj(A2DP_SINK_ENDPOINT);

    //Object path
    arguments<<QVariant::fromValue(obj);

    QVariantMap properties;
    //UUID
    properties.insert("UUID", QString(A2DP_SINK_UUID));

    //Codec
    int uchartype = qDBusRegisterMetaType<uchar>(); //Register the ushort metatype and get it's id
    QVariant codec(A2DP_CODEC_SBC);
    codec.convert((QVariant::Type)uchartype); //convert to the new type
    properties.insert("Codec", codec);

    //Capabilites
    a2dp_sbc_t capabilities;
    capabilities.channel_mode       = BT_A2DP_CHANNEL_MODE_MONO | BT_A2DP_CHANNEL_MODE_DUAL_CHANNEL |
                                      BT_A2DP_CHANNEL_MODE_STEREO | BT_A2DP_CHANNEL_MODE_JOINT_STEREO;
    capabilities.frequency          = BT_SBC_SAMPLING_FREQ_16000 | BT_SBC_SAMPLING_FREQ_32000 |
                                      BT_SBC_SAMPLING_FREQ_44100 | BT_SBC_SAMPLING_FREQ_48000;
    capabilities.allocation_method  = BT_A2DP_ALLOCATION_SNR | BT_A2DP_ALLOCATION_LOUDNESS;
    capabilities.subbands           = BT_A2DP_SUBBANDS_4 | BT_A2DP_SUBBANDS_8;
    capabilities.block_length       = BT_A2DP_BLOCK_LENGTH_4 | BT_A2DP_BLOCK_LENGTH_8 |
                                      BT_A2DP_BLOCK_LENGTH_12 | BT_A2DP_BLOCK_LENGTH_16;
    capabilities.min_bitpool        = MIN_BITPOOL;
    capabilities.max_bitpool        = MAX_BITPOOL;
//    uint capabVariant;
//    memccpy(&capabilities, &capabVariant, 1, sizeof(capabVariant));

    QByteArray aCapabilities((char*)&capabilities, 4);
    properties.insert("Capabilities", aCapabilities);
    arguments<<properties;

    msg.setArguments(arguments);

    qDebug()<<" Message"<<msg<<", signature: "<<msg.signature();
    QDBusMessage reply = QDBusConnection::systemBus().call(msg);
    qDebug()<<" Reply:"<<reply;


//    Methods		void RegisterEndpoint(object endpoint, dict properties)


}


//dbus_error_init(&err);
//msg = dbus_message_new_method_call("org.bluez",
//    bt_object,			  // object to call on
//    "org.bluez.Media",	  // interface to call on
//    "RegisterEndpoint");  // method name

////build the parameters
//dbus_message_iter_init_append (msg, &iter);

////first param - object path
//dbus_message_iter_append_basic (&iter, DBUS_TYPE_OBJECT_PATH, &endpoint);
////second param - properties
//dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY, "{sv}", &iterarray);
//    util_add_dict_variant_entry (&iterarray, "UUID", DBUS_TYPE_STRING, uuid);
//    util_add_dict_variant_entry (&iterarray, "Codec", DBUS_TYPE_BYTE, A2DP_CODEC_SBC);
//    util_add_dict_array_entry (&iterarray, "Capabilities", DBUS_TYPE_BYTE, &capabilities, sizeof (capabilities));


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
