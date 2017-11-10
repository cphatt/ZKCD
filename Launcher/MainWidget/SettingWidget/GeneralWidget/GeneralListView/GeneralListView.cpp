#include "GeneralListView.h"
#include "CustomItemDelegate.h"
#include "UserInterfaceUtility.h"
#include "GeneralSlider/GeneralSlider.h"
#include "Widget.h"
#include "AutoConnect.h"
#include "CustomScrollBar.h"
#include "SettingPersistent.h"
#include "AudioConfig.h"
#include "UserInterfaceUtility.h"
#include "Audio.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QPainter>
#include <QMetaType>
#include <QEvent>

namespace SourceString {
static const QString Brightness = QString(QObject::tr("Brightness"));
static const QString Contrast = QString(QObject::tr("Contrast"));
static const QString Saturation = QString(QObject::tr("Saturation"));
static const QString Volume = QString(QObject::tr("Volume"));
static const QString Calibrate = QString(QObject::tr("Calibrate"));
static const QString Reset = QString(QObject::tr("Reset"));
}

class GeneralVariant
{
public:
    GeneralVariant();
    ~GeneralVariant();
    QWidget* m_Slider;
    QString m_Text;
    QString m_Value;
};
Q_DECLARE_METATYPE(GeneralVariant)
class GeneralDelegate : public CustomItemDelegate
{
    Q_DISABLE_COPY(GeneralDelegate)
public:
    explicit GeneralDelegate(QWidget *parent = NULL);
    ~GeneralDelegate();
protected:
    void paint(QPainter* painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
};

class GeneralListViewPrivate
{
    Q_DISABLE_COPY(GeneralListViewPrivate)
public:
    explicit GeneralListViewPrivate(GeneralListView* parent);
    ~GeneralListViewPrivate();
    void initialize();
    void connectAllSlots();
    QStandardItemModel* m_StandardItemModel = NULL;
    GeneralDelegate* m_GeneralDelegate = NULL;
    CustomScrollBar* m_CustomScrollBar = NULL;
    GeneralSlider* m_BrightnessSlider = NULL;
    GeneralSlider* m_ConstrastSlider = NULL;
    GeneralSlider* m_SaturationSlider = NULL;
    GeneralSlider* m_VolumeSlider = NULL;
private:
    GeneralListView* m_Parent = NULL;
};


GeneralListView::GeneralListView(QWidget *parent)
    : CustomListView(parent)
    , m_Private(new GeneralListViewPrivate(this))
{
    setVisible(true);
}

GeneralListView::~GeneralListView()
{
}

void GeneralListView::onMinusBtnRelease()
{
    qDebug() << "GeneralListView::onMinusBtnRelease";
    if (sender() == m_Private->m_BrightnessSlider) {
        qDebug() << "m_BrightnessSlider";
        g_Setting->setBrightness(ST_Minus, 1);
    } else if (sender() == m_Private->m_ConstrastSlider) {
        qDebug() << "m_ConstrastSlider";
        g_Setting->setContrast(ST_Minus, 1);
    } else if (sender() == m_Private->m_SaturationSlider) {
        qDebug() << "m_Hue";
        g_Setting->setSaturation(ST_Minus, 1);
    } else if (sender() == m_Private->m_VolumeSlider) {
        qDebug() << "m_VolumeSlider";
        g_Audio->requestDecreaseVolume();
    }
}

void GeneralListView::onPlusBtnRelease()
{
    qDebug() << "GeneralWidget::onPlusBtnRelease";
    if (sender() == m_Private->m_BrightnessSlider) {
        qDebug() << "m_BrightnessSlider";
        g_Setting->setBrightness(ST_Plus, 1);
    } else if (sender() == m_Private->m_ConstrastSlider) {
        qDebug() << "m_ConstrastSlider";
        g_Setting->setContrast(ST_Plus, 1);
    } else if (sender() == m_Private->m_SaturationSlider) {
        qDebug() << "m_SaturationSlider";
        g_Setting->setSaturation(ST_Plus, 1);
    } else if (sender() == m_Private->m_VolumeSlider) {
        qDebug() << "m_VolumeSlider";
        g_Audio->requestIncreaseVolume();
    }
}

void GeneralListView::onTickMarksMillesimalEnd(const int millesimal)
{
    qDebug() << "GeneralWidget::onTickMarksMillesimalEnd" << millesimal;
    if (sender() == m_Private->m_BrightnessSlider) {
        qDebug() << "m_BrightnessSlider";
        g_Setting->setBrightness(ST_Value, millesimal * (7 - (-7)) / 1000);
    } else if (sender() == m_Private->m_ConstrastSlider) {
        qDebug() << "m_ConstrastSlider";
        g_Setting->setContrast(ST_Value, millesimal * (7 - (-7)) / 1000);
    } else if (sender() == m_Private->m_SaturationSlider) {
        qDebug() << "m_Hue";
        g_Setting->setSaturation(ST_Value, millesimal * (7 - (-7)) / 1000);
    } else if (sender() == m_Private->m_VolumeSlider) {
        qDebug() << "m_VolumeSlider";
        g_Audio->requestSetVolume(millesimal * (40 - (0)) / 1000);
    }
}

void GeneralListView::onBrightnessChange(const int value)
{
    qDebug() << "GeneralWidget::onBrightnessChange" << value << 1000 * value / (7 - (-7));
    m_Private->m_BrightnessSlider->setTickMarksMillesimal(1000 * value / (7 - (-7)));
    QModelIndex modelIndex = m_Private->m_StandardItemModel->index(0, 0, QModelIndex());
    GeneralVariant variant = qVariantValue<GeneralVariant>(modelIndex.data());
    variant.m_Value = QString::number(value - 7);
    m_Private->m_StandardItemModel->setData(modelIndex, qVariantFromValue(variant), Qt::DisplayRole);
}

void GeneralListView::onContrastChange(const int value)
{
    qDebug() << "GeneralWidget::onContrastChange" << value << 1000 * value / (7 - (-7));
    m_Private->m_ConstrastSlider->setTickMarksMillesimal(1000 * value / (7 - (-7)));
    QModelIndex modelIndex = m_Private->m_StandardItemModel->index(1, 0, QModelIndex());
    GeneralVariant variant = qVariantValue<GeneralVariant>(modelIndex.data());
    variant.m_Value = QString::number(value - 7);
    m_Private->m_StandardItemModel->setData(modelIndex, qVariantFromValue(variant), Qt::DisplayRole);
}

void GeneralListView::onSaturationChange(const int value)
{
    qDebug() << "GeneralListView::onSaturationChange" << value << 1000 * value / (7 - (-7));
    m_Private->m_SaturationSlider->setTickMarksMillesimal(1000 * value / (7 - (-7)));
    QModelIndex modelIndex = m_Private->m_StandardItemModel->index(2, 0, QModelIndex());
    GeneralVariant variant = qVariantValue<GeneralVariant>(modelIndex.data());
    variant.m_Value = QString::number(value - 7);
    m_Private->m_StandardItemModel->setData(modelIndex, qVariantFromValue(variant), Qt::DisplayRole);
}

void GeneralListView::onVolumeChange(int type, const int volume)
{
    qDebug() << __FUNCTION__;
    m_Private->m_VolumeSlider->setTickMarksMillesimal(1000 * volume / (40 - (-0)));
    QModelIndex modelIndex = m_Private->m_StandardItemModel->index(3, 0, QModelIndex());
    GeneralVariant variant = qVariantValue<GeneralVariant>(modelIndex.data());
    variant.m_Value = QString::number(volume);
    m_Private->m_StandardItemModel->setData(modelIndex, qVariantFromValue(variant), Qt::DisplayRole);
}

GeneralListViewPrivate::GeneralListViewPrivate(GeneralListView *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth() - 278, 626 - 73, m_Parent);
    g_Widget->geometryFit(209, 0, 636, 92, m_BrightnessSlider);
    g_Widget->geometryFit(209, 92, 636, 92, m_ConstrastSlider);
    g_Widget->geometryFit(209, 184, 636, 92, m_SaturationSlider);
    g_Widget->geometryFit(209, 276, 636, 92, m_VolumeSlider);
}

GeneralListViewPrivate::~GeneralListViewPrivate()
{
}

static const unsigned char brightnessStep(256 / 15);
static const unsigned char constrasStep(256 / 15);
static const unsigned char hueStep(256 / 15);

void GeneralListViewPrivate::initialize()
{
    m_CustomScrollBar = new CustomScrollBar(m_Parent);
    int width = 89 * g_Widget->widthScalabilityFactor();
    m_CustomScrollBar->setStyleSheet(QString("QScrollBar:vertical{"
                                             "width:" + QString::number(width) + "px;"
                                                                                 "background:rgba(255, 255, 255, 255);"
                                                                                 "margin:0px, 0px, 0px, 0px;"
                                                                                 "padding-top:0px;"
                                                                                 "padding-bottom:0px;"
                                                                                 "width:" + QString::number(width) + "px;"
                                                                                 "}"
                                                                                 "QScrollBar::handle:vertical:disabled{"
                                                                                 "width:" + QString::number(width) + "px;"
                                                                                                                     "background:rgba(0, 94, 187, 255);"
                                                                                                                     "width:" + QString::number(width) + "px;"
                                                                                                                     "}"
                                                                                                                     "QScrollBar::add-line:vertical{"
                                                                                                                     "height:0px;"
                                                                                                                     "}"
                                                                                                                     "QScrollBar::sub-line:vertical{"
                                                                                                                     "height:0px;"
                                                                                                                     "}"
                                             ));
    m_Parent->setVerticalScrollBar(m_CustomScrollBar);
    m_Parent->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_BrightnessSlider = new GeneralSlider(m_Parent);
    m_BrightnessSlider->setMinimumValue(-7);
    m_BrightnessSlider->setMaximumValue(7);
    int brightness = SettingPersistent::getBrightness();
    m_BrightnessSlider->setTickMarksMillesimal(1000 * brightness / (7 - (-7)));
    m_BrightnessSlider->setVisible(true);
    m_ConstrastSlider = new GeneralSlider(m_Parent);
    m_ConstrastSlider->setMinimumValue(-7);
    m_ConstrastSlider->setMaximumValue(7);
    int constrast = SettingPersistent::getContrast();
    m_ConstrastSlider->setTickMarksMillesimal(1000 * constrast / (7 - (-7)));
    m_ConstrastSlider->setVisible(true);
    m_SaturationSlider = new GeneralSlider(m_Parent);
    m_SaturationSlider->setMinimumValue(-7);
    m_SaturationSlider->setMaximumValue(7);
    int saturation = SettingPersistent::getSaturation();
    m_SaturationSlider->setTickMarksMillesimal(1000 * saturation / (7 - (-7)));
    m_SaturationSlider->setVisible(true);
    m_VolumeSlider = new GeneralSlider(m_Parent);
    m_VolumeSlider->setMinimumValue(0);
    m_VolumeSlider->setMaximumValue(40);
    int volume = AudioConfig::getVolume(true);
    m_VolumeSlider->setTickMarksMillesimal(1000 * volume / (40 - (-0)));
    m_VolumeSlider->setVisible(true);
    m_StandardItemModel = new QStandardItemModel(m_Parent);
    m_GeneralDelegate = new GeneralDelegate(m_Parent);
    m_Parent->setItemDelegate(m_GeneralDelegate);
    QStandardItem* brightnessItem = new QStandardItem();
    GeneralVariant variant;
    variant.m_Text = SourceString::Brightness;
    variant.m_Value = QString::number(brightness - 7);
    variant.m_Slider = m_BrightnessSlider;
    brightnessItem->setSizeHint(QSize((1174 - 278)  * g_Widget->widthScalabilityFactor(), 92 * g_Widget->heightScalabilityFactor()));
    brightnessItem->setData(qVariantFromValue(variant), Qt::DisplayRole);
    QStandardItem* contrastItem = new QStandardItem();
    variant.m_Text = SourceString::Contrast;
    variant.m_Value = QString::number(constrast - 7);
    variant.m_Slider = m_ConstrastSlider;
    contrastItem->setSizeHint(QSize((1174 - 278)  * g_Widget->widthScalabilityFactor(), 92 * g_Widget->heightScalabilityFactor()));
    contrastItem->setData(qVariantFromValue(variant), Qt::DisplayRole);
    QStandardItem* hueItem = new QStandardItem();
    variant.m_Text = SourceString::Saturation;
    variant.m_Value = QString::number(saturation - 7);
    variant.m_Slider = m_SaturationSlider;
    hueItem->setSizeHint(QSize((1174 - 278)  * g_Widget->widthScalabilityFactor(), 92 * g_Widget->heightScalabilityFactor()));
    hueItem->setData(qVariantFromValue(variant), Qt::DisplayRole);
    QStandardItem* volumeItem = new QStandardItem();
    variant.m_Text = SourceString::Volume;
    variant.m_Value = QString::number(volume);
    variant.m_Slider = m_VolumeSlider;
    volumeItem->setSizeHint(QSize(1174 - 278, 92 * g_Widget->heightScalabilityFactor()));
    volumeItem->setData(qVariantFromValue(variant), Qt::DisplayRole);
    QStandardItem* calibrateItem = new QStandardItem();
    variant.m_Text = SourceString::Calibrate;
    variant.m_Value.clear();
    variant.m_Slider = NULL;
    calibrateItem->setSizeHint(QSize((1174 - 278) * g_Widget->widthScalabilityFactor(), 92 * g_Widget->heightScalabilityFactor()));
    calibrateItem->setData(qVariantFromValue(variant), Qt::DisplayRole);
    QStandardItem* resetItem = new QStandardItem();
    variant.m_Text = SourceString::Reset;
    variant.m_Value.clear();
    variant.m_Slider = NULL;
    resetItem->setSizeHint(QSize((1174 - 278) * g_Widget->widthScalabilityFactor(), 92 * g_Widget->heightScalabilityFactor()));
    resetItem->setData(qVariantFromValue(variant), Qt::DisplayRole);
    QStandardItem* root = m_StandardItemModel->invisibleRootItem();
    root->setChild(0, 0, brightnessItem);
    root->setChild(1, 0, contrastItem);
    root->setChild(2, 0, hueItem);
    root->setChild(3, 0, volumeItem);
    root->setChild(4, 0, calibrateItem);
    root->setChild(5, 0, resetItem);
    m_Parent->setModel(m_StandardItemModel);
}

void GeneralListViewPrivate::connectAllSlots()
{
    qDebug() << "GeneralListViewPrivate::connectAllSlots";
    connectSignalAndSlotByNamesake(g_Setting, m_Parent);
    connectSignalAndSlotByNamesake(g_Audio, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_BrightnessSlider, SIGNAL(minusBtnRelease()),
                     m_Parent,           SLOT(onMinusBtnRelease()),
                     type);
    QObject::connect(m_BrightnessSlider, SIGNAL(plusBtnRelease()),
                     m_Parent,           SLOT(onPlusBtnRelease()),
                     type);
    QObject::connect(m_BrightnessSlider, SIGNAL(tickMarksMillesimalEnd(const int)),
                     m_Parent,           SLOT(onTickMarksMillesimalEnd(const int)),
                     type);
    QObject::connect(m_ConstrastSlider, SIGNAL(minusBtnRelease()),
                     m_Parent,          SLOT(onMinusBtnRelease()),
                     type);
    QObject::connect(m_ConstrastSlider, SIGNAL(plusBtnRelease()),
                     m_Parent,          SLOT(onPlusBtnRelease()),
                     type);
    QObject::connect(m_ConstrastSlider, SIGNAL(tickMarksMillesimalEnd(const int)),
                     m_Parent,          SLOT(onTickMarksMillesimalEnd(const int)),
                     type);
    QObject::connect(m_SaturationSlider, SIGNAL(minusBtnRelease()),
                     m_Parent,    SLOT(onMinusBtnRelease()),
                     type);
    QObject::connect(m_SaturationSlider, SIGNAL(plusBtnRelease()),
                     m_Parent,    SLOT(onPlusBtnRelease()),
                     type);
    QObject::connect(m_SaturationSlider, SIGNAL(tickMarksMillesimalEnd(const int)),
                     m_Parent,    SLOT(onTickMarksMillesimalEnd(const int)),
                     type);
    QObject::connect(m_VolumeSlider, SIGNAL(minusBtnRelease()),
                     m_Parent,       SLOT(onMinusBtnRelease()),
                     type);
    QObject::connect(m_VolumeSlider, SIGNAL(plusBtnRelease()),
                     m_Parent,       SLOT(onPlusBtnRelease()),
                     type);
    QObject::connect(m_VolumeSlider, SIGNAL(tickMarksMillesimalEnd(const int)),
                     m_Parent,       SLOT(onTickMarksMillesimalEnd(const int)),
                     type);
}

GeneralVariant::GeneralVariant()
{
    m_Slider = NULL;
    m_Text.clear();
    m_Value.clear();
}

GeneralVariant::~GeneralVariant()
{
}

GeneralDelegate::GeneralDelegate(QWidget *parent)
    : CustomItemDelegate(parent)
{
}

GeneralDelegate::~GeneralDelegate()
{
}

void GeneralDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    qDebug() << "GeneralDelegate::paint" << option.rect << option.rect.adjusted(0, 0, -17 * g_Widget->widthScalabilityFactor(), 0);
    GeneralVariant variant = qVariantValue<GeneralVariant>(index.data(Qt::DisplayRole));
    if (NULL != variant.m_Slider) {
        QRect rect(option.rect.x() + 209 * g_Widget->widthScalabilityFactor(), option.rect.y(), 636 * g_Widget->widthScalabilityFactor(), option.rect.height());
        variant.m_Slider->setGeometry(rect);
        //        qDebug() << "variant.m_Slider->" << variant.m_Slider->geometry();
    }
    painter->save();
    painter->fillRect(option.rect.adjusted(0, 0, -17 * g_Widget->widthScalabilityFactor(), 0), UserInterfaceUtility::listViewItemBrush());
    QFont font;
    font.setPointSize(20 *g_Widget->widthScalabilityFactor());
    painter->setFont(font);
    painter->setPen(Qt::white);
    QString text;
    text = QObject::tr(variant.m_Text.toLocal8Bit().constData());
    if (!variant.m_Value.isEmpty()) {
        text += QString(" ") + variant.m_Value;
    }
    painter->drawText(option.rect.adjusted(75 * g_Widget->widthScalabilityFactor(), 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, text);
    painter->setPen(UserInterfaceUtility::customBlackColor());
    painter->drawLine(QPoint(0, option.rect.y() + option.rect.height() - 1), QPoint(option.rect.width() - 17 * g_Widget->widthScalabilityFactor(), option.rect.y() + option.rect.height() - 1));
    painter->restore();
}
