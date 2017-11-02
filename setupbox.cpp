#include "setupbox.h"

QT_USE_NAMESPACE

SetupBox::SetupBox(QWidget* parent):QDialog(parent)
{
    setFixedHeight(350);
    setFixedWidth(420);
    setWindowTitle("设置打印机");
     compony = "konka";
     myName = "QiaoYuDong";

     eHostName = new QLineEdit(this);
     eHostPort = new QLineEdit(this);
     ePrintNum = new QLineEdit(this);
     rNet = new QRadioButton(this);
     rNet->setText("网络打印");
     rNet->setChecked(false);
     rUsb = new QRadioButton(this);
     rUsb->setText("USB打印");
     rUsb->setChecked(true);

//     debugCheck = new QCheckBox(this);
//     debugCheck->setText("测试");
//     debugCheck->setChecked(false);

     QButtonGroup* group = new QButtonGroup();
     group->addButton(rNet);
     group->addButton(rUsb);

     pb_Printe = new QPushButton("打印");
    pb_Printe->setFixedHeight(25);
     pb_cancel = new QPushButton("取消");
     pb_cancel->setFixedHeight(25);

     pb_test = new QPushButton("重连");
     pb_test->setFixedHeight(25);

     connect(pb_Printe, SIGNAL(clicked()),this, SLOT(printClick()));
     connect(pb_cancel, SIGNAL(clicked()),this, SLOT(cancelClick()));
     connect(pb_test, SIGNAL(clicked()),this, SLOT(testConnect()));


     QLabel* titleLab = new QLabel(this);
     titleLab->setText("打印机设置");
     titleLab->setFixedHeight(35);
     QFont font;
     font.setBold(true);
     font.setFamily("HEITI");
     font.setPointSize(18);
     titleLab->setFont(font);
     titleLab->setAlignment(Qt::AlignCenter);

     QVBoxLayout* mainLayout = new QVBoxLayout();
     this->setLayout(mainLayout);

     mainLayout->addWidget(titleLab);

     QHBoxLayout* hb_0 = new QHBoxLayout();
     QLabel* lab_0 = new QLabel(this);
     lab_0->setText("打印主机");
     lab_0->setFixedWidth(68);
     hb_0->addWidget(lab_0);
     hb_0->addWidget(eHostName);
     mainLayout->addLayout(hb_0);

     QHBoxLayout* hb_1 = new QHBoxLayout();
     QLabel* lab_1 = new QLabel(this);
     lab_1->setText("打印端口");
     lab_1->setFixedWidth(68);
     hb_1->addWidget(lab_1);
     hb_1->addWidget(eHostPort);
     mainLayout->addLayout(hb_1);

     QHBoxLayout* hb_2 = new QHBoxLayout();
     QLabel* lab_2 = new QLabel(this);
     lab_2->setText("打印份数");
     lab_2->setFixedWidth(68);
     hb_2->addWidget(lab_2);
     hb_2->addWidget(ePrintNum);
     mainLayout->addLayout(hb_2);

     QHBoxLayout* hb_3 = new QHBoxLayout();
     QLabel* lab_3 = new QLabel(this);
     lab_3->setText("打印方式");
     lab_3->setFixedWidth(68);
     hb_3->addWidget(lab_3);
     hb_3->addWidget(rUsb);
     hb_3->addWidget(rNet);
//     hb_3->addWidget(debugCheck);
     mainLayout->addLayout(hb_3);

     msgEdit = new QPlainTextEdit(this);
    // msgEdit->setFixedHeight(45);
     mainLayout->addWidget(msgEdit);


     QHBoxLayout* hb_4 = new QHBoxLayout();
    hb_4->setMargin(10);
     hb_4->addWidget(pb_Printe);     
     hb_4->addWidget(pb_cancel);
     hb_4->addWidget(pb_test);
     mainLayout->addLayout(hb_4);

     readData();
     isConnect = false;

     connect(&m_webSocket, SIGNAL(connected()),this,SLOT(onConnected()));
     connect(&m_webSocket, SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(happenError(QAbstractSocket::SocketError)));
     connect(&m_webSocket,SIGNAL(disconnected()),this,SLOT(onDisconnected()));


}

SetupBox::~SetupBox()
{
   deleteLater();
}

void SetupBox::readData()
{
  QSettings setting("C:\\PRINT.INI",QSettings::IniFormat);
  setting.beginGroup("print");
  QString hostName = setting.value("hostName").toString().trimmed();
  QString hostPort = setting.value("hostPort").toString().trimmed();
  QString printNum = setting.value("printNum").toString().trimmed();
  QString printMode = setting.value("printMode").toString().trimmed();
//  QString debugMode = setting.value("debugMode").toString().trimmed();


  if(hostName.isEmpty())
  {
      hostName = "localhost";
  }
   eHostName->setText(hostName);
  if(hostPort.isEmpty())
  {
      hostPort = "2012";
  }
  eHostPort->setText(hostPort);
  if(printNum.isEmpty())
  {
      printNum = "3";
  }
  ePrintNum->setText(printNum);
  if(printMode.isEmpty() || printMode == "0")
  {
      rUsb->setChecked(true);
  }
  else if(printMode == "1")
  {
      rNet->setChecked(true);
  }
//  if(debugMode.isEmpty() || debugMode == "0")
//  {
//      debugCheck->setChecked(false);
//  }
//  else
//  {
//     debugCheck->setChecked(true);
//  }

  msgEdit->appendPlainText("系统消息：读取配置文件.");

}

void SetupBox::setData(QString fId,QString userId,QString curDate,QString mType,QString mId)
{
     _fId = fId.trimmed();
     _userId = userId.trimmed();
     _curDate = curDate.trimmed();
     _mType = mType.trimmed();
     _mId = mId.trimmed();
//    if(debugCheck->isChecked())
//    {
//        QString str = QString(" fId=%0, userId=%1, curDate=%2, mType=%3, mId=%4").arg(_fId,_userId,_curDate,_mType,_mId);
//        QMessageBox::warning(this,"警告", str);
//    }
}

void SetupBox::init()
{
    QString hostName = eHostName->text().trimmed();
    QString hostPort = eHostPort->text().trimmed();
    QString url = QString("ws://%0:%1").arg(hostName,hostPort);
    m_webSocket.open(QUrl(url));
    m_webSocket.ignoreSslErrors();
//    if(debugCheck->isChecked())
//    {
//     QMessageBox::warning(this,"初始化", url);
//    }
    msgEdit->appendPlainText("发送消息：初始化连接 " + url);
}
void SetupBox::onConnected()
{
    QString str = "接收消息：与打印机服务连接成功";
    msgEdit->appendPlainText(str);
    //msgEdit->setPlainText(str);
    isConnect = true;
//    if(debugCheck->isChecked())
//    {
//        QMessageBox::warning(this,"警告", str);
//    }
}

void SetupBox::onDisconnected()
{
    QString str = "接收消息：已经断开了与打印机服务连接";
    msgEdit->appendPlainText(str);
    isConnect = false;
}

 void SetupBox::testConnect()
 {
    if(isConnect)
    {
        m_webSocket.close();
    }

    if(!m_webSocket.isValid())
    {
       init();
    }
 }

void SetupBox::SetupBox::socketError(QAbstractSocket::SocketError)
{
    QString err = "错误消息：" + m_webSocket.errorString();
    msgEdit->appendPlainText(err);
}

void SetupBox::onTextMessageReceived(QString message)
{
    msgEdit->appendPlainText("接收消息：" + message);
    //msgEdit->setPlainText(message);
    //    m_webSocket.close();
}

void SetupBox::writeData()
{
     QSettings setting("C:\\PRINT.INI",QSettings::IniFormat);
     setting.beginGroup("print");
     QString hostName = eHostName->text().trimmed();
     QString hostPort = eHostPort->text().trimmed();
     QString printNum = ePrintNum->text().trimmed();
     QString printMode = rUsb->isChecked() ? "0" : "1";
//     QString debugMode = debugCheck->isChecked() ? "1" : "0";

     setting.setValue("hostName",QVariant(hostName));
     setting.setValue("hostPort",QVariant(hostPort));
     setting.setValue("printNum",QVariant(printNum));
     setting.setValue("printMode", QVariant(printMode));
//     setting.setValue("debugMode", QVariant(debugMode));
//     if(debugCheck->isChecked())
//     {
//       QMessageBox::warning(this,"初始化", "写入 ini 文件配置信息");
//     }
     msgEdit->appendPlainText("系统消息：写入INI配置信息");
}

void SetupBox::printClick()
{
    QString hostName = eHostName->text().trimmed();
    QString hostPort = eHostPort->text().trimmed();
    QString printNum = ePrintNum->text().trimmed();
    QString printMode = rUsb->isChecked() ? "0" : "1";

    bool ok = true;

    if(hostName.isEmpty()) ok = false;
    if(hostPort.isEmpty()) ok = false;
    if(printNum.isEmpty()) ok = false;
    if(printMode.isEmpty()) ok = false;

   if(!ok)
   {
       QMessageBox::warning(this,"警告", "所有的项目必须填写！");
       return;
   }
   writeData();

   if(!m_webSocket.isValid())
   {
       init();
   }
//   if(debugCheck->isChecked())
//   {
//     QMessageBox::warning(this,"警告", "发送打印消息！");
//   }

   //m_webSocket.sendTextMessage(QStringLiteral("Hello, world!"));
   QString enumModeString1 = "";
   QString createPrint = "";
   if(rNet->isChecked())
   {
      enumModeString1 = "B_EnumNetPrinter";
      createPrint = "B_CreateNetPort|1";
   }
   else
   {
       enumModeString1 = "B_EnumUSB";
       createPrint = "B_CreateUSBPort|1";
   }

   QString str;
   str = "初始化打印机：" + enumModeString1;

   msgEdit->appendPlainText(str);
   m_webSocket.sendTextMessage(enumModeString1);

   str = "创建打印机：" + createPrint;

   msgEdit->appendPlainText(str);
   m_webSocket.sendTextMessage(createPrint);

   QString printDirect = "B_Set_Direction|B";
   msgEdit->appendPlainText("设置打印方向：" + printDirect);
   m_webSocket.sendTextMessage(printDirect);

   QString printmId = QString("B_Prn_Text_TrueType|25|15|40|黑体|1|600|0|0|0|CC|%0").arg(_mId);
   msgEdit->appendPlainText("打印物料号：" + printmId);
   m_webSocket.sendTextMessage(printmId);

   QString printmIdCode = QString("B_Prn_Barcode|45|55|0|1E|2|6|50|N|%0").arg(_fId);
   msgEdit->appendPlainText("打印条码：" + printmIdCode);
   m_webSocket.sendTextMessage(printmIdCode);

   QString printfId = QString("B_Prn_Text_TrueType|30|105|30|黑体|1|600|0|0|0|CD|%0").arg(_fId);
   msgEdit->appendPlainText("打印单号：" + printfId);
   m_webSocket.sendTextMessage(printfId);

   QString printfDate = QString("B_Prn_Text_TrueType|240|110|18|宋体|1|600|0|0|0|CE|%0").arg(_curDate+_userId);
   msgEdit->appendPlainText("打印日期：" + printfDate);
   m_webSocket.sendTextMessage(printfDate);

   QString printType = QString("B_Prn_Text_TrueType|400|50|60|黑体|1|600|0|0|0|CF|%0").arg(_mType);
   msgEdit->appendPlainText("打印类型：" + printType);
   m_webSocket.sendTextMessage(printType);

   QString num = ePrintNum->text().trimmed();
   if(num.isEmpty())
   {
       num = "1";
   }
   QString printNumStr = QString("B_Print_Out|%0").arg(num);
   msgEdit->appendPlainText("打印份数：" + printNumStr);
   m_webSocket.sendTextMessage(printNumStr);

   QString printClose = QString("B_ClosePrn");
   msgEdit->appendPlainText("关闭打印：" + printClose);
   m_webSocket.sendTextMessage(printClose);




}

void SetupBox::cancelClick()
{
    reject();
}
