#ifndef DOCUMENTPRINTER_HPP
#define DOCUMENTPRINTER_HPP

#include <QObject>
#include <QtPrintSupport/QPrinter>
#include <QTextFormat>
#include <QTextDocument>

struct documentTemplate
{

};

class DocumentPrinter : public QObject
{
    Q_OBJECT

    QPrinter _printer;

public:
    explicit DocumentPrinter(QObject *parent = nullptr);

signals:

public slots:
};

#endif // DOCUMENTPRINTER_HPP
