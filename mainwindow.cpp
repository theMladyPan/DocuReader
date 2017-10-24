#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete search_phrase;
    delete q_directory;
    delete filename;
    delete file;
}

void MainWindow::on_actionSearch_triggered()
{
    *search_phrase = QInputDialog::getText(this, tr("Input phrase"),
                                             tr("Search phrase: "), QLineEdit::Normal);
    ui->statusBar->showMessage(tr("Search phrase: ")+*search_phrase);
}

void MainWindow::on_actionOpen_directory_triggered()
{
    *q_directory = QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Open path..."), QDir::currentPath()));
    ui->statusBar->showMessage(tr("Working directory: ") + *q_directory);
}

std::vector<QString> MainWindow::get_files(QString *dir){
    QDir *q_dir = new QDir();
    *q_dir = QDir(*dir);
    if(q_dir->isReadable()){
        return q_dir->entryList().toVector().toStdVector();
    }
    else{
        throw(QFile::OpenError);
        return std::vector<QString>();
    }
}

void MainWindow::on_actionStart_triggered()
{
    std::vector<QString> files = get_files(q_directory);
    QStringList string_list;

    if(files.end()-files.begin()>0){
        ui->progressBar->setMaximum(files.end()-files.begin());
    }

    //iterate through files
    for(std::vector<QString>::iterator it = files.begin();it != files.end();it++){
        filename->clear();
        filename->append(q_directory).append("/").append(*it);
        ui->statusBar->showMessage(tr("Processing file: ")+*it);
        file->setFileName(*filename);
        file->open(QIODevice::ReadOnly);

        ui->progressBar->setValue(it-files.begin());

        QTextStream in(file);
        while(!in.atEnd()) { //read whole file
            QString line = in.readLine();
            if(line.contains(*search_phrase)){ //found phrase
                string_list.append(*it+QString().fromStdString(":  ")+line);
                break;
            }
        }
        file->close();
    }

    QAbstractItemModel *model = new QStringListModel(string_list);
    ui->listView->setModel(model);
    delete(file);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(100);
}

void MainWindow::on_actionExit_triggered()
{
    qApp->closeAllWindows();
}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    QProcess *process = new QProcess(this);

    QString temp;
    temp.append(DOCUMENT_READER);
    temp.append(q_directory);
    temp.append("/");
    temp.append(index.data().toString().toStdString().substr(0,(index.data().toString().toStdString().find(".pdf")+4)).c_str());
    //file ends in
    ui->statusBar->showMessage(QString(tr("Invoking: "))+temp);
    process->start(temp);
}

void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    MainWindow::on_listView_doubleClicked(index);
}
