#include "TreeModel.h"
#include "Data/DataBuilder.h"
#include <QDebug>
#include <algorithm>
#include "Windows/NodeInfoWindow.h"

namespace
{
   NodePtr getInternalPointer(const QModelIndex &index)
   {
      return static_cast<BaseNode*>(index.internalPointer())->GetPtr();
   }
}

TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
    , m_rootItem{nullptr}
{
}

void TreeModel::LoadData(const QString& fileName)
{
   qDebug() << fileName << "  " << fileName.lastIndexOf(".");
   const auto& fileType = fileName.right(fileName.length() - fileName.indexOf(".") - 1);

   if (fileType == "xml")
   {
      m_rootItem = DataBuilder::CreateXMLTree(fileName);
   }
   else if (fileType == "json")
   {
      m_rootItem = DataBuilder::CreateJSONTree(fileName);
   }
   else
   {
      qDebug() << "XMMM " << fileType;
   }

   SimpleModelUpdate();
}

QString TreeModel::GetTitle() const
{
   if (!m_rootItem)
   {
      return "";
   }
   else
   {
      return dynamic_cast<XMLNode*>(m_rootItem.get()) ? "XML" : "JSON";
   }
}

void TreeModel::ApplyFilter(const FilterPtr& filter)
{
   m_rootItem->ApplyFilter(filter);
   SimpleModelUpdate();
}

void TreeModel::ApplyFilter(const QString&)
{

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
   qDebug() << index.column() << " " << role;
    return !index.isValid() ? QVariant() : getInternalPointer(index)->GetData(role - Qt::UserRole - 1);
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
   roles[static_cast<int>(TreeModelRoles::FileType)] = "fileType";
   return roles;
}
