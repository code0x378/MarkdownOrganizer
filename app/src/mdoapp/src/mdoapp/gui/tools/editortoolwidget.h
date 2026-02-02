/*
* Markdown Organizer
* Copyright (C) 2016-2021 code0x378
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

#ifndef EDITORTOOLWIDGET_H
#define EDITORTOOLWIDGET_H

#include <QWidget>
class QWebEngineView;

namespace Ui {
class EditorToolWidget;
}

class EditorToolWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EditorToolWidget(QWidget *parent = 0);
    ~EditorToolWidget();

public Q_SLOTS:
    void loadFile(const QString filePath);
    void projectChanged(const QString projectName);
    void handleSave();
    void handleReset();

Q_SIGNALS:
    void htmlUpdated(QString filePath);

private Q_SLOTS:
    void insertDate();
    void formatBold();
    void formatItalic();
    void formatH1();
    void formatH2();
    void formatH3();
    void formatLink();
    void formatCode();
    void formatUl();
    void formatBlockQuote();
    void updatePreview();

private:
    Ui::EditorToolWidget *ui;
    void addSignalsAndSlots();
    QString selectProject(QString projectName);
    QString filePath;
    bool isDirty = false;
    void displaySaveWarning();
    void formatLines(QString txt);
    void displayTags();
    void displayCategories();
    void sendEmail(QString content);
};

#endif // EDITORTOOLWIDGET_H
