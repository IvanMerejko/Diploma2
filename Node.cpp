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

NodePtr Node::GetChild(int row) const noexcept
{
    return row < 0 || row > m_childs.size() ? nullptr : m_childs[row];
}

Node::Nodes Node::GetChilds() const noexcept
{
    return m_childs;
}

int Node::GetChildCount() const noexcept
{
    m_childs.count();
}

int Node::GetColumnCount() const noexcept
{

}

QVariant Node::GetData(int column) const
{

}

int Node::GetRow()
{
    return m_parent ? 0 : m_parent->GetChilds().indexOf(sharedFromThis());
}

NodePtr Node::GetParentItem() const noexcept
{
    return m_parent;
}
