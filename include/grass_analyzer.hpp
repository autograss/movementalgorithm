#include "image.hpp"

using namespace std;


class GrassAnalyzer
{
    public:
        cv::Mat find_line(Image image);
        cv::Mat entropy(cv::Mat image);
        void getLocalEntropyImage(cv::Mat gray, cv::Rect roi, cv::Mat entropy);
        void ind_to_sub(int p, int num_dims, int *cumprod, int *coords);
        int32_t sub_to_ind(int32_t *coords, int32_t *cumprod, int32_t num_dims);
        void removeSmallBlobs(cv::Mat& im, double size);
      
};

