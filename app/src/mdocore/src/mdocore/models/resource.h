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

#ifndef RESOURCE_H
#define RESOURCE_H

#include <QObject>
#include <QUuid>

class Resource : public QObject
{
    Q_OBJECT

public:
    Resource();

    QString getTitle() const;
    void setTitle(const QString &value);

    QString getDate() const;
    void setDate(const QString &value);

    QString getAuthor() const;
    void setAuthor(const QString &value);

    QString getContent() const;
    void setContent(const QString &value);

    QString getTags() const;
    void setTags(const QString &value);

    QString getCategories() const;
    void setCategories(const QString &value);

    QString getWebsite() const;
    void setWebsite(const QString &value);

    QString getFilePath() const;
    void setFilePath(const QString &value);

    bool isDraft() const;
    void setDraft(bool value);

    QString getUuid() const;
    void setUuid(const QString &value);

    QString getThumbnail() const;
    void setThumbnail(const QString &value);

    QString getImages() const;
    void setImages(const QString &value);

protected:
    QString title = "";
    QString date = "";
    QString author = "";
    QString content = "";
    QString tags = "";
    QString categories = "";
    QString website = "";
    QString filePath = "";
    QString thumbnail = "";
    QString images = "";
    bool draft = false;
    QString uuid = QUuid::createUuid().toString();
};

#endif // RESOURCE_H
