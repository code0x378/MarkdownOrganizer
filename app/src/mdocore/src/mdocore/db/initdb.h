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

#ifndef INITDB_H
#define INITDB_H

#include <QtSql>

QVariant addProject(QSqlQuery &q,
                    const QString &title,
                    const QString &description,
                    const QString &workingDirectoory,
                    const QString &postSaveCommand,
                    const QString &tags,
                    const QString &categories,
                    const QVariant &projectTypeId,
                    const QVariant &isDefault,
                    const QString &plugins,
                    const QVariant &emailTo,
                    const QVariant &emailFrom
                   )
{
    q.addBindValue(title);
    q.addBindValue(description);
    q.addBindValue(workingDirectoory);
    q.addBindValue(postSaveCommand);
    q.addBindValue(tags);
    q.addBindValue(categories);
    q.addBindValue(projectTypeId);
    q.addBindValue(isDefault);
    q.addBindValue(plugins);
    q.addBindValue(emailTo);
    q.addBindValue(emailFrom);
    q.exec();
    return q.lastInsertId();
}

QVariant addProjectType(QSqlQuery &q,
                        const QString &title,
                        const QString &description)
{
    q.addBindValue(title);
    q.addBindValue(description);
    q.exec();
    return q.lastInsertId();
}

QVariant addHistory(QSqlQuery &q,
                    const QString &title,
                    const QString &date,
                    const QString &author,
                    const QString &content,
                    const QString &tags,
                    const QString &categories,
                    const QString &website,
                    const QString &filePath,
                    const QVariant &projectId
                   )
{
    q.addBindValue(title);
    q.addBindValue(date);
    q.addBindValue(author);
    q.addBindValue(content);
    q.addBindValue(tags);
    q.addBindValue(categories);
    q.addBindValue(website);
    q.addBindValue(filePath);
    q.addBindValue(projectId);
    q.exec();
    return q.lastInsertId();
}

QVariant addResource(QSqlQuery &q,
                     const QString &title,
                     const QString &date,
                     const QString &author,
                     const QString &content,
                     const QString &tags,
                     const QString &categories,
                     const QString &website,
                     const QString &filePath,
                     const QVariant &projectId
                    )
{
    q.addBindValue(title);
    q.addBindValue(date);
    q.addBindValue(author);
    q.addBindValue(content);
    q.addBindValue(tags);
    q.addBindValue(categories);
    q.addBindValue(website);
    q.addBindValue(filePath);
    q.addBindValue(projectId);
    q.exec();
    return q.lastInsertId();
}

QSqlError initDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("markdownorganizer-database.db");

    if (!db.open())
        return db.lastError();

    QStringList tables = db.tables();
    if (tables.contains("project_types", Qt::CaseInsensitive))
        return QSqlError();
    QSqlQuery q;

    /********************************************************
     * Project Types
     ********************************************************/

    if (!q.exec(
                QLatin1String("create table project_types(id integer primary key, name varchar, description varchar)")))
        return q.lastError();

    if (!q.prepare(
                QLatin1String("insert into project_types(name, description) values(?, ?)")))
        return q.lastError();

    QVariant genericProjectTypeId = addProjectType(q,
                                                   QLatin1String("Generic"),
                                                   QLatin1String("A generic project type"));

    QVariant blogProjectTypeId = addProjectType(q,
                                                QLatin1String("Blog"),
                                                QLatin1String("A project type for blogs, news, events and similar"));

    QVariant linksProjectTypeId = addProjectType(q,
                                                 QLatin1String("Links"),
                                                 QLatin1String("A project type for simple links and directories"));

    QVariant helpProjectTypeId = addProjectType(q,
                                                QLatin1String("Help"),
                                                QLatin1String("A project type for help with TOC and other components"));

    QVariant notesProjectTypeId = addProjectType(q,
                                                 QLatin1String("Notes"),
                                                 QLatin1String("A project type for simple noes"));

    /********************************************************
    * Projects
    ********************************************************/

    if (!q.exec(
                QLatin1String("create table projects(id integer primary key, name varchar, description varchar, "
                              "workingDirectory varchar, postSaveCommand varchar,  tags varchar,  categories varchar, projectType int, isDefault int, plugins varchar, emailTo varchar, emailFrom varchar)")))
        return q.lastError();

    if (!q.prepare(
                QLatin1String("insert into projects(name, description, workingDirectory, postSaveCommand, tags, categories, projectType, isDefault, plugins, emailTo, emailFrom) "
                              "values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)")))
        return q.lastError();

    QVariant knowledgeProjectId = addProject(q,
                                             QLatin1String("Sample Project"),
                                             QLatin1String("Sample Markdown project"),
                                             QLatin1String("resources/sampleproject"),
                                             QLatin1String("ls"),
                                             QLatin1String("Tag1,Tag2,Tag3,Tag4,Tag5,Tag6,Tag7,Tag8"),
                                             QLatin1String("Cat1,Cat2,Cat3"),
                                             blogProjectTypeId,
                                             1,
                                             "Hugo,",
                                             "user@example.com",
                                             "user@example.com");

    /********************************************************
     * Resource
     ********************************************************/

    if (!q.exec(
                QLatin1String("create table resource(id integer primary key, title varchar, author varchar, date varchar, content text, tags varchar, "
                              "categories varchar,  website varchar, filePath varchar, project int)")))
        return q.lastError();


    /********************************************************
     * History
     ********************************************************/

    if (!q.exec(
                QLatin1String("create table history(id integer primary key, title varchar, author varchar, date varchar, content text, tags varchar, "
                              "categories varchar,  website varchar, filePath varchar, resource int)")))
        return q.lastError();


    return QSqlError();
}

#endif
