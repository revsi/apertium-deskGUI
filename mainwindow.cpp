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
    QString result = cUrl.exec(opt);

    if (cUrl.lastError().isOk()) {
       // qDebug() << result;
    }
    else {
        qDebug() << QString("Error: %1\nBuffer: %2")
                .arg(cUrl.lastError().text()).arg(cUrl.errorBuffer());
    }
   //qDebug() << result;
    QRegExp re("\"([a-z_\\./\\-\\s]*)\"");
    QStringList list;
    int pos=0;
    while((pos=re.indexIn(result, pos))!=-1)
    {
           list << re.cap(1);
           pos+=re.matchedLength();
    }
    QStringList pairs;
    QString temp;
  //  qDebug() << list;
    int listno = list.length()/2;
    for(int i=0,j=0; i<listno;j=j+2, i++)
    {
        temp = list[j+1]+"|"+list[j];
       // qDebug() << QString("%1").arg(temp);
        pairs << temp;
    }
    for(int i = 0; i < listno; i++)
    {
            ui->comboBox->addItem(pairs[i],QVariant::fromValue(pairs[i]));
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString targetpair =  ui->comboBox->currentText();
    //http://localhost:2737/translate?langpair=kaz|tat&q=Сен+бардың+ба?

    QtCUrl cUrl;
    cUrl.setTextCodec("UTF-8");
    QString text = ui->textEdit->toPlainText();
    QUrl url("http://localhost:2737/translate?langpair="+targetpair+"&q="+text);
    QtCUrl::Options opt;
    opt[CURLOPT_URL] = url;
    opt[CURLOPT_POST] = false;
    opt[CURLOPT_FOLLOWLOCATION] = false;
    opt[CURLOPT_FAILONERROR] = false;
    opt[CURLOPT_NOPROXY] = "localhost";
    QString result = cUrl.exec(opt);
    qDebug() << result;
    qDebug() << url;


}

void MainWindow::on_textEdit_textChanged()
{

}
