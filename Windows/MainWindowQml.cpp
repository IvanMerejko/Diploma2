#include <QQmlContext>
#include "NodeInfoWindow.h"
#include "Filter/Parser.h"
#include "MainWindowQml.h"

namespace
{
   constexpr auto TreeModelStr = "treeModel";
   constexpr auto MainWindowStr = "mainWindowObject";
   constexpr auto FiltersTableModelStr = "filtersModel";
   constexpr auto FilterResultTableModelStr = "filterResultModel";
}

MainWindowQml::MainWindowQml(const QString& file)
   : m_treeModel{TreeModelPtr::create()}
   , m_filtersModel{FiltersTableModelPtr::create()}
   , m_filterResultModel{FilterResultTableModelPtr::create()}
{
   initializeRootContext();
   load(file);
   initializeWindowPtr();
   initializeElements();
   createConnections();
}

void MainWindowQml::CreateNodeInfoWindow(const QModelIndex& index)
{
   m_displayNodeInfos.append(NodeInfoWindowPtr::create(m_treeModel->GetNode(index)));
}

void MainWindowQml::Search(const QVariant& searchKey)
{
   if (searchKey.userType() == QMetaType::Int)
   {
      m_treeModel->ApplyFilter(m_filtersModel->GetFilter(searchKey.toInt()));
   }
   else if (searchKey.userType() == QMetaType::QString)
   {
      m_treeModel->ApplyFilter(searchKey.toString());
   }
}

void MainWindowQml::initializeWindowPtr()
{
   auto list = rootObjects();
   auto window = std::find_if(list.begin() , list.end() , [](const QObject* object)
   {
      return  object->objectName() == "window";
   });
   if(window != list.end())
   {
       m_mainWindow = makeQObjectUP(*window);
   }
}

void MainWindowQml::initializeElements()
{
}

void MainWindowQml::initializeRootContext()
{
   rootContext()->setContextProperty(TreeModelStr, m_treeModel.get());
   rootContext()->setContextProperty(FiltersTableModelStr, m_filtersModel.get());
   rootContext()->setContextProperty(FilterResultTableModelStr, m_filterResultModel.get());
   rootContext()->setContextProperty(MainWindowStr, this);
}

void MainWindowQml::createConnections()
{
   connect(m_treeModel.get(), &TreeModel::onNodesReload, m_filterResultModel.get(), &FilterResultTableModel::connectWithNodes);
   connect(m_treeModel.get(), &TreeModel::onFilteringStarted, m_filterResultModel.get(), &FilterResultTableModel::filteringStarted);
   connect(m_treeModel.get(), &TreeModel::onFilteringFinished, m_filterResultModel.get(), &FilterResultTableModel::filteringFinished);
}

QObjectUp  MainWindowQml::getPointerForElementByName(const QString &name)
{
   return makeQObjectUP(m_mainWindow->findChild<QObject *>(name));
}

