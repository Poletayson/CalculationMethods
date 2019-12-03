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



//    Xout.push_back(Xin[0]);
//    Yout.push_back(Yin[0]);
////    QVector <double> Xscaled = Xin;
////    Xscaled[0] = 0;
//    for (int i = 1; i < n; i++){    //для всех известных точек
////        Xscaled[i] = (Xscaled[i] - f) / t;
//        double step = (Xin[i] - Xin[i - 1]) / INTERIUM_COUNT;

//        for (int j = 1; j < INTERIUM_COUNT - 1; j++){   //для всех точек между известными
//            double yTmp = 0;
//            double xTmp = Xin[i - 1] + step * j;
//            double Re = 0;
//            double Im = 0;
//            //суммируем
//            for (int q = 0; q < n; q++){
////                Re += qCos(2 * M_PI * q * xTmp);
////                Im += qSin(2 * M_PI * q * xTmp);
////                Complex pt = std::exp(((double) 2) * M_PI * j * q / n)/* * xTmp*/;
////                Re += pt.real() * A[q];
////                Im += pt.imag() * A[q];
//                yTmp += A[q] * (sin((double)2 * M_PI * q * j / n) + cos((double)2 * M_PI * q * j / n));//qExp(2 * M_PI * q * xTmp);//exponent(2 * M_PI * q * xTmp);
//            }
//            Xout.push_back(xTmp * t);
//            Yout.push_back(yTmp/*sqrt(Re*Re + Im*Im) / n*/);
//        }
//        Xout.push_back(Xin[i] * t);
//        Yout.push_back(Yin[i]);
}

bool FurieInterpolator::calculate()
{
    QVector <Complex> A = directTransformation();    //получаем значения A
//    Xout.clear();
//    Yout.clear();

//    n = 10;
//    st = 1.0 / 10;
//    t = M_PI;
//    Xin.clear();
//    Yin.clear();
//    for (int i = 0; i < n; i++){
//        Xin.push_back(i * st);
//        Yin.push_back(sin (Xin.last() * t));
//    }


    Xout.push_back(Xin[0]);
    Yout.push_back(Yin[0]);
    QVector <double> Xscaled = Xin;
    Xscaled[0] = 0;
    N = n * INTERIUM_COUNT; //общее число точек
    int nHalf = n/2;

    for (int j = 0; j <= N; j++){   //для всех точек между известными
        Complex yTmp = 0;
        //double xTmp = Xin[i - 1] + step * j;
        double Re = 0;
        double Im = 0;
//        int i = nHalf;
        //суммируем
        for (int q = -nHalf; q < 0; q++){

            yTmp += A[q + n] * std::exp((double)2 * M_PI * IC * (double)q * (double)j / (double)N);//qExp(2 * M_PI * q * xTmp);//exponent(2 * M_PI * q * xTmp);
        }
        for (int q = 0; q < nHalf; q++){

            yTmp += A[q] * std::exp((double)2 * M_PI * IC * (double)q * (double)j / (double)N);//qExp(2 * M_PI * q * xTmp);//exponent(2 * M_PI * q * xTmp);
        }
        Xout.push_back((double)j / N * M_PI);
        Yout.push_back(absComplex(yTmp)/n);
    }
//        Xout.push_back(Xin[i] * t);
//        Yout.push_back(Yin[i]);
//    }
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
//    int c = Xout.count();
//    for (int i = 0; i < c; i ++) {
//        Out += QString::number(Xout[i]) + " " + QString::number(Yout[i]) + " \n";
//    }
    return Out;
}

QVector<Complex> FurieInterpolator::directTransformation()    //вычисление коэффициентов A
{
    QVector <Complex> A;
    //double Re, Im;
    Complex a;
    //complex<double > a =  - 0.2 i
    for (int k = 0; k < n; k++){
        a = Complex (0, 0);
//        Re = 0;
//        Im = 0;
        for (int j = 0; j < n; j++){
            Complex pt = std::exp((double)- 2 * M_PI * IC * (double)k /*Xin[j]*/ * (double)j / (double)n);
//            Re += pt.real() * Yin[j];
//            Im += pt.imag() * Yin[j];

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
