#include "TreeModel.h"
#include "Data/DataBuilder.h"
#include <QDebug>
#include <algorithm>
#include "Windows/NodeInfoWindow.h"
#include "Executors/Rule.h"
#include "Executors/BaseFilter.h"

namespace
{
   NodePtr getInternalPointer(const QModelIndex &index)
   {
      return static_cast<BaseNode*>(index.internalPointer())->GetPtr();
   }

   bool isNodeMatchFilter(const NodePtr& node, int& currentRowIndex, int neededRowIndex)
   {
      bool isMatch = false;
      if (currentRowIndex == neededRowIndex)
      {
         return node->IsMatchFilter();
      }
      else
      {
         for (const auto& child : node->GetChilds())
         {
            ++currentRowIndex;
            if (isMatch |= isNodeMatchFilter(child, currentRowIndex, neededRowIndex);
                isMatch)
            {
               break;
            }
         }
      }
      return isMatch;
   }
}

void TreeModel::onDataChanged()
{
   beginResetModel();
   endResetModel();
}

TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
    , m_rootItem{nullptr}
{
}

void TreeModel::LoadData(const QString& fileName)
{
   beginResetModel();
   m_rootItem.reset();
   const auto& fileType = fileName.right(fileName.length() - fileName.indexOf(".") - 1);
   m_fileName = fileName;

   if (fileType == "xml")
   {
      m_rootItem = DataBuilder::CreateXMLTree(fileName, sharedFromThis());
   }
   else if (fileType == "json")
   {
      m_rootItem = DataBuilder::CreateJSONTree(fileName, sharedFromThis());
   }
   else
   {
      qDebug() << "XMMM " << fileType;
   }
   if (m_rootItem)
   {
      onNodesReload(m_rootItem);
   }
   endResetModel();
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

bool TreeModel::IsRowMathFilter(int row) const
{
   int currentNodeIndex = 0;

   return row != -1 && m_rootItem && m_rootItem->GetChilds().size() == 1 && isNodeMatchFilter(m_rootItem->GetChilds()[0], currentNodeIndex, row);
}

void TreeModel::Save()
{
   DataBuilder::SaveXMLTree(m_rootItem, m_fileName);
}

void TreeModel::ApplyFilter(const FilterPtr& filter)
{
   if (!m_rootItem)
   {
      return;
   }
   onFilteringStarted();
   filter->ApplyFilter(m_rootItem);
   onFilteringFinished();
   SimpleModelUpdate();
}

void TreeModel::ApplyFilter(const QString& key)
{
   if (!m_rootItem)
   {
      return;
   }
   onFilteringStarted();
   m_rootItem->ApplyFilter(key);
   onFilteringFinished();
   SimpleModelUpdate();
}

void TreeModel::ApplyRule(const RulePtr& rule)
{
   if (!m_rootItem)
   {
      return;
   }
   onFilteringStarted();
   rule->ApplyRule(m_rootItem);
   onFilteringFinished();
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

QVariant TreeModel::data(const QModelIndex &index, int) const
{
    return !index.isValid() ? QVariant() : getInternalPointer(index)->GetData();
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
