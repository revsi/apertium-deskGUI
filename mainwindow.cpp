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
    opt[CURLOPT_POST] = false;
    opt[CURLOPT_FOLLOWLOCATION] = false;
    opt[CURLOPT_FAILONERROR] = false;
    opt[CURLOPT_NOPROXY] = "localhost";
   QStringList headers;
    headers
        << "Accept  text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8"
        << "Accept-Encoding gzip, deflate"
        << "Accept-Language ru-RU,ru;q=0.8,en-US;q=0.5,en;q=0.3"
        << "User-Agent  Mozilla/5.0 (X11; Linux x86_64; rv:20.0) Gecko/20100101 Firefox/20.0";
    opt[CURLOPT_HTTPHEADER] = headers;
    QString result = cUrl.exec(opt);

    if (cUrl.lastError().isOk()) {
       // qDebug() << result;
    }
    else {
        qDebug() << QString("Error: %1\nBuffer: %2")
                .arg(cUrl.lastError().text()).arg(cUrl.errorBuffer());
    }
    QRegExp re("\"([a-z_\\./\\-\\s]*)\"");
    QStringList list;
    int pos=0;
    while((pos=re.indexIn(result, pos))!=-1)
    {
           list << re.cap(1);
           pos+=re.matchedLength();
    }

    for(int i=0; i<list.length(); i++)
    {
        qDebug() << list[i];
        qDebug() << "==============";
    }

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
