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

#include "previewdockwidget.h"
#include "ui_previewdockwidget.h"

#include <QWebEngineView>
#include <QWebEngineSettings>

#include "mdodockwidget.h"
#include "mdocore/util/qtutils.h"
#include "mdocore/models/resource.h"
#include "mdocore/pluginmanager.h"
#include "mdocore/logmanager.h"
#include "mdocore/settingsmanager.h"
#include "mdocore/mdoapplication.h"
#include "mdocore/iplugin.h"

#include "mdocore/lib/hoedown/src/html.h"
#include "mdocore/lib/hoedown/src/buffer.h"
#include "mdocore/logmanager.h"

PreviewDockWidget::PreviewDockWidget(QWidget *parent) :
    DsDockWidget(),
    ui(new Ui::PreviewDockWidget)
{
    ui->setupUi(this);

    view = new QWebEngineView(this);
    view->settings()->setAttribute(QWebEngineSettings::FocusOnNavigationEnabled,
                                   false);
    QVBoxLayout *layout = new QVBoxLayout();
    ui->viewFrame->setLayout(layout);
    ui->viewFrame->layout()->setContentsMargins(0, 0, 0, 0);
    ui->viewFrame->layout()->addWidget(view);
    loadCss();

    showWelcomePage();

}

PreviewDockWidget::~PreviewDockWidget()
{
    delete ui;
}

void PreviewDockWidget::updatePreview(QString htmlText)
{
    QTime t;
    t.start();
    view->setHtml(QtUtils::wrapInHTMLDoc(htmlText, this->css));

    LOG_DEBUG(QString("Preview rendered in: %1 ms").arg(t.elapsed()));
}

void PreviewDockWidget::loadCss()
{
    QString name(":/mdocore/css/%1.css");
    name = name.arg(SETTINGS_MANAGER->getString("Interface/ColorScheme",
                                                "Dark")).toLower();
    QFile file(name);
    if (!file.open(QIODevice::ReadOnly)) {
        LOG_DEBUG("Css file not loaded");
    }

    QTextStream in(&file);
    QString text;
    while (!in.atEnd()) {
        text += in.readLine();
    }
    file.close();

    this->css = text;

    LOG_DEBUG("Css file loaded");
}

void PreviewDockWidget::showWelcomePage()
{
    view->load(QUrl::fromLocalFile(
                   QFileInfo("resources/html/welcome.html").absoluteFilePath()));
}

void PreviewDockWidget::launchMdoWebsite()
{
    view->load(QUrl("http://localhost:7011/"));
}
