#ifndef LICENSE_H
#define LICENSE_H

#include <QCryptographicHash>
#include <math.h>

#include <QDebug>

namespace License {

    //this function takes a long int and returns a serial number in the form
    //0000-001-1234
    QString serialNumber(long sequenceNumber)
    {
        QByteArray seed = "BCM Software";
        QString number = QString::number(sequenceNumber);
        QByteArray data = seed + number.toUtf8();

        QByteArray hash = QCryptographicHash::hash(data, QCryptographicHash::Sha1);

        QString hashString = hash.toHex();

        QString str = hashString.mid(0,2);
        bool ok;
        int hex = str.left(1).toInt(&ok, 16);
        int hex2 = str.right(1).toInt(&ok, 16);

        str = hashString.mid(hashString.length() - 2, 2);
        int hex3 = str.left(1).toInt(&ok, 16);
        int hex4 = str.right(1).toInt(&ok, 16);

        int digit1, digit2, digit3, digit4;

        int temp = hex / 10;
        if(temp < 1)
            digit1 = hex;
        else if (temp >= 1)
            digit1 = hex - 10;

        temp = hex2 / 10;
        if(temp < 1)
            digit2 = hex2;
        else if (temp >= 1)
            digit2 = hex2 - 10;

        temp = hex3 / 10;
        if(temp < 1)
            digit3 = hex3;
        else if (temp >= 1)
            digit3 = hex3 - 10;

        temp = hex4 / 10;
        if(temp < 1)
            digit4 = hex4;
        else if (temp >= 1)
            digit4 = hex4 - 10;

        QString seqNum = QString("%1").arg(QString::number(sequenceNumber),7, QChar('0'));

        QString sn;
        sn = seqNum.left(4) + "-" + seqNum.right(3) + "-" + QString::number(digit1)
               + QString::number(digit2) + QString::number(digit3) + QString::number(digit4);

        return sn;
    }

    bool isValidLicense(QString sn) {

        if(sn.length() > 13)
            return false;
        if(sn.length() < 13)
            return false;

        QString seq = sn.left(8).remove("-");
        long num = seq.toLong();

        QString test = serialNumber(num);
        if(sn == test)
            return true;
        return false;
    }

}
#endif // LICENSE_H