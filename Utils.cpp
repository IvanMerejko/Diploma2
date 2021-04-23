#include "Utils.h"
#include "Executors/Filter.h"
namespace utils
{
bool IsMarchFilter(const QString& value, const FilterPtr& filter)
{
   switch (filter->GetSearchAction())
   {
      case SearchAction::Equal:
         return value == filter->GetValue();
      case SearchAction::NotEqual:
         return value != filter->GetValue();
      case SearchAction::Contains:
         return value.contains(filter->GetValue());
      case SearchAction::NotContains:
         return !value.contains(filter->GetValue());
      case SearchAction::Unknown:
         return false;
   }
}
}
