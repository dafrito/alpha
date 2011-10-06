#ifndef LOGO_H
#define LOGO_H

#include <QObject>
#include <QColor>

class Patch;
struct Geometry;

class Logo : public QObject
{
public:
    Logo(QObject *parent, qreal s = 1.0);
    ~Logo();
    void setColor(QColor c);
    void draw() const;
private:
    void buildGeometry(qreal s);

    QList<Patch *> parts;
    Geometry *geom;
};

#endif // LOGO_H

// vim: set ts=4 sw=4 et! :
