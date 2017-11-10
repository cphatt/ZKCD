#include "ArkApplication.h"
#include "UserInterfaceUtility.h"
#ifdef QT_GUI_LIB
#include <QFont>
#include <QFontDatabase>
#include <QStringList>
#include <QTranslator>
#include <QBrush>
#include <QColor>
#include <QWSServer>
#endif

class ArkApplicationPrivate
{
    Q_DISABLE_COPY(ArkApplicationPrivate)
public:
    explicit ArkApplicationPrivate(int &argc, char **argv, ArkApplication* parent);
    ~ArkApplicationPrivate();
#ifdef QT_GUI_LIB
    QStringList m_Arguments;
    QTranslator* m_Translator;
#endif
private:
    ArkApplication* m_Parent = NULL;
};

ArkApplication::ArkApplication(int &argc, char **argv)
#ifdef QT_GUI_LIB
    : QApplication(argc, argv, QApplication::GuiServer)
    #else
    : QCoreApplication(argc, argv)
    #endif
    , m_Private(new ArkApplicationPrivate(argc, argv, this))
{
#ifdef QT_GUI_LIB
    QFont font(QString("WenQuanYi Micro Hei"));
    font.setPixelSize(18);
    setFont(font);
    qDebug() << "Application font" << QApplication::font();
#endif
}

ArkApplication::~ArkApplication()
{
}

bool ArkApplication::installTranslatorPath(const QString &path)
{
    bool ret = m_Private->m_Translator->load(path);
    if (ret) {
        installTranslator(m_Private->m_Translator);
    }
    return ret;
}

int ArkApplication::size() const
{
    return m_Private->m_Arguments.size();
}

QStringList ArkApplication::arguments() const
{
    return m_Private->m_Arguments;
}

bool ArkApplication::notify(QObject *object, QEvent *event)
{
    return QApplication::notify(object, event);
}

ArkApplicationPrivate::ArkApplicationPrivate(int &argc, char **argv, ArkApplication* parent)
    : m_Parent(parent)
    , m_Translator(NULL)
{
    m_Translator = new QTranslator(m_Parent);
    m_Arguments.clear();
    if ((1 == argc) || (2 == argc)) {
        int tempArgc(3);
        char* tempArgv[3] = {argv[0], "-t", "-qws"};
        argc = tempArgc;
        argv = tempArgv;
    }
    qDebug() << "main argc=" << argc;
    for (int i = 0; i < argc; ++i) {
        qDebug() << "argv[" << i << "]=" << argv[i];
    }
    for (int i = 0; i < argc; ++i) {
        m_Arguments << QString(argv[i]);
    }
    qDebug() << "ArkApplicationPrivate" << argc << m_Arguments;
}

ArkApplicationPrivate::~ArkApplicationPrivate()
{
}

