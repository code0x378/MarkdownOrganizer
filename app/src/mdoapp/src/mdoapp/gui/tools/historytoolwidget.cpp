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

#include "historytoolwidget.h"
#include "ui_historytoolwidget.h"

#include <QSql>
#include <QSqlRelationalTableModel>
#include <QMessageBox>
#include <QHeaderView>
#include <QDataWidgetMapper>

#include "mdocore/logmanager.h"

HistoryToolWidget::HistoryToolWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryToolWidget)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::database();

    //    QSqlRelationalTableModel *model = new QSqlRelationalTableModel(ui->historyTableView);
    //    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //    model->setTable("projects");
    //    model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, tr("name"));
    //    model->setHeaderData(model->fieldIndex("description"), Qt::Horizontal, tr("description"));
    //    model->setHeaderData(model->fieldIndex("workingDirectory"), Qt::Horizontal, tr("workingDirectory"));
    //    model->setHeaderData(model->fieldIndex("postSaveCommand"), Qt::Horizontal, tr("postSaveCommand"));

    QSqlRelationalTableModel *model = new QSqlRelationalTableModel(
        ui->historyTableView);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("history");
    model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, tr("name"));
    model->setHeaderData(model->fieldIndex("date"), Qt::Horizontal, tr("date"));
    model->setHeaderData(model->fieldIndex("author"), Qt::Horizontal, tr("author"));
    model->setHeaderData(model->fieldIndex("tags"), Qt::Horizontal, tr("tags"));
    model->setHeaderData(model->fieldIndex("categories"), Qt::Horizontal,
                         tr("categories"));

    if (!model->select()) {
        showError(model->lastError());
        return;
    }

    ui->historyTableView->setModel(model);
    ui->historyTableView->setColumnHidden(model->fieldIndex("id"), true);
    ui->historyTableView->setColumnHidden(model->fieldIndex("content"), true);
    ui->historyTableView->setColumnHidden(model->fieldIndex("website"), true);
    ui->historyTableView->setColumnHidden(model->fieldIndex("filePath"), true);
    ui->historyTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->historyTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->historyTableView->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);

    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->addMapping(ui->textEdit, model->fieldIndex("content"));

    connect(ui->historyTableView->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
            mapper, SLOT(setCurrentModelIndex(QModelIndex)));

    LOG_DEBUG("History tool loaded");
}

HistoryToolWidget::~HistoryToolWidget()
{
    delete ui;
}

void HistoryToolWidget::showError(const QSqlError &err)
{
    QMessageBox::critical(this, "Unable to initialize Database",
                          "Error initializing database: " + err.text());
}
