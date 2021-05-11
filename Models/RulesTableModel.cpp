#include "RulesTableModel.h"
#include "Executors/Rule.h"
#include "Executors/Action.h"
#include "Executors/Filter.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>

RulesTableModel::RulesTableModel(const ActionsTableModelPtr& actions, const FiltersTableModelPtr& filters)
   : m_actions{actions}
   , m_filters{filters}
{
   readFromFile();
}

RulesTableModel::~RulesTableModel()
{
   saveToFile();
}

QString RulesTableModel::AddRule(const QString& ruleName, int filterIndex, int actionIndex)
{
   if (findRule(ruleName))
   {
      return "Rule with name \"" + ruleName + "\" already exists.";
   }
   else
   {
      const auto& filter = m_filters->GetFilter(filterIndex);
      const auto& action = m_actions->GetAction(actionIndex);
      if (filter && action)
      {
         beginResetModel();
         m_rules.push_back(RulePtr::create(ruleName, filter, action));
         endResetModel();
      }
      return "";
   }
}

void RulesTableModel::DeleteRule(int row)
{
   beginResetModel();
   m_rules.erase(std::remove(m_rules.begin(), m_rules.end(), m_rules[row]), m_rules.end());
   endResetModel();
}

const RulePtr& RulesTableModel::GetRule(int row) const noexcept
{
   return m_rules.at(row);
}

int RulesTableModel::rowCount(const QModelIndex&) const
{
   return m_rules.size();
}

int RulesTableModel::columnCount(const QModelIndex&) const
{
   return 3;
}

QVariant RulesTableModel::data(const QModelIndex& index, int role) const
{
   if(!index.isValid())
   {
      return QVariant();
   }

   const auto& rule = m_rules.at(index.row());
   switch(static_cast<Role>(role))
   {
      case Role::ActionName:
         return rule->GetAction()->GetActionName();
      case Role::FilterName:
         return rule->GetFilter()->GetName();
      case Role::RuleName:
         return rule->GetName();
   }
   return QVariant{};
}

QHash<int, QByteArray> RulesTableModel::roleNames() const
{
   QHash<int, QByteArray> roles;
   roles[static_cast<int>(Role::ActionName)] = "actionname";
   roles[static_cast<int>(Role::FilterName)] = "filtername";
   roles[static_cast<int>(Role::RuleName)] = "rulename";
   return roles;
}

void RulesTableModel::saveToFile()
{
   QFile outfile("Rules.txt");
   outfile.open(QIODevice::WriteOnly | QIODevice::Text);
   QTextStream writeStream(&outfile);
   for (const auto& rule : m_rules)
   {
      writeStream << rule->GetName() << "\\_/"
              << rule->GetFilter()->GetName() << "\\_/"
              << rule->GetAction()->GetActionName() << '\n';
   }
   outfile.close();
}

void RulesTableModel::readFromFile()
{
   QFile infile("Rules.txt");
   infile.open(QIODevice::ReadOnly);
   QTextStream in(&infile);
   while (!in.atEnd())
   {
      QString line = in.readLine();
      auto pieces = line.split(  "\\_/" );
      const auto& filter = m_filters->GetFilterByName(pieces[1]);
      const auto& action = m_actions->GetActionByName(pieces[2]);
      if (filter && action)
      {
         beginResetModel();
         m_rules.push_back(RulePtr::create(pieces[0], filter, action));
         endResetModel();
      }
   }
   infile.close();
}

const RulePtr RulesTableModel::findRule(const QString& ruleName) const noexcept
{
   const auto it = std::find_if(m_rules.begin(), m_rules.end(), [ruleName](const auto& filter) { return filter->GetName() == ruleName; });
   return it == m_rules.end() ? nullptr : *it;
}
