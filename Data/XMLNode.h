#pragma once
#include <QVariant>
#include <QEnableSharedFromThis>
#include "Types.h"
#include "BaseNode.h"

class XMLNode : public BaseNode
{
   Q_OBJECT
public:
    XMLNode(const NodePtr& parentItem = nullptr);

    int GetColumnCount() const noexcept override;
    QVariant GetData() const override;
    int GetRow() override;
};

