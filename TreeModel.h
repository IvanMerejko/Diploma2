#pragma once
#include <QAbstractItemModel>
#include <QModelIndex>
#include "Node.h"

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    TreeModel(QObject *parent = nullptr);

    void LoadData(QStringView fileName);
    void SimpleModelUpdate();

    const NodePtr GetNode(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

private:
    void setupModelData(const QStringList &lines, NodePtr parent);

    NodePtr m_rootItem;
};

