#include "JsonNode.h"
#include <QVariant>
#include <QDebug>
namespace
{
   QString jsonNodeTypeToString(JsonNodeType jsonNodeType)
   {
      switch(jsonNodeType)
      {
         case JsonNodeType::Undefind:
            return "Undefind";
         case JsonNodeType::Object:
            return "Object";
         case JsonNodeType::Value:
            return "Value";
         case JsonNodeType::Array:
            return "Array";
      }
   }
}

JsonNode::JsonNode(JsonNodeType jsonNodeType, const NodePtr& parentItem)
   : BaseNode(parentItem)
{
   m_jsonNodeType = jsonNodeType;
}

int JsonNode::GetColumnCount() const noexcept
{
    return 2;
}

QVariant JsonNode::GetData(int) const
{
    return m_name + (m_jsonNodeType == JsonNodeType::Array ? " (Array) " : "");
}

int JsonNode::GetRow()
{
    return m_parent ? m_parent->GetChilds().indexOf(sharedFromThis()) : 1;
}

void JsonNode::SetJsonNodeType(JsonNodeType jsonNodeType)
{
   m_jsonNodeType = jsonNodeType;
}
