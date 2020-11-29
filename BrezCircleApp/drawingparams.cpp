#include "drawingparams.hpp"
#include <mainwindow.h>

DrawingParams::DrawingParams()
{

}

bool DrawingParams::contains(Parts a)
{
    return params.contains(a);
}

void DrawingParams::addParams(Parts a)
{
    if(!params.contains(a)) params.push_back(a);
}
