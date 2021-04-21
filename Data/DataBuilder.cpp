#include "DataBuilder.h"
#include "Data/XMLNode.h"
#include "Data/JsonNode.h"
#include <QXmlStreamReader>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include "Data/Attribute.h"

namespace
{

Nodes parseXMLElement(QXmlStreamReader& xmlStream, NodePtr parent = nullptr)
{
    Nodes nodes;
    while(xmlStream.readNextStartElement())
    {
        NodePtr node = QSharedPointer<XMLNode>::create(parent);
        node->SetName(xmlStream.name().toString());
        Attributes attributes;
        for(const auto& attr : xmlStream.attributes())
        {
            attributes.push_back(QSharedPointer<Attribute>::create(attr.name().toString(), attr.value().toString()));
        }
        node->SetAttributes(attributes);

        xmlStream.readNext();
        if (!xmlStream.text().isNull())
        {
           qDebug() << xmlStream.text();
           node->SetValue(xmlStream.text().toString());
        }

        const auto childs = parseXMLElement(xmlStream, node);
        for(const auto& child : childs)
        {
            node->AppendChild(child);
        }
        nodes.append(node);
    }
    return nodes;
}
void parseJSONObject(const QJsonObject& jsonObject, const NodePtr& parent);
void parseJSONArray(const QJsonArray& array, const NodePtr& parent)
{
   for(const auto& element : array)
   {
      NodePtr node{};
      if (element.isArray())
      {
         node = QSharedPointer<JsonNode>::create(JsonNodeType::Array, parent);
         parent->AppendChild(node);
         parseJSONArray(element.toArray(), node);
      }
      else if(element.isObject())
      {
         node = QSharedPointer<JsonNode>::create(JsonNodeType::Object, parent);
         parseJSONObject(element.toObject(), node);
      }
      else if (element.isString() || element.isBool() || element.isDouble())
      {
         parent->AddAttribute(QSharedPointer<Attribute>::create("", element.toString()));
      }

      if (node)
      {
         parent->AppendChild(node);
      }
   }
}

void parseJSONObject(const QJsonObject& jsonObject, const NodePtr& parent)
{
   Nodes nodes;
   for(const auto& key : jsonObject.keys())
   {
      NodePtr node{};
      const auto& value = jsonObject.value(key);
      if (value.isString() || value.isBool() || value.isDouble())
      {
         parent->AddAttribute(QSharedPointer<Attribute>::create(key, value.toString()));
      }
      else if(value.isObject())
      {
         node = QSharedPointer<JsonNode>::create( JsonNodeType::Object, parent);
         parseJSONObject(value.toObject(), node);
      }
      else if (value.isArray())
      {
         node = QSharedPointer<JsonNode>::create(JsonNodeType::Array, parent);
         parseJSONArray(value.toArray(), node);
      }

      if (node)
      {
         node->SetName(key);
         parent->AppendChild(node);
      }
   }
}
}


NodePtr DataBuilder::CreateXMLTree(QStringView fileName)
{
    try
    {
        QFile xmlFile{fileName.toString()};
        xmlFile.open(QIODevice::ReadOnly);
        QXmlStreamReader xmlReader{&xmlFile};

        NodePtr root = QSharedPointer<XMLNode>::create(nullptr);
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
       NodePtr root = QSharedPointer<JsonNode>::create(JsonNodeType::Object);
       parseJSONObject(jsonObject, root);
       return root;
   }
   catch(...)
   {
       return nullptr;
  }
}
