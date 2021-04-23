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


   const QString& GetActionName() const noexcept;
   ActionType GetActionType() const noexcept;
   const QString& GetName() const noexcept;
   const QString& GetValue() const noexcept;

private:
   QString m_actionName;
   ActionType m_actionType;
   QString m_name;
   QString m_value;
};
