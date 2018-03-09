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

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>
#include <QQuickStyle>

#include "mdocore/global.h"

int main(int argc, char *argv[])
{
    QGuiApplication::setApplicationName("markdownOrganizer");
    QGuiApplication::setOrganizationName("QtProject");
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

#ifdef DS_OS_DESKTOP
    QGuiApplication::setApplicationName("markdownOrganizer Mobile Demo");
#endif

    Q_INIT_RESOURCE(mdocore);

    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle("Material");
    QQmlApplicationEngine engine;
    engine.load(QUrl("qrc:/mdomobile.qml"));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();

}
