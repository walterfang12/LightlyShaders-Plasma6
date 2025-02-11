#include "../lightlyshaders.h"
#include "lightlyshaders_kcm.h"
#include "kwineffects_interface.h"

#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusArgument>

#include <KPluginFactory>

namespace KWin
{

K_PLUGIN_CLASS(LightlyShadersKCM)

LightlyShadersKCM::LightlyShadersKCM(QObject* parent, const KPluginMetaData &data)
    : KCModule(parent, data)
{
    ui.setupUi(widget());
    addConfig(LightlyShadersConfig::self(), widget());

    if(ui.kcfg_CornersType->currentIndex() == LSHelper::SquircledCorners) {
        ui.kcfg_SquircleRatio->setEnabled(true);
    } else {
        ui.kcfg_SquircleRatio->setEnabled(false);
    }

    connect( ui.kcfg_CornersType, SIGNAL(currentIndexChanged(int)), SLOT(updateChanged()) );

}

void
LightlyShadersKCM::load()
{
    KCModule::load();
    LightlyShadersConfig::self()->load();
}

void
LightlyShadersKCM::save()
{
    LightlyShadersConfig::self()->save();
    KCModule::save();

    OrgKdeKwinEffectsInterface interface(QStringLiteral("org.kde.KWin"),
                                         QStringLiteral("/Effects"),
                                         QDBusConnection::sessionBus());
    interface.reconfigureEffect(QStringLiteral("kwin_effect_lightlyshaders"));
    interface.reconfigureEffect(QStringLiteral("lightlyshaders_blur"));
}

void
LightlyShadersKCM::defaults()
{
    KCModule::defaults();
    LightlyShadersConfig::self()->setDefaults();
}

void
LightlyShadersKCM::updateChanged()
{

    if(ui.kcfg_CornersType->currentIndex() == LSHelper::SquircledCorners) {
        ui.kcfg_SquircleRatio->setEnabled(true);
    } else {
        ui.kcfg_SquircleRatio->setEnabled(false);
    }

}

} // namespace KWin

#include "lightlyshaders_kcm.moc"
