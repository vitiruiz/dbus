#ifndef A2DPSOURCE_H
#define A2DPSOURCE_H

#include <QThread>
#include <QtDBus>

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

private:
    ManagedObjectList m_mapBluezObjects;

};

#endif // A2DPSOURCE_H
