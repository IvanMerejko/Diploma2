#include "JsonNode.h"
#include "Attribute.h"
#include <QVariant>
#include <QDebug>
namespace
{
   QString createRowData(const QString& value, const Attributes& attributes)
   {
      QString temp{};
      if (value.length() != 0)
      {
         temp.append(", value=").append(value);
      }
      if (!attributes.empty())
      {
         temp.append(" Attributes:");
      }

      for (const auto& attribute : attributes)
      {
         if (attribute->GetName().length() != 0)
         {
            temp.append(" ")
                .append(attribute->GetName())
                .append(" = ")
                .append(attribute->GetValue());
         }
         else
         {
            temp.append(" ")
                .append(attribute->GetValue());
         }
      }
      return temp;
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

QVariant JsonNode::GetData() const
{
    return m_name + (m_jsonNodeType == JsonNodeType::Array ? " (Array) " : "") + createRowData(m_value, m_attributes);;
}

int JsonNode::GetRow()
{
    return m_parent ? m_parent->GetChilds().indexOf(sharedFromThis()) : 1;
}

void JsonNode::SetJsonNodeType(JsonNodeType jsonNodeType)
{
   m_jsonNodeType = jsonNodeType;
}
