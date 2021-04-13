#include "TreeModel.h"


TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{

}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    return !index.isValid() || role != Qt::DisplayRole ?
                QVariant() :
                static_cast<Node*>(index.internalPointer())->GetData(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    return !index.isValid() ? Qt::NoItemFlags : QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return orientation == Qt::Horizontal && role == Qt::DisplayRole ?
                 m_rootItem->GetData(section) :
                 QVariant();

}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    auto parentItem = !parent.isValid() ? m_rootItem : NodePtr::create(static_cast<Node*>(parent.internalPointer()));
    auto childItem = parentItem->GetChild(row);
    return childItem ? createIndex(row, column, childItem.get()) : QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
    {
         return QModelIndex();
    }

     auto childItem = NodePtr::create(static_cast<Node*>(index.internalPointer()));
     auto parentItem = childItem->GetParentItem();
     return parentItem == m_rootItem ? QModelIndex() : createIndex(parentItem->GetRow(), 0, parentItem.get());
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
    {
        return 0;
    }
    return !parent.isValid() ? m_rootItem->GetChildCount() : static_cast<Node*>(parent.internalPointer())->GetChildCount();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? static_cast<Node*>(parent.internalPointer())->GetColumnCount() : m_rootItem->GetColumnCount();
}
