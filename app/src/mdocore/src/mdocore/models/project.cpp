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

#include "project.h"
#include "mdocore/mdoapplication.h"

#include <QFile>
#include <QSettings>

Project::Project()
{


}

Project::Project(const Project &other)
{

}

QString Project::getName() const
{
    return name;
}

void Project::setName(const QString &value)
{
    name = value;
}

QString Project::getDescription() const
{
    return description;
}

void Project::setDescription(const QString &value)
{
    description = value;
}

QString Project::getWorkingDirectory() const
{
    return workingDirectory;
}

void Project::setWorkingDirectory(const QString &value)
{
    workingDirectory = value;
}

QString Project::getPostSaveCommmand() const
{
    return postSaveCommmand;
}

void Project::setPostSaveCommmand(const QString &value)
{
    postSaveCommmand = value;
}

int Project::getType() const
{
    return type;
}

void Project::setType(const int value)
{
    type = value;
}

bool Project::getIsDefault() const
{
    return isDefault;
}

void Project::setIsDefault(bool value)
{
    isDefault = value;
}

QString Project::getTags() const
{
    return tags;
}

void Project::setTags(const QString &value)
{
    tags = value;
}

QString Project::getCategories() const
{
    return categories;
}

void Project::setCategories(const QString &value)
{
    categories = value;
}

QString Project::getCurrentDirectory() const
{
    return currentDirectory;
}

void Project::setCurrentDirectory(const QString &value)
{
    currentDirectory = value;
}

QString Project::getPlugins() const
{
    return plugins;
}

void Project::setPlugins(const QString &value)
{
    plugins = value;
}

QString Project::getEmailTo() const
{
    return emailTo;
}

void Project::setEmailTo(const QString &value)
{
    emailTo = value;
}

QString Project::getEmailFrom() const
{
    return emailFrom;
}

void Project::setEmailFrom(const QString &value)
{
    emailFrom = value;
}

QString Project::getStarred() const
{
    return starred;
}

void Project::setStarred(const QString &value)
{
    starred = value;
}

QString Project::getFileName() const
{
    return fileName;
}

void Project::setFileName(const QString &value)
{
    fileName = value;
}

void Project::saveProject(Project *project)
{
    QString path = qApp->applicationDirPath() + "/data/projects/" + project->getName() + ".ini";
    QSettings *settings = new QSettings( path, QSettings::IniFormat);

    settings->beginGroup("Project");
    settings->setValue("title", project->getName());
    settings->setValue("description", project->getDescription());
    settings->setValue("workingDirectory", project->getWorkingDirectory());
    settings->setValue("postSaveCommand", project->getPostSaveCommmand());
    settings->setValue("tags", project->getTags());
    settings->setValue("categories", project->getCategories());
    settings->setValue("isDefault", project->getIsDefault());
    settings->setValue("plugins", project->getPlugins());
    settings->setValue("emailTo", project->getEmailTo());
    settings->setValue("emailFrom", project->getEmailFrom());
    settings->endGroup();
}

void Project::deleteProject(Project *project)
{
    QString path = qApp->applicationDirPath() + "/data/projects/" + project->getName() + ".ini";
    QFile file (path);
    file.remove();
}

Project*  Project::loadProject(QString fileName)
{
    QString path = qApp->applicationDirPath() + "/data/projects/" + fileName;
    QSettings *settings = new QSettings(path, QSettings::IniFormat);
    Project  *project = new Project();

    settings->beginGroup("Project");
    project->setFileName(fileName);
    project->setName(settings->value("title", "").toString());
    project->setType(settings->value("type", false).toInt());
    project->setDescription(settings->value("description", "").toString());
    project->setWorkingDirectory(settings->value("workingDirectory", "").toString());
    project->setPostSaveCommmand(settings->value("postSaveCommand", "").toString());
    project->setTags(settings->value("tags", "").toString());
    project->setCategories(settings->value("categories", "").toString());
    project->setIsDefault(settings->value("isDefault", false).toBool());
    project->setPlugins(settings->value("plugins", "").toString());
    project->setEmailTo(settings->value("emailTo", "").toString());
    project->setEmailFrom(settings->value("emailFrom", "").toString());
    settings->endGroup();

    return project;
}
