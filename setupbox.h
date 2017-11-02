#ifndef SETUPBOX_H
#define SETUPBOX_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QLineEdit>
#include <QRadioButton>
#include <QWidget>
#include <QPushButton>
#include <QButtonGroup>
#include <QSettings>
#include <QPlainTextEdit>
//#include <QCheckBox>
#include <QMessageBox>
#include <QtWebSockets/QWebSocket>

class SetupBox : public QDialog
{
    Q_OBJECT
public:
    SetupBox(QWidget* parent);
    ~SetupBox();

    void readData();
    void writeData();
    void setData(QString fId,QString userId,QString curDate,QString mType,QString mId);
    void init();
signals:


public slots:
     void printClick();
     void cancelClick();

     void onConnected();
     void onDisconnected();
     void testConnect();
     void socketError(QAbstractSocket::SocketError);

     void onTextMessageReceived(QString message);


private:
    QLineEdit* eHostName;
    QLineEdit* eHostPort;
    QLineEdit* ePrintNum;
    QRadioButton* rNet;
    QRadioButton* rUsb;
    QPushButton* pb_Printe;
    QPushButton* pb_cancel;
    QPushButton* pb_test;
    QPlainTextEdit* msgEdit;
  //  QCheckBox* debugCheck;

    QString compony;
    QString myName;

    QString _fId;
    QString _userId;
    QString _curDate;
    QString _mType;
    QString _mId;

    bool isConnect;


    QWebSocket m_webSocket;
};

#endif // SETUPBOX_H
