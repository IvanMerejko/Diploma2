#pragma once
#include "BaseNode.h"

class JsonNode : public BaseNode
{
   Q_OBJECT
public:
   JsonNode(JsonNodeType, const NodePtr& parentItem = nullptr);

   int GetColumnCount() const noexcept override;
   QVariant GetData() const override;
   int GetRow() override;
   void SetJsonNodeType(JsonNodeType) override;
};

