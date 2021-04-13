#pragma once
#include <QSharedPointer>
#include <QVector>
#include <QVariant>
#include <QEnableSharedFromThis>

using NodePtr = QSharedPointer<class Node>;

class Node : public QEnableSharedFromThis<Node>
{
private:
    using Nodes = QVector<NodePtr>;
public:
    Node(const NodePtr parentItem = nullptr);

    void AppendChild(const NodePtr child);

    NodePtr GetChild(int row) const noexcept;
    Nodes GetChilds() const noexcept;
    int GetChildCount() const noexcept;
    int GetColumnCount() const noexcept;
    QVariant GetData(int column) const;
    int GetRow();
    NodePtr GetParentItem() const noexcept;
private:
    Nodes m_childs;
    NodePtr m_parent;
};

