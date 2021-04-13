#include "DataBuilder.h"
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>

namespace
{
NodePtr parseXMLElement(QXmlStreamReader& xmlStream, NodePtr parent = nullptr)
{
    qDebug() << "parseXMLElement";
    NodePtr node = NodePtr::create(parent);
    while (!xmlStream.atEnd() && !xmlStream.hasError())
    {
        auto token = xmlStream.readNext();
        if (token == QXmlStreamReader::StartDocument)
        {
            continue;
        }
        if (token == QXmlStreamReader::StartElement)
        {
            node->SetName(xmlStream.name().toString());
            Attributes attributes;
            for(const auto& attr : xmlStream.attributes())
            {
                attributes.push_back(qMakePair(attr.name().toString(),attr.value().toString()));
            }
            node->SetAttributes(attributes);
            qDebug() << node->GetName();
        }
        else if(token == QXmlStreamReader::Characters)
        {

            auto child = parseXMLElement(xmlStream, node);
            if (child && !child->GetName().isEmpty())
            {
                node->AppendChild(child);
            }
        }
    }
    qDebug() << "exit";
    return node;
}
}


NodePtr DataBuilder::CreateXMLTree(QStringView fileName)
{
    try
    {
        QFile xmlFile{fileName.toString()};
        xmlFile.open(QIODevice::ReadOnly);
        QXmlStreamReader xmlReader{&xmlFile};
        auto result = parseXMLElement(xmlReader);
        return result;
    }
    catch(...)
    {
        return nullptr;
    }
}
