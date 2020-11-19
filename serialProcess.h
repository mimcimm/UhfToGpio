#ifndef SERIALPROCESS_H
#define SERIALPROCESS_H

#include <QObject>
#include <QErrorMessage>
#include <QSerialPort>
#include <QDebug>
#include <QThread>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>
#include <QThread>
#include <QSerialPortInfo>

class SerialProcess : public QObject
{
    Q_OBJECT

public:
    explicit SerialProcess(QObject *parent = 0);
   // ~SerialProcess();

private:
    QSerialPort* serial;
    //QByteArray serialData ;
    bool initializeSerialPort();
    void writeData(QByteArray data);
    //void showMessageBox(QString error);


private slots:
    void serialPortReceived();
};
#endif // MAINWINDOW_H
