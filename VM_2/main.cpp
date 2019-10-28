#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <lucalculator.h>
#include <relaxcalculator.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    app.setOrganizationName("MyOrganization");
    app.setOrganizationDomain("MyOrganization.com");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);


    LUCalculator *calculator = new LUCalculator ();
    RelaxCalculator *relaxCalc = new RelaxCalculator ();
    engine.rootContext()->setContextProperty ("calculator", calculator);
    engine.rootContext()->setContextProperty ("relaxCalculator", relaxCalc);
    engine.load(url);

    return app.exec();
}
