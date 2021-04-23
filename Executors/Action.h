#pragma once
#include <QString>
#include "Types.h"

class Action
{
public:
   Action(const QString& actionName, ActionType);
   Action(const QString& actionName, ActionType, const QString&, const QString&);

   void SetValue(const QString&);
   void SetName(const QString&);

   void ApplyAction(const NodePtr&) const noexcept;

   const QString& GetActionName() const noexcept;
   ActionType GetActionType() const noexcept;
   const QString& GetName() const noexcept;
   const QString& GetValue() const noexcept;

private:
   void deleteNode(const NodePtr&) const noexcept;
   void modifyAttributeName(const NodePtr&) const noexcept;
   void deleteAttribute(const NodePtr&) const noexcept;
   void modifyAttributeValue(const NodePtr&) const noexcept;
   void modifyNodeName(const NodePtr&) const noexcept;
   void modifyNodeValue(const NodePtr&) const noexcept;
   void addAttribute(const NodePtr&) const noexcept;

private:
   QString m_actionName;
   ActionType m_actionType;
   QString m_name;
   QString m_value;
};
