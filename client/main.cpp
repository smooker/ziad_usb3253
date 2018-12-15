#include "mainwindow.h"
#include <QApplication>
#include <QByteArray>

#include "hidapi.h"
#define report_length 64 //This number depends on your HID report length.

hid_device *handle;
unsigned char buf[report_length];

#include <QFile>

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
    hid_set_nonblocking(handle, 0);

    DATA_OUT.clear();
    DATA_OUT.append('\x00');
    DATA_OUT.append('\x00');
//    DATA_OUT.append('\xd1');  //read input
//    DATA_OUT.append('\x00');

//    DATA_OUT.append('\xd0');    //set output
//    DATA_OUT.append('\x00');
//    DATA_OUT.append('\x01');

//    DATA_OUT.append('\xe0');    //set pwm DO1, DO6 are the outputs
//    DATA_OUT.append('\x01');
//    DATA_OUT.append('\x00');    //freq
//    DATA_OUT.append('\x03');
//    DATA_OUT.append('\xe8');
//    DATA_OUT.append('\x32');    //50% ratio
//    DATA_OUT.append('\x01');    // on/off
//    DATA_OUT.append('\x01');    //channel 0, 1


    DATA_OUT.append('\xa2');    //set output
    DATA_OUT.append('\x00');
    DATA_OUT.append('\x05');

    for(int i=DATA_OUT.size();i<report_length;i++) {
        DATA_OUT.append('\x00');
    }

    qDebug() << DATA_OUT.toHex();

    QFile file("./out.bin");
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "error.";
        exit(3);
    }

    QByteArray ba;

    ba.clear();

    for(int i=0;i<100;i++) {
        hid_write(handle, (const unsigned char*)DATA_OUT.data(), report_length+1);
        memset(buf, 0, sizeof(buf));
        hid_read_timeout(handle, buf, report_length, 25);
//        hid_read(handle, buf, report_length);
        DATA_IN = QByteArray(reinterpret_cast<char*>(buf), report_length); //DATA_IN is the received data
        ba.append(DATA_IN);
    }
    file.write(ba);
    file.close();
    qDebug() << DATA_IN.toHex();
}
