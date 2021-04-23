#include "NodeInfoWindow.h"
#include <QQmlContext>
#include "Executors/Filter.h"
#include "Data/XMLNode.h"
namespace
{
   constexpr auto AttributesModeStr = "attributtesModel";
   constexpr auto NodeInfoWindowStr = "nodeInfoWindowObject";
   constexpr auto NameFieldStr = "nameField";
   constexpr auto ValueFieldStr = "valueField";
}

NodeInfoWindow::NodeInfoWindow(const NodePtr& node)
   : m_node{node}
   , m_attributesModel{AttributesTableModelPtr::create(m_node)}
{
   initializeRootContext();
   load("qrc:/NodeInfoWindow.qml");
   initializeWindowPtr();
   initializeElements();
   createConnectionWithQmlObjects();
}

bool NodeInfoWindow::IsNameMatchFilter() const
{
   return m_node->IsMatchFilter() &&
         (m_node->GetMatchType() == SearchType::Name ||
          m_node->GetMatchType() == SearchType::BothNodeTypes);
}

bool NodeInfoWindow::IsValueMatchFilter() const
{
   return m_node->IsMatchFilter() &&
         (m_node->GetMatchType() == SearchType::Value ||
         m_node->GetMatchType() == SearchType::BothNodeTypes);
}

void NodeInfoWindow::onNameChanged()
{
   m_node->SetName(m_nameField->property("text").toString());
}

void NodeInfoWindow::onValueChanged()
{
   m_node->SetValue(m_valueField->property("text").toString());
}

void NodeInfoWindow::initializeRootContext()
{
   rootContext()->setContextProperty(AttributesModeStr, m_attributesModel.get());
   rootContext()->setContextProperty(NodeInfoWindowStr, this);
}

void NodeInfoWindow::initializeElements()
{
   m_nameField = getPointerForElementByName(NameFieldStr);
   if (m_nameField)
   {
      m_nameField->setProperty("text", m_node->GetName());
   }
   m_valueField = getPointerForElementByName(ValueFieldStr);
   if (m_valueField)
   {
      m_valueField->setProperty("text", m_node->GetValue());
   }
}

void NodeInfoWindow::initializeWindowPtr()
{
   auto list = rootObjects();
   auto window = std::find_if(list.begin() , list.end() , [](const QObject* object)
   {
      return  object->objectName() == "nodeInfoWindow";
   });
   if(window != list.end())
   {
       m_window = makeQObjectUP(*window);
   }
}

void NodeInfoWindow::createConnectionWithQmlObjects()
{
   connect(m_nameField.get(), SIGNAL(editingFinished()), this, SLOT(onNameChanged()));
   connect(m_valueField.get(), SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
}

QObjectUp NodeInfoWindow::getPointerForElementByName(const QString& name)
{
   return makeQObjectUP(m_window->findChild<QObject *>(name));
}
