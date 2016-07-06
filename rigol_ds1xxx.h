#ifndef RIGOL_DS1XXX_H
#define RIGOL_DS1XXX_H

#include <qt_windows.h>
#include <QDebug>
#include <QApplication>

class RIGOL_DS1XXX {
public:
    explicit RIGOL_DS1XXX()
        : Device(-1)
    {
        module = LoadLibrary(L"RigolTMCUsb_UI.dll");
        if (module) {
            GetDevice = (pGetDeviceNum)GetProcAddress(module, "GetTMCDeviceNum");
            Write = (pWrite)GetProcAddress(module, "WriteUSB");
            Read = (pRead)GetProcAddress(module, "ReadUSB");
            Device = GetDevice();
            qDebug() << "Device" << Device;
        }
        if (Device >= 0) {
            qDebug() << "Write" << SendToUSB("*IDN?\n");
            qDebug() << "ReadFromUSB" << ReadFromUSB();
        }
    }

    ~RIGOL_DS1XXX()
    {
        if (module > 0) {
        }
    }

private:
    HMODULE module;

    typedef int(CALLBACK* pGetDeviceNum)();
    typedef bool(CALLBACK* pWrite)(unsigned long, unsigned char, unsigned char, unsigned long, unsigned char*);
    typedef bool(CALLBACK* pRead)(unsigned long, unsigned long*, unsigned char*);
    /*
    Private Declare Function ReadUSB Lib "RigolTMCUsb_UI.dll" (ByVal Index As Long, ByVal lpszLength As Long, ByVal lpszBuffer As Long) As Boolean
    Private Declare Function WriteUSB Lib "RigolTMCUsb_UI.dll" (ByVal Index As Long, ByVal msgid As Long, ByVal tag As Long, ByVal length As Long, ByVal lpszBuffer As Long) As Boolean
    Private Declare Function GetDeviceNum Lib "RigolTMCUsb_UI.dll" () As Long
    */
    pGetDeviceNum GetDevice;
    pWrite Write;
    pRead Read;

    int Device;

    QByteArray strInput;

    bool SendToUSB(QString cmd)
    {
        int temp;
        //recall the GetTMCDeviceNum and WriteUSB function from RigolTMCUsb_UI.dll
        temp = cmd.length();
        strInput = cmd.toLocal8Bit();
        if (Device >= 0) {
            return Write(0, 1, 1, temp, (unsigned char*)strInput.data());
        }
        return false;
    }

    //acquire Returned Format from the oscilloscope
    QByteArray& ReadFromUSB(void)
    {
        unsigned long infoSize;
        int len = 100;
        strInput.resize(0);
        strInput.resize(len);

        if (Device >= 0) {
            qDebug() << "Write" << Write(0, 2, 2, len, 0);
            qDebug() << "Read" << Read(0, &infoSize, (unsigned char*)strInput.data()) << infoSize;
        }
        //strInput.resize(infoSize);
        //strInput[infoSize - 1] = '\0';
        return strInput;
    }
};

#endif // RIGOL_DS1XXX_H
