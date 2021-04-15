#include "DataBuilder.h"
#include <QXmlStreamReader>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>
#include <QJsonObject>

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

Nodes parseJSONObject(const QJsonObject& jsonObject, NodePtr parent = nullptr)
{
   qDebug() << "parseJSONObject";
    Nodes nodes;
    for(const auto& value : jsonObject)
    {
       if (value.isObject())
       {
          parseJSONObject(value.toObject());
       }
       else if(value.isString())
       {
          qDebug() << value.toString();
       }
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

NodePtr DataBuilder::CreateJSONTree(QStringView fileName)
{
   try
   {
       QFile jsonFile{fileName.toString()};
       jsonFile.open(QIODevice::ReadOnly | QIODevice::Text);
       QString value = jsonFile.readAll();
       auto jsonObject = QJsonDocument::fromJson(value.toUtf8()).object();
       parseJSONObject(jsonObject);
//       auto root = NodePtr::create();
//       const auto result = parseXMLElement(xmlReader, root);
//       root->AppendChild(result[0]);
       return nullptr;
   }
   catch(...)
   {
       return nullptr;
  }
}
