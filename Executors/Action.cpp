#include "Action.h"
#include <optional>
#include "Utils.h"
#include "Data/BaseNode.h"
#include "Data/Attribute.h"

Action::Action(const QString& actionName, ActionType actionType)
   : m_actionName{actionName}
   , m_actionType{actionType}
{
}

Action::Action(const QString& actionName, ActionType actionType, const QString& name, const QString& value)
   : m_actionName{actionName}
   , m_actionType{actionType}
   , m_name{name}
   , m_value{value}
{

}

void Action::SetValue(const QString& value)
{
   m_value = value;
}

void Action::SetName(const QString& name)
{
   m_name = name;
}

void Action::ApplyAction(const NodePtr& node) const noexcept
{
   switch (m_actionType)
   {
      case ActionType::DeleteNode:
         deleteNode(node);
         break;
      case ActionType::DeleteAttribute:
         deleteAttribute(node);
         break;
      case ActionType::ModifyAttributeName:
         modifyAttributeName(node);
         break;
      case ActionType::ModifyAttributeValue:
         modifyAttributeValue(node);
         break;
      case ActionType::ModifyNodeName:
         modifyNodeName(node);
         break;
      case ActionType::ModifyNodeValue:
         modifyNodeValue(node);
         break;
      case ActionType::AddAttribute:
         addAttribute(node);
         break;
   }
   node->DataChanged();
}

const QString& Action::GetActionName() const noexcept
{
   return m_actionName;
}

ActionType Action::GetActionType() const noexcept
{
   return m_actionType;
}

const QString& Action::GetName() const noexcept
{
   return m_name;
}

const QString& Action::GetValue() const noexcept
{
   return m_value;
}

void Action::deleteNode(const NodePtr&) const noexcept
{

}

void Action::modifyAttributeName(const NodePtr& node) const noexcept
{
   for(auto& attribute : node->GetAttributes())
   {
      if (attribute->IsMatchFilter())
      {
         attribute->SetName(m_name);
      }
   }
}

void Action::deleteAttribute(const NodePtr& node) const noexcept
{
   auto& attributes = node->GetAttributes();
   attributes.erase(std::remove_if(attributes.begin(), attributes.end(),
      [](const auto& attribute)
   {
      return attribute->IsMatchFilter();
   }),  attributes.end());
}

void Action::modifyAttributeValue(const NodePtr& node) const noexcept
{
   for(auto& attribute : node->GetAttributes())
   {
      if (attribute->IsMatchFilter())
      {
         attribute->SetValue(m_value);
      }
   }
}

void Action::modifyNodeName(const NodePtr& node) const noexcept
{
   node->SetName(m_name);
}

void Action::modifyNodeValue(const NodePtr& node) const noexcept
{
   node->SetValue(m_value);
}

void Action::addAttribute(const NodePtr& node) const noexcept
{
   node->GetAttributes().push_back(AttributePtr::create(m_name, m_value));
}
