#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

#ifndef __STRING__
#define __STRING__
#include <string>
#endif

#ifndef __IOSTREAM__
#define __IOSTREAM__
#include <iostream>
#endif

#ifndef __VECTOR__
#define __VECTOR__
#include <vector>
#endif

#ifndef __QFILE__
#define __QFILE__
#include <QFile>
#endif

#ifndef __QFILEDIALOG__
#define __QFILEDIALOG__
#include "QFileDialog"
#endif

#ifndef __QINPUTDIALOG__
#define __QINPUTDIALOG__
#include "QInputDialog"
#endif

#ifndef __QTEXTSTREAM__
#define __QTEXTSTREAM__
#include <QTextStream>
#endif

#ifndef __QSTRINGLISTMODEL__
#define __QSTRINGLISTMODEL__
#include <QStringListModel>
#endif

#ifndef __QABSTRACTITEMMODEL__
#define __QABSTRACTITEMMODEL__
#include <QAbstractItemModel>
#endif

#ifndef __QPROCESS__
#define __QPROCESS__
#include <QProcess>
#endif

#define DOCUMENT_READER "/usr/bin/evince "

  namespace Ui {
  class MainWindow;
  }

  class MainWindow : public QMainWindow
  {
      Q_OBJECT

  public:
      explicit MainWindow(QWidget *parent = 0);
      ~MainWindow();

  private slots:
      void on_actionSearch_triggered();

      void on_actionOpen_directory_triggered();

      void on_actionStart_triggered();

      void on_actionExit_triggered();

      void on_listView_doubleClicked(const QModelIndex &index);

      void on_listView_clicked(const QModelIndex &index);

  private:
      Ui::MainWindow *ui;
      QString *search_phrase = new QString();
      QString *q_directory = new QString();
      QString *filename = new QString();
      QFile *file = new QFile();
      std::vector<QString> get_files(QString *q_directory);
  };

  #endif // MAINWINDOW_H
