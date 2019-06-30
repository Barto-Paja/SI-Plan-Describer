#ifndef DOCUMENTPRINTER_HPP
#define DOCUMENTPRINTER_HPP

#include <QObject>
#include <QtPrintSupport/QPrinter>
#include <QTextFormat>
#include <QTextDocument>

struct documentTemplate
{
    QString title;
    QString childName;
    QString therapistName;
    QString coreTargetText;

};

class DocumentPrinter : public QObject
{
    Q_OBJECT

    QPrinter _printer;

public:
    explicit DocumentPrinter(QObject *parent = nullptr);

    bool printFile(QString file_name, documentTemplate &file_theme);

signals:

public slots:

private:


};

#endif // DOCUMENTPRINTER_HPP
