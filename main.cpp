#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/video.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    VideoCapture cap(1);


    if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open the video file" << endl;
         return -1;
    }

   // cap.get(CV_CAP_PROP_FPS);

    cap.set(CV_CAP_PROP_FOURCC,CV_FOURCC('Y','U','Y','V'));
    cap.set(CV_CAP_PROP_FRAME_WIDTH,352); //176,352,640,800
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,288); //144,288,360,600

    //cout << "Frame por segundo: " << fps << endl;

    int frame_width=cap.get(CV_CAP_PROP_FRAME_WIDTH);
    int frame_height=cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    VideoWriter video("out8.avi",CV_FOURCC('M','J','P','G'),3, Size(frame_width,frame_height),true);


    while(true)
    {
        Mat img,img2,src;
        cap >> img;
        cvtColor(img,img2,COLOR_BGR2GRAY);
        equalizeHist(img2,src);

    HOGDescriptor hog;
    vector<float> getPeopleDetector64x128();
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
    vector<Rect> found, found_filtered;
    hog.detectMultiScale(src, found,0, Size(4,4), Size(0,0),0.85,2,false);
    stringstream ss;
    string ObjNum = ss.str();
    ostringstream ContNum;

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
        for (i=0; i<found_filtered.size(); i++)
        {
            Rect r = found_filtered[i];
            r.x += cvRound(r.width*0.1);
            r.width = cvRound(r.width*0.8);
            r.y += cvRound(r.height*0.04);
            r.height = cvRound(r.height*0.75);
            rectangle(img, r.tl(), r.br(),Scalar(0,255,0), 2); //BGR
        }

        for(int i=0; i<found.size(); i++)
        {
            ContNum <<i+1;
            ObjNum = ContNum.str();
            Point pCoordinates(found[i].x+10,found[i].y+25);
            putText(img, ObjNum, pCoordinates, CV_FONT_HERSHEY_COMPLEX_SMALL,1,Scalar(0,255,0),1,8);
            cout << "Cantidad de personas: " << ObjNum << endl;
            ContNum.str("");
            ContNum.clear();
        }


     imshow("Deteccion HOG", img); //show the frame in "MyVideo" window

    video.write(img);

        if(waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
       {
                cout << "esc key is pressed by user" << endl;
                break;
       }
    }

                                            // Wait for a keystroke in the window
    return 0;
}
