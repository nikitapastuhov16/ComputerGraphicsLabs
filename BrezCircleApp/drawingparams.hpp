#ifndef DRAWINGPARAMS_HPP
#define DRAWINGPARAMS_HPP

#include <parts.h>
#include <QVector>

class DrawingParams
{
public:
    DrawingParams();
    QVector<Parts> params;
    bool contains(Parts a);
    void addParams(Parts a);
};

#endif // DRAWINGPARAMS_HPP
