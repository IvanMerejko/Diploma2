#pragma once
#include <QSharedPointer>
#include <QVector>

using NodePtr = QSharedPointer<class Node>;
using Nodes = QVector<NodePtr>;
using Attribute = QPair<QString, QString>;
using Attributes = QVector<Attribute>;
