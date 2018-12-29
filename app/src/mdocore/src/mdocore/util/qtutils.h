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

#pragma once
#include <QString>
#include <QModelIndex>

QT_BEGIN_NAMESPACE
class QThread;
class QTreeWidgetItem;
class QAbstractItemModel;
QT_END_NAMESPACE

#ifdef QT_NO_DEBUG
#define VERIFY(x) (x)
#else //QT_NO_DEBUG
#define VERIFY(x) Q_ASSERT(x)
#endif //QT_NO_DEBUG

namespace QtUtils {
template<typename T>
QString toQString(const T &value);
std::string toStdString(const QString &value);
std::string toStdStringSafe(const QString &value);
void cleanUpThread(QThread *const thread);
QString removeFrontMatter(QString text);
QString markdownConverter(QString in);
QString wrapInHTMLDoc(QString in, QString css = QString());
}
