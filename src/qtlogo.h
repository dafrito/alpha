#ifndef QTLOGO_H
#define QTLOGO_H

#include <QObject>
#include <QColor>

class Patch;
struct Geometry;

class QtLogo : public QObject
{
public:
    QtLogo(QObject *parent, qreal s = 1.0);
    ~QtLogo();
    void setColor(QColor c);
    void draw() const;
private:
    void buildGeometry(qreal s);

    QList<Patch *> parts;
    Geometry *geom;
};

#endif // QTLOGO_H
