#pragma once
#include <QVariant>
#include <QEnableSharedFromThis>
#include "Types.h"

class Node : public QEnableSharedFromThis<Node>
{
public:
    Node(const NodePtr parentItem = nullptr);

    void AppendChild(const NodePtr child);

    const NodePtr GetChild(int row) const noexcept;
    Nodes GetChilds() const noexcept;
    int GetChildCount() const noexcept;
    int GetColumnCount() const noexcept;
    QVariant GetData(int column) const;
    int GetRow();
    const NodePtr GetParentItem() const noexcept;

    void SetName(const QString& name) { m_name = name; }

    void SetAttributes(const Attributes& attributes);
    void AddAttribute(const Attribute& attribute);

    const Attributes& GetAttributes() const noexcept { return m_attributes; }
    const QString& GetName() const noexcept { return m_name; }
private:
    QString m_name;
    Attributes m_attributes;
    Nodes m_childs;
    NodePtr m_parent;
};

