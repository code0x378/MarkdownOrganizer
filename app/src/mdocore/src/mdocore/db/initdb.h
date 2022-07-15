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
                                             QLatin1String("LDBU - Knowledge"),
                                             QLatin1String("Little Dog Big Universe Knowledge Repository"),
                                             QLatin1String("c:\\data\\dev\\syntiva\\manicdev-www\\webapp\\content\\knowledge"),
                                             QLatin1String("cd c:\\data\\dev\\syntiva\\manicdev-www\\bin && .\\deploy-s3.bat"),
                                             QLatin1String("Linux, Arch, Ubuntu, Gnome, Kde, Qt, Java, JavaScript, Python, Kotlin, OSX, Windows, VCS, Cloud, Database"),
                                             QLatin1String("SysAdmin, Development"),
                                             blogProjectTypeId,
                                             0,
                                             "Hugo,",
                                             "jsmith@syntiva.com",
                                             "jsmith@syntiva.com");
    QVariant coolstuffProjectId = addProject(q,
                                             QLatin1String("LDBU - Coolstuff"),
                                             QLatin1String("Little Dog Big Universe Coolstuff"),
                                             QLatin1String("c:\\data\\dev\\syntiva\\manicdev-www\\webapp\\content\\coolstuff"),
                                             QLatin1String("cd c:\\data\\dev\\syntiva\\manicdev-www\\bin && .\\deploy-s3.bat"),
                                             QLatin1String("Apps, Open Source, Tools, Libraries, Linux, OSX, Windows, Robotics"),
                                             QLatin1String("SysAdmin, Development, Other"),
                                             linksProjectTypeId,
                                             0,
                                             "Hugo, ",
                                             "jsmith@syntiva.com",
                                             "jsmith@syntiva.com");
    QVariant notesProjectId = addProject(q,
                                         QLatin1String("Per - Notes"),
                                         QLatin1String("Basic note taking"),
                                         QLatin1String("c:\\data\\personal\\notes"),
                                         QLatin1String("dir"),
                                         QLatin1String("ArfArfBebe, code0x378, infoQuant, Shopping, Todo"),
                                         QLatin1String("Personal, Work"),
                                         notesProjectTypeId,
                                         1,
                                         "Hugo,Mdo",
                                         "jsmith@syntiva.com",
                                         "jsmith@syntiva.com");

    QVariant helpProjectId = addProject(q,
                                        QLatin1String("MDO - Help"),
                                        QLatin1String("markdownOrganizer Help System"),
                                        QLatin1String("c:\\data\\dev\\syntiva\\markdownorganizer\\app\\src\\help"),
                                        QLatin1String("dir"),
                                        QLatin1String("Gui, Installation, Settings"),
                                        QLatin1String("Free, Pro, Enterprise"),
                                        helpProjectTypeId,
                                        0,
                                        "Hugo, ",
                                        "jsmith@syntiva.com",
                                        "jsmith@syntiva.com");

    QVariant gfHelpProjectId = addProject(q,
                                          QLatin1String("GF - Help"),
                                          QLatin1String("GF Help System"),
                                          QLatin1String("c:\\data\\dev\\infoquant\\gf\\gf-help\\src\\main\\resources\\help\\docs"),
                                          QLatin1String("dir"),
                                          QLatin1String("Gui, Installation, Settings, Database, Security, Admin, Analytics"),
                                          QLatin1String("GenomeFusion, Genomius, cnTrack"),
                                          helpProjectTypeId,
                                          0,
                                          "Hugo, ",
                                          "jsmith@syntiva.com",
                                          "jeff@infoquant.com");
    QVariant mitoProjectId = addProject(q,
                                        QLatin1String("Mito - Website"),
                                        QLatin1String("Mitotech static website"),
                                        QLatin1String("c:\\data\\dev\\syntiva\\mitotechpharma-www\\webapp\\hugo\\content"),
                                        QLatin1String("dir"),
                                        QLatin1String("SKQ, Biotech, Conference, Dry Eye"),
                                        QLatin1String("News, Events"),
                                        blogProjectTypeId,
                                        0,
                                        "Hugo, ",
                                        "jsmith@syntiva.com",
                                        "jeff@infoquant.com");
    QVariant skqProjectId = addProject(q,
                                       QLatin1String("SKQ - Website"),
                                       QLatin1String("Skq static website"),
                                       QLatin1String("c:\\data\\dev\\syntiva\\skq-www\\webapp\\hugo\\content"),
                                       QLatin1String("dir"),
                                       QLatin1String("SKQ, Biotech, Conference, Dry Eye, Mitotech"),
                                       QLatin1String("News, Events, Publications"),
                                       blogProjectTypeId,
                                       0,
                                       "Hugo, ",
                                       "jsmith@syntiva.com",
                                       "jeff@infoquant.com");









    QVariant knowledgeProjectOSXId = addProject(q,
                                                QLatin1String("LDBU (osx) - Knowledge"),
                                                QLatin1String("Little Dog Big Universe Knowledge Repository"),
                                                QLatin1String("/Users/jeff/data/dev/syntiva/code0x378-www/webapp/content/knowledge"),
                                                QLatin1String("cd /Users/jeff/data/dev/syntiva/code0x378-www/bin && ./deploy-s3.sh"),
                                                QLatin1String("Linux, Arch, Ubuntu, Gnome, Kde, Qt, Java, JavaScript, Python, Kotlin, OSX, Windows, VCS, Cloud, Database"),
                                                QLatin1String("SysAdmin, Development"),
                                                blogProjectTypeId,
                                                0,
                                                "Hugo,",
                                                "jsmith@syntiva.com",
                                                "jsmith@syntiva.com");
    QVariant coolstuffProjectOSXId = addProject(q,
                                                QLatin1String("LDBU (osx) - Coolstuff"),
                                                QLatin1String("Little Dog Big Universe Coolstuff"),
                                                QLatin1String("/Users/jeff/data/dev/syntiva/code0x378-www/webapp/content/coolstuff"),
                                                QLatin1String("cd /Users/jeff/data/dev/syntiva/code0x378-www/bin && ./deploy-s3.sh"),
                                                QLatin1String("Apps, Open Source, Tools, Libraries, Linux, OSX, Windows, Robotics"),
                                                QLatin1String("SysAdmin, Development, Other"),
                                                linksProjectTypeId,
                                                0,
                                                "Hugo, ",
                                                "jsmith@syntiva.com",
                                                "jsmith@syntiva.com");
    QVariant notesProjectOSXId = addProject(q,
                                            QLatin1String("Per (osx) - Notes"),
                                            QLatin1String("Basic note taking"),
                                            QLatin1String("/Users/jeff/data/personal/notes"),
                                            QLatin1String("ls"),
                                            QLatin1String("ArfArfBebe, code0x378, infoQuant, Shopping, Todo"),
                                            QLatin1String("Personal, Work"),
                                            notesProjectTypeId,
                                            1,
                                            "Hugo,Mdo",
                                            "jsmith@syntiva.com",
                                            "jsmith@syntiva.com");

    QVariant helpProjectOSXId = addProject(q,
                                           QLatin1String("MDO (osx) - Help"),
                                           QLatin1String("markdownOrganizer Help System"),
                                           QLatin1String("/Users/jeff/data/dev/syntiva/markdownorganizer/app/src/resources/help"),
                                           QLatin1String("dir"),
                                           QLatin1String("Gui, Installation, Settings"),
                                           QLatin1String("Free, Pro, Enterprise"),
                                           helpProjectTypeId,
                                           0,
                                           "Hugo, ",
                                           "jsmith@syntiva.com",
                                           "jsmith@syntiva.com");

    QVariant gfHelpProjectOSXId = addProject(q,
                                             QLatin1String("GF (osx) - Help"),
                                             QLatin1String("GF Help System"),
                                             QLatin1String("/Users/jeff/data/dev/infoquant/gf/gf-help/src/main/resources/help/docs"),
                                             QLatin1String("ls"),
                                             QLatin1String("Gui, Installation, Settings, Database, Security, Admin, Analytics"),
                                             QLatin1String("GenomeFusion, Genomius, cnTrack"),
                                             helpProjectTypeId,
                                             0,
                                             "Hugo, ",
                                             "jsmith@syntiva.com",
                                             "jeff@infoquant.com");
    QVariant mitoProjectOSXId = addProject(q,
                                           QLatin1String("Mito (osx) - Website"),
                                           QLatin1String("Mitotech static website"),
                                           QLatin1String("/Users/jeff/data/dev/syntiva/mitotechpharma-www/webapp/hugo/content"),
                                           QLatin1String("ls"),
                                           QLatin1String("SKQ, Biotech, Conference, Dry Eye"),
                                           QLatin1String("News, Events"),
                                           blogProjectTypeId,
                                           0,
                                           "Hugo, ",
                                           "jsmith@syntiva.com",
                                           "jeff@infoquant.com");
    QVariant skqProjectOSXId = addProject(q,
                                          QLatin1String("SKQ (osx) - Website"),
                                          QLatin1String("Skq static website"),
                                          QLatin1String("/Users/jeff/data/dev/syntiva/skq-www/webapp/hugo/content"),
                                          QLatin1String("ls"),
                                          QLatin1String("SKQ, Biotech, Conference, Dry Eye, Mitotech"),
                                          QLatin1String("News, Events, Publications"),
                                          blogProjectTypeId,
                                          0,
                                          "Hugo, ",
                                          "jsmith@syntiva.com",
                                          "jeff@infoquant.com");

    /********************************************************
     * Resource
     ********************************************************/

    if (!q.exec(
                QLatin1String("create table resource(id integer primary key, title varchar, author varchar, date varchar, content text, tags varchar, "
                              "categories varchar,  website varchar, filePath varchar, project int)")))
        return q.lastError();

//    if (!q.prepare(
//                QLatin1String("insert into resource(title, author, date, content, tags, categories, website, filePath, project) values(?, ?, ?, ?, ?, ?, ?, ?, ?)")))
//        return q.lastError();

//    QVariant resourceOneId = addResource(q,
//                                         QLatin1String("Some important to say"),
//                                         QLatin1String("2017-01-01"),
//                                         QLatin1String("Author"),
//                                         QLatin1String("#hello"),
//                                         QLatin1String("linux, arch"),
//                                         QLatin1String("SysAdmin"),
//                                         QLatin1String(""),
//                                         QLatin1String("c:\\Users\\jeff\\Desktop"),
//                                         knowledgeProjectId
//                                         );
//    QVariant resourceTwoId = addResource(q,
//                                         QLatin1String("Some else to say"),
//                                         QLatin1String("2016-01-01"),
//                                         QLatin1String("Me"),
//                                         QLatin1String("#hi"),
//                                         QLatin1String("linux"),
//                                         QLatin1String("Dev"),
//                                         QLatin1String(""),
//                                         QLatin1String("c:\\Users\\jeff\\Desktop"),
//                                         knowledgeProjectId
//                                         );
//    QVariant resourceThreeId = addResource(q,
//                                           QLatin1String("Some more to say"),
//                                           QLatin1String("2017-01-01"),
//                                           QLatin1String("Paulva"),
//                                           QLatin1String("#howdy"),
//                                           QLatin1String("FreeBSD"),
//                                           QLatin1String("Dev"),
//                                           QLatin1String(""),
//                                           QLatin1String("c:\\Users\\jeff\\Desktop"),
//                                           coolstuffProjectId
//                                           );


    /********************************************************
     * History
     ********************************************************/

    if (!q.exec(
                QLatin1String("create table history(id integer primary key, title varchar, author varchar, date varchar, content text, tags varchar, "
                              "categories varchar,  website varchar, filePath varchar, resource int)")))
        return q.lastError();

//    if (!q.prepare(
//                QLatin1String("insert into history(title, author, date, content, tags, categories, website, filePath, resource) values(?, ?, ?, ?, ?, ?, ?, ?, ?)")))
//        return q.lastError();

//    QVariant exampleHistoryOne = addHistory(q,
//                                            QLatin1String("Some important to say"),
//                                            QLatin1String("2017-01-01"),
//                                            QLatin1String("Author"),
//                                            QLatin1String("#hello"),
//                                            QLatin1String("linux, arch"),
//                                            QLatin1String("SysAdmin"),
//                                            QLatin1String(""),
//                                            QLatin1String("c:\\Users\\jeff\\Desktop"),
//                                            resourceOneId
//                                            );
//    QVariant exampleHistoryTwo = addHistory(q,
//                                            QLatin1String("Some else to say"),
//                                            QLatin1String("2016-01-01"),
//                                            QLatin1String("Me"),
//                                            QLatin1String("#hi"),
//                                            QLatin1String("linux"),
//                                            QLatin1String("Dev"),
//                                            QLatin1String(""),
//                                            QLatin1String("c:\\Users\\jeff\\Desktop"),
//                                            resourceTwoId
//                                            );
//    QVariant exampleHistoryThree = addHistory(q,
//                                              QLatin1String("Some more to say"),
//                                              QLatin1String("2017-01-01"),
//                                              QLatin1String("Paulva"),
//                                              QLatin1String("#howdy"),
//                                              QLatin1String("FreeBSD"),
//                                              QLatin1String("Dev"),
//                                              QLatin1String(""),
//                                              QLatin1String("c:\\Users\\jeff\\Desktop"),
//                                              resourceThreeId
//                                              );


    return QSqlError();
}

#endif
