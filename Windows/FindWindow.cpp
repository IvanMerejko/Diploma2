#include "FindWindow.h"
#include "ui_FindWindow.h"

FindWindow::FindWindow(QWidget *parent)
   : QWidget(parent)
   , ui(new Ui::FindWindow)
{
   ui->setupUi(this);
}

FindWindow::~FindWindow()
{
   delete ui;
}
