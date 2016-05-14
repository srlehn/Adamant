#ifndef SHOPVIEWER_H
#define SHOPVIEWER_H

#include <QDir>
#include <QWidget>

namespace Ui {
class ShopViewer;
}

class AdamantShopPlugin;
class Shop;
class QListWidgetItem;

class ShopViewer : public QWidget
{
    Q_OBJECT

public:
    explicit ShopViewer(AdamantShopPlugin* plugin, QWidget *parent = 0);
    ~ShopViewer();

    void setLeagues(const QStringList &leagues);
    void setShops(const QList<Shop*> shops);

private slots:
    void on_leagueBox_currentTextChanged(const QString &arg1);

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    AdamantShopPlugin* _plugin;
    QList<Shop*> _shops;
    Ui::ShopViewer *ui;
};

#endif // SHOPVIEWER_H