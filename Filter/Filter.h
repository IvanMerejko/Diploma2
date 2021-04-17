#pragma once
#include "Types.h"
class Filter
{
public:
   enum class SearchType
   {
      Name = 0,
      Value,
      AttributeName,
      AttributeValue
   };

   enum class SearchAction
   {
      Equal = 0,
      NotEqual,
      Contains,
      NotContains
   };

   Filter(const QString& name, const QString& value, int searchType, int searchAction);

   const QString& GetName() const noexcept { return m_name; }
   const QString& GetValue() const noexcept { return m_value; }
   QString GetSearchTypeStr() const noexcept;
   SearchType GetSearchType() const noexcept { return m_searchType; }
   QString GetSearchActionStr() const noexcept;
   SearchAction GetSearchAction() const noexcept { return m_searchAction; }
public:
   Filter();
private:
   QString m_name;
   QString m_value;
   SearchType m_searchType;
   SearchAction m_searchAction;
};

using FilterPtr = QSharedPointer<Filter>;
using Filters =  QVector<FilterPtr>;

