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

#include "resource.h"

Resource::Resource()
{

}

QString Resource::getTitle() const
{
    return title;
}

void Resource::setTitle(const QString &value)
{
    title = value;
}

QString Resource::getDate() const
{
    return date;
}

void Resource::setDate(const QString &value)
{
    date = value;
}

QString Resource::getAuthor() const
{
    return author;
}

void Resource::setAuthor(const QString &value)
{
    author = value;
}

QString Resource::getContent() const
{
    return content;
}

void Resource::setContent(const QString &value)
{
    content = value;
}

QString Resource::getTags() const
{
    return tags;
}

void Resource::setTags(const QString &value)
{
    tags = value;
}

QString Resource::getCategories() const
{
    return categories;
}

void Resource::setCategories(const QString &value)
{
    categories = value;
}

QString Resource::getWebsite() const
{
    return website;
}

void Resource::setWebsite(const QString &value)
{
    website = value;
}

QString Resource::getFilePath() const
{
    return filePath;
}

void Resource::setFilePath(const QString &value)
{
    filePath = value;
}

bool Resource::isDraft() const
{
    return draft;
}

void Resource::setDraft(bool value)
{
    draft = value;
}

QString Resource::getUuid() const
{
    return uuid;
}

void Resource::setUuid(const QString &value)
{
    uuid = value;
}

