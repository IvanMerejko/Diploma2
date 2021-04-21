#pragma once
#include <QAbstractItemModel>
#include <QModelIndex>
#include "Filter/Filter.h"
#include "Data/BaseNode.h"
#include "Types.h"

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
private:
   enum TreeModelRoles
   {
       FileType = Qt::UserRole + 1
   };
signals:
   void onNodesReload(const NodePtr);
   void onFilteringStarted();
   void onFilteringFinished();
public:
    TreeModel(QObject *parent = nullptr);

    Q_INVOKABLE void LoadData(const QString& fileName);
    Q_INVOKABLE QString GetTitle() const;
    Q_INVOKABLE bool IsRowMathFilter(int row) const;

    template <typename FilterT>
    void ApplyFilter(const FilterT&);

    void SimpleModelUpdate();
    const NodePtr GetNode(const QModelIndex &index) const;
protected:
    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    void setupModelData(const QStringList &lines, NodePtr parent);

    NodePtr m_rootItem;
};

template <typename FilterT>
void TreeModel::ApplyFilter(const FilterT& key)
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

using TreeModelPtr = QSharedPointer<TreeModel>;

