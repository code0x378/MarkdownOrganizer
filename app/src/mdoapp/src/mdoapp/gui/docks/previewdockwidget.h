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

#ifndef PREVIEWDOCKWIDGET_H
#define PREVIEWDOCKWIDGET_H

#include <QDockWidget>
#include <QWebEngineView>

#include "mdodockwidget.h"

namespace Ui {
class PreviewDockWidget;
}

class PreviewDockWidget : public DsDockWidget
{
    Q_OBJECT

public:
    explicit PreviewDockWidget(QWidget *parent = 0);
    ~PreviewDockWidget();

public slots:
    void showWelcomePage();
    void launchMdoWebsite();
private slots:
    void updatePreview(QString);

private:
    Ui::PreviewDockWidget *ui;
    QWebEngineView *view;
    void loadCss();
    QString css;
};

#endif // PREVIEWDOCKWIDGET_H
