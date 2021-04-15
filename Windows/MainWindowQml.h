#pragma once
#include <QQmlApplicationEngine>
#include <QObject>
#include "NodeInfoWindow.h"
#include "Models/AttributesTableModel.h"
#include "Models/TreeModel.h"
#include "Types.h"


class MainWindowQml : public QQmlApplicationEngine
{
   Q_OBJECT
public:
   MainWindowQml(const QString& file);

public:
   Q_INVOKABLE void CreateNodeInfoWindow(const QModelIndex&);
private:
   void initializeWindowPtr();
   void initializeElements();
   void initializeRootContext();
   QObjectUp getPointerForElementByName(const QString &name);

private:
    TreeModelPtr m_treeModel;
    QObjectUp m_mainWindow;
    QVector<NodeInfoWindowPtr> m_displayNodeInfos;
};
