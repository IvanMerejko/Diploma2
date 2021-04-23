#include "Rule.h"
#include "Data/BaseNode.h"
#include "Action.h"
#include "Executors/Filter.h"
Rule::Rule(const QString& name, const FilterPtr& filter, const ActionPtr& action)
   : m_name{name}
   , m_filter{filter}
   , m_action{action}
{

}

void Rule::ApplyRule(const NodePtr& node)
{
   m_filter->ApplyFilter(node, false);
   if (node->IsMatchFilter())
   {
      m_action->ApplyAction(node);
   }
   if (node)
   {
      for (const auto& child : node->GetChilds())
      {
         ApplyRule(child);
      }
   }
}

const QString& Rule::GetName() const noexcept
{
   return m_name;
}

const FilterPtr& Rule::GetFilter() const noexcept
{
   return m_filter;
}

const ActionPtr& Rule::GetAction() const noexcept
{
   return m_action;
}
