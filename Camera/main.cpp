#include <iostream>
#include <iomanip>
#include <video/video.hpp>
#include <opencv.hpp>
#include "commonFunction.h"
#include "fragile.h"

using namespace cv;
bool init = false;
int main(int argc, char** argv)
{
    Fragile f;
    VideoCapture cap(argv[1]); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
    {
        return -1;
    }
    HOGDescriptor hog;
    Mat mono_img;
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
    namedWindow("test",1);
    std::vector<Rect> found;
    std::vector<Rect> foundsave;
    std::vector<std::vector<Rect> > found_filtered(3,std::vector<Rect>(0));
    int k = 0;
    Mat frame;
<<<<<<< HEAD
    Mat rW;
    Rect save(Point_<int>(0,0), Point_<int>(0,0));
    Point2d prevPos;
    std::vector<Point2d> src(4);
    src[0] = Point2d(263,281); src[1] = Point2d(7,265); src[2] = Point2d(357,147); src[3] = Point2d(161,147);
    std::vector<Point2d> dest(4);
    dest[0] = Point2d(3,0); dest[1] = Point2d(0,0); dest[2] = Point2d(3,4.5); dest[3] = Point2d(0,3);
    Mat H;
    H = findHomography(src,dest,H);
=======
    Rect save(Point_<int>(0,0),Point_<int>(0,0));
>>>>>>> b627d60e3b8e59da6299997913fa8606a8c7345e
    for(;;)
    {
        foundsave = found_filtered[k%3];
        found_filtered[k%3] = std::vector<Rect>(0);
        cap >> frame; // get a new frame from camera
        if(k==0)
        {
            rW = frame;
            warpPerspective(frame,rW,H,Size(1000,1000));
            imwrite("/home/benjamin.michelland/calibrated.png",rW);
        }
        cvtColor(frame, mono_img, CV_BGR2GRAY);
        hog.detectMultiScale(mono_img, found,-0.5);
        size_t i, j;
        for (i=0; i<found.size(); i++)
        {
            Rect r = found[i];
            for (j=0; j<found.size(); j++)
                if (j!=i && (r & found[j])==r)
                    break;
            if (j==found.size())
                found_filtered[k%3].push_back(r);
        }
        if(k>=3)
        {
            if(found_filtered[k%3].empty())
            {
                found_filtered[k%3] = foundsave;
            }
            if(!found_filtered[0].empty() && !found_filtered[1].empty() && !found_filtered[2].empty())
            {
                std::vector<int> list = threeNearest(save,found_filtered);
                for(unsigned i = 0; i < found_filtered[0].size(); i++) {
<<<<<<< HEAD
                    if(list[0] != -1 && list[1] != -1 && list[2] !=-1)
                    {
                        Rect r1 = found_filtered[0][list[0]];
                        Rect r2 = found_filtered[1][list[1]];
                        Rect r3 = found_filtered[2][list[2]];
                        Point_<int> c1 = r1.tl() + Point_<int>(r1.width/2,r1.height-10);
                        c1 = c1 + r2.tl() + Point_<int>(r2.width/2,r2.height-10);
                        c1 = c1 + r3.tl() + Point_<int>(r3.width/2,r3.height-10);
                        c1 = Point_<int>(c1.x/3.0,c1.y/3.0);
                        rectangle(frame, c1, c1, Scalar(0,255,0), 2);
                        save = Rect(c1,c1);
                    }
                }
                float speed = 0;
                if(k%25==0)
                {
                    std::vector<Point2d> pix(1);
                    pix[0] = save.tl();
                    std::vector<Point2d> pos(1);
                    perspectiveTransform(pix,pos,H);
                if(init)
                {
                    speed = sqrt((pos[0]-prevPos).dot(pos[0]-prevPos));
                    std::cout << std::setprecision(3) << speed << " m/s" << std::endl;
                }
                prevPos=pos[0];
                init = true;
=======
                    Rect r1 = found_filtered[0][list[0]];
                    Rect r2 = found_filtered[1][list[1]];
                    Rect r3 = found_filtered[2][list[2]];
                    Point_<int> c1 = r1.tl() + Point_<int>(r1.width/2-1,r1.height-10);
                    Point_<int> c2 = r1.tl() + Point_<int>(r1.width/2+1,r1.height-10);
                    c1 = c1 + r2.tl() + Point_<int>(r2.width/2-1,r2.height-10);
                    c1 = c1 + r3.tl() + Point_<int>(r3.width/2-1,r3.height-10);
                    c2 = c2 + r2.tl() + Point_<int>(r2.width/2+1,r2.height-10);
                    c2 = c2 + r2.tl() + Point_<int>(r3.width/2+1,r3.height-10);
                    c1 = Point_<int>(c1.x/3.0,c1.y/3.0); c2 = Point_<int>(c2.x/3.0,c2.y/3.0);
                    rectangle(frame, c1, c2, Scalar(0,255,0), 2);
                    save = Rect(c1,c2);
>>>>>>> b627d60e3b8e59da6299997913fa8606a8c7345e
                }
            }
        }
        imshow("test", frame);
        if(waitKey(30) >= 0) break;
        k++;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
