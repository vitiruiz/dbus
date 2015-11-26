#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

#define SETT_COMP_NAME  "Qt"
#define SETT_APP_NAME   "BlueGateway"



class Settings
{
public:
    //Singleton getter
    static Settings * getSettings();


    struct mSettings{



    };




    void writeSettings();

    void readSettings();

    mSettings *settings();
    static QString getPath();

private:

    Settings();

    static bool objCreado;

    mSettings m_settings;
};


#endif // SETTINGS_H
