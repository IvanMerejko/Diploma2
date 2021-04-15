#pragma once
#include "Node.h"

class DataBuilder
{
public:
   static NodePtr CreateXMLTree(QStringView);
   static NodePtr CreateJSONTree(QStringView);
};

