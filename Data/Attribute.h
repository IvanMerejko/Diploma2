#pragma once
#include <QString>
#include "Executors/BaseFilter.h"
class Attribute
{
public:
   Attribute(const QString&, const QString&);
   void ApplyFilter(const QString&);
   void SetMathFilter(const FilterPtr&);
   void SetName(const QString&);
   void SetValue(const QString&);
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
