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

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "mdocore/global.h"

class DatabaseManager
{

public:
    DatabaseManager();
    static DatabaseManager *instance();

private:
    static DatabaseManager *databaseManager;
};

#define DATABASE_MANAGER DatabaseManager::instance()
#define DATABASE_MANAGER_INITIALIZE DatabaseManager::instance()

#endif // DATABASEMANAGER_H
