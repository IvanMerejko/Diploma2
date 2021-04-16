#pragma once
#include "XMLNode.h"

class DataBuilder
{
public:
   static NodePtr CreateXMLTree(QStringView);
   static NodePtr CreateJSONTree(QStringView);
};

