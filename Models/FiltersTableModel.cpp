#include "FiltersTableModel.h"
#include <Filter/Filter.h>
FiltersTableModel::FiltersTableModel()
   : m_filters{}
{

}

void FiltersTableModel::AddFilter(const QString& name, const QString& value, int searchType, int searchAction)
{
   if (const auto it = std::find_if(m_filters.begin(), m_filters.end(), [name](const auto& filter) { return filter->GetName() == name; });
       it == m_filters.end())
   {
      beginResetModel();
      m_filters.append(FilterPtr::create(name, value, searchType, searchAction));
      endResetModel();
   }
}

const FilterPtr& FiltersTableModel::GetFilter(int row) const
{
   return m_filters.at(row);
}

int FiltersTableModel::rowCount(const QModelIndex&) const
{
   return m_filters.size();
}

int FiltersTableModel::columnCount(const QModelIndex&) const
{
   return 4;
}

QVariant FiltersTableModel::data(const QModelIndex& index, int role) const
{
   if(!index.isValid())
   {
      return QVariant();
   }


   const auto& filter = m_filters.at(index.row());
   switch(static_cast<FiltersRole>(role))
   {
      case FiltersRole::Name:
         return filter->GetName();
      case FiltersRole::SearchType:
         return filter->GetSearchTypeStr();
      case FiltersRole::SearchAction:
         return filter->GetSearchActionStr();
      case FiltersRole::Value:
         return filter->GetValue();
   }
   return QVariant{};
}

QHash<int, QByteArray> FiltersTableModel::roleNames() const
{
   QHash<int, QByteArray> roles;
   roles[static_cast<int>(FiltersRole::Name)] = "name";
   roles[static_cast<int>(FiltersRole::SearchType)] = "searchType";
   roles[static_cast<int>(FiltersRole::SearchAction)] = "searchAction";
   roles[static_cast<int>(FiltersRole::Value)] = "value";
   return roles;
}

bool FiltersTableModel::removeRows(int, int, const QModelIndex&)
{
   return true;
}

bool FiltersTableModel::setData(const QModelIndex&, const QVariant&, int)
{
   return true;
}
