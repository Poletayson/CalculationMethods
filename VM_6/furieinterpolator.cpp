#include "furieinterpolator.h"

FurieInterpolator::FurieInterpolator(QObject *parent) : QObject(parent)
{
    st = 1.0 / n;
    t = M_PI;
    Xin.clear();
    Yin.clear();
    for (int i = 0; i < n; i++){
        Xin.push_back(i * st);
        Yin.push_back(sin (Xin.last() * t));
    }
}

bool FurieInterpolator::calculate()
{
    QVector <Complex> A = directTransformation();    //получаем значения A
    Xout.clear();
    Yout.clear();

    Xout.push_back(Xin[0]);
    Yout.push_back(Yin[0]);
    QVector <double> Xscaled = Xin;
    Xscaled[0] = 0;
    N = n * INTERIUM_COUNT; //общее число точек
    int nHalf = n/2;

    for (int j = 0; j <= N; j++){   //для всех точек между известными
        Complex yTmp = 0;
        //суммируем, у нас сдвинуто на n/2
        for (int q = -nHalf; q < 0; q++){
            yTmp += A[q + n] * std::exp((double)2 * M_PI * IC * (double)q * (double)j / (double)N);//qExp(2 * M_PI * q * xTmp);//exponent(2 * M_PI * q * xTmp);
        }
        for (int q = 0; q < nHalf; q++){

            yTmp += A[q] * std::exp((double)2 * M_PI * IC * (double)q * (double)j / (double)N);//qExp(2 * M_PI * q * xTmp);//exponent(2 * M_PI * q * xTmp);
        }
        Xout.push_back((double)j / N * M_PI);
        Yout.push_back(absComplex(yTmp)/n);
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

QVector<double> FurieInterpolator::getYRight() const
{
    QVector<double> Yr;
    for (int i = 0; i < N; i++){
        Yr.append(sin(Xout[i]));
    }
    return Yr;
}

QString FurieInterpolator::getSolution()
{
    double maxD = 0;
    for (int i = 0; i < N; i++){
        double maxPtr = abs(Yout[i] - sin(Xout[i]));
        if (maxPtr > maxD)
            maxD = maxPtr;
    }

    QString Out = "Максимальная погрешность: " + QString::number(maxD);
    return Out;
}

QVector<Complex> FurieInterpolator::directTransformation()    //вычисление коэффициентов A
{
    QVector <Complex> A;
    Complex a;
    for (int k = 0; k < n; k++){
        a = Complex (0, 0);

        for (int j = 0; j < n; j++){
            Complex pt = std::exp((double)- 2 * M_PI * IC * (double)k /*Xin[j]*/ * (double)j / (double)n);

            a += Yin[j] * pt; //exponent(- 2 * M_PI * i * Xin[j]);/*(-sin((double)2 * M_PI * k * j / n) + cos((double)2 * M_PI * k * j / n)) * Yin[j];*/
        }
        A.push_back(a); //(sqrt(Re*Re + Im*Im));//(a / n);
    }
    return A;
}

double FurieInterpolator::exponent(double fi)
{
    double r = qCos(fi);
    double i = qCos(fi);
    return qSqrt(r * r + i * i);
}

double FurieInterpolator::absComplex(Complex c)
{
    return (sqrt(c.real()*c.real() + c.imag()*c.imag()));
}
