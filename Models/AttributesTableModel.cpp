#include "AttributesTableModel.h"
#include "Data/XMLNode.h"
#include "Data/Attribute.h"
#include "Executors/Filter.h"
#include <QDebug>

namespace
{
   constexpr auto AttributeNameStr = "name";
   constexpr auto AttributeValueStr = "value";
}

AttributesTableModel::AttributesTableModel(const NodePtr& node, const TreeModelPtr& treeModel)
   : m_node{node}
   , m_treeModel{treeModel}
{
}

void AttributesTableModel::UpdateModel()
{
   beginResetModel();
   endResetModel();
}

bool AttributesTableModel::IsItemMatchFilter(int row, int column) const
{
   if (row < 0 || row >  m_node->GetAttributes().size())
   {
      return false;
   }
   const auto& attribute = m_node->GetAttributes().at(row);
   switch(column)
   {
      case 0:
         return attribute->GetMatchType() == SearchType::AttributeName;
      case 1:
         return attribute->GetMatchType() == SearchType::AttributeValue;
      default:
         return false;
   }
}

void AttributesTableModel::OnAttributeValueChanged(int row, const QString& value)
{
   if (row < 0 || row >  m_node->GetAttributes().size())
   {
      return;
   }
   beginResetModel();
   m_node->GetAttributes().at(row)->SetValue(value);
   endResetModel();
}

void AttributesTableModel::OnAttributeNameChanged(int row, const QString& name)
{
   if (row < 0 || row >  m_node->GetAttributes().size())
   {
      return;
   }
   beginResetModel();
   m_node->GetAttributes().at(row)->SetName(name);
   endResetModel();
}

void AttributesTableModel::CreateNewAttribute()
{
   const auto attribute = QSharedPointer<Attribute>::create();
   QObject::connect(attribute.get(), &Attribute::onDataChanged, m_treeModel.get(), &TreeModel::onDataChanged);
   beginResetModel();
   m_node->GetAttributes().push_back(attribute);
   endResetModel();
}

void AttributesTableModel::DeleteAttribute(int row)
{
   beginResetModel();
   auto& attributes = m_node->GetAttributes();
   attributes.erase(std::remove(attributes.begin(), attributes.end(), attributes[row]), attributes.end());
   endResetModel();
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
         return attribute->GetName();
      case AttributeType::Value:
         return attribute->GetValue();
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
