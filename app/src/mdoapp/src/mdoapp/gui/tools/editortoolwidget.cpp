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

#include "editortoolwidget.h"
#include "ui_editortoolwidget.h"

#include <QMessageBox>
#include <QTextCursor>
#include <QTextBlock>
#include <QTextDocumentFragment>
#include <QCheckBox>
#include <QSpacerItem>
#include <QWebEngineView>
#include <QWebEngineSettings>

#include "SmtpMime"

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

EditorToolWidget::EditorToolWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorToolWidget)
{
    ui->setupUi(this);

    ui->lineEditAuthor->setText("Jeff Smith");
    ui->lineEditDate->setText(QDate::currentDate().toString("yyyy-MM-dd"));
    addSignalsAndSlots();
    projectChanged(APP->getActiveProject()->getName());
    displayTags();
    displayCategories();
    ui->lineEditTitle->setFocus();

    LOG_DEBUG("Editor tool loaded");
}

EditorToolWidget::~EditorToolWidget()
{
    delete ui;
}

void EditorToolWidget::displayTags()
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

void EditorToolWidget::displayCategories()
{
    QList<QCheckBox *>  checkboxes =
        ui->groupBoxCategories->findChildren<QCheckBox *>();
    for (QCheckBox *chk : checkboxes)
        delete chk;

    int row = 1;
    int col = 1;
    QStringList categories = APP->getActiveProject()->getCategories().split(",");
    QVBoxLayout *catLayout = new QVBoxLayout();
    delete ui->groupBoxCategories->layout();
    ui->groupBoxCategories->setLayout (catLayout);
    foreach (QString category, categories) {
        catLayout->addWidget(new QCheckBox(category));
    }
    catLayout->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Minimum,
                                             QSizePolicy::Expanding));
}


void EditorToolWidget::loadFile(const QString filePath)
{
    if (isDirty) {
        displaySaveWarning();
    }

    ui->editorTabWidget->setHidden(true);

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

    this->filePath = filePath;
    ui->mdPlainTextEdit->document()->setPlainText(text);
    isDirty = false;

    LOG_INFO("Resource file loaded: " + filePath);
}

void EditorToolWidget::projectChanged(const QString projectName)
{
    displayTags();
    displayCategories();
//    ui->lineEditWebsite->setVisible(false);
    ui->tocPlainTextEdit->setVisible(false);
    ui->tocLabel->setVisible(false);
    ui->editTabWidget->setVisible(true);

    ProjectType p = APP->getActiveProject()->getType();
    switch (p) {
    case ProjectType::Link:
//        ui->lineEditWebsite->setVisible(true);
        ui->editTabWidget->setVisible(false);
        break;
    case ProjectType::Help:
        ui->tocLabel->setVisible(true);
        ui->tocPlainTextEdit->setVisible(true);
        break;
    default:
        break;
    }
}

void EditorToolWidget::addSignalsAndSlots()
{
    VERIFY(connect(ui->buttonReset, SIGNAL(released()), this, SLOT(handleReset())));
    VERIFY(connect(ui->buttonSave, SIGNAL(released()), this, SLOT(handleSave())));
    VERIFY(connect(ui->mdPlainTextEdit, SIGNAL(textChanged()), this,
                   SLOT(updatePreview())));
    VERIFY(connect(ui->mdPlainTextEdit, SIGNAL(textChanged()), this,
                   SLOT(updatePreview())));

    VERIFY(connect(ui->boldToolButton, SIGNAL(released()), this,
                   SLOT(formatBold())));
    VERIFY(connect(ui->italicToolButton, SIGNAL(released()), this,
                   SLOT(formatItalic())));
    VERIFY(connect(ui->h1ToolButton, SIGNAL(released()), this, SLOT(formatH1())));
    VERIFY(connect(ui->h2ToolButton, SIGNAL(released()), this, SLOT(formatH2())));
    VERIFY(connect(ui->h3ToolButton, SIGNAL(released()), this, SLOT(formatH3())));
    VERIFY(connect(ui->linkToolButton, SIGNAL(released()), this,
                   SLOT(formatLink())));
    VERIFY(connect(ui->codeToolButton, SIGNAL(released()), this,
                   SLOT(formatCode())));
    VERIFY(connect(ui->ulToolButton, SIGNAL(released()), this, SLOT(formatUl())));
    VERIFY(connect(ui->blockquoteToolButton, SIGNAL(released()), this,
                   SLOT(formatBlockQuote())));
}

void EditorToolWidget::formatBold()
{
    if (!ui->mdPlainTextEdit->textCursor().hasSelection())
        return;
    ui->mdPlainTextEdit->textCursor().insertText(QString("**%1**").arg(
                                                     ui->mdPlainTextEdit->textCursor().selectedText()));
}

void EditorToolWidget::formatItalic()
{
    if (!ui->mdPlainTextEdit->textCursor().hasSelection())
        return;
    ui->mdPlainTextEdit->textCursor().insertText(QString("*%1*").arg(
                                                     ui->mdPlainTextEdit->textCursor().selectedText()));
}

void EditorToolWidget::formatH1()
{
    if (!ui->mdPlainTextEdit->textCursor().hasSelection())
        return;
    ui->mdPlainTextEdit->textCursor().insertText(QString("# %1").arg(
                                                     ui->mdPlainTextEdit->textCursor().selectedText()));
}

void EditorToolWidget::formatH2()
{
    if (!ui->mdPlainTextEdit->textCursor().hasSelection())
        return;
    ui->mdPlainTextEdit->textCursor().insertText(QString("## %1").arg(
                                                     ui->mdPlainTextEdit->textCursor().selectedText()));
}

void EditorToolWidget::formatH3()
{
    if (!ui->mdPlainTextEdit->textCursor().hasSelection())
        return;
    ui->mdPlainTextEdit->textCursor().insertText(QString("### %1").arg(
                                                     ui->mdPlainTextEdit->textCursor().selectedText()));
}

void EditorToolWidget::formatLink()
{
    if (!ui->mdPlainTextEdit->textCursor().hasSelection())
        return;
    ui->mdPlainTextEdit->textCursor().insertText(QString("[%1](http://)").arg(
                                                     ui->mdPlainTextEdit->textCursor().selectedText()));
}

void EditorToolWidget::formatCode()
{
    if (!ui->mdPlainTextEdit->textCursor().hasSelection())
        return;
    ui->mdPlainTextEdit->textCursor().insertText(QString("```\n%1\n```").arg(
                                                     ui->mdPlainTextEdit->textCursor().selectedText()));
}

void EditorToolWidget::formatUl()
{
    if (!ui->mdPlainTextEdit->textCursor().hasSelection())
        return;
    formatLines("* ");
}

void EditorToolWidget::formatBlockQuote()
{
    if (!ui->mdPlainTextEdit->textCursor().hasSelection())
        return;
    formatLines("> ");
}

void EditorToolWidget::formatLines(QString txt)
{
    QTextCursor cursor = ui->mdPlainTextEdit->textCursor();

    int start = cursor.selectionStart();
    int end = cursor.selectionEnd();

    cursor.setPosition(end, QTextCursor::KeepAnchor);
    QTextBlock endBlock = cursor.block();
    cursor.setPosition(start, QTextCursor::KeepAnchor);
    QTextBlock block = cursor.block();

    for (; block.isValid() && !(endBlock < block); block = block.next()) {
        if (!block.isValid())
            continue;

        cursor.movePosition(QTextCursor::StartOfLine);
        cursor.clearSelection();
        cursor.insertText(txt);
        cursor.movePosition(QTextCursor::NextBlock);
    }
}

void EditorToolWidget::handleSave()
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
    resource->setImages(ui->lineEditImages->text());
    resource->setThumbnail(ui->lineEditThumbnail->text());
    resource->setContent(ui->mdPlainTextEdit->document()->toPlainText());
    resource->setFilePath(filePath);
    resource->setTags(tags.replace("&", ""));
    resource->setCategories(categories.replace("&", ""));
    resource->setDraft(ui->draftCheckBox->isChecked());

    foreach (IPlugin *plugin,  PLUGIN_MANAGER->getPluginList()) {
        if (APP->getActiveProject()->getPlugins().contains(plugin->getName())) {
            plugin->save(*APP->getActiveProject(), *resource);
        }
    }

    if (ui->emailCheckBox->isChecked()) {
        sendEmail(resource->getContent());
    }

    handleReset();
    isDirty = false;
    LOG_INFO("Resource file saved: " + resource->getFilePath());
}

void EditorToolWidget::handleReset()
{
    ui->editorTabWidget->setHidden(false);

    filePath = "";
    ui->lineEditAuthor->setText("Jeff Smith");
    ui->lineEditDate->setText(QDate::currentDate().toString("yyyy-MM-dd"));
    ui->lineEditTitle->setText("");
    ui->lineEditWebsite->setText("");
    ui->mdPlainTextEdit->setPlainText("");


    QList<QCheckBox *> checkboxes = ui->groupBoxTags->findChildren<QCheckBox *>();
    for (QCheckBox *chk : checkboxes) {
        chk->setChecked(false);
    }

    checkboxes = ui->groupBoxCategories->findChildren<QCheckBox *>();
    for (QCheckBox *chk : checkboxes) {
        chk->setChecked(false);
    }
    LOG_DEBUG("Editor reset");
}


void EditorToolWidget::updatePreview()
{
    QTime t;
    t.start();
    QString plainText;
    plainText  = ui->mdPlainTextEdit->toPlainText();
    plainText = QtUtils::removeFrontMatter(plainText);
    QString htmlText = QtUtils::markdownConverter(plainText);

    emit htmlUpdated(htmlText);

    //    //view->setHtml(QtUtils::wrapInHTMLDoc(htmlText, this->css));
        isDirty = true;

        LOG_DEBUG(QString("Preview rendered in: %1 ms").arg(t.elapsed()));
}


void EditorToolWidget::displaySaveWarning()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Save Changes?",
                                  "The content was modified.  Do you want to save the changes?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        handleSave();
        LOG_INFO("Saved dirty data");
    }
}

void EditorToolWidget::sendEmail(QString content)
{

    if (SETTINGS_MANAGER->getString("Email/Server", "") != "") {
        SmtpClient smtp(SETTINGS_MANAGER->getString("Email/Server", ""),
                        SETTINGS_MANAGER->getInt("Email/Port", 0), SmtpClient::SslConnection);
        smtp.setUser(SETTINGS_MANAGER->getString("Email/User", ""));
        smtp.setPassword(SETTINGS_MANAGER->getString("Email/Password", ""));

        MimeMessage message;
        message.setSender(new EmailAddress(APP->getActiveProject()->getEmailFrom()));
        message.addRecipient(new EmailAddress(APP->getActiveProject()->getEmailTo()));
        message.setSubject(QString("Markdown Doc from %1").arg(APP->getActiveProject()->getName()));

        MimeText text;
        text.setText(content);
        message.addPart(&text);

        smtp.connectToHost();
        smtp.login();
        smtp.sendMail(message);
        smtp.quit();
    }
}
