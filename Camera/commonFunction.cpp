#include "commonFunction.h"

using namespace cv;

std::vector<int> threeNearest(Rect p, std::vector<std::vector<Rect> > f)
{
    if(f.size() < 3)
    {
        std::cout << "il n'y a pas assez de points" << std::endl;
    }

    double dot1 = std::numeric_limits<double>::max();
    double dot2 = std::numeric_limits<double>::max();
    double dot3 = std::numeric_limits<double>::max();
    std::vector<int> out(3); out[0]=-1; out[1]=-1; out[2]=-1;
    Point_<int> pp = p.tl() + Point_<int>(p.width/2,p.height/2);
    for(unsigned int i = 0; i < f[0].size(); i++)
    {
        Point_<int> fp = f[0][i].tl() + Point_<int>(f[0][i].width/2,f[0][i].height/2);
        double dot = (pp-fp).dot(pp-fp);
        if(dot1>dot && dot <= 25000.0)
        {
            dot1=dot;
            out[0]=i;
        }
    }
    for(unsigned int i = 0; i < f[1].size(); i++)
    {
        Point_<int> fp = f[1][i].tl() + Point_<int>(f[1][i].width/2,f[1][i].height/2);
        double dot = (pp-fp).dot(pp-fp);
        if(dot2>dot && dot <= 25000.0)
        {
            dot2=dot;
            out[1]=i;
        }
    }
    for(unsigned int i = 0; i < f[2].size(); i++)
    {
        Point_<int> fp = f[2][i].tl() + Point_<int>(f[2][i].width/2,f[2][i].height/2);
        double dot = (pp-fp).dot(pp-fp);
        if(dot3>dot && dot <= 25000.0)
        {
            dot3=dot;
            out[2]=i;
        }
    }

    return out;
}
