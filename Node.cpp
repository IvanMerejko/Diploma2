#include "Node.h"
#include <algorithm>

namespace
{
   QString createRowData(const QString& name, const Attributes& attributes)
   {
      auto temp{name};
      for (const auto& [attributeName, attributeValue] : attributes)
      {
         temp.append(" ").append(attributeName).append(" = ").append(attributeValue);
      }
      return temp;
   }
}

Node::Node(const NodePtr parentItem)
    : m_parent{parentItem}
{
}

void Node::AppendChild(const NodePtr child)
{
    m_childs.append(child);
}

const NodePtr Node::GetChild(int row) const noexcept
{
    return row < 0 || row > m_childs.size() ? nullptr : m_childs[row];
}

Nodes Node::GetChilds() const noexcept
{
    return m_childs;
}

int Node::GetChildCount() const noexcept
{
    return m_childs.count();
}

int Node::GetColumnCount() const noexcept
{
    return 1;
}

QVariant Node::GetData(int) const
{
    return createRowData(m_name, m_attributes);
}

int Node::GetRow()
{
    return m_parent ? m_parent->GetChilds().indexOf(sharedFromThis()) : 1;
}

const NodePtr Node::GetParentItem() const noexcept
{
    return m_parent;
}

void Node::SetAttributes(const Attributes &attributes)
{
    m_attributes = attributes;
}

void Node::AddAttribute(const Attribute &attribute)
{
   m_attributes.push_back(attribute);
}

const NodePtr Node::GetPtr() noexcept
{
   return sharedFromThis();
}
