#include "documentparser.hpp"

DocumentParser::DocumentParser(QObject *parent) : QObject(parent)
{

}

QByteArray DocumentParser::generateXML(documentCoreSave &documentData)
{
    QByteArray ba;
    QXmlStreamWriter writer(&ba);

    writer.setAutoFormatting(false);
    writer.writeStartDocument();
    writer.writeStartElement("DOCUMENT_EXPORT");

        writer.writeStartElement("DATY");
            writer.writeStartElement("DATA_ROZPOCZECIA");
                writer.writeCharacters(QString::number(documentData.dateStart.year()));
            writer.writeEndElement();
            writer.writeStartElement("DATA_ZAKONCZENIA");
                writer.writeCharacters(QString::number(documentData.dateEnd.year()));
            writer.writeEndElement();
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
