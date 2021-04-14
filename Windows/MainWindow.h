#pragma once

#include <QMainWindow>
#include <QShortcut>
#include "TreeModel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
   void loadFile();
   void onRowSelected(const QModelIndex&);
   void findWindow();
private:
   void setTreeView();
   void createShortcurs();
   void connectAllSlots();

private:
    Ui::MainWindow *ui;
    TreeModel m_treeModel;
    QShortcut* m_keyFind;
};
