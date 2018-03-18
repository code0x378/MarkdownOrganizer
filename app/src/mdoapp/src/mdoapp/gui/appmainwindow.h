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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "helpwindow.h"

#include <QMainWindow>
#include <QDir>
#include <QTreeWidget>
#include <QStackedLayout>

#include <mdocore/lib/QtAwesome/QtAwesome/QtAwesome.h>
class QGridLayout;
class QMenu;
class QWidget;
class QSqlError;
class QWebEngineView;

class AboutDialog;
class SettingsDialog;
class PluginDialog;
class BrowserWindow;
class MenuDockWidget;
class ProjectDockWidget;
class PreviewDockWidget;
class LogDockWidget;
class HelpDockWidget;
class DashboardToolWidget;
class EditorToolWidget;
class HistoryToolWidget;
class HelpToolWidget;
class PluginDialog;
class ProjectDialog;
class ProjectWidget;

namespace Ui {
class AppMainWindow;
}

namespace AppConstants {
const int EDITOR_TOOL = 0;
const int HISTORY_TOOL = 1;
const int DASHBOARD_TOOL = 2;
}

class AppMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    AppMainWindow(QWidget *parent = 0);
    ~AppMainWindow();
    static AppMainWindow *instance();

private:
    static AppMainWindow *appMainWindow;
    Ui::AppMainWindow *ui;
    QAction *newAction;
    QAction *saveAction;
    QAction *toolbarNewAction;
    QAction *toolbarSaveAction;
    QAction *exitAction;
    QAction *aboutAction;
    QAction *helpAction;
    QAction *settingsAction;
    QAction *projectAction;
    QAction *viewWelcomeAction;
    QAction *viewLittleDogBigUniverseWebsiteAction;
    QAction *toggleCntrackWorkspaceAction;
    QAction *togglePreviewAction;
    QAction *toggleLogDockAction;
    QAction *toggleHelpDockAction;
    QAction *launchMainAppAction;
//    QAction *viewDsWebsiteAction;

    QMenu *fileMenu;
    QMenu *toolsMenu;
    QMenu *editMenu;
    QMenu *windowMenu;
    QMenu *helpMenu;
    QMenu *panelsMenu;
    AboutDialog *aboutDialog;
    SettingsDialog *settingsDialog;
    ProjectDialog *projectDialog;
    PluginDialog *pluginDialog;
    QWidget *mainWidget;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QWidget *sideBarWidget;
    QGridLayout *gridLayout_3;
    QTreeWidget *menuTreeWidget;
    BrowserWindow *browserWindow;
    HelpWindow *helpWindow;
    QDockWidget *workspaceDock;
    MenuDockWidget *menuDockWidget = 0;
    LogDockWidget *logDockWidget = 0;
    HelpDockWidget *helpDockWidget = 0;
    ProjectDockWidget *projectDockWidget = 0;
    PreviewDockWidget *previewDockWidget = 0;
    QStackedLayout *stackedLayout;
    DashboardToolWidget *dashboardToolWidget;
    EditorToolWidget *editorToolWidget;
    HistoryToolWidget *historyToolWidget;
    HelpToolWidget *helpToolWidget;
    ProjectWidget *projectWidget;


    void setupMainMenu();
    void setupMainToolBar();
    void addStatusBar();
    void addLayout();
    void retranslateUi();
    void setupComponents();
    void setupSlots();
    void showError(const QSqlError &err);

    QDir pluginsDir;
    QStringList pluginFileNames;
    QtAwesome *awesome;

    void readUISettings();
    void writeUISettings();
private slots:
    void closeEvent(QCloseEvent *event);
    void showAboutDialog();
    void showSettingsDialog();
    void openWebBrowser();
    void handleTreeMenuSelection();
    void toggleMenuWorkspaceWidget();
    void toggleHelpDock();
    void toggleLogDock();
    void launchMainApp();
    void handleTreeMenuSelection(int index);
    void viewDashboard();
    void viewEditor();
    void viewHistory();
    void showProjectDialog();
    void showHelpWindow();
    void togglePreviewWidget();
};

#define MAINWINDOW AppMainWindow::instance()->instance()

#endif // MAINWINDOW_H
