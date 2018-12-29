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

#include "qtutils.h"

#include <QThread>
#include <QTreeWidgetItem>

#include "mdocore/lib/hoedown/src/html.h"
#include "mdocore/lib/hoedown/src/buffer.h"
#include "mdocore/logmanager.h"

namespace QtUtils {
template<>
QString toQString<std::string>(const std::string &value)
{
    //static QTextCodec *LOCALECODEC = QTextCodec::codecForLocale();
    return QString::fromUtf8(value.c_str(), value.size());
}

template<>
QString toQString<std::wstring>(const std::wstring &value)
{
    return  QString((const QChar *)value.c_str(), value.length());
}

std::string toStdString(const QString &value)
{
    QByteArray sUtf8 = value.toUtf8();
    return std::string(sUtf8.constData(), sUtf8.length());
}

std::string toStdStringSafe(const QString &value)
{
#ifdef Q_OS_WIN
    QByteArray sUtf8 = value.toLocal8Bit();
#else
    QByteArray sUtf8 = value.toUtf8();
#endif
    return std::string(sUtf8.constData(), sUtf8.length());
}

QString removeFrontMatter(QString text)
{
    QStringList markers;
    markers << "+++" << "---" << "===";

    for (int i = 0; i < markers.size(); ++i) {
        if (text.indexOf(markers.at(i)) == -1)
            continue;
        text.remove(text.indexOf(markers.at(i)), text.lastIndexOf(markers.at(i)) + 3);
    }
    return text;
}


QString markdownConverter(QString in)
{

    if (in != "") {
        QByteArray qba = in.toUtf8();
        const char *txt = qba.constData();
        if (NULL == txt) LOG_INFO("txt was null!");
        if (0 < qba.size()) {
            hoedown_renderer *renderer = hoedown_html_renderer_new((hoedown_html_flags)NULL,
                                                                   16);
            unsigned int extensions = HOEDOWN_EXT_BLOCK | HOEDOWN_EXT_SPAN;
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
            LOG_WARNING("No text provided - Nothing to render with markdow");
    }
    return "";
}

QString wrapInHTMLDoc(QString in, QString css)
{
    QString result(in
                   .prepend("<html>\n <head>\n <meta charset=\"utf-8\">\n <style>" + css +
                            "</style>\n </head>\n <body>\n")
                   .append("\n </body>\n</html>"));
    return result;
}
}
