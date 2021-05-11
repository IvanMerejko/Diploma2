#include "DataBuilder.h"
#include "Data/XMLNode.h"
#include "Data/JsonNode.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include "Data/Attribute.h"

namespace
{

void saveXMLElement(QXmlStreamWriter& xmlWriter, const NodePtr& node)
{
   if (node->GetValue().length() == 0)
   {
      xmlWriter.writeStartElement(node->GetName());
      for(const auto& attribut : node->GetAttributes())
      {
         xmlWriter.writeAttribute(attribut->GetName(), attribut->GetValue());
      }
      for(const auto& child : node->GetChilds())
      {
         saveXMLElement(xmlWriter, child);
      }
      xmlWriter.writeEndElement();
   }
   else
   {
      xmlWriter.writeStartElement(node->GetName());
      for(const auto& attribut : node->GetAttributes())
      {
         xmlWriter.writeAttribute(attribut->GetName(), attribut->GetValue());
      }
      xmlWriter.writeCharacters(node->GetValue());
      xmlWriter.writeEndElement();
   }

}

Nodes parseXMLElement(QXmlStreamReader& xmlStream, const TreeModelPtr& model, NodePtr parent = nullptr)
{
    Nodes nodes;
    if (xmlStream.tokenType() == QXmlStreamReader::EndElement)
    {
       xmlStream.readNext();
       return nodes;
    }

    while(xmlStream.readNextStartElement())
    {
        NodePtr node = QSharedPointer<XMLNode>::create(parent);
        QObject::connect(node.get(), &BaseNode::onDataChanged, model.get(), &TreeModel::onDataChanged);
        node->SetName(xmlStream.name().toString());
        Attributes attributes;
        for(const auto& attr : xmlStream.attributes())
        {
           const auto attribute = QSharedPointer<Attribute>::create(attr.name().toString(), attr.value().toString());
           QObject::connect(attribute.get(), &Attribute::onDataChanged, model.get(), &TreeModel::onDataChanged);
           attributes.push_back(attribute);
        }
        node->SetAttributes(attributes);

        xmlStream.readNext();
        if (!xmlStream.text().isNull())
        {
           node->SetValue(xmlStream.text().toString());
        }

        const auto childs = parseXMLElement(xmlStream, model, node);
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


NodePtr DataBuilder::CreateXMLTree(QStringView fileName, const TreeModelPtr& model)
{
    try
    {
        QFile xmlFile{fileName.toString()};
        xmlFile.open(QIODevice::ReadOnly);
        QXmlStreamReader xmlReader{&xmlFile};

        NodePtr root = QSharedPointer<XMLNode>::create(nullptr);
        const auto result = parseXMLElement(xmlReader, model, root);
        if (result.length() != 1)
        {
           return nullptr;
        }
        root->AppendChild(result[0]);
        return root;
    }
    catch(...)
    {
        return nullptr;
   }
}

NodePtr DataBuilder::CreateJSONTree(QStringView fileName, const TreeModelPtr& tree)
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

void DataBuilder::SaveXMLTree(const NodePtr& root, const QString& fileName)
{
   if (!root)
   {
      return;
   }
   qDebug() << fileName;
   QFile file(fileName);
   file.open(QIODevice::WriteOnly);
   QXmlStreamWriter xmlWriter(&file);
   xmlWriter.setAutoFormatting(true);
   xmlWriter.writeStartDocument();
   saveXMLElement(xmlWriter, root->GetChilds()[0]);
   xmlWriter.writeEndDocument();
   file.close();
}
