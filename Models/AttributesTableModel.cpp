#include "AttributesTableModel.h"
#include "Data/XMLNode.h"
#include "Filter/Filter.h"
#include <QDebug>

namespace
{
   constexpr auto AttributeNameStr = "name";
   constexpr auto AttributeValueStr = "value";
}

AttributesTableModel::AttributesTableModel(const NodePtr& node)
   : m_node{node}
{
}

bool AttributesTableModel::IsItemMatchFilter(int row, int column) const
{
   const auto& attribute = m_node->GetAttributes().at(row);
   qDebug() << row << " " << column << " name " << attribute.GetName() << " value " << attribute.GetValue() << " type " << static_cast<int>(attribute.GetMatchType());
   switch(column)
   {
      case 0:
         return attribute.GetMatchType() == Filter::SearchType::AttributeName;
      case 1:
         return attribute.GetMatchType() == Filter::SearchType::AttributeValue;
      default:
         return false;
   }
}

int AttributesTableModel::rowCount(const QModelIndex&) const
{
   return m_node->GetAttributes().size();
}

int AttributesTableModel::columnCount(const QModelIndex&) const
{
   return 2;
}

QVariant AttributesTableModel::data(const QModelIndex& index, int role) const
{
   if(!index.isValid())
   {
      return QVariant();
   }
   const auto& attribute = m_node->GetAttributes().at(index.row());
   switch(static_cast<AttributeType>(role))
   {
      case AttributeType::Name:
         return attribute.GetName();
      case AttributeType::Value:
         return attribute.GetValue();
   }
   return QVariant{};
}

QHash<int, QByteArray> AttributesTableModel::roleNames() const
{
   QHash<int, QByteArray> roles;
   roles[static_cast<int>(AttributeType::Name)] = AttributeNameStr;
   roles[static_cast<int>(AttributeType::Value)] = AttributeValueStr;
   return roles;
}

bool AttributesTableModel::removeRows(int, int, const QModelIndex&)
{
   return true;
}

bool AttributesTableModel::setData(const QModelIndex&, const QVariant&, int)
{
   return true;
}
