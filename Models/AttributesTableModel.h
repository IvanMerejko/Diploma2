#pragma once
#include <QAbstractTableModel>
#include "Types.h"
#include "TreeModel.h"

class AttributesTableModel : public QAbstractTableModel
{
   Q_OBJECT
public:
   AttributesTableModel(const NodePtr& node, const TreeModelPtr& treeModel);
   void UpdateModel();
   Q_INVOKABLE bool IsItemMatchFilter(int row, int column) const;
   Q_INVOKABLE void DeleteAttribute(int row);
   Q_INVOKABLE void OnAttributeValueChanged(int row, const QString& value);
   Q_INVOKABLE void OnAttributeNameChanged(int row, const QString& name);
   Q_INVOKABLE void CreateNewAttribute();
protected:
   int rowCount(const QModelIndex &parent = QModelIndex()) const override;
   int columnCount(const QModelIndex &parent = QModelIndex()) const override;
   QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
   QHash<int , QByteArray> roleNames() const override;

private:
   NodePtr m_node;
   TreeModelPtr m_treeModel;
};

using AttributesTableModelPtr = QSharedPointer<AttributesTableModel>;
