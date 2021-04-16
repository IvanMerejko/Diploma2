#pragma once
#include <QVariant>
#include <QEnableSharedFromThis>
#include "Types.h"
#include "BaseNode.h"

class XMLNode : public BaseNode
{
public:
    XMLNode(const NodePtr& parentItem = nullptr);

    int GetColumnCount() const noexcept override;
    QVariant GetData(int) const override;
    int GetRow() override;
};

