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

#include "helpwidget.h"
#include "ui_helpwidget.h"

#include <QFileSystemModel>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QTextStream>

#include "mdocore/util/qtutils.h"
#include "mdocore/logmanager.h"

HelpWidget::HelpWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpWidget)
{
    ui->setupUi(this);

    model = new QFileSystemModel;
    model->setRootPath("help/");
    ui->tocTreeView->setModel(model);
    ui->tocTreeView->setColumnHidden(1, true);
    ui->tocTreeView->setColumnHidden(2, true);
    ui->tocTreeView->setColumnHidden(3, true);
    ui->tocTreeView->setRootIndex(model->index("help/", 0));

    QStandardItemModel *model1 = new QStandardItemModel(0, 1, this);
    model1->setHeaderData(0, Qt::Horizontal,  tr("topics"));
    ui->tocTreeView->header()->setModel(model1);

    VERIFY(connect(ui->tocTreeView, SIGNAL(clicked(const QModelIndex &)), this,
                   SLOT(viewHelp(const QModelIndex &))));
}

HelpWidget::~HelpWidget()
{
    delete ui;
}

void HelpWidget::viewHelp(const QModelIndex index)
{
    QString filePath = model->fileInfo(index).absoluteFilePath();

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);
    QString text;
    while (!in.atEnd()) {
        text += in.readLine() + "\n";
    }
    file.close();

    ui->contentTextEdit->document()->setHtml(
        QtUtils::wrapInHTMLDoc(
            QtUtils::markdownConverter(
                QtUtils::removeFrontMatter(text))));

    LOG_INFO("Help file loaded: " + filePath);
}
