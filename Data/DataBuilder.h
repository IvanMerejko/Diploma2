#pragma once
#include "XMLNode.h"
#include "Models/TreeModel.h"

class DataBuilder
{
public:
   static NodePtr CreateXMLTree(QStringView, const TreeModelPtr&);
   static NodePtr CreateJSONTree(QStringView, const TreeModelPtr&);
   static void SaveXMLTree(const NodePtr&, const QString&);
};

