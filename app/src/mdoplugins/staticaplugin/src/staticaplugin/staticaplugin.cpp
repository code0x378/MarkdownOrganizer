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


#include "staticaplugin.h"

#include <QWidget>
#include <QApplication>
#include <QFile>
#include <QProcess>

#include "mdocore/global.h"
#include "mdocore/plugindata.h"
#include "mdocore/models/project.h"
#include "mdocore/models/resource.h"
#include "mdocore/slugify.hpp"

bool StaticaPlugin::initialize(const QStringList &arguments,
                            QStringList *error_strings)
{
    Q_UNUSED(arguments);
    Q_UNUSED(error_strings);
    data = new PluginData();
    return true;
}

bool StaticaPlugin::save (const Project &project, const Resource &resource )
{
    QString compiled;
    QString filename;

    if (resource.getFilePath() == NULL || resource.getFilePath() == "") {
        QHash<QString, QString> model;
        model.insert("{{uuid}}", resource.getUuid());
        model.insert("{{title}}", resource.getTitle());
        model.insert("{{date}}", resource.getDate());
        model.insert("{{author}}", resource.getAuthor());
        model.insert("{{website}}", resource.getWebsite());
        model.insert("{{content}}", resource.getContent());
        model.insert("{{tags}}", resource.getTags().replace("&", "").replace("\"", ""));
        model.insert("{{categories}}", resource.getCategories().replace("&", ""
                                                                             "").replace("\"", ""));
        model.insert("{{draft}}", resource.isDraft() ? "true" : "false");
        model.insert("{{images}}", resource.getImages());
        model.insert("{{thumbnail}}", resource.getThumbnail());

        QString tpl =
            "--- \n"
            "uuid: {{uuid}} \n"
            "title: {{title}} \n"
            "linktitle: {{title}} \n"
            "date: {{date}} \n"
            "author: {{author}} \n"
            "website: {{website}} \n"
            "tags:  {{tags}} \n"
            "categories:  {{categories}} \n"
            "draft: {{draft}} \n"
            "images: {{images}} \n"
            "thumbnail: {{thumbnail}} \n"
            "--- \n\n"
            "{{content}} \n";

        compiled = tpl;
        QHash<QString, QString>::iterator i;
        for (i = model.begin(); i != model.end(); ++i) {
            compiled = compiled.replace(i.key(), i.value());
        }

        QString title = resource.getTitle();
        QString slug  =  QString::fromStdString(slugify(title.toLower().toStdString()));
        qInfo() << compiled;
        filename = project.getCurrentDirectory() + QDir::separator() + slug + ".md";
    } else {
        compiled = resource.getContent();
        filename = resource.getFilePath();
    }

    QFile file(filename);
    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << compiled;
    }

    file.close();

    int i = QProcess::execute(project.getPostSaveCommmand());

    return true;
}

bool StaticaPlugin::finalize()
{
    return true;
}

QString StaticaPlugin::getName() const
{
    return "Statica";
}
QString StaticaPlugin::getCategory() const
{
    return "Formats";
}
QString StaticaPlugin::getVersion() const
{
    return "1.0.0";
}
QString StaticaPlugin::getPublisher() const
{
    return "code0x378";
}
QString StaticaPlugin::getPublisherWebsite() const
{
    return "http://www.code0x378.com";
}
QString StaticaPlugin::getPublisherContact() const
{
    return "support@code0x378.com";
}
QString StaticaPlugin::getDescription() const
{
    return tr("Edit and manage statica text files");
}
QString StaticaPlugin::getCopyright() const
{
    return QString(tr("Copyright") + " 2021 code0x378.");
}
QString StaticaPlugin::getLicense() const
{
    return tr("See the MarkdownOrganizer Plugin License");
}
