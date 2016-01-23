#include "pluginitem.h"
#include "ui_pluginitem.h"

PluginItem::PluginItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PluginItem)
{
    ui->setupUi(this);
}

PluginItem::~PluginItem()
{
    delete ui;
}

void PluginItem::SetVersionString(const QString &version) {
    ui->versionLabel->setText(version);
}

void PluginItem::SetText(const QString &text) {
    ui->nameLabel->setText(text);
}

void PluginItem::SetSelected(bool selected) {
    setBackgroundRole(selected ? QPalette::Highlight : QPalette::Background);
    setForegroundRole(selected ? QPalette::HighlightedText : QPalette::Text);
}

void PluginItem::SetState(PluginState state) {
    setStyleSheet("");
    switch(state) {
        case PluginState::Unknown: {
            ui->verifiedLabel->setText("");
        } break;
        case PluginState::UpdateRequired: {
            ui->verifiedLabel->setText("Update Required");
        } break;
        case PluginState::UpToDate: {
            ui->verifiedLabel->setText("Verified");
        } break;
        case PluginState::Unverified: {
            ui->verifiedLabel->setText("<font color='red'>Failed to Verify</font>");
        } break;
    }
}
