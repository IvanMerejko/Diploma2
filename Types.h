#pragma once
#include <QSharedPointer>
#include <QVector>

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

using NodePtr = QSharedPointer<class Node>;
using Nodes = QVector<NodePtr>;

enum class AttributeType
{
   Name = 0,
   Value
};
using Attribute = QPair<QString, QString>;
using Attributes = QVector<Attribute>;
