#include "Rule.h"

Rule::Rule(const QString& name, const FilterPtr& filter, const ActionPtr& action)
   : m_name{name}
   , m_filter{filter}
   , m_action{action}
{

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
