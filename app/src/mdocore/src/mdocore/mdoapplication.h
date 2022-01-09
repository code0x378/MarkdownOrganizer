/*
* Markdown Organizer
* Copyright (C) 2016-2021 code0x378
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

#ifndef GFAPPLICATION_H
#define GFAPPLICATION_H

#include <QApplication>

#include "mdocore/models/project.h"

class ObjectManager;
class LogManager;
class PluginManager;
class SettingsManager;
class MainWindow;

class MdoApplication : public QApplication
{
    Q_OBJECT
public:
    explicit MdoApplication(int &argc, char **argv);

    static PluginManager *getPluginManager();
    static LogManager *getLogManager();
    static SettingsManager *getSettingsManager();
    //    static ObjectManager *getObjectManager();
    static MainWindow *getMainWindow();

    static void setProxyServer();
    static QString getSystemMemory();
    static void delay(int duration);
    void logStartupMessage();
    void init();
    QHash<QString, Project *> *getProjects() const;
    void setProjects(QHash<QString, Project *> *value);
    Project *getActiveProject() const;
    void setActiveProject(Project *value);
    QString *getConfigDirectory() const;
    QString *getLogFile() const;
    QString *getSettingsFile() const;

private:
    QHash<QString, Project *> *projects = new QHash<QString, Project *>();
    Project *activeProject = new Project();

    QString *configDirectory;
    QString *logFile;
    QString *settingsFile;
};

#define APP ((MdoApplication *) QApplication::instance())

#endif // GFAPPLICATION_H
