#include "FiltersTableModel.h"
#include "Executors/Parser.h"
#include "Executors/Filter.h"
#include "Executors/CompoundFilter.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>

FiltersTableModel::FiltersTableModel()
   : m_filters{}
{
   readFromFile();
}

FiltersTableModel::~FiltersTableModel()
{
   saveToFile();
}

void FiltersTableModel::AddFilter(const QString& name, const QString& value, int searchType, int searchAction)
{
   if (!findFilter(name))
   {
      beginResetModel();
      if (const auto searchTypeEnum = static_cast<SearchType>(searchType);
          searchTypeEnum == SearchType::Compound)
      {
         if (const auto filter = Parser::ParseExpression(name, value.toStdString(),  m_filters))
         {
            m_filters.append(filter);
         }
      }
      else
      {
         m_filters.append(QSharedPointer<Filter>::create(name, value, static_cast<SearchType>(searchType), static_cast<SearchAction>(searchAction)));
      }
      endResetModel();
   }
}

void FiltersTableModel::DeleteFilter(int row)
{
   beginResetModel();
   m_filters.erase(std::remove(m_filters.begin(), m_filters.end(), m_filters[row]), m_filters.end());
   endResetModel();
}

const FilterPtr& FiltersTableModel::GetFilter(int row) const
{
   return m_filters.at(row);
}

const FilterPtr FiltersTableModel::GetFilterByName(const QString& name) const
{
   return findFilter(name);
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

void FiltersTableModel::saveToFile()
{
   QFile outfile("Filters.txt");
   outfile.open(QIODevice::WriteOnly | QIODevice::Text);
   QTextStream writeStream(&outfile);
   for (const auto& filter : m_filters)
   {
      writeStream << filter->GetName() << "\\_/"
              << filter->GetValue() << "\\_/"
              << static_cast<int>(filter->GetSearchType()) << "\\_/"
              << static_cast<int>(filter->GetSearchAction()) << '\n';
   }
   outfile.close();
}

void FiltersTableModel::readFromFile()
{
   QFile infile("Filters.txt");
   infile.open(QIODevice::ReadOnly);
   QTextStream in(&infile);
   while (!in.atEnd())
   {
      QString line = in.readLine();
      auto pieces = line.split(  "\\_/" );
      const auto searchType = static_cast<SearchType>(pieces[2].toInt());
      if (searchType == SearchType::Compound)
      {
         m_filters.append(Parser::ParseExpression(pieces[0], pieces[1].toStdString(),  m_filters));
      }
      else
      {
         m_filters.append(QSharedPointer<Filter>::create(pieces[0],
            pieces[1], searchType, static_cast<SearchAction>(pieces[3].toInt())));
      }
   }
   infile.close();
}

const FilterPtr FiltersTableModel::findFilter(const QString& filterName) const noexcept
{
   const auto it = std::find_if(m_filters.begin(), m_filters.end(), [filterName](const auto& filter) { return filter->GetName() == filterName; });
   return it == m_filters.end() ? nullptr : *it;
}
