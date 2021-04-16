#include "XMLNode.h"
#include <algorithm>

namespace
{
   QString createRowData(const QString& name, const Attributes& attributes)
   {
      auto temp{name};
      for (const auto& [attributeName, attributeValue] : attributes)
      {
         temp.append(" ")
             .append(*attributeName)
             .append(" = ")
             .append(attributeValue);
      }
      return temp;
   }
}

XMLNode::XMLNode(const NodePtr& parentItem)
    : BaseNode{parentItem}
{
}

int XMLNode::GetColumnCount() const noexcept
{
    return 1;
}

QVariant XMLNode::GetData(int) const
{
    return createRowData(m_name, m_attributes);
}

int XMLNode::GetRow()
{
    return m_parent ? m_parent->GetChilds().indexOf(sharedFromThis()) : 1;
}
