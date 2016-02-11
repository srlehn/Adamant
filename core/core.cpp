#include "core.h"
#include "pluginmanager.h"
#include "ui/ui.h"
#include <items/itemmanager.h>
#include <ui/pages/pluginpage.h>
#include "session/sessionrequest.h"

CoreService::CoreService()
    : QObject()
    , _pluginManager(new PluginManager(this))
    , _settings("plugins.ini", QSettings::IniFormat)
    , _sensitiveSettings("sensitive.ini", QSettings::IniFormat)
    , _itemManager(new ItemManager(this)) {
    Session::SetCoreService(this);

    _ui = new UI(this);

    connect(_pluginManager, &PluginManager::pluginMessage, [this] (QString msg, QtMsgType type) {
        emit message(msg, type);
    });
}

CoreService::~CoreService() {
}

bool CoreService::load() {
    sensitiveSettings()->beginGroup("session");
    QString sessionId = sensitiveSettings()->value("id").toString();
    sensitiveSettings()->endGroup();

    // Required here so that the setup dialog also gets this palette
    interface()->setTheme();

    interface()->start();

    while (sessionId.isEmpty()) {
        // Oh no, run setup.
        int result = interface()->showSetup(); // Blocking
        if (result != 0x0) {
            interface()->window()->close();
            return false;
        }

        QVariantMap map = interface()->getSetupDialog()->getData();

        // Setup completed, we should have valid data
        sensitiveSettings()->beginGroup("session");
        for (QString key : map.uniqueKeys()) {
            sensitiveSettings()->setValue(key, map.value(key));
        }
        sessionId = sensitiveSettings()->value("id").toString();
        sensitiveSettings()->endGroup();
    }

    connect(session(), &Session::Request::profileData, this, &CoreService::ready);

    // Load Plugins
    getPluginManager()->scanPlugins(true);
    getPluginManager()->verifyPlugins();
    getPluginManager()->preparePlugins();

    // Load the main application!
    session()->loginWithSessionId(sessionId);

    return true;
}

void CoreService::ready() {
    disconnect(session(), &Session::Request::profileData, this, &CoreService::ready);
    getPluginManager()->loadPlugins();

    emit message("Adamant Started!", QtInfoMsg);
    interface()->registerPages();

    // Set page to home
    interface()->window()->setPageIndex(0);
}

void CoreService::loggedMessage(const QString &message, QtMsgType type) {
    QString sType;
    switch (type) {
        case QtDebugMsg:      sType = "DEB"; break;
        case QtInfoMsg:       sType = "LOG"; break;
        case QtWarningMsg:    sType = "WAR"; break;
        case QtCriticalMsg:   sType = "ERR"; break;
        case QtFatalMsg:      sType = "FAT"; break;
    }

    interface()->window()->appendScriptOutput(message, sType);
}

QDir CoreService::applicationPath() {
    return QDir(QApplication::applicationDirPath());
}
