#include "Filter.h"
#include "Utils.h"
#include "Data/BaseNode.h"
#include "Data/Attribute.h"
#include <QDebug>
Filter::Filter(const QString& name, const QString& value, SearchType searchType, SearchAction searchAction)
   : BaseFilter(name, value, searchType, searchAction)
{
}

void Filter::ApplyFilter(const NodePtr& node, bool includeChilds)
{
   node->ResetMatchFilter();
   const auto self = sharedFromThis();
   if (m_searchType == SearchType::Name || m_searchType == SearchType::Value)
   {
      if (utils::IsMarchFilter(m_searchType == SearchType::Name ? node->GetName() : node->GetValue(), self))
      {
         node->SetMathFilter(self);
      }
   }
   else
   {
      for(const auto& attribute : node->GetAttributes())
      {
         ApplyFilter(attribute);
         if (attribute->IsMatchFilter())
         {
            node->SetMathFilter(self);
         }
      }
   }

   if (includeChilds)
   {
      for (const auto& child : node->GetChilds())
      {
         ApplyFilter(child);
      }
   }
}

void Filter::ApplyFilter(const AttributePtr& attribute)
{
   attribute->ResetMatchFilter();
   if (m_searchType == SearchType::Name || m_searchType == SearchType::Value)
   {
      return;
   }

   if (const auto self = sharedFromThis();
       utils::IsMarchFilter(m_searchType == SearchType::AttributeName ? attribute->GetName(): attribute->GetValue(), self))
   {
       attribute->SetMathFilter(self);
   }
}

CompoundFilterNodePtr Filter::GetRoot() const noexcept
{
   return nullptr;
}
