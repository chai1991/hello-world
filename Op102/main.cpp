#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include<opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <iostream>

using namespace cv;
using namespace std;

static void help()
{
    cout << "\nThis program demonstrates circle finding with the Hough transform.\n"
            "Usage:\n"
            "./houghcircles <image_name>, Default is ../data/board.jpg\n" << endl;
}
/** hough _circle*/
/*static void hough_circle()
{
    cv::CommandLineParser parser(argc, argv,
        "{help h ||}{@image|../data/board.jpg|}"
    );
    if (parser.has("help"))
    {
        help();
        return 0;
    }
    //![load]
    string filename = parser.get<string>("@image");
    Mat img = imread(filename, IMREAD_COLOR);
    if(img.empty())
    {
        help();
        cout << "can not open " << filename << endl;
        return -1;
    }
    //![load]
    //![convert_to_gray]
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    //![convert_to_gray]
    //![reduce_noise]
    medianBlur(gray, gray, 5);
    //![reduce_noise]
    //![houghcircles]
    vector<Vec3f> circles;
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
                 gray.rows/16, // change this value to detect circles with different distances to each other
                 100, 30, 1, 30 // change the last two parameters
                                // (min_radius & max_radius) to detect larger circles
                 );
    //![houghcircles]

    //![draw]
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        circle( img, Point(c[0], c[1]), c[2], Scalar(0,0,255), 3, LINE_AA);
        circle( img, Point(c[0], c[1]), 2, Scalar(0,255,0), 3, LINE_AA);
    }
    //![draw]

    //![display]
    imshow("detected circles", img);
    waitKey();
    //![display]

}
*/
string path = "../data/";

Mat image;

Rect2d roi;
Point point1;
Rect selection;
bool secectionObj;
bool getRoi = false;

//在视频显示画面双击鼠标左键，设置跟踪目标
static void onMouse(int event, int x, int y, int, void*)
{

        switch (event)
        {
        case EVENT_LBUTTONDBLCLK://EVENT_LBUTTONDOWN://
                cout << "EVENT_LBUTTONDOWN" << endl;
                getRoi = false;
                secectionObj = true;
                break;
        }

}
int main(int argc, char** argv)
{
    //5种跟踪算法
            // "KCF"：目标人物与其他人在画面上大面积交错以后，会出现跟踪错误
            // "MIL"：速度慢
            //"BOOSTING"：非常慢，显示严重卡顿
            //"MEDIANFLOW"：比较流畅，但是跟踪效果差
            //"TLD"：非常慢，自动调整跟踪目标的大小（框），在目标周围没有明显干扰的情况下，也会跟踪错误
            string trackerTypeString = "KCF";
            string winName = "lsn6_hw:" + trackerTypeString;
            namedWindow(winName);
            setMouseCallback(winName, onMouse, 0);

            //打开视频文件
            VideoCapture vCap;
            vCap.open(path + "car.avi");
            if (!vCap.isOpened())
            {
                    cout << "Open file failed!" << endl;
                    waitKey(3000);
                    return -1;
            }

            double rate = vCap.get(CAP_PROP_FPS);
            int frameDly = 1000 / rate;

            //定义视频帧
            Mat frame;
            int frames = 0;

            //定义写视频
            bool intWriter = true;
            VideoWriter vWriter;

            Ptr<Tracker> tracker;// = Tracker::create("KCF");

            while (true)
            {
                    //读视频帧
                    if (!secectionObj)
                    {
                            if (vCap.read(frame) == false) break;
                    }

                    if (secectionObj)
                    {
                            //目标选择
                            tracker = Tracker::create(trackerTypeString);
                            string trackerName = "select roi:" + trackerTypeString + ", then SPACE or ENTER or ESC";
                            roi = selectROI(trackerName, frame);

                            if (roi.height > 0 && roi.width > 0)
                            {
                                    cout << "   get roi" << endl;
                                    tracker->init(frame, roi);
                                    getRoi = true;
                            }
                            secectionObj = false;
                    }
                    else
                    {
                            //跟踪目标刷新显示
                            if (getRoi)
                            {
                                    tracker->update(frame, roi);
                                    rectangle(frame, roi, Scalar(255, 0, 0), 2, 1);
                            }
                    }

                    imshow(winName, frame);

                    //写视频帧
                    if (intWriter)
                    {
                            intWriter = false;
                            vWriter.open("tracker_" + trackerTypeString+".avi", VideoWriter::fourcc('M', 'J', 'P', 'G'),rate,Size(frame.cols,frame.rows));        //CV_FOURCC('M', 'J', 'P', 'G')
                    }
                    else
                    {
                            //if (getRoi)
                            {
                                    if (frames < 200)
                                    {
                                            vWriter.write(frame);
                                            frames++;
                                    }
                            }
                    }

                    int key = waitKey(frameDly);
                    if (key == 27)                //ESC
                    {
                            break;
                    }
            }

            vWriter.release();



    return 0;
}
