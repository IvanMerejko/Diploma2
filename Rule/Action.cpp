#include "Action.h"
#include <optional>
#include "Utils.h"



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
