#include "Node.h"
#include <algorithm>

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
    return m_name;
}

int Node::GetRow()
{
    return m_parent ? 0 : m_parent->GetChilds().indexOf(sharedFromThis());
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
