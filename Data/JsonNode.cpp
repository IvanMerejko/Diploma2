#include "JsonNode.h"
#include <QVariant>

JsonNode::JsonNode(JsonNodeType jsonNodeType, const NodePtr& parentItem)
   : BaseNode(parentItem)
{
   m_jsonNodeType = jsonNodeType;
}

int JsonNode::GetColumnCount() const noexcept
{
    return 1;
}

QVariant JsonNode::GetData(int) const
{
    return m_name;
}

int JsonNode::GetRow()
{
    return m_parent ? m_parent->GetChilds().indexOf(sharedFromThis()) : 1;
}

void JsonNode::SetJsonNodeType(JsonNodeType jsonNodeType)
{
   m_jsonNodeType = jsonNodeType;
}
