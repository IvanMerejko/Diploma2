#include "BaseNode.h"
#include "Filter/Filter.h"


namespace
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

BaseNode::BaseNode(const NodePtr parentItem)
   : m_parent{parentItem}
{}

void BaseNode::ApplyFilter(const FilterPtr& filter)
{
   switch (filter->GetSearchType())
   {
      case Filter::SearchType::Name:
         break;
      case Filter::SearchType::Value:
         break;

   }
}

void BaseNode::AppendChild(const NodePtr child) { m_childs.push_back(child); }

void BaseNode::AddAttribute(const Attribute& attribute) { m_attributes.push_back(attribute); }

void BaseNode::SetAttributes(const Attributes& attributes) { m_attributes = attributes; }

void BaseNode::SetName(const QString& name) { m_name = name; }

void BaseNode::SetValue(const QString& value) { m_value = value; }

void BaseNode::SetJsonNodeType(JsonNodeType) {}

const NodePtr BaseNode::GetChild(int row) const noexcept {return row < 0 || row > m_childs.size() ? nullptr : m_childs[row];}

const NodePtr BaseNode::GetParentItem() const noexcept { return m_parent; }

Nodes BaseNode::GetChilds() const noexcept { return m_childs; }

int BaseNode::GetChildCount() const noexcept { return m_childs.count(); }

const Attributes& BaseNode::GetAttributes() const noexcept { return m_attributes; }

const QString& BaseNode::GetName() const noexcept { return m_name; }

const QString& BaseNode::GetValue() const noexcept { return m_value; }

const NodePtr BaseNode::GetPtr() noexcept
{
   return sharedFromThis();
}

JsonNodeType BaseNode::GetJsonNodeType() const noexcept
{
   return m_jsonNodeType;
}

bool BaseNode::IsMatchFilter() const noexcept
{
   return m_isMatchFilter;
}

void BaseNode::ResetMatchFilter() noexcept
{
   m_isMatchFilter = false;
}
