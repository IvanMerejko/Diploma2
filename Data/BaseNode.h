#pragma once
#include "Types.h"

class BaseNode: public QObject, public QEnableSharedFromThis<BaseNode>
{
   Q_OBJECT
public:
    BaseNode(const NodePtr parentItem = nullptr);
    virtual ~BaseNode() = default;

   virtual int GetColumnCount() const noexcept  = 0;
   virtual QVariant GetData() const = 0;
   virtual int GetRow()  = 0;
   void ApplyFilter(const QString&);

   void AppendChild(const NodePtr child);;
   void AddAttribute(const AttributePtr& attribute);;
   void SetAttributes(const Attributes& attributes);;
   void SetName(const QString& name);
   void SetMathFilter(const FilterPtr&);
   void SetValue(const QString& value);

   virtual void SetJsonNodeType(JsonNodeType);
   const NodePtr GetChild(int row) const noexcept;
   const NodePtr GetParentItem() const noexcept;
   Nodes GetChilds() const noexcept;
   int GetChildCount() const noexcept;
   const Attributes& GetAttributes() const noexcept;
   Attributes& GetAttributes() noexcept;
   const QString& GetName() const noexcept;
   const QString& GetValue() const noexcept;
   const NodePtr GetPtr() noexcept;
   JsonNodeType GetJsonNodeType() const noexcept;
   bool IsMatchFilter() const noexcept;
   SearchType GetMatchType() const noexcept;
   void ResetMatchFilter() noexcept;
public slots:
   void onAttributeDataChanged();
signals:
   void onNodeMatchFilter(const NodePtr&);
   void onResetMatchFilter(const NodePtr&);
   void onDataChanged();
protected:
    QString m_name;
    QString m_value;
    Attributes m_attributes;
    JsonNodeType m_jsonNodeType = JsonNodeType::Undefind;
    Nodes m_childs;
    NodePtr m_parent;
    bool m_isMatchFilter{false};
    SearchType m_matchType{SearchType::Unknown};
};


