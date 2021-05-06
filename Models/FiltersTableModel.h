#pragma once
#include <Executors/Filter.h>
#include <QAbstractTableModel>
class FiltersTableModel : public QAbstractTableModel
{
   Q_OBJECT
private:
   enum class FiltersRole
   {
      Name = Qt::UserRole + 1,
      SearchType,
      SearchAction,
      Value
   };
public:
   FiltersTableModel();
   ~FiltersTableModel();
   Q_INVOKABLE QString AddFilter(const QString& name, const QString& value, int searchType, int searchAction);
   Q_INVOKABLE void DeleteFilter(int row);
   Q_INVOKABLE QVariantList GetFiltersName() const noexcept;
   const FilterPtr& GetFilter(int) const;
   const FilterPtr GetFilterByName(const QString& name) const;

protected:
   int rowCount(const QModelIndex &parent = QModelIndex()) const override;
   int columnCount(const QModelIndex &parent = QModelIndex()) const override;
   QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
   QHash<int , QByteArray> roleNames() const override;

private:
   void saveToFile();
   void readFromFile();
   const FilterPtr findFilter(const QString& filterName) const noexcept;

private:
   Filters m_filters;
};

using FiltersTableModelPtr = QSharedPointer<FiltersTableModel>;
