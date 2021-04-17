#include "Filter.h"

Filter::Filter(const QString& name, const QString& value, int searchType, int searchAction)
   : m_name{name}
   , m_value{value}
   , m_searchType{static_cast<SearchType>(searchType)}
   , m_searchAction{static_cast<SearchAction>(searchAction)}
{

}

QString Filter::GetSearchTypeStr() const noexcept
{
   switch (m_searchType)
   {
      case SearchType::Name:
         return "Name";
      case SearchType::Value:
         return "Value";
      case SearchType::AttributeName:
         return "AttributeName";
      case SearchType::AttributeValue:
         return "AttributeValue";
   }
}

QString Filter::GetSearchActionStr() const noexcept
{
   switch (m_searchAction)
   {
      case SearchAction::Equal:
         return "Equal";
      case SearchAction::NotEqual:
         return "NotEqual";
      case SearchAction::Contains:
         return "Contains";
      case SearchAction::NotContains:
         return "NotContains";
   }
}

