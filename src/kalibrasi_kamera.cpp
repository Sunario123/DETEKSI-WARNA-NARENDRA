#include <opencv4/opencv2/opencv.hpp>
#include <iostream>

/*
Nama: Narendra Andhi Putra Pratama
NRP: 5022251034
Prodi: Teknik Elektro

Program deteksi warna kuning dengan tambahan bounding box
*/

int main(){
    cv::VideoCapture cam(0);

    cv::Mat frame;
    while (true)
    {
        cam >> frame;
        cv::Mat hsv;
        cv::cvtColor(frame,hsv,cv::COLOR_BGR2HSV);

        //menentukan batas bawah atas
        cv::Scalar batasbawah(15/2,100,100);
        cv::Scalar batastas(77/2,255,255);

        cv::Mat biner;

        //treshold
        cv::inRange(hsv,batasbawah,batastas,biner);

        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(biner, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        for (auto &contour : contours) {
            double area = cv::contourArea(contour);
            if (area > 10000) { // abaikan area kecil
                cv::Rect box = cv::boundingRect(contour);

                // Warna garis bounding box (B, G, R)
                cv::Scalar warnaGaris(0, 255, 255); // kuning

                // Gambar kotak dan label
                cv::rectangle(frame, box, warnaGaris, 2);
                cv::putText(frame, "Kuning", {box.x, box.y - 10},
                            cv::FONT_HERSHEY_SIMPLEX, 0.6, warnaGaris, 2);
            }
        }

        //memfilter warna yang sudah di filter

        cv::imshow("bounding box dan deteksi kuning", frame);
        cv::imshow("biner", biner);
        if(cv::waitKey(1) == 48){
            break;
        }

    }

    cam.release();
    cv::destroyAllWindows();
    return 0;
    
}