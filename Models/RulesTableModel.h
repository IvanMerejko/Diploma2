#include "Types.h"
#include "FiltersTableModel.h"
#include "ActionsTableModel.h"
class RulesTableModel: public QAbstractTableModel
{
   Q_OBJECT
private:
   enum class Role
   {
      RuleName = Qt::UserRole + 1,
      FilterName,
      ActionName
   };

public:
   RulesTableModel(const ActionsTableModelPtr&, const FiltersTableModelPtr&);
   ~RulesTableModel();
   Q_INVOKABLE void AddRule(const QString& ruleName, int filterIndex, int actionIndex);
   Q_INVOKABLE void DeleteRule(int row);
   const RulePtr& GetRule(int) const noexcept;

protected:
   int rowCount(const QModelIndex &parent = QModelIndex()) const override;
   int columnCount(const QModelIndex &parent = QModelIndex()) const override;
   QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
   QHash<int , QByteArray> roleNames() const override;

private:
   void saveToFile();
   void readFromFile();

private:
   Rules m_rules;
   ActionsTableModelPtr m_actions;
   FiltersTableModelPtr m_filters;
};

using RulesTableModelPtr = QSharedPointer<RulesTableModel>;
