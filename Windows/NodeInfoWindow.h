#pragma once
#include <QQmlApplicationEngine>
#include <QObject>
#include "Models/AttributesTableModel.h"
#include "Types.h"

class NodeInfoWindow : public QQmlApplicationEngine
{
   Q_OBJECT
public:
   NodeInfoWindow(const NodePtr&, const TreeModelPtr& treeModel);
   Q_INVOKABLE bool IsNameMatchFilter() const;
   Q_INVOKABLE bool IsValueMatchFilter() const;
   void OnFiltering();
public slots:
   void onNameChanged();
   void onValueChanged();
private:
   void initializeRootContext();
   void initializeElements();
   void initializeWindowPtr();
   void createConnectionWithQmlObjects();
   QObjectUp getPointerForElementByName(const QString &name);
private:
   NodePtr m_node;
   QObjectUp m_window;
   QObjectUp m_nameField;
   QObjectUp m_valueField;
   AttributesTableModelPtr m_attributesModel;
   TreeModelPtr m_treeModel;
};

using NodeInfoWindowPtr = QSharedPointer<NodeInfoWindow>;
