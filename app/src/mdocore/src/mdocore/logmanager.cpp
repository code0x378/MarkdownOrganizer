/*
* Markdown Organizer
* Copyright (C) 2016-2018 JeffSmithDev
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

#include "logmanager.h"

#include <QDateTime>
#include <QDir>
#include <QMessageBox>
#include <QMutex>
#include <QTextStream>
#include <fstream>
#include <QDebug>

#include "mdocore/global.h"
#include "mdoapplication.h"


LogManager *LogManager::logManager = 0;
LogManager *LogManager::instance()
{
    static QMutex mutex;
    if (!logManager) {
        mutex.lock();

        if (!logManager)
            logManager = new LogManager();

        mutex.unlock();
    }

    return logManager;
}

LogManager::LogManager(QObject *parent) : QObject(parent)
{
    logFile = new QFile(*APP->getLogFile());
    if (logFile->open(QIODevice::ReadWrite)) {
        logStream = new QTextStream(logFile);
    } else {
        qCritical() << "Unable to open log file";
        exit(1);
    }
}

LogManager::~LogManager()
{
}

QString LogManager::formatLogMsg(QString type, QString date, QString msg)
{
    return QString("%1 %2 %3 \r\n").arg(type, date, msg);
}

void LogManager::fatal(const QString str)
{
    QString s = formatLogMsg("FATAL", QDateTime::currentDateTimeUtc().toString(),
                             str);
    emit messageLogged(s);
    *logStream << s;
    logStream->flush();
}

void LogManager::error(const QString str)
{
    const QString s = formatLogMsg("ERROR",
                                   QDateTime::currentDateTimeUtc().toString(), str);
    emit messageLogged(str);
    *logStream << s;
    logStream->flush();
}

void LogManager::warning(const QString str)
{
    const QString s = formatLogMsg("WARNING",
                                   QDateTime::currentDateTimeUtc().toString(), str);
    emit messageLogged(s);
    *logStream << s;
    logStream->flush();
}

void LogManager::debug(const QString str)
{
    const QString s = formatLogMsg("DEBUG",
                                   QDateTime::currentDateTimeUtc().toString(), str);
    emit messageLogged(s);
    *logStream << s;
    logStream->flush();
}

void LogManager::info(const QString str)
{
    const QString s = formatLogMsg("INFO",
                                   QDateTime::currentDateTimeUtc().toString(), str);
    emit messageLogged(s);
    *logStream << s;
    logStream->flush();
}








