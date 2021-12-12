#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtCore/QTranslator>
#include <QtCore/QLocale>
#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QDir>
#include <QtGui/QAction>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    auto apTs = new QTranslator(&app);
    app.installTranslator(apTs);

    QQmlApplicationEngine engine;
    QDir dir{":/i18n/"};
    QList<QVariant> languages;
    const auto &entries = dir.entryInfoList(QDir::Files);
    for (const auto &entry : entries) {
        if (entry.suffix() != "qm") continue;
        QLocale locale{entry.baseName().right(5)};
        auto action = new QAction(locale.nativeLanguageName(), &app);
        QObject::connect(action, &QAction::triggered, &app, [apTs, locale, entry, &engine] {
            if (apTs->load(entry.absoluteFilePath())) {
                qDebug() << "qm load error:" << entry.absoluteFilePath();
            }
            engine.retranslate();
        });
        languages.append(QVariant::fromValue(action));
    }
    engine.rootContext()->setContextProperty("languages", QVariant::fromValue(languages));
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
