#ifndef A2DPSOURCE_H
#define A2DPSOURCE_H

#include <QThread>
#include <QtDBus>

#define DEVICE_IFZ "org.bluez.Device1"

typedef QMap<QString, QVariantMap> InterfaceList;
typedef QMap<QDBusObjectPath, InterfaceList> ManagedObjectList;
Q_DECLARE_METATYPE(InterfaceList)
Q_DECLARE_METATYPE(ManagedObjectList)

class A2DPSourceThread: public QThread
{
public:
    A2DPSourceThread();

protected:

    virtual void run();

public slots:
    void onPropertyChanged(QDBusMessage msg);

private:
    ManagedObjectList m_mapBluezObjects;

    void connect(QString path);

};

#endif // A2DPSOURCE_H
