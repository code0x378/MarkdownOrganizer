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

#include "widgetmainwindow.h"
#include "ui_widgetmainwindow.h"

#include <QApplication>
#include <QToolButton>
#include <QMessageBox>
#include <QWidgetAction>
#include <QMenuBar>
#include <QMenu>
#include <QKeyEvent>
#include <QToolBar>
#include <QToolTip>
#include <QDockWidget>
#include <QDesktopWidget>
#include <QTimer>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QDesktopServices>
#include <QSizePolicy>
#include <QPluginLoader>
#include <QMutex>
#include <QDialog>
#include <QHash>
#include <QTime>
#include <QProcess>
#include <QCheckBox>

#include "mdocore/lib/hoedown/src/html.h"
#include  "mdocore/lib/hoedown/src/buffer.h"

#include "mdocore/util/qtutils.h"
#include "mdocore/global.h"
#include "mdocore/util/qtutils.h"
#include "mdocore/gui/dialogs/aboutdialog.h"
#include "mdocore/iplugin.h"
#include "mdocore/pluginmanager.h"
#include "mdocore/logmanager.h"
#include "mdocore/gui/dialogs/aboutdialog.h"
#include "mdocore/gui/dialogs/settingsdialog.h"
#include "mdocore/mdoapplication.h"
#include "mdocore/models/project.h"
#include "mdocore/models/resource.h"

#include <mdocore/gui/dialogs/projectdialog.h>


WidgetMainWindow::WidgetMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WidgetMainWindow)
{
    ui->setupUi(this);
    addMainMenu();
    addComponentDynamically();
    createActions();
    addSignalsAndSlots();
    setupTrayIcon();
    // stressTest(1000);
    displayTags();
    displayCategories();

    ui->lineEditAuthor->setText("LittleDogBigUniverse");
    ui->lineEditDate->setText(QDate::currentDate().toString("yyyy-MM-dd"));


    QHash<QString, Project *>::iterator i;
    for (i = APP->getProjects()->begin(); i != APP->getProjects()->end(); ++i)
        ui->comboBoxProjects->addItem((i.value()->getName()));

    VERIFY(connect(ui->comboBoxProjects, SIGNAL(currentIndexChanged(int)),
                   SLOT(changeProject())));
    selectActiveProduct();
}

WidgetMainWindow::~WidgetMainWindow()
{
    delete ui;
}


void WidgetMainWindow::selectActiveProduct()
{
    QString projectName = APP->getActiveProject()->getName();
    ui->comboBoxProjects->setCurrentIndex(ui->comboBoxProjects->findText(
                                              projectName));
}

void WidgetMainWindow::changeProject()
{
    APP->setActiveProject(APP->getProjects()->value(
                              ui->comboBoxProjects->currentText()));

    displayTags();
    displayCategories();

    ui->lineEditWebsite->setVisible(false);

    ProjectType p = APP->getActiveProject()->getType();
    switch (p) {
    case ProjectType::Link:
        ui->lineEditWebsite->setVisible(true);
        break;
    default:
        break;
    }
}

WidgetMainWindow *WidgetMainWindow::mainWindow = 0;
WidgetMainWindow *WidgetMainWindow::instance()
{
    static QMutex mutex;
    if (!mainWindow) {
        mutex.lock();

        if (!mainWindow)
            mainWindow = new WidgetMainWindow();

        mutex.unlock();
    }
    return mainWindow;
}


void WidgetMainWindow::addMainMenu()
{
    /********************************************************
     * File menu
     ********************************************************/

    exitAction = new QAction(tr("&exit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    VERIFY(connect(exitAction, SIGNAL(triggered()), this, SLOT(close())));

    fileMenu = menuBar()->addMenu(tr("&file"));
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    /********************************************************
     * Edit menu
     ********************************************************/

    projectAction = new QAction(tr("&projects"), this);
    VERIFY(connect(projectAction, SIGNAL(triggered()), this,
                   SLOT(showProjectDialog())));

    settingsAction = new QAction(tr("&settings"), this);
    VERIFY(connect(settingsAction, SIGNAL(triggered()), this,
                   SLOT(showSettingsDialog())));

    editMenu = menuBar()->addMenu(tr("&edit"));
    editMenu->addAction(projectAction);
    editMenu->addSeparator();
    editMenu->addAction(settingsAction);

    /********************************************************
     * Tools menu
     ********************************************************/

    launchMainAppAction = new QAction(tr("open &markdownOrganizer"), this);
    launchMainAppAction->setObjectName("launchMainAppAction");
    launchMainAppAction->setShortcut(QApplication::translate("AppMainWindow",
                                                             "Alt+W", 0));
    VERIFY(connect(launchMainAppAction, SIGNAL(triggered()), this,
                   SLOT(launchMainApp())));

    toolsMenu = new QMenu(tr("&tools"));
    menuBar()->addMenu(toolsMenu);
    toolsMenu->addAction(launchMainAppAction);

    /********************************************************
     * Help menu
     ********************************************************/

    aboutAction = new QAction(tr("&about"), this);
    VERIFY(connect(aboutAction, SIGNAL(triggered()), this,
                   SLOT(showAboutDialog())));

    viewLittleDogBigUniverseWebsiteAction = new QAction(
        QApplication::translate("AppMainWindow",
                                "visit littledogbiguniverse.com", 0), this);
    viewLittleDogBigUniverseWebsiteAction->setObjectName("viewLittleDogBigUniverseWebsiteAction");
    connect(viewLittleDogBigUniverseWebsiteAction, SIGNAL(triggered()), this,
            SLOT(openWebBrowser()));

    helpMenu = menuBar()->addMenu(tr("&help"));
    helpMenu->addAction(viewLittleDogBigUniverseWebsiteAction);
    helpMenu->addSeparator();
    helpMenu->addAction(aboutAction);
}

void WidgetMainWindow::addComponentDynamically()
{
}

void WidgetMainWindow::addSignalsAndSlots()
{
    VERIFY(connect(ui->buttonReset, SIGNAL(released()), this, SLOT(handleReset())));
    VERIFY(connect(ui->buttonSave, SIGNAL(released()), this, SLOT(handleSave())));
    //    VERIFY(connect(ui->plainTextEdit, SIGNAL(textChanged()),this, SLOT(updatePreview())));
    VERIFY(connect(ui->tabWidgetEditor, SIGNAL(currentChanged(int)), this,
                   SLOT(updatePreview())));
}

void WidgetMainWindow::showAboutDialog()
{
    aboutDialog = new AboutDialog(this);
    aboutDialog->exec();
}

void WidgetMainWindow::showProjectDialog()
{
    projectDialog = new ProjectDialog(this);
    projectDialog->exec();
}

void WidgetMainWindow::showSettingsDialog()
{
    settingsDialog = new SettingsDialog(this);
    settingsDialog->exec();
}

void WidgetMainWindow::createActions()
{
    open = new QAction(tr("&Open"), this);
    VERIFY(connect(open, SIGNAL(triggered()), this, SLOT(show())));

    close = new QAction(tr("&Quit"), this);
    VERIFY(connect(close, SIGNAL(triggered()), this, SLOT(exitApp())));
}

void WidgetMainWindow::openWebBrowser()
{
    QObject *pObject = sender();
    QString name = pObject->objectName();
    QString url = "http://www.google.com";

    if (name == "viewLittleDogBigUniverseWebsiteAction") {
        url = "http://www.littledogbiguniverse.com";
    } else {
        url = "http://www.google.com";
    }

    QDesktopServices::openUrl(QUrl(url));
}

void WidgetMainWindow::launchMainApp()
{
    QString path = QCoreApplication::applicationDirPath();
    path.append("/markdownorganizer-app");

    QProcess process;
    process.startDetached(path, QStringList());
}

void WidgetMainWindow::exitApp()
{
#ifndef QT_DEBUG
    if (QMessageBox::No == QMessageBox::question(this, "Confirm",
                                                 "Are you sure you want to quit?")) {
        return;
    }
#endif
    // this->writeUISettings();
    qApp->quit();
}


void WidgetMainWindow::closeEvent(QCloseEvent *event)
{
#ifndef QT_DEBUG
    if (trayIcon->isVisible()) {
        if (!hiddenMessageDisplayed) {
            hiddenMessageDisplayed = true;
            trayIcon->showMessage(tr("markdownOrganizer"),
                                  tr("The markdownOrganizer Widget is still running. To quit please right-click this icon and select Quit"));
        }
        hide();
        event->ignore();
    }
#else
    qApp->quit();
#endif
}


void WidgetMainWindow::displayTags()
{

    QList<QCheckBox *> checkboxes = ui->groupBoxTags->findChildren<QCheckBox *>();
    for (QCheckBox *chk : checkboxes)
        delete chk;

    int row = 1;
    int col = 1;
    QStringList tags = APP->getActiveProject()->getTags().split(",");
    QGridLayout *layout = new QGridLayout();
    delete ui->groupBoxTags->layout();
    ui->groupBoxTags->setLayout (layout);
    foreach (QString tag, tags) {
        layout->addWidget(new QCheckBox(tag), row - 1, col - 1, 1, 1);
        if (col % 3 == 0) {
            col = 1;
            row++;
        } else {
            col++;
        }
    }
}

void WidgetMainWindow::displayCategories()
{

    QList<QCheckBox *>  checkboxes =
        ui->groupBoxCategories->findChildren<QCheckBox *>();
    for (QCheckBox *chk : checkboxes)
        delete chk;

    int row = 1;
    int col = 1;
    QStringList categories = APP->getActiveProject()->getCategories().split(",");
    delete ui->groupBoxCategories->layout();
    QGridLayout *layout = new QGridLayout();
    ui->groupBoxCategories->setLayout (layout);
    foreach (QString category, categories) {
        layout->addWidget(new QCheckBox(category), row - 1, col - 1, 1, 1);
        if (col % 3 == 0) {
            col = 1;
            row++;
        } else {
            col++;
        }
    }

}

void WidgetMainWindow::handleSave()
{
    QString tags = "";
    QList<QCheckBox *> checkboxes = ui->groupBoxTags->findChildren<QCheckBox *>();
    for (QCheckBox *chk : checkboxes) {
        if (chk->isChecked())
            tags += "\"" + chk->text() + "\", ";
    }

//    if (ui->otherLineEdit->text() != "") {
//        QStringList tempTags = ui->otherLineEdit->text().split(',',
//                                                               QString::SkipEmptyParts);
//        for (int i = 0; i < tempTags.size(); ++i)
//            tags += "\"" + tempTags[i] + "\", ";
//    }

    QString categories = "";
    checkboxes = ui->groupBoxCategories->findChildren<QCheckBox *>();
    for (QCheckBox *chk : checkboxes) {
        if (chk->isChecked())
            categories += "\"" + chk->text() + "\", ";
    }

    Resource *resource = new Resource();
    resource->setTitle(ui->lineEditTitle->text());
    resource->setDate(ui->lineEditDate->text());
    resource->setAuthor(ui->lineEditAuthor->text());
    resource->setWebsite(ui->lineEditWebsite->text());
    resource->setContent(ui->plainTextEdit->document()->toPlainText());
    resource->setTags(tags.replace("&", ""));
    resource->setCategories(categories.replace("&", ""));

    foreach (IPlugin *plugin,  PLUGIN_MANAGER->getPluginList()) {
        if (APP->getActiveProject()->getPlugins().contains(plugin->getName())) {
            plugin->save(*APP->getActiveProject(), *resource);
        }
    }
}

void WidgetMainWindow::handleReset()
{
    ui->lineEditAuthor->setText("LittleDogBigUniverse");
    ui->lineEditDate->setText(QDate::currentDate().toString("yyyy-MM-dd"));
    ui->lineEditTitle->setText("");
    ui->lineEditWebsite->setText("");


    QList<QCheckBox *> checkboxes = ui->groupBoxTags->findChildren<QCheckBox *>();
    for (QCheckBox *chk : checkboxes) {
        chk->setChecked(false);
    }

    checkboxes = ui->groupBoxCategories->findChildren<QCheckBox *>();
    for (QCheckBox *chk : checkboxes) {
        chk->setChecked(false);
    }
}

void WidgetMainWindow::setupTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(open);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(close);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/mdocore/icons/app_196.png"));
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->show();

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this,
            SLOT(trayIconClicked(QSystemTrayIcon::ActivationReason)));
}

void WidgetMainWindow::trayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger)
        this->show();
}


void WidgetMainWindow::updatePreview()
{
    QTime t;
    t.start();
    QString plainText  = ui->plainTextEdit->toPlainText();
    plainText = QtUtils::removeFrontMatter(plainText);
    QString htmlText = markdown(plainText);
    ui->textPreview->setHtml(htmlText);
    //    ui->textPreview->setHtml(ui->plainTextEdit->toPlainText());
    ui->plainTextEdit->setFocus();
}

void WidgetMainWindow::stressTest(int cnt)
{
    QString t = "";
    for (int i = 0; i < cnt; i ++) {
        t += "#This is a long, long, long, long line of text to be rendeered \n";
    }
    ui->plainTextEdit->setPlainText(t);
}

QString WidgetMainWindow::markdown(QString in)
{

    if (in != "") {
        QByteArray qba = in.toUtf8();
        const char *txt = qba.constData();
        if (NULL == txt) qDebug() << "txt was null!";
        if (0 < qba.size()) {
            hoedown_renderer *renderer = hoedown_html_renderer_new((hoedown_html_flags)NULL,
                                                                   16);
            // TODO: investigate further extensions
            unsigned int extensions = HOEDOWN_EXT_FOOTNOTES;
            hoedown_document *document = hoedown_document_new(renderer,
                                                              (hoedown_extensions)extensions, 16);
            hoedown_buffer *in_buf = hoedown_buffer_new(qba.size());
            hoedown_buffer_puts(in_buf, txt);
            hoedown_buffer *html = hoedown_buffer_new(64);
            hoedown_document_render(document, html, in_buf->data, in_buf->size);
            QString result(QString::fromUtf8(hoedown_buffer_cstr(html)));
            hoedown_buffer_free(html);
            hoedown_buffer_free(in_buf);
            hoedown_document_free(document);
            hoedown_html_renderer_free(renderer);
            return result;
        } else
            LOG_INFO("No text provided - Nothing to render with markdow");
    }
    return "";
}

QString WidgetMainWindow::wrapInHTMLDoc(QString in)
{
    QString result(in
                   .prepend("<html>\n <head>\n <meta charset=\"utf-8\">\n</head>\n <body>\n")
                   .append("\n </body>\n</html>"));
    return result;
}
