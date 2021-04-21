#pragma once

#include "Types.h"
#include <QSharedPointer>

class BaseFilter : public QEnableSharedFromThis<BaseFilter>
{

public:
   virtual void ApplyFilter(const NodePtr&, bool includeChilds = true) = 0;
   virtual void ApplyFilter(const AttributePtr&) = 0;
   virtual CompoundFilterNodePtr GetRoot() const noexcept = 0;
   virtual ~BaseFilter() = default;

   BaseFilter(const QString& name, const QString& value, SearchType searchType, SearchAction searchAction);

   const QString& GetName() const noexcept { return m_name; }
   const QString& GetValue() const noexcept { return m_value; }
   QString GetSearchTypeStr() const noexcept;
   SearchType GetSearchType() const noexcept { return m_searchType; }
   QString GetSearchActionStr() const noexcept;
   SearchAction GetSearchAction() const noexcept { return m_searchAction; }
protected:
   QString m_name;
   QString m_value;
   SearchType m_searchType;
   SearchAction m_searchAction;
};
