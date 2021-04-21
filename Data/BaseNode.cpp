#include "BaseNode.h"
#include "Filter/Filter.h"
#include <QDebug>
#include "Utils.h"

BaseNode::BaseNode(const NodePtr parentItem)
   : m_parent{parentItem}
{}

void BaseNode::ApplyFilter(const FilterPtr& filter)
{
   ResetMatchFilter();
   if (const auto searchType = filter->GetSearchType();
       searchType == Filter::SearchType::Name || searchType == Filter::SearchType::Value)
   {
      m_matchType = searchType;
      m_isMatchFilter = utils::IsMarchFilter(searchType == Filter::SearchType::Name ? m_name : m_value, filter);
   }
   else
   {
      for(auto& attribute : m_attributes)
      {
         attribute.ApplyFilter(filter);
         m_isMatchFilter |= attribute.IsMatchFilter();
      }
   }

   for (const auto& child : m_childs)
   {
      child->ApplyFilter(filter);
   }
   if (m_isMatchFilter)
   {
      onNodeMatchFilter(GetPtr());
   }
}

void BaseNode::ApplyFilter(const QString& key)
{
   ResetMatchFilter();
   const auto isNameMatch = m_name.contains(key);
   const auto isValueMatch = m_value.contains(key);
   if (isNameMatch && isValueMatch)
   {
      m_isMatchFilter = true;
      m_matchType = Filter::SearchType::BothNodeTypes;
   }
   else if (isNameMatch)
   {
      m_isMatchFilter = true;
      m_matchType = Filter::SearchType::Name;
   }
   else if (isValueMatch)
   {
      m_isMatchFilter = true;
      m_matchType = Filter::SearchType::Value;
   }

   for(auto& attribute : m_attributes)
   {
      attribute.ApplyFilter(key);
      m_isMatchFilter |= attribute.IsMatchFilter();
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

Filter::SearchType BaseNode::GetMatchType() const noexcept
{
   return m_matchType;
}

void BaseNode::ResetMatchFilter() noexcept
{
   m_isMatchFilter = false;
   m_matchType = Filter::SearchType::Unknown;
}
