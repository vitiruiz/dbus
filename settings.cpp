#include "settings.h"




//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
bool Settings::objCreado = false;
Settings *Settings::getSettings()
{
    static  Settings *m_settingsObject;
    if (!Settings::objCreado)
      m_settingsObject = new Settings();

    Settings::objCreado = true;
    return m_settingsObject;
}


//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
Settings::Settings()
{

}



//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
QString Settings::getPath()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, SETT_COMP_NAME, SETT_APP_NAME);
    QStringList tokens = settings.fileName().split("/");
    tokens.removeLast();
    return tokens.join("/");
}


//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
void Settings::writeSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, SETT_COMP_NAME, SETT_APP_NAME);

//    settings.beginGroup("App");
//    settings.setValue("state", m_settings.app.state);
//    settings.setValue("geometry", m_settings.app.geometry);
//    settings.endGroup();





}


//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
void Settings::readSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, SETT_COMP_NAME, SETT_APP_NAME);


    //Thumbnails section
//    settings.beginGroup("App");
//    m_settings.app.state = settings.value("state").toByteArray();
//    m_settings.app.geometry = settings.value("geometry").toByteArray();
//    settings.endGroup();


}





//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
Settings::mSettings *Settings::settings()
{
    return &m_settings;
}
