#ifndef A2DPSOURCE_H
#define A2DPSOURCE_H

#include <QThread>
#include <QtDBus>

#define DEVICE_IFZ "org.bluez.Device1"

typedef QMap<QString, QVariantMap> InterfaceList;
typedef QMap<QDBusObjectPath, InterfaceList> ManagedObjectList;
Q_DECLARE_METATYPE(InterfaceList)
Q_DECLARE_METATYPE(ManagedObjectList)


#define A2DP_CODEC_SBC			0x00
#define A2DP_CODEC_MPEG12		0x01
#define A2DP_CODEC_MPEG24		0x02
#define A2DP_CODEC_ATRAC		0x03

// sink and source uuid and endpoints
#define A2DP_SINK_UUID		"0000110b-0000-1000-8000-00805f9b34fb"
#define A2DP_SINK_ENDPOINT "/MediaEndpoint/A2DPSink" // bt --> alsa (sink for bt)
#define A2DP_SOURCE_UUID	"0000110a-0000-1000-8000-00805f9b34fb"
#define A2DP_SOURCE_ENDPOINT "/MediaEndpoint/A2DPSource" // alsa --> bt (source for bt)


#include "bluetooth/bluez/device1_bluez5_p.h"
#include "bluetooth/bluez/adapter1_bluez5_p.h"


class A2DPSourceThread: public QThread
{
    Q_OBJECT
public:
    A2DPSourceThread();

protected:

    virtual void run();

public slots:
    void onPropertyChanged(QString,QVariantMap,QStringList);

private:
    ManagedObjectList                       m_mapBluezObjects;

    QList<OrgBluezDevice1Interface *>       m_lDevices;
    OrgBluezAdapter1Interface *             m_pAdapter;

    void connect(QString path);
    void registerEndPoint();

};

#endif // A2DPSOURCE_H
