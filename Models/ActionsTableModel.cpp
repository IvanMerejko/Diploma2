#include "ActionsTableModel.h"
#include "Executors/Action.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
namespace
{
   constexpr auto ActionNameStr = "actionname";
   constexpr auto ActionTypeStr = "actiontype";
   constexpr auto NameStr = "name";
   constexpr auto ValueStr = "value";

   QString actionTypeToStr(ActionType actionType)
   {
      switch (actionType)
      {
         case ActionType::DeleteNode:
            return "DeleteNode";
         case ActionType::DeleteAttribute:
            return "DeleteAttribute";
         case ActionType::ModifyAttributeName:
            return "ModifyAttributeName";
         case ActionType::ModifyAttributeValue:
            return "ModifyAttributeValue";
         case ActionType::ModifyNodeName:
            return "ModifyNodeName";
         case ActionType::ModifyNodeValue:
            return "ModifyNodeValue";
         case ActionType::AddAttribute:
            return "AddAttribute";
      }
   }
}

ActionsTableModel::ActionsTableModel()
{
   readFromFile();
}

ActionsTableModel::~ActionsTableModel()
{
   saveToFile();
}

void ActionsTableModel::DeleteAction(int row)
{
   beginResetModel();
   m_actions.erase(std::remove(m_actions.begin(), m_actions.end(), m_actions[row]), m_actions.end());
   endResetModel();
}

void ActionsTableModel::AddAction(const QString& actionName, int actionType, const QString& name, const QString& value)
{
   if (!findAction(actionName))
   {
      beginResetModel();
      const auto actionTypeEnum = static_cast<ActionType>(actionType);
      const auto newAction = ActionPtr::create(actionName, actionTypeEnum);
      switch(actionTypeEnum)
      {
         case ActionType::ModifyAttributeName:
         case ActionType::ModifyNodeName:
            newAction->SetName(name);
            break;
         case ActionType::ModifyAttributeValue:
         case ActionType::ModifyNodeValue:
            newAction->SetValue(value);
            break;
         case ActionType::AddAttribute:
            newAction->SetName(name);
            newAction->SetValue(value);
            break;
         default:
            break;
      }
      m_actions.append(newAction);
      endResetModel();
   }
}

QVariantList ActionsTableModel::GetActionsName() const noexcept
{
   QVariantList list;
   for(const auto& action : m_actions)
   {
      list.append(action->GetActionName());
   }
   return list;
}

const ActionPtr& ActionsTableModel::GetAction(int index) const
{
   return m_actions.at(index);
}

const ActionPtr ActionsTableModel::GetActionByName(const QString& actionName) const
{
   return findAction(actionName);
}

int ActionsTableModel::rowCount(const QModelIndex&) const
{
   return m_actions.size();
}

int ActionsTableModel::columnCount(const QModelIndex&) const
{
   return 4;
}

QVariant ActionsTableModel::data(const QModelIndex& index, int role) const
{
   if(!index.isValid())
   {
      return QVariant();
   }
   const auto& action = m_actions.at(index.row());
   switch(static_cast<Role>(role))
   {
      case Role::ActionName:
         return action->GetActionName();
      case Role::ActionType:
         return actionTypeToStr(action->GetActionType());
      case Role::Name:
         return action->GetName();
      case Role::Value:
         return action->GetValue();
   }
   return QVariant{};
}

QHash<int, QByteArray> ActionsTableModel::roleNames() const
{
   QHash<int, QByteArray> roles;
   roles[static_cast<int>(Role::ActionName)] = ActionNameStr;
   roles[static_cast<int>(Role::ActionType)] = ActionTypeStr;
   roles[static_cast<int>(Role::Name)] = NameStr;
   roles[static_cast<int>(Role::Value)] = ValueStr;
   return roles;
}

void ActionsTableModel::saveToFile()
{
   QFile outfile("Actions.txt");
   outfile.open(QIODevice::WriteOnly | QIODevice::Text);
   QTextStream writeStream(&outfile);
   for (const auto& action : m_actions)
   {
      writeStream << action->GetActionName() << "\\_/"
              << static_cast<int>(action->GetActionType()) << "\\_/"
              << action->GetName() << "\\_/"
              << action->GetValue() << '\n';
   }
   outfile.close();
}

void ActionsTableModel::readFromFile()
{
   QFile infile("Actions.txt");
   infile.open(QIODevice::ReadOnly);
   QTextStream in(&infile);
   while (!in.atEnd())
   {
      QString line = in.readLine();
      auto pieces = line.split(  "\\_/" );
      m_actions.append(ActionPtr::create(pieces[0],
         static_cast<ActionType>(pieces[1].toInt()), pieces[2], pieces[3]));
   }
   infile.close();
}

const ActionPtr ActionsTableModel::findAction(const QString& actionName) const noexcept
{
   const auto it = std::find_if(m_actions.begin(), m_actions.end(), [actionName](const auto& action) { return action->GetActionName() == actionName; });
   return it == m_actions.end() ? nullptr : *it;
}
