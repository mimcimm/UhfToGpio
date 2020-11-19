#include "serialProcess.h"

SerialProcess::SerialProcess(QObject *parent)
    : QObject(parent)
{
  initializeSerialPort();
}

bool SerialProcess::initializeSerialPort()
{
    QThread *serialThread = new QThread;
    serial = new QSerialPort();
    serial->setParent(NULL);
    serial->moveToThread(serialThread);

    serial->setPortName("ttyAMA2");
    serial->setBaudRate(9600);
    serial->setParity(QSerialPort::NoParity);
    serial->setDataBits(QSerialPort::Data8);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    connect(serialThread,SIGNAL(finished()),serialThread,SLOT(deleteLater()));
    connect(serialThread,SIGNAL(finished()),serial,SLOT(deleteLater()));
    connect(serial,SIGNAL(readyRead()),this,SLOT(serialPortReceived()));
    connect(serialThread,&QThread::started,[=]()->void{
        if(!serial->open(QIODevice::ReadWrite)) // possible race condition but shouldn't cause any problems at this stage
        {
            qDebug() << "Serial Port açılmıyor";
            qDebug() << "error code = " << serial->error();
            qDebug() << "error string = " << serial->errorString();
            serialThread->quit();
        }else{
            qDebug() << "Serial Port acildi";
        }
    });
    serialThread->start();
}

void SerialProcess::writeData(QByteArray data)
{
    if(serial->isWritable()){
        serial->write(data);
    }
}

void SerialProcess::serialPortReceived()
{
    QByteArray bytArrayData = serial->readAll();//serial->read(100);
    QByteArray newTest;
    for(int i=0; i<bytArrayData.length();i++){
        newTest.append(bytArrayData[i]);
    }
    qDebug() << "newTest  :  " << newTest;
    qDebug() << "newTest HEX :  " << newTest.toHex();
    qDebug() << "bytArrayData  :  " << bytArrayData;
    qDebug() << "bytArrayData  Result:  " << bytArrayData.toHex();
    qDebug() << "bytArrayData  Lenght:  " << bytArrayData.length();
    if(bytArrayData.at(2) == static_cast<char> (0x00)){
        qDebug() << "BisikletLİ";
        system("echo 1 > /sys/class/gpio/gpio41/value");
    }else{
        qDebug() << "BisikletSİZ";
        system("echo 0 > /sys/class/gpio/gpio41/value");
    }
    serial->flush();
}
