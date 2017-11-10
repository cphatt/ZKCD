#include "TextWidget.h"
#include <QPainter>

class TextWidgetPrivate
{
    Q_DISABLE_COPY(TextWidgetPrivate)
public:
    explicit TextWidgetPrivate(TextWidget* parent);
    ~TextWidgetPrivate();
    QString m_Text;
    int m_Flags = Qt::AlignCenter;
    QFont m_Font;
    TextWidget::Type m_LanguageType = TextWidget::T_Translate;
private:
    TextWidget* m_Parent = NULL;
};

TextWidget::TextWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new TextWidgetPrivate(this))
{
}

TextWidget::~TextWidget()
{
}

void TextWidget::setText(const QString &text)
{
    m_Private->m_Text = text;
    update();
}

void TextWidget::setLanguageType(const TextWidget::Type type)
{
    m_Private->m_LanguageType = type;
    update();
}

void TextWidget::setAlignmentFlag(const int flags)
{
    m_Private->m_Flags = flags;
    update();
}

void TextWidget::setFontPointSize(const int pointSize)
{
    m_Private->m_Font.setPointSize(pointSize);
    update();
}

void TextWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if (!m_Private->m_Text.isEmpty()) {
        painter.setPen(QPen(Qt::white));
        painter.setFont(m_Private->m_Font);
        if (TextWidget::T_Translate == m_Private->m_LanguageType) {
            painter.drawText(rect(), m_Private->m_Flags, QObject::tr(m_Private->m_Text.toLocal8Bit().constData()));
        } else {
            QFontMetrics fontMetrics(m_Private->m_Font);
            QString text = fontMetrics.elidedText(m_Private->m_Text, Qt::ElideRight, width());
            painter.drawText(rect(), m_Private->m_Flags, text);
        }
    }
    QWidget::paintEvent(event);
}

TextWidgetPrivate::TextWidgetPrivate(TextWidget* parent)
    : m_Parent(parent)
{
}

TextWidgetPrivate::~TextWidgetPrivate()
{
}
