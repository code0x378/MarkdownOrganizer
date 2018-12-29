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

#include "appmainwindow.h"
#include "helpwindow.h"

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
#include <QPushButton>
#include <QLabel>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QDesktopServices>
#include <QSizePolicy>
#include <QPluginLoader>
#include <QMutex>
#include <QProcess>
#include <QtSql>
#include <QWebEngineView>

#include <mdocore/lib/QtAwesome/QtAwesome/QtAwesome.h>

#include "mdocore/global.h"
#include "ui_appmainwindow.h"
#include "mdocore/util/qtutils.h"
#include "mdocore/mdoapplication.h"
#include "mdocore/gui/dialogs/aboutdialog.h"
#include "mdocore/gui/dialogs/settingsdialog.h"
#include "mdocore/gui/dialogs/plugindialog.h"
#include "mdocore/gui/dialogs/projectdialog.h"
#include "mdocore/iplugin.h"
#include "mdocore/pluginmanager.h"
#include "mdocore/settingsmanager.h"
#include "mdocore/logmanager.h"
#include "mdoapp/gui/browserwindow.h"
#include "mdoapp/gui/docks/menudockwidget.h"
#include "mdoapp/gui/docks/logdockwidget.h"
#include "mdoapp/gui/docks/projectdockwidget.h"
#include "mdoapp/gui/docks/helpdockwidget.h"
#include "mdoapp/gui/docks/previewdockwidget.h"
#include "mdoapp/gui/tools/dashboardtoolwidget.h"
#include "mdoapp/gui/tools/editortoolwidget.h"
#include "mdoapp/gui/tools/historytoolwidget.h"
#include "mdoapp/gui/tools/helptoolwidget.h"


AppMainWindow::AppMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AppMainWindow)
{
    ui->setupUi(this);

    awesome = new QtAwesome();
    awesome->initFontAwesome();

    setupComponents();
    setupMainMenu();
    setupMainToolBar();
    setupSlots();
    addStatusBar();
    readUISettings();

    LOG_DEBUG("Main window loaded");
}

AppMainWindow::~AppMainWindow()
{
    delete ui;
}

AppMainWindow *AppMainWindow::appMainWindow = 0;
AppMainWindow *AppMainWindow::instance()
{
    static QMutex mutex;
    if (!appMainWindow) {
        mutex.lock();

        if (!appMainWindow)
            appMainWindow = new AppMainWindow();

        mutex.unlock();
    }
    return appMainWindow;
}

void AppMainWindow::setupMainMenu()
{
    awesome = new QtAwesome( qApp );
    awesome->initFontAwesome();

    /********************************************************
     * File menu
     ********************************************************/

    newAction = new QAction( tr("&new"), this);
    VERIFY(connect(newAction, SIGNAL(triggered()), editorToolWidget,
                   SLOT(handleReset())));

    saveAction = new QAction(tr("&save"), this);
    VERIFY(connect(saveAction, SIGNAL(triggered()), editorToolWidget,
                   SLOT(handleSave())));

    exitAction = new QAction(tr("&exit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    VERIFY(connect(exitAction, SIGNAL(triggered()), this, SLOT(close())));

    fileMenu = menuBar()->addMenu(tr("&file"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(saveAction);
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

    launchMainAppAction = new QAction(tr("open &widget"), this);
    launchMainAppAction->setObjectName("launchMainAppAction");
    launchMainAppAction->setShortcut(QApplication::translate("AppMainWindow",
                                                             "Alt+W", 0));
    VERIFY(connect(launchMainAppAction, SIGNAL(triggered()), this,
                   SLOT(launchMainApp())));

//    viewDsWebsiteAction = new QAction(tr("open &markdownorganizer.com"), this);
//    viewDsWebsiteAction->setObjectName("viewDsWebsiteAction");
//    viewDsWebsiteAction->setShortcut(QApplication::translate("AppMainWindow",
//                                                             "Alt+D", 0));
//    VERIFY(connect(viewDsWebsiteAction, SIGNAL(triggered()), previewDockWidget,
//                   SLOT(launchMdoWebsite())));

    toolsMenu = new QMenu(tr("&tools"));
    menuBar()->addMenu(toolsMenu);
    toolsMenu->addAction(launchMainAppAction);
//    toolsMenu->addAction(viewDsWebsiteAction);

    /********************************************************
     * Window menu
     ********************************************************/

//    toggleCntrackWorkspaceAction = new QAction(tr("&menu"), this);
//    toggleCntrackWorkspaceAction->setShortcut(
//        QApplication::translate("AppMainWindow", "Alt+M", 0));
//    toggleCntrackWorkspaceAction->setCheckable(true);
//    VERIFY(connect(toggleCntrackWorkspaceAction, SIGNAL(triggered()), this,
//                   SLOT(toggleMenuWorkspaceWidget())));

    togglePreviewAction = new QAction(tr("&preview"), this);
    togglePreviewAction->setShortcut(
        QApplication::translate("AppMainWindow", "Alt+P", 0));
//    togglePreviewAction->setCheckable(true);
    togglePreviewAction->setIcon(awesome->icon(fa::eye));
    VERIFY(connect(togglePreviewAction, SIGNAL(triggered()), this,
                   SLOT(togglePreviewWidget())));

    toggleLogDockAction = new QAction(tr("&logs"), this);
//    toggleLogDockAction->setCheckable(true);
    toggleLogDockAction->setIcon(awesome->icon(fa::list));
    toggleLogDockAction->setShortcut(QApplication::translate("AppMainWindow",
                                                             "Alt+L", 0));
    VERIFY(connect(toggleLogDockAction, SIGNAL(triggered()), this,
                   SLOT(toggleLogDock())));

    toggleHelpDockAction = new QAction(tr("&help"), this);
//    toggleHelpDockAction->setCheckable(true);
    toggleHelpDockAction->setIcon(awesome->icon(fa::questioncircle));
    toggleHelpDockAction->setShortcut(QApplication::translate("AppMainWindow",
                                                              "Alt+H", 0));
    VERIFY(connect(toggleHelpDockAction, SIGNAL(triggered()), this,
                   SLOT(toggleHelpDock())));

    windowMenu = new QMenu(tr("&window"));
    menuBar()->addMenu(windowMenu);
//    panelsMenu = new QMenu(tr("&panels"));
//    windowMenu->addMenu(panelsMenu);
//    windowMenu->addAction(toggleCntrackWorkspaceAction);
    windowMenu->addAction(togglePreviewAction);
    windowMenu->addAction(toggleLogDockAction);
    windowMenu->addAction(toggleHelpDockAction);

    /********************************************************
     * Help menu
     ********************************************************/

    aboutAction = new QAction(tr("&about"), this);
    VERIFY(connect(aboutAction, SIGNAL(triggered()), this,
                   SLOT(showAboutDialog())));

    helpAction = new QAction(tr("&helpContents"), this);
    VERIFY(connect(helpAction, SIGNAL(triggered()), this,
                   SLOT(showHelpWindow())));

    viewJeffSmithDevWebsiteAction = new QAction(tr(
                                                    "visit JeffSmithDev.com", 0), this);
    viewJeffSmithDevWebsiteAction->setObjectName("viewJeffSmithDevWebsiteAction");
    connect(viewJeffSmithDevWebsiteAction, SIGNAL(triggered()), this,
            SLOT(openWebBrowser()));

    viewWelcomeAction = new QAction(tr(
                                        "view welcome page", 0), this);
    viewWelcomeAction->setObjectName("viewWelcomeAction");
    connect(viewWelcomeAction, SIGNAL(triggered()), previewDockWidget,
            SLOT(showWelcomePage()));

    helpMenu = menuBar()->addMenu(tr("&help"));
    helpMenu->addAction(helpAction);
    helpMenu->addAction(viewJeffSmithDevWebsiteAction);
    helpMenu->addAction(viewWelcomeAction);
    helpMenu->addSeparator();
    helpMenu->addAction(aboutAction);
}

void AppMainWindow::togglePreviewWidget()
{
    addDockWidget(Qt::RightDockWidgetArea, previewDockWidget);
    previewDockWidget->setVisible(!previewDockWidget->isVisible());
    togglePreviewAction->setChecked(previewDockWidget->isVisible());
}

void AppMainWindow::toggleMenuWorkspaceWidget()
{
    addDockWidget(Qt::LeftDockWidgetArea, menuDockWidget);
    menuDockWidget->setVisible(!menuDockWidget->isVisible());
    toggleCntrackWorkspaceAction->setChecked(menuDockWidget->isVisible());
}

void AppMainWindow::toggleLogDock()
{
    addDockWidget(Qt::BottomDockWidgetArea, logDockWidget);
    logDockWidget->setVisible(!logDockWidget->isVisible());
    toggleLogDockAction->setChecked(logDockWidget->isVisible());
}

void AppMainWindow::toggleHelpDock()
{
    addDockWidget(Qt::BottomDockWidgetArea, helpDockWidget);
    helpDockWidget->setVisible(!helpDockWidget->isVisible());
    toggleHelpDockAction->setChecked(helpDockWidget->isVisible());
}

void AppMainWindow::setupMainToolBar()
{
    // @fixme: default icon size is too large
    // ui->toolBar->setIconSize(QSize(18, 18));
    // @fixme: on mac icon is not displayed unless a pixmap
    // toolbarNewAction = new QAction(awesome->icon( fa::filetexto ).pixmap(16, 16),

    toolbarNewAction = new QAction(awesome->icon( fa::filetexto ).pixmap(16, 16),
                                   tr("&new"), this);
    VERIFY(connect(toolbarNewAction, SIGNAL(triggered()), editorToolWidget,
                   SLOT(handleReset())));
    ui->toolBar->addAction(toolbarNewAction);

    toolbarSaveAction = new QAction(awesome->icon( fa::save ), tr("&save"), this);
    VERIFY(connect(toolbarSaveAction, SIGNAL(triggered()), editorToolWidget,
                   SLOT(handleSave())));
    ui->toolBar->addAction(toolbarSaveAction);

    ui->toolBar->setVisible(false);

//    QAction *displayEditorAction = new QAction(awesome->icon( fa::pencilsquare ),
//                                               "Editor", this);
//    ui->toolBar->addAction(displayEditorAction);
//    VERIFY(connect(displayEditorAction, &QAction::triggered, [this]() {
//        handleTreeMenuSelection(0);
//    }));

//    QAction *displayHistoryAction = new QAction(awesome->icon( fa::list ),
//                                                "History", this);
//    ui->toolBar->addAction(displayHistoryAction);
//    VERIFY(connect(displayHistoryAction, &QAction::triggered, [this]() {
//        handleTreeMenuSelection(1);
//    }));

//    QAction *displayDashboardAction = new QAction(awesome->icon( fa::dashboard ),
//                                                  "Dashboard", this);
//    ui->toolBar->addAction(displayDashboardAction);
//    VERIFY(connect(displayDashboardAction, &QAction::triggered, [this]() {
//        handleTreeMenuSelection(2);
//    }));

//    QAction *displayHelpAction = new QAction(awesome->icon( fa::question ),
//                                                  "Help", this);
//    ui->toolBar->addAction(displayHelpAction);
//    VERIFY(connect(displayHelpAction, &QAction::triggered, [this]() {
//        handleTreeMenuSelection(3);
//    }));
}

void AppMainWindow::addStatusBar()
{
    QColor windowColor = palette().window().color();
    QColor buttonBgColor = windowColor.lighter(0);
    QColor buttonBorderBgColor = windowColor.darker(120);
    QColor buttonPressedColor = windowColor.darker(125);

    QString styles = QString("QToolButton {"
                             "   background-color: transparent;"
                             "   border-style: outset;"
                             "   border-width: 0px;"
                             "   border-radius: 0px;"
                             "   border-color: %2;"
                             "   padding: 3px;"
                             "} \n"
                             ""
                             "QToolButton:checked, QToolButton:pressed {"
                             "   background-color: %3;"
                             "   border-style: inset;"
                             "}")
                     .arg(buttonBgColor.name())
                     .arg(buttonBorderBgColor.name())
                     .arg(buttonPressedColor.name());

    QToolButton *log = new QToolButton(this);
    log->setText("");
    log->setCheckable(true);
    log->setDefaultAction(toggleLogDockAction);
    log->setStyleSheet(styles);
    statusBar()->insertWidget(0, log);

    QToolButton *help = new QToolButton(this);
    help->setText("");
    help->setCheckable(true);
    help->setDefaultAction(toggleHelpDockAction);
    help->setStyleSheet(styles);
    statusBar()->insertWidget(1, help);
}

void AppMainWindow::retranslateUi()
{
    setWindowTitle(QApplication::translate("AppMainWindow", "MarkdownOrganizer",
                                           0));
}

void AppMainWindow::setupComponents()
{
    projectDockWidget = new ProjectDockWidget();
    projectDockWidget->dockData.area = (int) Qt::LeftDockWidgetArea;
//    projectDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    projectDockWidget->setVisible(true);
    addDockWidget((Qt::DockWidgetArea)projectDockWidget->dockData.area,
                  projectDockWidget);

    previewDockWidget = new PreviewDockWidget();
    previewDockWidget->dockData.area = (int) Qt::RightDockWidgetArea;
//    projectDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    previewDockWidget->setVisible(true);
    addDockWidget((Qt::DockWidgetArea)previewDockWidget->dockData.area,
                  previewDockWidget);

    menuDockWidget = new MenuDockWidget();
//    menuDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea);
//    menuDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);

    logDockWidget = new LogDockWidget();
//    logDockWidget->setAllowedAreas(Qt::BottomDockWidgetArea);
//    logDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);

    helpDockWidget = new HelpDockWidget();
//    helpDockWidget->setAllowedAreas(Qt::BottomDockWidgetArea);
//    helpDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);

    dashboardToolWidget = new DashboardToolWidget();
    editorToolWidget = new EditorToolWidget();
    historyToolWidget = new HistoryToolWidget();
    helpToolWidget = new HelpToolWidget();

    stackedLayout = new QStackedLayout;
    stackedLayout->addWidget(editorToolWidget);
    stackedLayout->addWidget(historyToolWidget);
    stackedLayout->addWidget(dashboardToolWidget);
    stackedLayout->addWidget(helpToolWidget);
    stackedLayout->setCurrentIndex(0);

    ui->centralwidget->setLayout(stackedLayout);
    this->setUnifiedTitleAndToolBarOnMac(false);
}

void AppMainWindow::setupSlots()
{
    VERIFY(connect(projectDockWidget, SIGNAL(fileSelected(const QString &)),
                   editorToolWidget, SLOT(loadFile(const QString &))));
    VERIFY(connect(projectDockWidget, SIGNAL(fileSelected(const QString &)),
                   this, SLOT(viewEditor())));
    VERIFY(connect(editorToolWidget, SIGNAL(htmlUpdated(const QString &)),
                   previewDockWidget, SLOT(updatePreview(const QString &))));
    VERIFY(connect(projectDockWidget, SIGNAL(projectChanged(const QString &)),
                   editorToolWidget, SLOT(projectChanged(const QString &))));
    VERIFY(connect(LOG_MANAGER, SIGNAL(messageLogged(const QString &)),
                   logDockWidget, SLOT(handleMessage(const QString &))));
}

void AppMainWindow::showAboutDialog()
{
    aboutDialog = new AboutDialog(this);
    aboutDialog->exec();
}

void AppMainWindow::showHelpWindow()
{
    helpWindow = new HelpWindow(this);
    helpWindow->show();
}

void AppMainWindow::showProjectDialog()
{
    projectDialog = new ProjectDialog(this);
    projectDialog->exec();
}

void AppMainWindow::showSettingsDialog()
{
    settingsDialog = new SettingsDialog(this);
    settingsDialog->exec();
}

void AppMainWindow::openWebBrowser()
{
    QObject *pObject = sender();
    QString name = pObject->objectName();
    QString url = "http://www.google.com";

    if (name == "viewJeffSmithDevWebsiteAction") {
        url = "http://www.JeffSmithDev.com";
    } else if (name == "viewGenomiusWebsiteAction") {
        url = "http://www.genomius.com";
    }

    QDesktopServices::openUrl(QUrl(url));
}

void AppMainWindow::handleTreeMenuSelection()
{
    stackedLayout->setCurrentIndex(
        menuDockWidget->getMenuTree()->currentIndex().row());
}

void AppMainWindow::handleTreeMenuSelection(int index)
{
    stackedLayout->setCurrentIndex(index);
}

void AppMainWindow::viewDashboard()
{
    stackedLayout->setCurrentIndex(AppConstants::DASHBOARD_TOOL);
}

void AppMainWindow::viewEditor()
{
    stackedLayout->setCurrentIndex(AppConstants::EDITOR_TOOL);
}

void AppMainWindow::viewHistory()
{
    stackedLayout->setCurrentIndex(AppConstants::HISTORY_TOOL);
}

void AppMainWindow::launchMainApp()
{
    QString path = QCoreApplication::applicationDirPath();
    path.append("MDOWidget");

    QProcess process;
    process.startDetached(path, QStringList());
}

void AppMainWindow::readUISettings()
{
    if (SETTINGS_MANAGER->getInt("Gui/x") > 0) {
        int x = SETTINGS_MANAGER->getInt("Gui/x");
        int y = SETTINGS_MANAGER->getInt("Gui/y");
        int height = SETTINGS_MANAGER->getInt("Gui/height");
        int width = SETTINGS_MANAGER->getInt("Gui/width");
        setGeometry(x, y, width, height);
    } else {
        QRect rec = QApplication::desktop()->screenGeometry();
        int height = rec.height();
        int width = rec.width();
        int windowHeight = height * .8;
        int windowWidth = width * .8;
        setGeometry(width / 2 - windowWidth / 2,
                    height / 2 - windowHeight / 2, windowWidth,
                    windowHeight);
    }
}

void AppMainWindow::writeUISettings()
{
    SETTINGS_MANAGER->setSetting("Gui/x", x());
    SETTINGS_MANAGER->setSetting("Gui/y", y());
    SETTINGS_MANAGER->setSetting("Gui/height", height());
    SETTINGS_MANAGER->setSetting("Gui/width", width());
}

void AppMainWindow::closeEvent(QCloseEvent *event)
{
    writeUISettings();
}

void AppMainWindow::showError(const QSqlError &err)
{
    QMessageBox::critical(this, "Unable to initialize Database",
                          "Error initializing database: " + err.text());
}
