#include "BaseFilter.h"

BaseFilter::BaseFilter(const QString& name, const QString& value, SearchType searchType, SearchAction searchAction)
   : m_name{name}
   , m_value{value}
   , m_searchType{searchType}
   , m_searchAction{searchAction}
{

}

QString BaseFilter::GetSearchTypeStr() const noexcept
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
      case SearchType::Compound:
         return "Compound";
      default:
         return "";
   }
}

QString BaseFilter::GetSearchActionStr() const noexcept
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
      default:
         return "";
   }
}
