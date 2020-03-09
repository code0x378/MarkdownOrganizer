/*
* Markdown Organizer
* Copyright (C) 2016-2020 code0x378
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


#include "hugoplugin.h"

#include <QWidget>
#include <QApplication>
#include <QFile>
#include <QProcess>

#include "mdocore/global.h"
#include "mdocore/plugindata.h"
#include "mdocore/models/project.h"
#include "mdocore/models/resource.h"
#include "mdocore/slugify.hpp"

bool HugoPlugin::initialize(const QStringList &arguments,
                            QStringList *error_strings)
{
    Q_UNUSED(arguments);
    Q_UNUSED(error_strings);
    data = new PluginData();
    return true;
}

bool HugoPlugin::save (const Project &project, const Resource &resource )
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
        model.insert("{{tags}}", resource.getTags().replace("&", ""));
        model.insert("{{categories}}", resource.getCategories().replace("&", ""));
        model.insert("{{draft}}", resource.isDraft() ? "true" : "false");

        QString tpl =
            "+++ \n"
            "uuid = \"{{uuid}}\" \n"
            "title = \"{{title}}\" \n"
            "linktitle = \"{{title}}\" \n"
            "date = \"{{date}}\" \n"
            "author = \"{{author}}\" \n"
            "website = \"{{website}}\" \n"
            "tags = [ {{tags}} ] \n"
            "categories = [ {{categories}} ] \n"
            "draft = \"{{draft}}\" \n"
            "+++ \n\n"
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

bool HugoPlugin::finalize()
{
    return true;
}

QString HugoPlugin::getName() const
{
    return "Hugo";
}
QString HugoPlugin::getCategory() const
{
    return "Formats";
}
QString HugoPlugin::getVersion() const
{
    return "1.0.0";
}
QString HugoPlugin::getPublisher() const
{
    return "code0x378";
}
QString HugoPlugin::getPublisherWebsite() const
{
    return "http://www.code0x378.com";
}
QString HugoPlugin::getPublisherContact() const
{
    return "support@code0x378.com";
}
QString HugoPlugin::getDescription() const
{
    return tr("Edit and manage hugo text files");
}
QString HugoPlugin::getCopyright() const
{
    return QString(tr("Copyright") + " 2020 code0x378.");
}
QString HugoPlugin::getLicense() const
{
    return tr("See the MarkdownOrganizer Plugin License");
}
