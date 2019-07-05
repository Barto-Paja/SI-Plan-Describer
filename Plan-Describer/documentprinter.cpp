#include "documentprinter.hpp"
#include <QTextDocument>

DocumentPrinter::DocumentPrinter(QObject *parent) : QObject(parent)
{
    loadPrinterConfiguration();
}

bool DocumentPrinter::printFile(QString file_name)
{
    QTextDocument doc;

    doc.setDefaultFont(_font);
    doc.setPageSize(_printer.pageSizeMM()); // This is necessary if you want to hide the page number

    QTextCursor cursor(&doc);

    QTextBlockFormat block_format_title;
    block_format_title.setAlignment(Qt::AlignCenter);
    cursor.insertBlock(block_format_title);
    cursor.insertHtml(QString("<p><b>%1</b></p><br>").arg(_document.title));

    QTextBlockFormat block_format;
    block_format.setAlignment(Qt::AlignLeft);
    cursor.insertBlock(block_format);

    cursor.insertHtml(QString("<p><b>Imię i nazwisko:</b> %1<br>").arg(_document.studentName));
    cursor.insertHtml(QString("<p><b>Terapeuta prowadzący:</b> %1<br>").arg(_document.therapistName));
    cursor.insertHtml("<br>");
    cursor.insertHtml(QString("<p><b>Cel główny:</b> "
                              "stymulacja rozwoju sensomotorycznego w celu poprawy funkcjonowania"
                              " Centralnego Układu Nerwowego poprzez dostarczanie właściwych "
                              "bodźców sensorycznych. </p><br><br>"));

    QTextTable *table = cursor.insertTable(_document.table.count()+1, 2);
    table->setFormat(_tableFormat);

    // ========================

    // Header

    table->cellAt(0, 0).firstCursorPosition().insertHtml("<b>Cel</b>");
    table->cellAt(0, 1).firstCursorPosition().insertHtml("<b>Metody i środki realizacji</b>");

    // Content

    for (int i = 0;i<_document.table.count();++i)
    {
        table->cellAt(i+1,0).firstCursorPosition().insertHtml(_document.table.at(i).columnTarget);

        QString content;

        for(int j = 0; j < _document.table.at(i).columnMethods.count(); ++j)
        {
            if(j>0)
            {
               content.append(QString("<br>- %1").arg(_document.table.at(i).columnMethods.at(j)));
            }
            else
            {
               content.append(QString("- %1").arg(_document.table.at(i).columnMethods.at(j)));
            }
        }

        table->cellAt(i+1,1).firstCursorPosition().insertHtml(content);
    }

    // =========================


    QTextBlockFormat block_format_;
    block_format_.setAlignment(Qt::AlignRight);

    cursor.movePosition(QTextCursor::End);

    cursor.insertBlock(block_format_);
    cursor.insertHtml("<br><br>");
    cursor.insertHtml(QString("<p><i>%1</i></p>").arg(_document.therapistSignature));

    _printer.setOutputFileName(QString("%1.pdf").arg(file_name));
    doc.print(&_printer);

    return true;
}

void DocumentPrinter::setDocument(const documentTemplate &document)
{
    _document = document;
}

void DocumentPrinter::loadPrinterConfiguration()
{
    prepareMargins();
    prepareFont();
    preapareTableFormat();

    _printer.setResolution(QPrinter::HighResolution);
    _printer.setPageSize(_pageSize);
    _printer.setMargins(_margins);

    _printer.setOutputFileName("output.pdf");
    _printer.setOutputFormat(QPrinter::PdfFormat);   
}

void DocumentPrinter::prepareMargins()
{
    _margins.top = 11.5;
    _margins.left = 12.6;
    _margins.right = 11.5;
    _margins.bottom = 11.8;
}

void DocumentPrinter::prepareFont()
{
    _font.setPointSize(5);
    _font.setStyleHint(QFont::AnyStyle,QFont::PreferDevice);
    _font.setFamily("Roboto");
    _font.setLetterSpacing(QFont::PercentageSpacing,100);
}

void DocumentPrinter::preapareTableFormat()
{
    _tableFormat.setCellPadding(2);
    _tableFormat.setCellSpacing(-0.5);
    _tableFormat.setMargin(0);
    _tableFormat.setBorderBrush(QBrush(Qt::SolidPattern));
    _tableFormat.setWidth(_printer.pageSizeMM().width()-_margins.left-_margins.right);
    _tableFormat.setBorder(0.5);
    _tableFormat.setHeaderRowCount(1);
}

void DocumentPrinter::prepareTable(QTextTable &table)
{
    // Header

    table.cellAt(0, 0).firstCursorPosition().insertHtml("<b>Cel</b>");
    table.cellAt(0, 1).firstCursorPosition().insertHtml("<b>Metody i środki realizacji</b>");

    // Content

    for (int i = 0;i<_document.table.count();++i)
    {
        table.cellAt(i+1,0).firstCursorPosition().insertHtml(_document.table.at(i).columnTarget);

        QString content;

        for(int j = 0; j < _document.table.at(i).columnMethods.count(); ++j)
        {
            if(j>0)
            {
               content.append(QString("\n- %1").arg(_document.table.at(i).columnMethods.at(j)));
            }
            else
            {
               content.append(QString("- %1").arg(_document.table.at(i).columnMethods.at(j)));
            }
        }

        table.cellAt(i+1,1).firstCursorPosition().insertHtml(content);
    }
}

