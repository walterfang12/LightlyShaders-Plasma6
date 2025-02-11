#pragma once
 
#include <kcmodule.h>
#include "lightlyshaders_config.h"
#include "ui_lightlyshaders_config.h"

namespace KWin
{

class LightlyShadersKCM : public KCModule
{
    Q_OBJECT
public:
    explicit LightlyShadersKCM(QObject* parent, const KPluginMetaData &data);
public Q_SLOTS:
    void save() override;
    void load() override;
    void defaults() override;
    void updateChanged();

private:
    void setChanged(bool value);
    Ui::LightlyShadersKCM ui;
};

} // namespace KWin