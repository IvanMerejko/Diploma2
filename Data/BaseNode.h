#pragma once
#include "Types.h"
#include "Attribute.h"
#include "Filter/Filter.h"

class BaseNode: public QEnableSharedFromThis<BaseNode>
{
public:
    BaseNode(const NodePtr parentItem = nullptr);;

   virtual int GetColumnCount() const noexcept  = 0;
   virtual QVariant GetData(int column) const = 0;
   virtual int GetRow()  = 0;
   void ApplyFilter(const FilterPtr&);

   void AppendChild(const NodePtr child);;
   void AddAttribute(const Attribute& attribute);;
   void SetAttributes(const Attributes& attributes);;
   void SetName(const QString& name);
   void SetValue(const QString& value);

   virtual void SetJsonNodeType(JsonNodeType);
   const NodePtr GetChild(int row) const noexcept;
   const NodePtr GetParentItem() const noexcept;
   Nodes GetChilds() const noexcept;
   int GetChildCount() const noexcept;
   const Attributes& GetAttributes() const noexcept;
   const QString& GetName() const noexcept;
   const QString& GetValue() const noexcept;
   const NodePtr GetPtr() noexcept;
   JsonNodeType GetJsonNodeType() const noexcept;
   bool IsMatchFilter() const noexcept;
   Filter::SearchType GetMatchType() const noexcept;
   void ResetMatchFilter() noexcept;
protected:
    QString m_name;
    QString m_value;
    Attributes m_attributes;
    JsonNodeType m_jsonNodeType = JsonNodeType::Undefind;
    Nodes m_childs;
    NodePtr m_parent;
    bool m_isMatchFilter{false};
    Filter::SearchType m_matchType{Filter::SearchType::Unknown};
};
