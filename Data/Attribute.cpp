#include "Attribute.h"
#include <optional>
#include "Utils.h"

Attribute::Attribute(const QString& name, const QString& value)
   : m_name{name}
   , m_value{value}
   , m_isMatchFilter{false}
   , m_matchType{SearchType::Unknown}
{

}

void Attribute::ApplyFilter(const QString& key)
{
   ResetMatchFilter();
   const auto isNameMatch = m_name.contains(key);
   const auto isValueMatch = m_value.contains(key);
   if (isNameMatch && isValueMatch)
   {
      m_isMatchFilter = true;
      m_matchType = SearchType::BothAttributeTypes;
   }
   else if (isNameMatch)
   {
      m_isMatchFilter = true;
      m_matchType = SearchType::AttributeName;
   }
   else if (isValueMatch)
   {
      m_isMatchFilter = true;
      m_matchType = SearchType::AttributeValue;
   }
}

void Attribute::SetMathFilter(const FilterPtr& filter)
{
   m_isMatchFilter = true;
   if (const auto searchType = filter->GetSearchType();
       searchType == SearchType::Name || searchType == SearchType::Value)
   {
      m_matchType = filter->GetSearchType();
   }
}

const QString& Attribute::GetName() const noexcept
{
   return m_name;
}

const QString& Attribute::GetValue() const noexcept
{
   return m_value;
}

bool Attribute::IsMatchFilter() const noexcept
{
   return m_isMatchFilter;
}

SearchType Attribute::GetMatchType() const noexcept
{
   return m_matchType;
}

void Attribute::ResetMatchFilter() noexcept
{
   m_isMatchFilter = false;
   m_matchType = SearchType::Unknown;
}
