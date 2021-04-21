#include "CompoundFilter.h"
#include "Data/BaseNode.h"
#include <QDebug>

namespace
{
   bool applyFilter(const NodePtr& node, const CompoundFilterNodePtr& filter)
   {
      qDebug() << "applyFilter " << node->GetName();
      const auto op = filter->operation;
      switch(op)
      {
         case Operation::Value:
         {
            filter->m_filter->ApplyFilter(node, false);
            return node->IsMatchFilter();
         };
         case Operation::Not:
         {
            return !applyFilter(node, filter->m_leftOperand);
         };
         case Operation::And:
         {
            return applyFilter(node, filter->m_leftOperand) && applyFilter(node, filter->m_rightOperand);
         };
         case Operation::Or:
         {
            return applyFilter(node, filter->m_leftOperand) || applyFilter(node, filter->m_rightOperand);
         };
      }
   }
}



CompoundFilter::CompoundFilter(const QString& name, const QString& value, SearchType searchType,
   const CompoundFilterNodePtr& root)
   : BaseFilter(name, value, searchType, SearchAction::Unknown)
   , m_compoundFilter{root}
{
}

void CompoundFilter::ApplyFilter(const NodePtr& node, bool)
{
   if (!m_compoundFilter)
   {
      return;
   }

   if (!applyFilter(node, m_compoundFilter))
   {
      node->ResetMatchFilter();
   }
   else if(!node->IsMatchFilter())
   {
      node->SetMathFilter(sharedFromThis());
   }

   for(const auto& child : node->GetChilds())
   {
      ApplyFilter(child);
   }
}

void CompoundFilter::ApplyFilter(const AttributePtr&)
{
}

CompoundFilterNodePtr CompoundFilter::GetRoot() const noexcept
{
   return m_compoundFilter;
}
