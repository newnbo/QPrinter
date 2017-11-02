/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QAxBindable>
#include <QAxFactory>
#include <QApplication>
#include <QWidget>
#include "setupbox.h"

//! [0]
class QPrinter : public QObject, public QAxBindable
{
    Q_OBJECT
    Q_CLASSINFO("ClassID",     "{D7A7E867-7EF1-4479-8C4D-5DED2B6F62EE}")
    Q_CLASSINFO("InterfaceID", "{8599CF5E-5AD8-4F34-A08E-54790D36FFBB}")
    Q_CLASSINFO("EventsID",    "{CE9CFFB6-1C64-4D2E-B9DE-CBB1A9285AAD}")
    Q_PROPERTY( QString fId READ fId WRITE setFId )
    Q_PROPERTY( QString userId READ userId WRITE setUserId )
    Q_PROPERTY( QString curDate READ curDate WRITE setCurDate )
    Q_PROPERTY( QString mType READ mType WRITE setMType )
    Q_PROPERTY( QString mId READ mId WRITE setMId )


public:
    QPrinter(QObject *parent = 0)
    : QObject(parent)
    {

    }

    QString fId() const
    {
        return _fId;
    }
    QString userId() const
    {
        return _userId;
    }

    QString curDate() const
    {
        return _curDate;
    }
    QString mType() const
    {
        return _mType;
    }

    QString mId() const
    {
        return _mId;
    }



signals:
    void someSignal();
    void valueChanged(int);
    void textChanged(const QString&);

public slots:

    void  setupBox()
    {
        SetupBox* box = new SetupBox(NULL);
        box->setModal(true);
        box->setData(_fId,_userId,_curDate,_mType,_mId);
        box->init();
        box->exec();
        delete box;
    }

    void setFId( const QString &string )
    {
        if ( !requestPropertyChange( "fId" ) )
            return;

        _fId = string;
        //emit textChanged( string );
        propertyChanged( "fId" );
    }

    void setUserId( const QString &string )
    {
        if ( !requestPropertyChange( "userId" ) )
            return;
        _userId = string;
        propertyChanged( "userId" );
    }

    void setCurDate( const QString &string )
    {
        if ( !requestPropertyChange( "curDate" ) )
            return;
        _curDate = string;
        propertyChanged( "curDate" );
    }

    void setMType( const QString &string )
    {
        if ( !requestPropertyChange( "mType" ) )
            return;
        _mType = string;
        propertyChanged( "mType" );
    }

    void setMId( const QString &string )
    {
        if ( !requestPropertyChange( "mId" ) )
            return;
        _mId = string;
        propertyChanged( "mId" );
    }

private:
    QString _fId;
    QString _userId;
    QString _curDate;
    QString _mType;
    QString _mId;


};

//! [0]
#include "main.moc"

//! [1]
QAXFACTORY_BEGIN(
    "{BB89AE3F-44B6-4994-A306-792B804FB328}", // type library ID
    "{93568EA6-2C2F-4F91-83AB-0DFB8F5956E7}") // application ID
    QAXCLASS(QPrinter)
QAXFACTORY_END()
//! [1]
