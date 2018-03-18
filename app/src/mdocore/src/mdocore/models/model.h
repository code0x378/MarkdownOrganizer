/*
* Markdown Organizer
* Copyright (C) 2016-2018 LittleDogBigUniverse
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

#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QDate>

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

    QString getCreatedBy() const;
    void setCreatedBy(const QString &value);

    QDate getCreatedAt() const;
    void setCreatedAt(const QDate &value);

    QString getUpddatedBy() const;
    void setUpddatedBy(const QString &value);

    QDate getUpdatedAt() const;
    void setUpdatedAt(const QDate &value);

private:

    QString createdBy;
    QDate createdAt;
    QString upddatedBy;
    QDate updatedAt;

signals:

public slots:
};

#endif // MODEL_H
