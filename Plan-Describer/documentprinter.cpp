#include "documentprinter.hpp"

#include <QPainter>
#include <QDebug>
#include <QPageSize>
#include <QAbstractTextDocumentLayout>
#include <QTextTable>

DocumentPrinter::DocumentPrinter(QObject *parent) : QObject(parent)
{
    _printer.setResolution(QPrinter::HighResolution);

    QPageSize pageSize(QPageSize::A4);
    _printer.setPageSize(pageSize);

    QPagedPaintDevice::Margins margins;
    margins.top = 11.5;
    margins.left = 12.6;
    margins.right = 11.5;
    margins.bottom = 11.8;
    _printer.setMargins (margins);

    //_printer.setFullPage(true);
    _printer.setOutputFileName("output.pdf");
    _printer.setOutputFormat(QPrinter::PdfFormat);
}

bool DocumentPrinter::printFile(QString file_name, documentTemplate &file_theme)
{
    QTextDocument docP;
    docP.setHtml(file_theme.coreTargetText);
    qDebug() << docP.toRawText();

    QTextDocument doc;
//        doc.setDefaultStyleSheet("p {"
//                                 "      font-family: Calibri, \"Times New Roma\", sans-serif;"
//                                 "      font-size: 5pt; "
//                                 "   } ");


        QFont font;
        font.setPointSize(5);
        //font.setPixelSize(6);
        font.setStyleHint(QFont::AnyStyle,QFont::PreferDevice);
        font.setFamily("Roboto");
        font.setLetterSpacing(QFont::PercentageSpacing,100);
        doc.setDefaultFont(font);
        doc.setPageSize(_printer.pageSizeMM()); // This is necessary if you want to hide the page number

        QTextCursor cursor(&doc);
        QTextBlockFormat block_format_title;
        block_format_title.setAlignment(Qt::AlignCenter);
        cursor.insertBlock(block_format_title);
        cursor.insertHtml(QString("<p><b>%1</b></p><br>").arg(file_theme.title));
        QTextBlockFormat block_format;
        block_format.setAlignment(Qt::AlignLeft);
        cursor.insertBlock(block_format);


        QTextCharFormat char_format;
        char_format.setFontPointSize(4.5);

//        QFont font_2;
//        font_2.setPointSize(4);
//        font_2.setFamily("Calibri");
//        //cursor.setCharFormat(char_format);
//        cursor.insertHtml("<br><br>");
//        //cursor.insertText("Inny text",char_format);
//        cursor.charFormat().setFont(font_2);
        cursor.insertHtml(QString("<p><b>Imię i nazwisko:</b> %1<br>").arg(file_theme.childName));
        cursor.insertHtml(QString("<p><b>Terapeuta prowadzący:</b> %1<br>").arg(file_theme.therapistName));
        cursor.insertHtml("<br>");
        cursor.insertHtml(QString("<p><b>Cel główny:</b> "
                                  "stymulacja rozwoju sensomotorycznego w celu poprawy funkcjonowania"
                                  " Centralnego Układu Nerwowego poprzez dostarczanie właściwych "
                                  "bodźców sensorycznych. </p><br><br>"));


        QTextTableFormat table_format;
        table_format.setCellPadding(2);
        table_format.setCellSpacing(-0.5);
        table_format.setMargin(0);
        table_format.setBorderBrush(QBrush(Qt::SolidPattern));
        table_format.setWidth(_printer.pageSizeMM().width()-12.6-11.5);
        table_format.setBorder(0.5);



        table_format.setHeaderRowCount(1);


        QTextTable *table = cursor.insertTable(2, 2);
        table->setFormat(table_format);



        table->cellAt(0, 0).firstCursorPosition().insertHtml("<b>Cel</b>");

        table->cellAt(0, 1).firstCursorPosition().insertHtml("Metody i środki realizacji");

    doc.print(&_printer);
}

