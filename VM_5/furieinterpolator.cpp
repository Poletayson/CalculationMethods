#include "furieinterpolator.h"

FurieInterpolator::FurieInterpolator(QObject *parent) : QObject(parent)
{

}

bool FurieInterpolator::calculate()
{
    QVector <double> A = directTransformation();    //получаем значения A
    Xout.clear();
    Yout.clear();

    n = 10;
    st = 1.0 / 10;
    t = M_PI;
    Xin.clear();
    Yin.clear();
    for (int i = 0; i < n; i++){
        Xin.push_back(i * st);
        Yin.push_back(sin (Xin.last() * t));
    }


    Xout.push_back(Xin[0]);
    Yout.push_back(Yin[0]);
//    QVector <double> Xscaled = Xin;
//    Xscaled[0] = 0;
    for (int i = 1; i < n; i++){    //для всех известных точек
//        Xscaled[i] = (Xscaled[i] - f) / t;
        double step = (Xin[i] - Xin[i - 1]) / INTERIUM_COUNT;

        for (int j = 1; j < INTERIUM_COUNT - 1; j++){   //для всех точек между известными
            double yTmp = 0;
            double xTmp = Xin[i - 1] + step * j;
            double Re = 0;
            double Im = 0;
            //суммируем
            for (int q = 0; q < n; q++){
//                Re += qCos(2 * M_PI * q * xTmp);
//                Im += qSin(2 * M_PI * q * xTmp);
//                Complex pt = std::exp(((double) 2) * M_PI * j * q / n)/* * xTmp*/;
//                Re += pt.real() * A[q];
//                Im += pt.imag() * A[q];
                yTmp += A[q] * (sin((double)2 * M_PI * q * j / n) + cos((double)2 * M_PI * q * j / n));//qExp(2 * M_PI * q * xTmp);//exponent(2 * M_PI * q * xTmp);
            }
            Xout.push_back(xTmp * t);
            Yout.push_back(yTmp/*sqrt(Re*Re + Im*Im) / n*/);
        }
        Xout.push_back(Xin[i] * t);
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

     for (int i = 0; i < n; i ++) {
         Xin[0] = (Xin[0] - f) / t;
     }
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
    double Re, Im;
    double a;
    //complex<double > a =  - 0.2 i
    for (int k = 0; k < n; k++){
        a = 0;
        Re = 0;
        Im = 0;
        for (int j = 0; j < n; j++){
            //Complex pt = std::exp((double)- 2 * k * j / n) * IC * M_PI  * Xin[j];
//            Re += pt.real() * Yin[j];
//            Im += pt.imag() * Yin[j];

            a += (-sin((double)2 * M_PI * k * j / n) + cos((double)2 * M_PI * k * j / n)) * Yin[j];//pt.real(); //Yin[j] * std::exp(pt);//exponent(- 2 * M_PI * i * Xin[j]);
        }
        A.push_back(a / n);//(sqrt(Re*Re + Im*Im));//(a / n);
    }
    return A;
}

double FurieInterpolator::exponent(double fi)
{
    double r = qCos(fi);
    double i = qCos(fi);
    return qSqrt(r * r + i * i);
}
