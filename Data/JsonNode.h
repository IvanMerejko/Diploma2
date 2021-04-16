#pragma once
#include "BaseNode.h"

class JsonNode : public BaseNode
{
public:
   JsonNode(JsonNodeType, const NodePtr& parentItem = nullptr);

   int GetColumnCount() const noexcept override;
   QVariant GetData(int) const override;
   int GetRow() override;
   void SetJsonNodeType(JsonNodeType) override;
};

