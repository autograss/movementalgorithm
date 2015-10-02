#include <opencv2/opencv.hpp>
#include <string>


class WatershedSegmenter{
private:
  cv::Mat markers;
public:
  void setMarkers(cv::Mat& markerImage)
  {
    markerImage.convertTo(markers, CV_32S);
  }

  cv::Mat process(cv::Mat &image)
  {
    cv::watershed(image, markers);
    markers.convertTo(markers,CV_8U);
    return markers;
  }
};


int main(int argc, char* argv[])
{
  if ( argc != 2 )
  {
    std::cout << "Usage: " << argv[0] << " <image_path>" << std::endl;
    return -1;
  }

  cv::Mat image = cv::imread(argv[1]);
  cv::Mat binary;
  cv::cvtColor(image, binary, CV_BGR2GRAY);
  cv::threshold(binary, binary, 100, 255, cv::THRESH_BINARY);

  cv::imshow("originalimage", image);
  cv::imshow("originalbinary", binary);

  // Eliminate noise and smaller objects
  cv::Mat fg;
  cv::erode(binary, fg, cv::Mat(), cv::Point( -1, -1), 2);
  cv::imshow("fg", fg);

  // Identify image pixels without objects
  cv::Mat bg;
  cv::dilate(binary,bg,cv::Mat(),cv::Point(-1,-1),3);
  cv::threshold(bg, bg, 1, 128, cv::THRESH_BINARY_INV);
  cv::imshow("bg", bg);

  // Create markers image
  cv::Mat markers(binary.size(), CV_8U, cv::Scalar(0));
  markers = fg + bg;
  cv::imshow("markers", markers);

  // Create watershed segmentation object
  WatershedSegmenter segmenter;
  segmenter.setMarkers(markers);

  cv::Mat result = segmenter.process(image);
  result.convertTo(result, CV_8U);
  cv::imshow("final_result", result);

  cv::waitKey(0);

  return 0;
}
