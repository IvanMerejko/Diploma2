#include "TreeModel.h"
#include "DataBuilder.h"
#include <QDebug>
#include "Windows/NodeInfoWindow.h"

namespace
{
   NodePtr getInternalPointer(const QModelIndex &index)
   {
      return static_cast<Node*>(index.internalPointer())->GetPtr();
   }
}

TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
    , m_rootItem{nullptr}
{
}

void TreeModel::LoadData(const QString& fileName)
{
   m_rootItem = DataBuilder::CreateXMLTree(fileName);
   SimpleModelUpdate();
}

void TreeModel::SimpleModelUpdate()
{
   beginResetModel();
   endResetModel();
}

const NodePtr TreeModel::GetNode(const QModelIndex& index) const
{
   return getInternalPointer(index);
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    return !index.isValid() || role != TreeModelRoles::XML ?
        QVariant() : getInternalPointer(index)->GetData(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    return !index.isValid() ? Qt::NoItemFlags : QAbstractItemModel::flags(index);
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent) || !m_rootItem)
    {
        return QModelIndex();
    }

    auto parentItem = !parent.isValid() ? m_rootItem : getInternalPointer(parent);
    auto childItem = parentItem->GetChild(row);
    return childItem ? createIndex(row, column, childItem.get()) : QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid() || !m_rootItem)
    {
         return QModelIndex();
    }

     auto childItem = getInternalPointer(index);
     auto parentItem = childItem->GetParentItem();
     return parentItem == m_rootItem ? QModelIndex() : createIndex(parentItem->GetRow(), 0, parentItem.get());
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0 || !m_rootItem)
    {
        return 0;
    }
    return !parent.isValid() ? m_rootItem->GetChildCount() : getInternalPointer(parent)->GetChildCount();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (!m_rootItem)
    {
        return 0;
    }
    return parent.isValid() || !m_rootItem ? getInternalPointer(parent)->GetColumnCount() : m_rootItem->GetColumnCount();
}

QHash<int, QByteArray> TreeModel::roleNames() const
{
   QHash<int, QByteArray> roles;
   roles[static_cast<int>(TreeModelRoles::XML)] = "xml";
   return roles;
}
