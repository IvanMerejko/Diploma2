#pragma once
#include "Types.h"
#include "BaseFilter.h"

enum class Operation
{
   Not,
   And,
   Or,
   Value
};

struct CompoundFilterNode
{
   Operation operation;
   CompoundFilterNodePtr m_leftOperand;
   CompoundFilterNodePtr m_rightOperand;
   FilterPtr m_filter;
};

class CompoundFilter : public BaseFilter
{
public:
   CompoundFilter(const QString& name, const QString& value, SearchType searchType, const CompoundFilterNodePtr&);
   void ApplyFilter(const NodePtr&, bool includeChilds = true) override;
   void ApplyFilter(const AttributePtr&) override;

   CompoundFilterNodePtr GetRoot() const noexcept override;

private:
   CompoundFilterNodePtr m_compoundFilter;
};

