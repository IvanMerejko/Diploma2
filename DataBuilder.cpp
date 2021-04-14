#include "DataBuilder.h"
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>

namespace
{
Nodes parseXMLElement(QXmlStreamReader& xmlStream, NodePtr parent = nullptr)
{
    Nodes nodes;
    while(xmlStream.readNextStartElement())
    {
        NodePtr node = NodePtr::create(parent);
        node->SetName(xmlStream.name().toString());
        node->SetValue(xmlStream.text().toString());
        Attributes attributes;
        for(const auto& attr : xmlStream.attributes())
        {
            attributes.push_back(qMakePair(attr.name().toString(), attr.value().toString()));
        }
        node->SetAttributes(attributes);
        const auto childs = parseXMLElement(xmlStream, node);
        for(const auto& child : childs)
        {
            node->AppendChild(child);
        }
        nodes.append(node);
    }
    return nodes;
}
}


NodePtr DataBuilder::CreateXMLTree(QStringView fileName)
{
    try
    {
        QFile xmlFile{fileName.toString()};
        xmlFile.open(QIODevice::ReadOnly);
        QXmlStreamReader xmlReader{&xmlFile};

        auto root = NodePtr::create();
        const auto result = parseXMLElement(xmlReader, root);
        root->AppendChild(result[0]);
        return root;
    }
    catch(...)
    {
        return nullptr;
    }
}
