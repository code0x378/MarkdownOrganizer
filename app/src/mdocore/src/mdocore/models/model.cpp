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

#include "model.h"

Model::Model(QObject *parent) : QObject(parent)
{

}

QString Model::getCreatedBy() const
{
    return createdBy;
}

void Model::setCreatedBy(const QString &value)
{
    createdBy = value;
}

QDate Model::getCreatedAt() const
{
    return createdAt;
}

void Model::setCreatedAt(const QDate &value)
{
    createdAt = value;
}

QString Model::getUpddatedBy() const
{
    return upddatedBy;
}

void Model::setUpddatedBy(const QString &value)
{
    upddatedBy = value;
}

QDate Model::getUpdatedAt() const
{
    return updatedAt;
}

void Model::setUpdatedAt(const QDate &value)
{
    updatedAt = value;
}
