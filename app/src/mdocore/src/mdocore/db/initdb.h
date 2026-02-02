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
                u"create table project_types(id integer primary key, name varchar, description varchar)"_qs))
        return q.lastError();

    if (!q.prepare(
                u"insert into project_types(name, description) values(?, ?)"_qs))
        return q.lastError();

    QVariant genericProjectTypeId = addProjectType(q,
                                                   u"Generic"_qs,
                                                   u"A generic project type"_qs);

    QVariant blogProjectTypeId = addProjectType(q,
                                                u"Blog"_qs,
                                                u"A project type for blogs, news, events and similar"_qs);

    QVariant linksProjectTypeId = addProjectType(q,
                                                 u"Links"_qs,
                                                 u"A project type for simple links and directories"_qs);

    QVariant helpProjectTypeId = addProjectType(q,
                                                u"Help"_qs,
                                                u"A project type for help with TOC and other components"_qs);

    QVariant notesProjectTypeId = addProjectType(q,
                                                 u"Notes"_qs,
                                                 u"A project type for simple noes"_qs);

    /********************************************************
    * Projects
    ********************************************************/

    if (!q.exec(
                u"create table projects(id integer primary key, name varchar, description varchar, workingDirectory varchar, postSaveCommand varchar,  tags varchar,  categories varchar, projectType int, isDefault int, plugins varchar, emailTo varchar, emailFrom varchar)"_qs))
        return q.lastError();

    if (!q.prepare(
                u"insert into projects(name, description, workingDirectory, postSaveCommand, tags, categories, projectType, isDefault, plugins, emailTo, emailFrom) values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"_qs))
        return q.lastError();

    QVariant knowledgeProjectId = addProject(q,
                                             u"LDBU - Knowledge"_qs,
                                             u"Little Dog Big Universe Knowledge Repository"_qs,
                                             u"c:\data\dev\syntiva\manicdev-www\webapp\content\knowledge"_qs,
                                             u"cd c:\data\dev\syntiva\manicdev-www\bin && .\deploy-s3.bat"_qs,
                                             u"Linux, Arch, Ubuntu, Gnome, Kde, Qt, Java, JavaScript, Python, Kotlin, OSX, Windows, VCS, Cloud, Database"_qs,
                                             u"SysAdmin, Development"_qs,
                                             blogProjectTypeId,
                                             0,
                                             "Hugo,",
                                             "jsmith@syntiva.com",
                                             "jsmith@syntiva.com");
    QVariant coolstuffProjectId = addProject(q,
                                             u"LDBU - Coolstuff"_qs,
                                             u"Little Dog Big Universe Coolstuff"_qs,
                                             u"c:\data\dev\syntiva\manicdev-www\webapp\content\coolstuff"_qs,
                                             u"cd c:\data\dev\syntiva\manicdev-www\bin && .\deploy-s3.bat"_qs,
                                             u"Apps, Open Source, Tools, Libraries, Linux, OSX, Windows, Robotics"_qs,
                                             u"SysAdmin, Development, Other"_qs,
                                             linksProjectTypeId,
                                             0,
                                             "Hugo, ",
                                             "jsmith@syntiva.com",
                                             "jsmith@syntiva.com");
    QVariant notesProjectId = addProject(q,
                                         u"Per - Notes"_qs,
                                         u"Basic note taking"_qs,
                                         u"c:\data\personal\notes"_qs,
                                         u"dir"_qs,
                                         u"ArfArfBebe, code0x378, infoQuant, Shopping, Todo"_qs,
                                         u"Personal, Work"_qs,
                                         notesProjectTypeId,
                                         1,
                                         "Hugo,Mdo",
                                         "jsmith@syntiva.com",
                                         "jsmith@syntiva.com");

    QVariant helpProjectId = addProject(q,
                                        u"MDO - Help"_qs,
                                        u"markdownOrganizer Help System"_qs,
                                        u"c:\data\dev\syntiva\markdownorganizer\app\src\help"_qs,
                                        u"dir"_qs,
                                        u"Gui, Installation, Settings"_qs,
                                        u"Free, Pro, Enterprise"_qs,
                                        helpProjectTypeId,
                                        0,
                                        "Hugo, ",
                                        "jsmith@syntiva.com",
                                        "jsmith@syntiva.com");

    QVariant gfHelpProjectId = addProject(q,
                                          u"GF - Help"_qs,
                                          u"GF Help System"_qs,
                                          u"c:\data\dev\infoquant\gf\gf-help\src\main\resources\help\docs"_qs,
                                          u"dir"_qs,
                                          u"Gui, Installation, Settings, Database, Security, Admin, Analytics"_qs,
                                          u"GenomeFusion, Genomius, cnTrack"_qs,
                                          helpProjectTypeId,
                                          0,
                                          "Hugo, ",
                                          "jsmith@syntiva.com",
                                          "jeff@infoquant.com");
    QVariant mitoProjectId = addProject(q,
                                        u"Mito - Website"_qs,
                                        u"Mitotech static website"_qs,
                                        u"c:\data\dev\syntiva\mitotechpharma-www\webapp\hugo\content"_qs,
                                        u"dir"_qs,
                                        u"SKQ, Biotech, Conference, Dry Eye"_qs,
                                        u"News, Events"_qs,
                                        blogProjectTypeId,
                                        0,
                                        "Hugo, ",
                                        "jsmith@syntiva.com",
                                        "jeff@infoquant.com");
    QVariant skqProjectId = addProject(q,
                                       u"SKQ - Website"_qs,
                                       u"Skq static website"_qs,
                                       u"c:\data\dev\syntiva\skq-www\webapp\hugo\content"_qs,
                                       u"dir"_qs,
                                       u"SKQ, Biotech, Conference, Dry Eye, Mitotech"_qs,
                                       u"News, Events, Publications"_qs,
                                       blogProjectTypeId,
                                       0,
                                       "Hugo, ",
                                       "jsmith@syntiva.com",
                                       "jeff@infoquant.com");









    QVariant knowledgeProjectOSXId = addProject(q,
                                                u"LDBU (osx) - Knowledge"_qs,
                                                u"Little Dog Big Universe Knowledge Repository"_qs,
                                                u"/Users/jeff/data/dev/syntiva/code0x378-www/webapp/content/knowledge"_qs,
                                                u"cd /Users/jeff/data/dev/syntiva/code0x378-www/bin && ./deploy-s3.sh"_qs,
                                                u"Linux, Arch, Ubuntu, Gnome, Kde, Qt, Java, JavaScript, Python, Kotlin, OSX, Windows, VCS, Cloud, Database"_qs,
                                                u"SysAdmin, Development"_qs,
                                                blogProjectTypeId,
                                                0,
                                                "Hugo,",
                                                "jsmith@syntiva.com",
                                                "jsmith@syntiva.com");
    QVariant coolstuffProjectOSXId = addProject(q,
                                                u"LDBU (osx) - Coolstuff"_qs,
                                                u"Little Dog Big Universe Coolstuff"_qs,
                                                u"/Users/jeff/data/dev/syntiva/code0x378-www/webapp/content/coolstuff"_qs,
                                                u"cd /Users/jeff/data/dev/syntiva/code0x378-www/bin && ./deploy-s3.sh"_qs,
                                                u"Apps, Open Source, Tools, Libraries, Linux, OSX, Windows, Robotics"_qs,
                                                u"SysAdmin, Development, Other"_qs,
                                                linksProjectTypeId,
                                                0,
                                                "Hugo, ",
                                                "jsmith@syntiva.com",
                                                "jsmith@syntiva.com");
    QVariant notesProjectOSXId = addProject(q,
                                            u"Per (osx) - Notes"_qs,
                                            u"Basic note taking"_qs,
                                            u"/Users/jeff/data/personal/notes"_qs,
                                            u"ls"_qs,
                                            u"ArfArfBebe, code0x378, infoQuant, Shopping, Todo"_qs,
                                            u"Personal, Work"_qs,
                                            notesProjectTypeId,
                                            1,
                                            "Hugo,Mdo",
                                            "jsmith@syntiva.com",
                                            "jsmith@syntiva.com");

    QVariant helpProjectOSXId = addProject(q,
                                           u"MDO (osx) - Help"_qs,
                                           u"markdownOrganizer Help System"_qs,
                                           u"/Users/jeff/data/dev/syntiva/markdownorganizer/app/src/resources/help"_qs,
                                           u"dir"_qs,
                                           u"Gui, Installation, Settings"_qs,
                                           u"Free, Pro, Enterprise"_qs,
                                           helpProjectTypeId,
                                           0,
                                           "Hugo, ",
                                           "jsmith@syntiva.com",
                                           "jsmith@syntiva.com");

    QVariant gfHelpProjectOSXId = addProject(q,
                                             u"GF (osx) - Help"_qs,
                                             u"GF Help System"_qs,
                                             u"/Users/jeff/data/dev/infoquant/gf/gf-help/src/main/resources/help/docs"_qs,
                                             u"ls"_qs,
                                             u"Gui, Installation, Settings, Database, Security, Admin, Analytics"_qs,
                                             u"GenomeFusion, Genomius, cnTrack"_qs,
                                             helpProjectTypeId,
                                             0,
                                             "Hugo, ",
                                             "jsmith@syntiva.com",
                                             "jeff@infoquant.com");
    QVariant mitoProjectOSXId = addProject(q,
                                           u"Mito (osx) - Website"_qs,
                                           u"Mitotech static website"_qs,
                                           u"/Users/jeff/data/dev/syntiva/mitotechpharma-www/webapp/hugo/content"_qs,
                                           u"ls"_qs,
                                           u"SKQ, Biotech, Conference, Dry Eye"_qs,
                                           u"News, Events"_qs,
                                           blogProjectTypeId,
                                           0,
                                           "Hugo, ",
                                           "jsmith@syntiva.com",
                                           "jeff@infoquant.com");
    QVariant skqProjectOSXId = addProject(q,
                                          u"SKQ (osx) - Website"_qs,
                                          u"Skq static website"_qs,
                                          u"/Users/jeff/data/dev/syntiva/skq-www/webapp/hugo/content"_qs,
                                          u"ls"_qs,
                                          u"SKQ, Biotech, Conference, Dry Eye, Mitotech"_qs,
                                          u"News, Events, Publications"_qs,
                                          blogProjectTypeId,
                                          0,
                                          "Hugo, ",
                                          "jsmith@syntiva.com",
                                          "jeff@infoquant.com");

    /********************************************************
     * Resource
     ********************************************************/

    if (!q.exec(
                u"create table resource(id integer primary key, title varchar, author varchar, date varchar, content text, tags varchar, categories varchar,  website varchar, filePath varchar, project int)"_qs))
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
                u"create table history(id integer primary key, title varchar, author varchar, date varchar, content text, tags varchar, categories varchar,  website varchar, filePath varchar, resource int)"_qs))
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
