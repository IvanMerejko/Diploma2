#pragma once
#include <QAbstractTableModel>
#include "Types.h"

class ActionsTableModel : public QAbstractTableModel
{
   Q_OBJECT
private:
   enum class Role
   {
      ActionName = Qt::UserRole + 1,
      ActionType,
      Name,
      Value
   };

public:
   ActionsTableModel();
   ~ActionsTableModel();
   Q_INVOKABLE void DeleteAction(int row);
   Q_INVOKABLE void AddAction(const QString& actionName, int actionType, const QString& name, const QString& value);
   Q_INVOKABLE QVariantList GetActionsName() const noexcept;
   const ActionPtr& GetAction(int) const;
   const ActionPtr GetActionByName(const QString& actionName) const;

protected:
   int rowCount(const QModelIndex &parent = QModelIndex()) const override;
   int columnCount(const QModelIndex &parent = QModelIndex()) const override;
   QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
   QHash<int , QByteArray> roleNames() const override;
private:
   void saveToFile();
   void readFromFile();
   const ActionPtr findAction(const QString&) const noexcept;
private:
   Actions m_actions;
};

using ActionsTableModelPtr = QSharedPointer<ActionsTableModel>;
