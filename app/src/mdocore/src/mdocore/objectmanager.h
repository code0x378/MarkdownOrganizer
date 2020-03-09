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

#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <QObject>

class ObjectManager : public QObject
{
    Q_OBJECT
public:
    explicit ObjectManager(QObject *parent = 0);
    static ObjectManager *instance();
private:
    static ObjectManager *objectManager;

};

#define OBJECT_MANAGER ObjectManager::instance()
#define OBJECT_MANAGER_INITIALIZE ObjectManager::instance()

#endif // OBJECTMANAGER_H
