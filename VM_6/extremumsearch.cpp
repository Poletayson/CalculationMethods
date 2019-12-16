#include "extremumsearch.h"

ExtremumSearch::ExtremumSearch(QObject *parent) : QObject(parent)
{

}

bool ExtremumSearch::calculate()
{
    for (int i = 0; i < 2; i++){
        intervals[i][0] = -10;      //устанавливаем интервалы
        intervals[i][1] = 10;
        extremum[i] = intervals[i][0];  //иизначально экстремумы ищем из границы интервала
    }


    double zNew = std::numeric_limits <double>::max();     //изначально берем z как максимально возможное

    do {
        zExtremum = zNew;   //берем z с предыдущей итерации
        for (int i = 0; i < 2; i++){
            zNew = goldenSection(i);
        }
    } while(abs(zExtremum - zNew) > EPSILLON);  //пока разница не станет несущественной
    return true;
}

QString ExtremumSearch::getSolution()
{
    QString Out = "Точка экстремума: " + QString::number(extremum[0]) + ", " + QString::number(extremum[1]) +
            "\nЗначение: " + QString::number(zExtremum);

    return Out;
}

QVector<double> ExtremumSearch::getVariable(int num)
{
    Variables.clear();
    double a = intervals[num][0];
    while (a < intervals[num][1]) {
        Variables.append(a);
        a += step;
    }
    return Variables;
}

QVector<double> ExtremumSearch::getValues(int num)
{
    Values.clear();
    double ptrVar[2];
    for (int i = 0; i < 2; i++){    //по умолчанию берем значения переменных в точке экстремума
        ptrVar[i] = extremum[i];
    }
    foreach (double var, Variables) {
        ptrVar[num] = var;    //меняем только заданную переменную, по которой и делаем "срез"
        Values.append(functionValue(ptrVar[0], ptrVar[1]));
    }
    return Values;
}

QVector<double> ExtremumSearch::getExtremum()
{
    QVector <double> ptr;
    for (int i = 0; i < 2; i++){
        ptr.append(extremum[0]);
    }
    return ptr;
}

double ExtremumSearch::getZExtremum() const
{
    return zExtremum;
}

double ExtremumSearch::goldenSection(int coordNumber)
{
    double currExtremum[2] = {extremum[0], extremum[1]};    //экстремум, полученный на этой итерации
    //currExtremum[coordNumber] = intervals[coordNumber][0];  //одну из координат начинаем искать из границы

//изначальные параметры золотого сечения
    double a = intervals[coordNumber][0],  b = intervals[coordNumber][1];
    double x1 = b - (b - a)/1.61803399, x2 = a + (b - a)/1.61803399;
    //double newZ;

    currExtremum[coordNumber] = a;
    double z1 = functionValue(currExtremum[0], currExtremum[1]);
    currExtremum[coordNumber] = x1;
    double z2 = functionValue(currExtremum[0], currExtremum[1]);
    currExtremum[coordNumber] = x2;
    double z3 = functionValue(currExtremum[0], currExtremum[1]);
    currExtremum[coordNumber] = b;
    double z4 = functionValue(currExtremum[0], currExtremum[1]);


    //пока интервал не сожмется
    while (abs(b - a) > EPSILLON_X){

        //В левой точке значение побольше
        if(z2 > z3){
            a = x1; //выкидываем левую точку
            x1 = x2;
            x2 = b - (x1 - a);    //передвигаем a

            z1 = z2;
            z2 = z3;

            currExtremum[coordNumber] = x2;
            z3 = functionValue(currExtremum[0], currExtremum[1]);
        }
        else{
            b = x2; //выкидываем левую точку
            x2 = x1;
            x1 = a + (b - x2);

            z4 = z3;
            z3 = z2;

            currExtremum[coordNumber] = x1;
            z2 = functionValue(currExtremum[0], currExtremum[1]);
        }
    }
    //currExtremum[coordNumber] = (x1 + x2) / 2;
    extremum[coordNumber] = (a + b) / 2;
    return functionValue(extremum[0], extremum[1]);
}

//эллиптический параболоид
// (x+1.8)^2 /7 + (y+0.2)^2 /5.6
double ExtremumSearch::functionValue(double x, double y)
{
    double p = 3.5, q = 2.8;
    double xOffset = 1.8, yOffset = 0.2;    //смещения
    x += xOffset;
    y += yOffset;
    return (x * x) / (2 * p) + (y * y) / (2 * q);
}
