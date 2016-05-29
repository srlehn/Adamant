#ifndef SHOPVIEWER_H
#define SHOPVIEWER_H

#include <QDir>
#include <QMenu>
#include <QWidget>

namespace Ui {
class ShopViewer;
}

class AdamantShopPlugin;
class Shop;
class QListWidgetItem;
class StashViewer;
class NewShopDialog;

class ShopViewer : public QWidget
{
    Q_OBJECT

public:
    explicit ShopViewer(AdamantShopPlugin* plugin, StashViewer* viewer, QWidget *parent = 0);
    ~ShopViewer();

    void setLeagues(const QStringList &leagues);
    void setupStashIntegration();
    void addShop(const Shop* shop, bool selected = false);
    void showShop(const Shop* shop);
private slots:
    void on_leagueBox_currentTextChanged(const QString &league);
    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_viewItemsButton_clicked();

    void on_newShopButton_clicked();

    void on_listWidget_customContextMenuRequested(const QPoint &pos);

    void on_addThreadButton_clicked();

private:
    AdamantShopPlugin* _plugin;
    StashViewer* _stashViewer;
    QList<Shop*> _shops;
    Shop* _currentShop;
    Ui::ShopViewer *ui;
    NewShopDialog* _shopDialog;
    QStringList _leagues;
};

#endif // SHOPVIEWER_H
