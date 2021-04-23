#pragma once
#include "Executors/BaseFilter.h"
class Filter : public BaseFilter
{
public:
   Filter(const QString& name, const QString& value, SearchType searchType, SearchAction searchAction);
   void ApplyFilter(const NodePtr&, bool includeChilds = true) override;
   void ApplyFilter(const AttributePtr&) override;
   CompoundFilterNodePtr GetRoot() const noexcept override;
};

