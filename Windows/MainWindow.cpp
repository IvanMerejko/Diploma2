#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "DataBuilder.h"
#include "Windows/NodeInfoWindow.h"
#include <QPushButton>
#include <QFileDialog>
#include <QAbstractItemView>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_treeModel{}
{
   ui->setupUi(this);
   setTreeView();
   createShortcurs();
   connectAllSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Address Book"), "",
        tr("All Files (*)"));
    m_treeModel.LoadData(fileName);
}

void MainWindow::onRowSelected(const QModelIndex &index)
{

   NodeInfoWindow window(m_treeModel.GetNode(index), this);
   window.setModal(true);
   window.exec();
}

void MainWindow::findWindow()
{
   qDebug() << "findWindow";
}

void MainWindow::setTreeView()
{
   ui->treeView->setModel(&m_treeModel);
   ui->treeView->header()->hide();
//   ui->treeView->setStyleSheet("QTreeView::item{ background-color: rgb(150, 180, 220) }");
//   ui->treeView->setStyleSheet("border: 1px solid black;"
   //                               "background-color: yellow;");
}

void MainWindow::createShortcurs()
{
   m_keyFind = new QShortcut(this);
   m_keyFind->setKey(Qt::Key_F1);
}

void MainWindow::connectAllSlots()
{
   connect(ui->loadFile, &QPushButton::clicked, this, &MainWindow::loadFile);
   connect(ui->treeView, &QAbstractItemView::doubleClicked, this, &MainWindow::onRowSelected);
   connect(m_keyFind, &QShortcut::activated, this, &MainWindow::findWindow);
}


