#ifndef CHARACTERITEMLOCATION_H
#define CHARACTERITEMLOCATION_H

#include "itemlocation.h"
#include <QJsonObject>
#include <QString>

class CORE_EXTERN CharacterItemLocation : public ItemLocation
{
    Q_GADGET
public:
    CharacterItemLocation(const QJsonObject &data);

    LocationType location() const final;
    QString header() const final;
    QString hash() const final;
    QString forumCode(const Item &item) const final;
    bool operator<(const ItemLocation &other) const final;
    bool operator==(const ItemLocation &other) const final;
    QJsonObject toJson() const final;
    QPointF itemPos(const Item &item) const;
    QSizeF itemSize(const Item &item) const;

private:
    QString _name;
    QString _class;
    int _level;

    static QMap<QString, QPointF> InventoryLayout;
};

#endif // CHARACTERITEMLOCATION_H
