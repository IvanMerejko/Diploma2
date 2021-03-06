#include "FilterResultTable.h"

QVariant FilterResultTableModel::data(const QModelIndex &index, int role) const
{
   if (!index.isValid())
   {
      return QVariant{};
   }

   return m_nodes.at(index.row())->GetData();
}

const NodePtr& FilterResultTableModel::GetNode(int index) const noexcept
{
   return m_nodes.at(index);
}

void FilterResultTableModel::addNode(const NodePtr& node)
{
   m_nodes.push_back(node);
}

void FilterResultTableModel::removeNode(const NodePtr& node)
{
   m_nodes.removeOne(node);
}

void FilterResultTableModel::filteringStarted()
{
   m_nodes.clear();
}

void FilterResultTableModel::filteringFinished()
{
   beginResetModel();
   endResetModel();
}

void FilterResultTableModel::connectWithNodes(const NodePtr& node)
{
   if (node)
   {
      connect(node.get(), &BaseNode::onNodeMatchFilter, this, &FilterResultTableModel::addNode);
      connect(node.get(), &BaseNode::onResetMatchFilter, this, &FilterResultTableModel::removeNode);
      for(const auto& child : node->GetChilds())
      {
         connectWithNodes(child);
      }
   }
}

int FilterResultTableModel::rowCount(const QModelIndex &) const
{
   return m_nodes.size();
}

int FilterResultTableModel::columnCount(const QModelIndex &) const
{
   return 1;
}

QHash<int, QByteArray> FilterResultTableModel::roleNames() const
{
   QHash<int, QByteArray> roles;
   roles[static_cast<int>(Role::Result)] = "result";
   return roles;
}
