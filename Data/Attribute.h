#pragma once
#include <QString>
#include "Filter/BaseFilter.h"
class Attribute
{
public:
   Attribute(const QString&, const QString&);
   void ApplyFilter(const QString&);
   void SetMathFilter(const FilterPtr&);
   const QString& GetName() const noexcept;
   const QString& GetValue() const noexcept;
   bool IsMatchFilter() const noexcept;
   SearchType GetMatchType() const noexcept;
   void ResetMatchFilter() noexcept;
private:
   QString m_name;
   QString m_value;
   bool m_isMatchFilter;
   SearchType m_matchType;
};
