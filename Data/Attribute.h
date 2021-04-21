#pragma once
#include <QString>
#include "Filter/Filter.h"
class Attribute
{
public:
   Attribute(const QString&, const QString&);
   void ApplyFilter(const FilterPtr&);
   void ApplyFilter(const QString&);
   const QString& GetName() const noexcept;
   const QString& GetValue() const noexcept;
   bool IsMatchFilter() const noexcept;
   Filter::SearchType GetMatchType() const noexcept;
   void ResetMatchFilter() noexcept;
private:
   QString m_name;
   QString m_value;
   bool m_isMatchFilter;
   Filter::SearchType m_matchType;
};

using Attributes = QVector<Attribute>;
