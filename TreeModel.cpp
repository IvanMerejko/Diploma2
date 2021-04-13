#include "TreeModel.h"
#include "DataBuilder.h"
#include <QDebug>

TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
    , m_rootItem{nullptr}
{
//    QString vale {"X:\\QTProjects\\DiplomaDebug\\debug\\file.xml"};
//    m_rootItem = DataBuilder::CreateXMLTree(vale);
//    qDebug() << "2 " << m_rootItem->GetName();
}

void TreeModel::LoadData(QStringView fileName)
{
    m_rootItem = DataBuilder::CreateXMLTree(fileName);
    beginResetModel();
    endResetModel();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
//    qDebug() << __FUNCTION__;
    return !index.isValid() || role != Qt::DisplayRole ?
                QVariant() :
                static_cast<Node*>(index.internalPointer())->GetData(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
//    qDebug() << __FUNCTION__;
    return !index.isValid() ? Qt::NoItemFlags : QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
//    qDebug() << __FUNCTION__;
    return m_rootItem && orientation == Qt::Horizontal && role == Qt::DisplayRole ?
                 m_rootItem->GetData(section) :
                 QVariant();

}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
//    qDebug() << __FUNCTION__;
    if (!hasIndex(row, column, parent) || !m_rootItem)
    {
        return QModelIndex();
    }

    auto parentItem = !parent.isValid() ? m_rootItem.get() : static_cast<Node*>(parent.internalPointer());
    auto childItem = parentItem->GetChild(row);
    return childItem ? createIndex(row, column, childItem.get()) : QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
//    qDebug() << __FUNCTION__;
    if (!index.isValid() || !m_rootItem)
    {
         return QModelIndex();
    }

     auto childItem = static_cast<Node*>(index.internalPointer());
     auto parentItem = childItem->GetParentItem();
     return parentItem == m_rootItem ? QModelIndex() : createIndex(parentItem->GetRow(), 0, parentItem.get());
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
//    qDebug() << __FUNCTION__;
    if (parent.column() > 0 || !m_rootItem)
    {
        return 0;
    }
    return !parent.isValid() ? m_rootItem->GetChildCount() : static_cast<Node*>(parent.internalPointer())->GetChildCount();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
//    qDebug() << __FUNCTION__;
    if (!m_rootItem)
    {
        return 0;
    }
    return parent.isValid() || !m_rootItem ? static_cast<Node*>(parent.internalPointer())->GetColumnCount() : m_rootItem->GetColumnCount();
}
