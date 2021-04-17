#pragma once
#include <QAbstractItemModel>
#include <QModelIndex>
#include "Filter/Filter.h"
#include "Types.h"

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
private:
   enum TreeModelRoles
   {
       FileType = Qt::UserRole + 1
   };
public:
    TreeModel(QObject *parent = nullptr);

    Q_INVOKABLE void LoadData(const QString& fileName);
    Q_INVOKABLE QString GetTitle() const;

    void ApplyFilter(const FilterPtr&);
    void ApplyFilter(const QString&);

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

using TreeModelPtr = QSharedPointer<TreeModel>;

