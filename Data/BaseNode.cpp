#include "BaseNode.h"
#include "Executors/Filter.h"
#include "Data/Attribute.h"
#include <QDebug>
#include "Utils.h"

BaseNode::BaseNode(const NodePtr parentItem)
   : m_parent{parentItem}
{}

void BaseNode::ApplyFilter(const QString& key)
{
   ResetMatchFilter();
   const auto isNameMatch = m_name.contains(key);
   const auto isValueMatch = m_value.contains(key);
   if (isNameMatch && isValueMatch)
   {
      m_isMatchFilter = true;
      m_matchType = SearchType::BothNodeTypes;
   }
   else if (isNameMatch)
   {
      m_isMatchFilter = true;
      m_matchType = SearchType::Name;
   }
   else if (isValueMatch)
   {
      m_isMatchFilter = true;
      m_matchType = SearchType::Value;
   }

   for(auto& attribute : m_attributes)
   {
      attribute->ApplyFilter(key);
      m_isMatchFilter |= attribute->IsMatchFilter();
   }

   for (const auto& child : m_childs)
   {
      child->ApplyFilter(key);
   }

   if (m_isMatchFilter)
   {
      onNodeMatchFilter(GetPtr());
   }
}

void BaseNode::AppendChild(const NodePtr child)
{
   m_childs.push_back(child);
   onDataChanged();
}

void BaseNode::AddAttribute(const AttributePtr& attribute)
{
   m_attributes.push_back(attribute);
   connect(attribute.get(), &Attribute::onDataChanged, this, &BaseNode::onAttributeDataChanged);
   onDataChanged();
}

void BaseNode::SetAttributes(const Attributes& attributes)
{
   m_attributes = attributes;
   onDataChanged();
}

void BaseNode::SetName(const QString& name)
{
   m_name = name;
   onDataChanged();
}

void BaseNode::SetMathFilter(const FilterPtr& filter)
{
   m_isMatchFilter = true;
   if (const auto searchType = filter->GetSearchType();
       searchType == SearchType::Name || searchType == SearchType::Value)
   {
      m_matchType = filter->GetSearchType();
   }

   onNodeMatchFilter(GetPtr());
}

void BaseNode::SetValue(const QString& value)
{
   auto tmp = value.simplified();
   tmp.replace( " ", "" );
   if (tmp.length() != 0)
   {
      m_value = value;
      onDataChanged();
   }
}

void BaseNode::SetJsonNodeType(JsonNodeType) {}

const NodePtr BaseNode::GetChild(int row) const noexcept {return row < 0 || row > m_childs.size() ? nullptr : m_childs[row];}

const NodePtr BaseNode::GetParentItem() const noexcept { return m_parent; }

Nodes BaseNode::GetChilds() const noexcept { return m_childs; }

int BaseNode::GetChildCount() const noexcept { return m_childs.count(); }

const Attributes& BaseNode::GetAttributes() const noexcept { return m_attributes; }

Attributes& BaseNode::GetAttributes() noexcept { return m_attributes; }

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

SearchType BaseNode::GetMatchType() const noexcept
{
   return m_matchType;
}

void BaseNode::ResetMatchFilter() noexcept
{
   m_isMatchFilter = false;
   m_matchType = SearchType::Unknown;
   onResetMatchFilter(GetPtr());
}

void BaseNode::DataChanged() noexcept
{
   onDataChanged();
}

void BaseNode::onAttributeDataChanged()
{
   onDataChanged();
}
