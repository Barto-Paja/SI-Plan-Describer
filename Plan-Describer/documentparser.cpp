#include "documentparser.hpp"

DocumentParser::DocumentParser(QObject *parent) : QObject(parent)
{

}

QByteArray DocumentParser::generateXML(documentCoreSave &documentData)
{
    QByteArray ba;
    QXmlStreamWriter writer(&ba);

    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("DOCUMENT_EXPORT");

        writer.writeStartElement("DATA_ROZPOCZECIA");
            writer.writeCharacters(QString::number(documentData.dateStart.year()));
        writer.writeEndElement();
        writer.writeStartElement("IMIE_I_NAZWISKO");
            writer.writeCharacters(documentData.studentName);
        writer.writeEndElement();
        writer.writeStartElement("TERAPEUTA");
            writer.writeCharacters(documentData.therapistName);
        writer.writeEndElement();

        writer.writeStartElement("CELE");

        for(int i = 0; i < documentData.targets.count(); ++i)
        {
            writer.writeStartElement("CEL");
                writer.writeCharacters(documentData.targets[i]);
            writer.writeEndElement();
        }

        writer.writeEndElement();
    writer.writeEndElement();
    writer.writeEndDocument();

    return ba;
}

bool DocumentParser::readXML(QFile &file, documentCoreSave &documentData)
{
    QXmlStreamReader reader(&file);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }

    while (!reader.atEnd() && !reader.hasError() ) {
        QXmlStreamReader::TokenType token = reader.readNext();

        if(token == QXmlStreamReader::StartDocument)
        {
            continue;
        }

        if(token == QXmlStreamReader::StartElement)
        {
            if(reader.name() == "DOCUMENT_EXPORT")
            {
                continue;
            }
            else if (reader.name() == "DATA_ROZPOCZECIA")
            {
                documentData.dateStart = QDate::fromString(QString::number(reader.readElementText().toInt()),"yyyy");
            }
            else if (reader.name() == "IMIE_I_NAZWISKO")
            {
                documentData.studentName = reader.readElementText();
            }
            else if (reader.name() == "TERAPEUTA")
            {
                documentData.therapistName = reader.readElementText();
            }
            else if (reader.name() == "CELE")
            {
                continue;
            }
            else if (reader.name() == "CEL")
            {
                documentData.targets.append(reader.readElementText());
                continue;
            }
        }

    }

    if(reader.hasError())
    {
        return false;
    }

    reader.clear();
    file.close();

    return true;

}
