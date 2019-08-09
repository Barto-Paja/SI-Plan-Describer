#ifndef DOCUMENTPRINTER_HPP
#define DOCUMENTPRINTER_HPP

#include <QObject>
#include <QtPrintSupport/QPrinter>
#include <QTextFormat>
#include <QTextDocument>

#include <QPainter>
#include <QDebug>
#include <QPageSize>
#include <QAbstractTextDocumentLayout>
#include <QTextTable>

struct table
{
    QString columnTarget;
    QList<QString> columnMethods;
};

struct documentTemplate
{
    QString title;
    QString studentName;
    QString therapistName;
    QString therapistSignature;
    QString note;

    QList<QString> headers;
    QList<QList<QString>> rows;

    QList<table> table;
};

class DocumentPrinter : public QObject
{
    Q_OBJECT

    QPrinter _printer;
    QPagedPaintDevice::Margins _margins;
    QPageSize _pageSize = QPageSize(QPageSize::A4);

    QFont _font;
    QTextTableFormat _tableFormat;


public:
    explicit DocumentPrinter(QObject *parent = nullptr);

    bool printFile(QString file_name);

    void setDocument(const documentTemplate &document);

signals:

public slots:

private:

    documentTemplate _document;

    void loadPrinterConfiguration();
    void prepareMargins();
    void prepareFont();
    void preapareTableFormat();

    void prepareTable(QTextTable &table);
};

#endif // DOCUMENTPRINTER_HPP
