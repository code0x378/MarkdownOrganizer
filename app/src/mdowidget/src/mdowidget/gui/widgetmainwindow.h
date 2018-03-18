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

#ifndef WidgetMainWindow_H
#define WidgetMainWindow_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QHeaderView>
#include <QMenu>
#include <QMenuBar>
#include <QLabel>
#include <QList>

class Project;
class SettingsDialog;
class ProjectDialog;
class AboutDialog;

namespace Ui {
class WidgetMainWindow;
}

class WidgetMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit WidgetMainWindow(QWidget *parent = 0);
    ~WidgetMainWindow();
    static WidgetMainWindow *instance();

private slots:
    void handleSave();
    void handleReset();
    void showSettingsDialog();
    void showAboutDialog();
    void openWebBrowser();
    void trayIconClicked(QSystemTrayIcon::ActivationReason reason);
    void exitApp();
    void updatePreview();
    void changeProject();
    void launchMainApp();

    void showProjectDialog();
private:
    static WidgetMainWindow *mainWindow;
    Ui::WidgetMainWindow *ui;

    QAction *open;
    QAction *close;

    QAction *exitAction;
    QAction *aboutAction;
    QAction *settingsAction;
    QAction *projectAction;
    QAction *viewLittleDogBigUniverseWebsiteAction;
    QAction *toggleCntrackWorkspaceAction;
    QAction *toggleLogDockAction;
    QAction *toggleHelpDockAction;
    QAction *launchMainAppAction;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *toolsMenu;
    QMenu *helpMenu;
    AboutDialog *aboutDialog;
    SettingsDialog *settingsDialog;
    ProjectDialog *projectDialog;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QLabel *labelStatusMessage;

    void addSignalsAndSlots();
    void addMainMenu();
    void adddSignalsAndSlots();
    void setupTrayIcon();
    void createActions();
    void stressTest(int cnt);
    QString markdown(QString in);
    QString wrapInHTMLDoc(QString in);
    void addComponentDynamically();
    void closeEvent(QCloseEvent *event);

    bool hiddenMessageDisplayed = false;
    void selectActiveProduct();
    void displayTags();
    void displayCategories();
};

#define MAINWINDOW WidgetMainWindow::instance()->instance()

#endif // WidgetMainWindow_H
