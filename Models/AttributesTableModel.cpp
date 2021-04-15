#include "AttributesTableModel.h"
#include "Node.h"
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
   const auto& [name, value] = m_node->GetAttributes().at(index.row());
   switch(static_cast<AttributeType>(role))
   {
      case AttributeType::Name:
         return name;
      case AttributeType::Value:
         return value;
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
