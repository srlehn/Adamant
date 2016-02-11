#ifndef GRAPHICITEMFACTORY_H
#define GRAPHICITEMFACTORY_H

#include <QObject>
#include <items/item.h>
#include <items/itemlocation.h>
#include <session/imagecache.h>
#include "graphicitem.h"

class GraphicItemFactory : public QObject
{
    Q_OBJECT
public:
    explicit GraphicItemFactory(ImageCache* cache)
        : QObject()
        , _imageCache(cache) {
        qRegisterMetaType<const ItemLocation*>("const ItemLocation*");
        qRegisterMetaType<QList<GraphicItem*>>("QList<GraphicItem*>");
        qRegisterMetaType<QSet<QString>>("QSet<QString>");
    }

signals:
    void OnItemsReady(QList<GraphicItem*> items, QSet<QString> images, void* ptr);

public slots:
    void SubmitLocation(const ItemLocation* location, void* ptr) {
        QList<GraphicItem*> items;
        QSet<QString> images;
        for (const Item* item : location->items()) {
            QString icon = item->data("icon").toString();

            if (icon.startsWith("/")) {
                icon.prepend("https://www.pathofexile.com");
            }
            QString path = _imageCache->generateFileName(icon);

            GraphicItem* gItem = new GraphicItem(0, item, path);
            // Set to always show links
            gItem->ShowLinks(true, GraphicItem::ShowLinkReason::Always);

            if (_imageCache->hasLocalImage(icon)) {
                gItem->SetImage(_imageCache->getImage(icon));
            }
            else {
                images << icon;
            }
            items.append(gItem);
        }

        emit OnItemsReady(items, images, ptr);
    }
private:
    ImageCache* _imageCache;
};

#endif // GRAPHICITEMFACTORY_H
