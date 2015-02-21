#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtCUrl.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QtCUrl cUrl;
    cUrl.setTextCodec("UTF-8");

    QUrl url("http://localhost:2737/listPairs");

    QtCUrl::Options opt;
    opt[CURLOPT_URL] = url;
   // opt[CURLOPT_POST] = true;
  //  opt[CURLOPT_FOLLOWLOCATION] = true;
    //opt[CURLOPT_FAILONERROR] = true;

    QString result = cUrl.exec(opt);

    if (cUrl.lastError().isOk()) {
        qDebug() << result;
    }
    else {
        qDebug() << QString("Error: %1\nBuffer: %2")
                .arg(cUrl.lastError().text()).arg(cUrl.errorBuffer());
    }
    ui->textEdit->setPlainText(result);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{


}

void MainWindow::on_textEdit_textChanged()
{

}
