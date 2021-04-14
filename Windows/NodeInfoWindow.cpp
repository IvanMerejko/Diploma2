#include "NodeInfoWindow.h"
#include "ui_NodeInfoWindow.h"
#include <Node.h>

NodeInfoWindow::NodeInfoWindow(const NodePtr& node, QWidget *parent)
   : QDialog(parent)
   , ui(new Ui::NodeInfoWindow)
   , m_node{node}
{
   ui->setupUi(this);
   setData();
}

NodeInfoWindow::~NodeInfoWindow()
{
   delete ui;
}

void NodeInfoWindow::setData()
{
   ui->lineEditName->setText(m_node->GetName());
   ui->lineEditName->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);

   ui->lineEditValue->setText(m_node->GetValue());
   ui->lineEditValue->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);

   ui->labelName->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
   ui->labelValue->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
}
