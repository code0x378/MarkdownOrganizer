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

#include <QApplication>
#include <QDesktopWidget>
#include <QtDebug>
#include <QTextStream>
#include <QSettings>
#include <QStatusBar>
#include <QSplashScreen>
#include <QTimer>
#include <QtGlobal>
#include <QtNetwork>
#include <QtSql>
#include <QMessageBox>
#include <QStyleFactory>

#include "mdocore/db/initdb.h"
#include "mdocore/mdoapplication.h"
#include "mdoapp/gui/appmainwindow.h"
#include "mdocore/global.h"
#include "mdocore/objectmanager.h"
#include "mdocore/logmanager.h"
#include "mdocore/pluginmanager.h"
#include "mdocore/settingsmanager.h"

#ifdef _WIN32 || _WIN64
#include <Windows.h>
#include <tlhelp32.h>
#include <QMessageBox>
#endif

int main(int argc, char *argv[])
{
    /********************************************************
     * Application initialization
     ********************************************************/
    MdoApplication::setOrganizationName("ThoughtLogix.");
    MdoApplication::setOrganizationDomain("thoughtlogix.com");
    MdoApplication::setApplicationName("MarkdownOrganizer");
    MdoApplication::setApplicationVersion("1.0.0");
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    MdoApplication app(argc, argv);
    app.init();
    Q_INIT_RESOURCE(mdocore);

    /********************************************************
     * Command Line Options
     ********************************************************/
    QCommandLineParser parser;
    parser.setApplicationDescription("MarkdownOrganizer: Distributed Information Management by ThoughtLogix");
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption setLoggingLevelOption(QStringList() << "l" << "level",
                                             QCoreApplication::translate("MdoCore",
                                                                         "set logging level"),
                                             QCoreApplication::translate("MdoCore", "level"));
    parser.addOption(setLoggingLevelOption);
    parser.process(app);

    /********************************************************
     * Setup Logging
     ********************************************************/
    LOG_MANAGER_INITIALIZE;
    QString loggingLevel = parser.value(setLoggingLevelOption);
    if (!loggingLevel.isNull() && !loggingLevel.isEmpty()) {
        LOG_WARNING("Setting logging level not implemented");
        return 1;
    }

    /********************************************************
     * Settings
     ********************************************************/
    SETTINGS_MANAGER_INITIALIZE;
    SETTINGS_MANAGER->loadSettings();

    /********************************************************
     * Plugins
     ********************************************************/
    PLUGIN_MANAGER_INITIALIZE;
    PLUGIN_MANAGER->loadPlugins();

    /********************************************************
     * Global Stylesheet & Theme
     ********************************************************/
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    QPalette palette;
    palette.setColor(QPalette::Window, QColor(53,53,53));
    palette.setColor(QPalette::WindowText, Qt::white);
    palette.setColor(QPalette::Base, QColor(40,40,40));
    palette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    palette.setColor(QPalette::ToolTipBase, Qt::white);
    palette.setColor(QPalette::ToolTipText, Qt::white);
    palette.setColor(QPalette::Text, Qt::white);
    palette.setColor(QPalette::Button, QColor(53,53,53));
    palette.setColor(QPalette::ButtonText, Qt::white);
    palette.setColor(QPalette::BrightText, Qt::red);
    palette.setColor(QPalette::Highlight, QColor(100,100,100).lighter());
    palette.setColor(QPalette::HighlightedText, Qt::black);
    qApp->setPalette(palette);

    QFile file(":/mdocore/mdocore.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    app.setStyleSheet(styleSheet);

    /********************************************************
     * Global Internationalization
     ********************************************************/
    QTranslator translator;
    translator.load(":/mdocore/lang/mdo_en.qm");
    app.installTranslator(&translator);

    /********************************************************
     * Sexy Splash
     ********************************************************/
#ifndef QT_DEBUG
    QPixmap pixmap(":/mdocore/images/splash.png");
    QSplashScreen *splash = new QSplashScreen(pixmap);
    splash->show();
    splash->showMessage("Herding the cats...", Qt::AlignHCenter | Qt:: AlignBottom,
                        Qt::white);
    QThread::sleep(1);
    delete splash;
#endif

    /********************************************************
     * Proxy Networking
     ********************************************************/
    MdoApplication::setProxyServer();

    /********************************************************
     * Database
     ********************************************************/
    if (!QSqlDatabase::drivers().contains("QSQLITE"))
        QMessageBox::critical(nullptr, "Unable to load database",
                              "MarkdownOrganizer needs the SQLITE driver");

    QSqlError err = initDb();
    if (err.type() != QSqlError::NoError) {
        LOG_FATAL(err.text());
        return 1;
    }

    QSqlQuery query;
    query.exec("SELECT name, description, workingDirectory, postSaveCommand, tags, categories, projectType, isDefault, plugins, emailTo, emailFrom from projects order by name asc");

    Project  *project;
    while (query.next()) {
        project = new Project();
        project->setName(query.value(0).toString());
        project->setType(ProjectType::Blog);
        project->setDescription(query.value(1).toString());
        project->setWorkingDirectory(query.value(2).toString());
        project->setPostSaveCommmand(query.value(3).toString());
        project->setTags(query.value(4).toString());
        project->setCategories(query.value(5).toString());
        project->setType((ProjectType) query.value(6).toInt());
        project->setIsDefault(query.value(7).toBool());
        project->setPlugins(query.value(8).toString());
        project->setEmailTo(query.value(9).toString());
        project->setEmailFrom(query.value(10).toString());
        app.getProjects()->insert(project->getName(), project);
        if (project->getIsDefault() == 1) {
            app.setActiveProject(project);
            app.getActiveProject()->setCurrentDirectory(
                app.getActiveProject()->getWorkingDirectory());
        }
    }

    /********************************************************
     * Manage main Window
     ********************************************************/
    APP->logStartupMessage();
    MAINWINDOW->show();

    /********************************************************
     * Ready to rock
     ********************************************************/
    try {
        return app.exec();
    } catch (const std::bad_alloc &) {
        LOG_ERROR("We just exploded");
        return 0;
    }
}