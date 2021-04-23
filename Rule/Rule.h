#pragma once
#include "Types.h"
class Rule
{
public:
   Rule(const QString&, const FilterPtr&, const ActionPtr&);

   const QString& GetName() const noexcept;
   const FilterPtr& GetFilter() const noexcept;
   const ActionPtr& GetAction() const noexcept;
private:
   QString m_name;
   FilterPtr m_filter;
   ActionPtr m_action;
};

