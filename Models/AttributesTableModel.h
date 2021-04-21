#pragma once
#include <QAbstractTableModel>
#include "Types.h"

class AttributesTableModel : public QAbstractTableModel
{
   Q_OBJECT
public:
   AttributesTableModel(const NodePtr& node);
   Q_INVOKABLE bool IsItemMatchFilter(int row, int column) const;
   Q_INVOKABLE void DeleteAttribute(int row);

protected:
   int rowCount(const QModelIndex &parent = QModelIndex()) const override;
   int columnCount(const QModelIndex &parent = QModelIndex()) const override;
   QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
   QHash<int , QByteArray> roleNames() const override;
   bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;
   bool setData(const QModelIndex& index , const QVariant& value , int role) override;

private:
   NodePtr m_node;
};

using AttributesTableModelPtr = QSharedPointer<AttributesTableModel>;
