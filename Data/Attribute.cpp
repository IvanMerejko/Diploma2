#include "Attribute.h"
#include <optional>
#include "Utils.h"

Attribute::Attribute(const QString& name, const QString& value)
   : m_name{name}
   , m_value{value}
   , m_isMatchFilter{false}
   , m_matchType{Filter::SearchType::Unknown}
{

}

void Attribute::ApplyFilter(const FilterPtr& filter)
{
   ResetMatchFilter();
   const auto searchType = filter->GetSearchType();
   if (searchType == Filter::SearchType::Name || searchType == Filter::SearchType::Value)
   {
      return;
   }

   m_isMatchFilter = utils::IsMarchFilter(searchType == Filter::SearchType::AttributeName ? m_name : m_value, filter);
   if (m_isMatchFilter)
   {
      m_matchType = searchType;
   }
}

void Attribute::ApplyFilter(const QString& key)
{
   ResetMatchFilter();
   const auto isNameMatch = m_name.contains(key);
   const auto isValueMatch = m_value.contains(key);
   if (isNameMatch && isValueMatch)
   {
      m_isMatchFilter = true;
      m_matchType = Filter::SearchType::BothAttributeTypes;
   }
   else if (isNameMatch)
   {
      m_isMatchFilter = true;
      m_matchType = Filter::SearchType::AttributeName;
   }
   else if (isValueMatch)
   {
      m_isMatchFilter = true;
      m_matchType = Filter::SearchType::AttributeValue;
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

Filter::SearchType Attribute::GetMatchType() const noexcept
{
   return m_matchType;
}

void Attribute::ResetMatchFilter() noexcept
{
   m_isMatchFilter = false;
   m_matchType = Filter::SearchType::Unknown;
}
