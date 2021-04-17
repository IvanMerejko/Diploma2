#include <QQmlContext>
#include "NodeInfoWindow.h"
#include "MainWindowQml.h"

namespace
{
   constexpr auto TreeModelStr = "treeModel";
   constexpr auto MainWindowStr = "mainWindowObject";
   constexpr auto FiltersTableModeStr = "filtersModel";
}

MainWindowQml::MainWindowQml(const QString& file)
   : m_treeModel{TreeModelPtr::create()}
   , m_filtersModel{FiltersTableModelPtr::create()}
{
   initializeRootContext();
   load(file);
   initializeWindowPtr();
   initializeElements();
}

void MainWindowQml::CreateNodeInfoWindow(const QModelIndex& index)
{
   m_displayNodeInfos.append(NodeInfoWindowPtr::create(m_treeModel->GetNode(index)));
}

void MainWindowQml::Search(const QVariant& searchKey)
{
   if (searchKey.userType() == QMetaType::Int)
   {
      const auto& filter = m_filtersModel->GetFilter(searchKey.toInt());
   }
   else if (searchKey.userType() == QMetaType::QString)
   {

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
   rootContext()->setContextProperty(FiltersTableModeStr, m_filtersModel.get());
   rootContext()->setContextProperty(MainWindowStr, this);
}

QObjectUp  MainWindowQml::getPointerForElementByName(const QString &name)
{
   return makeQObjectUP(m_mainWindow->findChild<QObject *>(name));
}

