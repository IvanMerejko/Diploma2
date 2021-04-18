#include "Utils.h"

namespace utils
{
bool IsMarchFilter(const QString& value, const FilterPtr& filter)
{
   switch (filter->GetSearchAction())
   {
      case Filter::SearchAction::Equal:
         return value == filter->GetValue();
      case Filter::SearchAction::NotEqual:
         return value != filter->GetValue();
      case Filter::SearchAction::Contains:
         return value.contains(filter->GetValue());
      case Filter::SearchAction::NotContains:
         return !value.contains(filter->GetValue());
   }
}
}
