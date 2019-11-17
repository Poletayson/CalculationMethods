#include "furieinterpolator.h"

FurieInterpolator::FurieInterpolator(QObject *parent) : QObject(parent)
{

}

bool FurieInterpolator::calculate()
{
    QVector <double> A = directTransformation();    //получаем значения A
    Xout.clear();
    Yout.clear();
    Xout.push_back(Xin[0]);
    Yout.push_back(Yin[0]);
    QVector <double> Xscaled = Xin;
    Xscaled[0] = 0;
    for (int i = 1; i < n; i++){    //для всех известных точек
        Xscaled[i] = (Xscaled[i] - f) / t;
        double step = (Xscaled[i] - Xscaled[i - 1]) / INTERIUM_COUNT;

        for (int j = 0; j < INTERIUM_COUNT - 1; j++){   //для всех точек между известными
            double yTmp = 0;
            double xTmp = Xscaled[i - 1] + step * j;
            //суммируем
            for (int q = 0; q < n; q++){
                yTmp += A[q] * exponent(2 * M_PI * q * xTmp);
            }
            Xout.push_back(xTmp * t + f);
            Yout.push_back(yTmp);
        }
        Xout.push_back(Xin[i]);
        Yout.push_back(Yin[i]);
    }
}

bool FurieInterpolator::setFromFile(QString filename)
{
    QFile file (QQmlFile::urlToLocalFileOrQrc(filename));
     file.open(QFile::ReadOnly);
     QString inputText = file.readLine();         //получаем массив b
     QStringList  strListX = inputText.split(' ');     //разбиваем
     QStringList  strListY = inputText.split(' ');     //разбиваем
     n = strListX.length();
     Xin.clear();
     Yin.clear();

     for (int i = 0; i < n; i ++) {
         Xin.push_back(strListX[i].toDouble());
         Yin.push_back(strListY[i].toDouble());
     }
     t = Xin[n - 1] - Xin[0];
     f = Xin[0];
}

QVector<double> FurieInterpolator::getXout() const
{
    return Xout;
}

QVector<double> FurieInterpolator::getYout() const
{
    return Yout;
}

QString FurieInterpolator::getSolution()
{
    QString Out = "";
    int c = Xout.count();
    for (int i = 0; i < c; i ++) {
        Out += QString::number(Xout[i]) + " " + QString::number(Yout[i]) + " \n";
    }
    return Out;
}

QVector<double> FurieInterpolator::directTransformation()    //вычисление коэффициентов A
{
    QVector <double> A;
    double a;
    for (int i = 0; i < n; i++){
        a = 0;
        for (int j = 0; j < n; j++){
            a += Yin[j] * exponent(- 2 * M_PI * i * Xin[j]);
        }
        A.push_back(a / n);
    }
    return A;
}

double FurieInterpolator::exponent(double fi)
{
    double r = qCos(fi);
    double i = qCos(fi);
    return qSqrt(r * r + i * i);
}
