#pragma once
#include <QSharedPointer>
#include <QVector>
#include <optional>

struct QObjectDeleter
{
    void operator()(QObject *object)
    {
        object->deleteLater();
    }
};

using QObjectUp = std::unique_ptr<QObject, QObjectDeleter>;

template<typename ...Args>
QObjectUp makeQObjectUP(Args&&... value)
{
    QObjectDeleter deleter;
    return std::unique_ptr<QObject, decltype(deleter)>(std::forward<Args>(value)..., deleter);
}

using NodePtr = QSharedPointer<class BaseNode>;
using Nodes = QVector<NodePtr>;
using AttributePtr = QSharedPointer<class Attribute>;
using Attributes = QVector<AttributePtr>;
using FilterPtr = QSharedPointer<class BaseFilter>;
using Filters =  QVector<FilterPtr>;
using CompoundFilterNodePtr = QSharedPointer<struct CompoundFilterNode>;
using ActionPtr = QSharedPointer<class Action>;
using Actions = QVector<ActionPtr>;
using RulePtr = QSharedPointer<class Rule>;
using Rules = QVector<RulePtr>;

enum class SearchType
{
   Name = 0,
   Value,
   AttributeName,
   AttributeValue,
   Compound,
   BothAttributeTypes,
   BothNodeTypes,
   Unknown
};

enum class SearchAction
{
   Equal = 0,
   NotEqual,
   Contains,
   NotContains,
   Unknown
};

enum class AttributeType
{
   Name = 0,
   Value
};
enum class JsonNodeType
{
   Undefind = 0,
   Value,
   Object,
   Array
};

enum class ActionType
{
   DeleteNode,
   DeleteAttribute,
   ModifyAttributeName,
   ModifyAttributeValue,
   ModifyNodeName,
   ModifyNodeValue,
   AddAttribute
};

