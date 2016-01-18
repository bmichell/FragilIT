#include <iostream>
#include <video/video.hpp>
#include <opencv.hpp>

using namespace cv;

int main(int argc, char** argv)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;
    cv::HOGDescriptor hog;
    cv::Mat mono_img;
    hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
    std::vector<cv::Rect> found;
    namedWindow("test",1);
    std::vector<Point2f> src(4);
    src[0] = Point2f(716,464);src[1] = Point2f(758,742); src[2] = Point2f(371,754);src[3] = Point2f(390,478);
    std::vector<Point2f> dest(4);
    dest[0] = Point2d(0,0);dest[1] = Point2d(0,6);dest[2] = Point2d(6,6);dest[3] = Point2d(6,0);
    Mat h = findHomography(src,dest);
    std::vector<Point2f> dstPoint(1), srcPoint(1);
    srcPoint[0] = Point2f(617,552);dstPoint[0] = Point2f(617,552);
    perspectiveTransform(srcPoint,dstPoint,h);
    std::cout << dstPoint << std::endl;
    for(;;)
    {
        std::vector<cv::Rect> found_filtered;
        Mat frame;
        cap >> frame; // get a new frame from camera
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
                         found_filtered.push_back(r);
                }
        for(unsigned i = 0; i < found_filtered.size(); i++) {
            Rect r = found_filtered[i];
            rectangle(frame, r.tl(), r.br(), Scalar(0,255,0), 2);
        }
        imshow("test", frame);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
