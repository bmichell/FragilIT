#include "commonFunction.h"

using namespace cv;

std::vector<int> threeNearest(Rect p, std::vector<std::vector<Rect> > f)
{
    if(f.size() < 3)
    {
        std::cout << "il n'y a pas assez de points" << std::endl;
    }

    int dot1 = p.tl().dot(f[0][0].tl());
    int dot2 = p.tl().dot(f[1][0].tl());
    int dot3 = p.tl().dot(f[2][0].tl());
    std::vector<int> out(3); out[0]=0; out[1]=0; out[2]=0;
    for(unsigned int i = 1; i < f[0].size(); i++)
    {
        if(dot1>(p.tl()-f[0][i].tl()).dot(p.tl()-f[0][i].tl()))
        {
            dot1=(p.tl()-f[0][i].tl()).dot(p.tl()-f[0][i].tl());
            out[0]=i;
        }
    }
    for(unsigned int i = 1; i < f[1].size(); i++)
    {
        if(dot2>(p.tl()-f[1][i].tl()).dot(p.tl()-f[1][i].tl()))
        {
            dot2=(p.tl()-f[1][i].tl()).dot(p.tl()-f[1][i].tl());
            out[1]=i;
        }
    }
    for(unsigned int i = 1; i < f[2].size(); i++)
    {
        if(dot3>(p.tl()-f[2][i].tl()).dot(p.tl()-f[2][i].tl()))
        {
            dot3=(p.tl()-f[2][i].tl()).dot(p.tl()-f[2][i].tl());
            out[2]=i;
        }
    }
    return out;
}
