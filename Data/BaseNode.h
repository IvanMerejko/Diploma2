#pragma once
#include "Types.h"

class BaseNode: public QEnableSharedFromThis<BaseNode>
{
public:
    BaseNode(const NodePtr parentItem = nullptr)
       : m_parent{parentItem}
    {};

   virtual int GetColumnCount() const noexcept  = 0;
   virtual QVariant GetData(int column) const = 0;
   virtual int GetRow()  = 0;



   void AppendChild(const NodePtr child) { m_childs.push_back(child); };
   void AddAttribute(const Attribute& attribute) { m_attributes.push_back(attribute); };
   void SetAttributes(const Attributes& attributes) { m_attributes = attributes; };
   void SetName(const QString& name) { m_name = name; }
   void SetValue(const QString& value) { m_value = value; }

   virtual void SetJsonNodeType(JsonNodeType) {}
   const NodePtr GetChild(int row) const noexcept {return row < 0 || row > m_childs.size() ? nullptr : m_childs[row];}
   const NodePtr GetParentItem() const noexcept { return m_parent; }
   Nodes GetChilds() const noexcept { return m_childs; }
   int GetChildCount() const noexcept { return m_childs.count(); }
   const Attributes& GetAttributes() const noexcept { return m_attributes; }
   const QString& GetName() const noexcept { return m_name; }
   const QString& GetValue() const noexcept { return m_value; }
   const NodePtr GetPtr() noexcept { return sharedFromThis(); }
   JsonNodeType GetJsonNodeType() const noexcept { return m_jsonNodeType; }
protected:
    QString m_name;
    QString m_value;
    Attributes m_attributes;
    JsonNodeType m_jsonNodeType = JsonNodeType::Undefind;
    Nodes m_childs;
    NodePtr m_parent;
};
