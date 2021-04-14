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

    void SetAttributes(const Attributes& attributes);
    void AddAttribute(const Attribute& attribute);
    const Attributes& GetAttributes() const noexcept { return m_attributes; }

    void SetName(const QString& name) { m_name = name; }
    const QString& GetName() const noexcept { return m_name; }

    void SetValue(const QString& value) { m_value = value; }
    const QString& GetValue() const noexcept { return m_value; }
    const NodePtr GetPtr() noexcept;
private:
    QString m_name;
    QString m_value;
    Attributes m_attributes;
    Nodes m_childs;
    NodePtr m_parent;
};

