#include <opencv4/opencv2/opencv.hpp>
#include <chrono>
#include <iostream>
#include <thread>
using namespace std;
using namespace cv;
string pixelToASCII (int strength_display) {
  //Use below characters for displaying output.
  const string ASCII_CHARS = "   ._-=+*!&#%$@";
  string s =
      string (1, ASCII_CHARS [strength_display * ASCII_CHARS.length () / 256]);
  return s;
} int main() {
  string path_to_src = "/home/magi-01/Work/CODE/HOME/MAJOR/ascii_video/video-to-ascii-cpp/vid1.mp4";
  VideoCapture cap (path_to_src);
  double fps = cap.get (CAP_PROP_FPS);
  cout << fps << endl;
  int frame_duration_ms = 1000 / fps;
  int width = 250;
  int height = 50;
  int frame_width = cap.get (CAP_PROP_FRAME_WIDTH);
  int frame_height = cap.get (CAP_PROP_FRAME_HEIGHT);
  cout << frame_width << " " << frame_height << endl;
  // Resolution Initial: L4096W2160
  // Resolution Final: L751W944
  height = (width * frame_height / frame_width) * 0.4194;
  Mat frame, gray_frame, resized_frame;
  while (1) {
    cap >> frame;
    if (frame.empty ())
      break;
    cv::cvtColor (frame, gray_frame, cv::COLOR_BGR2GRAY);
    resize (gray_frame, resized_frame, Size (width, height), 0, 0, INTER_LINEAR);
    string output_cycle;
    for (int x = 0; x < height; x++) {
      for (int y = 0; y < width; y++) {
        output_cycle += pixelToASCII (resized_frame.at<uchar> (x, y));
      } output_cycle += "\n";
    } system ("clear"); //Clear Console to refresh video output
    cout << output_cycle;
    std::this_thread::sleep_for (std::chrono::milliseconds (frame_duration_ms));
  } return 0;
}
