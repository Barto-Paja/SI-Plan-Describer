#include "documentprinter.hpp"

DocumentPrinter::DocumentPrinter(QObject *parent) : QObject(parent)
{
    _printer.setResolution(QPrinter::HighResolution);
    _printer.setPageSize(QPrinter::A4);
    _printer.setOrientation(QPrinter::Portrait);
    _printer.setPageMargins (15,15,15,15,QPrinter::Millimeter);
    _printer.setFullPage(false);
    _printer.setOutputFileName("output.pdf");
    _printer.setOutputFormat(QPrinter::PdfFormat);
}
