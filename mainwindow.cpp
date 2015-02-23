#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // create custom temporary event loop on stack
    QEventLoop eventLoop;

       // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

       // the HTTP request
    QNetworkRequest req( QUrl( QString("http://localhost:2737/listPairs") ) );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called
    QString result;
    if (reply->error() == QNetworkReply::NoError)
    {
           //success
           result = (QString)reply->readAll();
           qDebug() << "Success" <<result;
    }
    else
    {
           //failure
           qDebug() << "Failure" <<reply->errorString();
           delete reply;
    }


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
    // create custom temporary event loop on stack
    QEventLoop eventLoop;

       // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QString targetpair =  ui->comboBox->currentText();
    //http://localhost:2737/translate?langpair=kaz|tat&q=Сен+бардың+ба?

    QString text = ui->textEdit->toPlainText();
    QNetworkRequest req( QUrl( QString("http://localhost:2737/translate?langpair="+targetpair+"&q="+text) ) );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called
    QString result;
    QByteArray temp;
    if (reply->error() == QNetworkReply::NoError)
    {
           //success
           temp = reply->readAll();
           result = (QString)temp;
           qDebug() << "Success" <<result;
    }
    else
    {
           //failure
           qDebug() << "Failure" <<reply->errorString();
           delete reply;
    }
    QStringList translated;
    QJsonDocument jsonResponse = QJsonDocument::fromJson(result.toUtf8());
   // qDebug() << jsonResponse;
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["responseData"].toArray();
    QJsonObject jsonObject2 = jsonObject["responseData"].toObject();
    //qDebug() << jsonObject2;
    QString text2 = jsonObject2["translatedText"].toString();
    qDebug() << text2;
    ui->textEdit_2->setText(text2);

}

void MainWindow::on_textEdit_textChanged()
{

}
