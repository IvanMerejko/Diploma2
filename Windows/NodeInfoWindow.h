#pragma once
#include <QQmlApplicationEngine>
#include <QObject>
#include "Models/AttributesTableModel.h"
#include "Types.h"

class NodeInfoWindow : public QQmlApplicationEngine
{
   Q_OBJECT
public:
   NodeInfoWindow(const NodePtr&);
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
};

using NodeInfoWindowPtr = QSharedPointer<NodeInfoWindow>;
