#pragma once
#include <QDialog>
#include "Types.h"

namespace Ui {
class NodeInfoWindow;
}

class NodeInfoWindow : public QDialog
{
   Q_OBJECT

public:
   NodeInfoWindow(const NodePtr& node, QWidget *parent = nullptr);
   ~NodeInfoWindow();

private:
   void setData();
private:
   Ui::NodeInfoWindow *ui;
   NodePtr m_node;
};

