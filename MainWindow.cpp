#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "DataBuilder.h"
#include <QPushButton>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_treeModel{new TreeModel}
{
    ui->setupUi(this);
    ui->treeView->setModel(m_treeModel);

    connect(ui->loadFile, &QPushButton::clicked, this, &MainWindow::loadFile);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_treeModel;
}

void MainWindow::loadFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Address Book"), "",
        tr("All Files (*)"));
    m_treeModel->LoadData(fileName);
}

