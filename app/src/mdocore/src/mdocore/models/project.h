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

#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>
#include "model.h"

enum class ProjectType { Generic = 0, Blog = 1, Link = 2, Help = 3, Notes = 4 };

class Project : public Model
{
    Q_ENUMS(Types)
    Q_OBJECT

public:
    Project();
    Project(const Project &other);

    QString getName() const;
    void setName(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QString getWorkingDirectory() const;
    void setWorkingDirectory(const QString &value);

    QString getPostSaveCommmand() const;
    void setPostSaveCommmand(const QString &value);

    int getType() const;
    void setType(int value);

    bool getIsDefault() const;
    void setIsDefault(bool value);

    QString getTags() const;
    void setTags(const QString &value);

    QString getCategories() const;
    void setCategories(const QString &value);

    QString getCurrentDirectory() const;
    void setCurrentDirectory(const QString &value);

    QString getPlugins() const;
    void setPlugins(const QString &value);

    QString getEmailTo() const;
    void setEmailTo(const QString &value);

    QString getEmailFrom() const;
    void setEmailFrom(const QString &value);

    QString getStarred() const;
    void setStarred(const QString &value);

    QString getFileName() const;
    void setFileName(const QString &value);

    static void saveProject(Project *project);
    static void deleteProject(Project *project);

private:

    QString name;
    QString description;
    QString workingDirectory;
    QString postSaveCommmand;
    bool isDefault;
    QString tags;
    QString categories;
    int type = 2;
    QString currentDirectory;
    QString plugins;
    QString emailTo;
    QString emailFrom;
    QString starred;
    QString fileName;

};

#endif // PROJECT_H
