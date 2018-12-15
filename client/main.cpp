#include "mainwindow.h"
#include <QApplication>
#include <QByteArray>

#include "hidapi.h"
#define report_length 34 //This number depends on your HID report length.

hid_device *handle;
unsigned char buf[report_length];


QByteArray DATA_IN;
QByteArray DATA_OUT;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
    //5351:3253
    //hid_open args depend on the device VID, PID, and optionally the Serial number.
    handle = hid_open(0x5351, 0x3253, NULL); //(0x1234, 0x6, L"0123456789")
    if (!handle)
    {
        qFatal("unable to open device");
    }
    hid_set_nonblocking(handle, 1);

    DATA_OUT.clear();
    DATA_OUT.append('\x00');
    DATA_OUT.append('\xd0');
    DATA_OUT.append('\x01');

    for(int i=DATA_OUT.size();i<report_length;i++) {
        DATA_OUT.append('\x00');
    }

    qDebug() << DATA_OUT.toHex();

//    exit(1);

    memcpy(buf, DATA_OUT, report_length); //DATA_OUT is the data to be sent.
    hid_write(handle, buf, report_length+1);

    hid_read(handle, buf, report_length);
    DATA_IN = QByteArray(reinterpret_cast<char*>(buf), report_length); //DATA_IN is the received data
//    printf("DI:%s\n",DATA_IN.data());
    qDebug() << DATA_IN.toHex();

//    memcpy(buf, DATA_OUT, report_length); //DATA_OUT is the data to be sent.
//    buf[report_length]=buf[report_length-1];
//    buf[report_length-1]=buf[report_length-2];
//    //.
//    //.
//    //.
//    buf[2]=buf[1];
//    buf[1]=buf[0];
//    buf[0]=0x0;
    hid_write(handle, buf, report_length+1);
}
