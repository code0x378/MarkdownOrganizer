/*
* Markdown Organizer
* Copyright (C) 2016-2018 ThoughtLogix
* 
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "mdoapplication.h"

#include <QMutex>
#include <QSqlError>
#include <QTimer>
#include <QtGlobal>
#include <QtNetwork>
#include <QSqlDatabase>

#include "mdocore/settingsmanager.h"
#include "mdocore/logmanager.h"
#include "mdocore/models/project.h"


MdoApplication::MdoApplication(int &argc, char **argv):
    QApplication(argc, argv)
{
    configDirectory = new QString(QDir::homePath() + QDir::separator() +
                                  ".markdownorganizer");

    QDir dir(*configDirectory);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    logFile = new QString(configDirectory + QDir::separator() + "log.txt");
    settingsFile = new QString(configDirectory + QDir::separator() +
                               "settings.txt");
}

void MdoApplication::init()
{

}

QHash<QString, Project *> *MdoApplication::getProjects() const
{
    return projects;
}

void MdoApplication::setProjects(QHash<QString, Project *> *value)
{
    projects = value;
}

Project *MdoApplication::getActiveProject() const
{
    return activeProject;
}

void MdoApplication::setActiveProject(Project *value)
{
    activeProject = value;
}

QString *MdoApplication::getConfigDirectory() const
{
    return configDirectory;
}

QString *MdoApplication::getLogFile() const
{
    return logFile;
}

QString *MdoApplication::getSettingsFile() const
{
    return settingsFile;
}

void MdoApplication::delay(int duration)
{
    QTime dieTime = QTime::currentTime().addSecs(duration);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MdoApplication::setProxyServer()
{
    //    QNetworkProxyQuery q(QUrl("http://www.google.com"));
    //    q.setQueryType(QNetworkProxyQuery::UrlRequest);
    //    q.setProtocolTag("http");
    //    QList<QNetworkProxy> proxies = QNetworkProxyFactory::systemProxyForQuery(q);
    //    if( proxies.size() > 0 && proxies[0].type() != QNetworkProxy::NoProxy ) {

    if (SETTINGS_MANAGER->getBool("Proxy/enabled")) {
        QNetworkProxy::setApplicationProxy(
            QNetworkProxy(QNetworkProxy::HttpCachingProxy,
                          SETTINGS_MANAGER->getString("Proxy/hostname"),
                          SETTINGS_MANAGER->getInt("Proxy/port"),
                          SETTINGS_MANAGER->getString("Proxy/username"),
                          SETTINGS_MANAGER->getPassword("Proxy/password")
                         ));
        qDebug("Proxy Server Enabled");
    } else
        qDebug("Proxy server disabled");
}

QString MdoApplication::getSystemMemory()
{

    QString mem = "";

#ifdef __linux__
    QProcess p;
    p.start("awk", QStringList() << "/MemTotal/ { print $2 }" << "/proc/meminfo");
    p.waitForFinished();
    QString memory = p.readAllStandardOutput();
    p.close();
    return QString(" %1MB").arg(memory.toLong() / 1024);


#endif

#ifdef __APPLE__
    QProcess p;
    p.start("sysctl", QStringList() << "kern.version" << "hw.physmem");
    p.waitForFinished();
    mem = p.readAllStandardOutput();
    p.close();
#endif

#ifdef __MINGW32__
//        MEMORYSTATUSEX memory_status;
//        ZeroMemory(&memory_status, sizeof(MEMORYSTATUSEX));
//        memory_status.dwLength = sizeof(MEMORYSTATUSEX);
//        if (GlobalMemoryStatusEx(&memory_status)) {
//          system_info.append(
//                mem = QString(" %1MB")
//                .arg(memory_status.ullTotalPhys / (1024 * 1024)));
//        }
#endif

    return mem;

}

void MdoApplication::logStartupMessage()
{
    LOG_INFO("---------------------------------------------------");
    LOG_INFO("DOTSYNERGY STARTED");
    LOG_INFO("---------------------------------------------------");
    LOG_INFO("App Dir: " + qApp->applicationDirPath());
    LOG_INFO("Config Dir: " + *getConfigDirectory());
    LOG_INFO("Log File: " + *getLogFile());
    LOG_INFO("Settings File: " + *getSettingsFile());
    LOG_INFO("System Memmory: " + MdoApplication::getSystemMemory());
}




