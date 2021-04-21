#pragma once

#include <QAbstractTableModel>
#include "Data/BaseNode.h"
class FilterResultTableModel : public QAbstractTableModel
{
   Q_OBJECT
public:
   FilterResultTableModel() = default;
public slots:
   void addNode(const NodePtr&);
   void filteringStarted();
   void filteringFinished();
   void connectWithNodes(const NodePtr&);
private:
   enum class Role
   {
      Result = Qt::UserRole + 1
   };
protected:
   int rowCount(const QModelIndex &parent = QModelIndex()) const override;
   int columnCount(const QModelIndex &parent = QModelIndex()) const override;
   QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
   QHash<int , QByteArray> roleNames() const override;

private:
   Nodes m_nodes;
};

using FilterResultTableModelPtr = QSharedPointer<FilterResultTableModel>;

