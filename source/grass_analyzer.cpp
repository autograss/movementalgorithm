#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "image.hpp"
#include "grass_analyzer.hpp"

using namespace std;

cv::Mat GrassAnalyzer::find_line(Image image)
{

    cv::Mat ycbr_image;
    cv::cvtColor(image.getCvImage(), ycbr_image, CV_RGB2GRAY);
    image.setYcbcrImage(ycbr_image);

    cv::Mat blurred_image;

    medianBlur(ycbr_image, blurred_image, 41);

    cv::Mat bin_image;
    threshold(blurred_image, bin_image, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    cv::Mat threshold_image;
    threshold(bin_image, threshold_image, 0, 255, cv::THRESH_BINARY);

    float data[7][7] = {{1,1,1,1,1,1,1}, {1,1,1,1,1,1,1}};

    cv::Mat kernel = cv::Mat(2, 5, CV_32FC1, &data);

    cv::Mat dilate_image;
    dilate(threshold_image, dilate_image, kernel);

    cv::Mat entropy_image =  entropy(dilate_image);

    cv::Mat entropy2_image;
    threshold(entropy_image, entropy2_image, 204, 255, cv::THRESH_BINARY);

    removeSmallBlobs(entropy2_image, 2000);

    return entropy2_image;

    //img.convertTo( dimg, CV_64FC3, 1.0/255.0 );

}


cv::Mat GrassAnalyzer::entropy(cv::Mat image)
{
    cv::Rect roi(0, 0, image.cols, image.rows);
    cv::Mat dst(image.rows, image.cols, CV_32F);
    getLocalEntropyImage(image, roi, dst);
    cv::normalize(dst, dst, 0, 255, cv::NORM_MINMAX);
    cv::Mat entropy;
    dst.convertTo(entropy, CV_8U);
    return entropy;
}

void GrassAnalyzer::getLocalEntropyImage(cv::Mat gray, cv::Rect roi, cv::Mat entropy)
{
    using namespace cv;
    clock_t func_begin, func_end;
    func_begin = clock();
    //1.define nerghbood model,here it's 9*9
    int neighbood_dim = 2;
    int neighbood_size[] = {9, 9};

    //2.Pad gray_src
    Mat gray_src_mat(gray);
    Mat pad_mat;
    int left = (neighbood_size[0] - 1) / 2;
    int right = left;
    int top = (neighbood_size[1] - 1) / 2;
    int bottom = top;
    copyMakeBorder(gray_src_mat, pad_mat, top, bottom, left, right, BORDER_REPLICATE, 0);
    Mat *pad_src = &pad_mat;
    roi = cv::Rect(roi.x + top, roi.y + left, roi.width, roi.height);

    //3.initial neighbood object,reference to Matlab build-in neighbood object system
    //        int element_num = roi_rect.area();
    //here,implement a histogram by ourself ,each bin calcalate gray value frequence
    int hist_count[256] = {0};
    int neighbood_num = 1;
    for (int i = 0; i < neighbood_dim; i++)
        neighbood_num *= neighbood_size[i];

    //neighbood_corrds_array is a neighbors_num-by-neighbood_dim array containing relative offsets
    int *neighbood_corrds_array = (int *)malloc(sizeof(int)*neighbood_num * neighbood_dim);
    //Contains the cumulative product of the image_size array;used in the sub_to_ind and ind_to_sub calculations.
    int *cumprod = (int *)malloc(neighbood_dim * sizeof(*cumprod));
    cumprod[0] = 1;
    for (int i = 1; i < neighbood_dim; i++)
        cumprod[i] = cumprod[i - 1] * neighbood_size[i - 1];
    int *image_cumprod=(int*)malloc(2 * sizeof(*image_cumprod));
    image_cumprod[0] = 1;
    image_cumprod[1]= pad_src->cols;
    //initialize neighbood_corrds_array
    int p;
    int q;
    int *coords;
    for (p = 0; p < neighbood_num; p++){
        coords = neighbood_corrds_array+p * neighbood_dim;
        ind_to_sub(p, neighbood_dim, cumprod, coords);
        for (q = 0; q < neighbood_dim; q++)
            coords[q] -= (neighbood_size[q] - 1) / 2;
    }
    //initlalize neighbood_offset in use of neighbood_corrds_array
    int *neighbood_offset = (int *)malloc(sizeof(int) * neighbood_num);
    int *elem;
    for (int i = 0; i < neighbood_num; i++){
        elem = neighbood_corrds_array + i * neighbood_dim;
        neighbood_offset[i] = sub_to_ind(elem, image_cumprod, 2);
    }

    //4.calculate entroy for pixel
    uchar *array=(uchar *)pad_src->data;
    //here,use entroy_table to avoid frequency log function which cost losts of time
    float entroy_table[82];
    const float log2 = log(2.0f);
    entroy_table[0] = 0.0;
    float frequency = 0;
    for (int i = 1; i < 82; i++){
        frequency = (float)i / 81;
        entroy_table[i] = frequency * (log(frequency) / log2);
    }
    int neighbood_index;
    //        int max_index=pad_src->cols*pad_src->rows;
    float e;
    int current_index = 0;
    int current_index_in_origin = 0;
    for (int y = roi.y; y < roi.height; y++){
        current_index = y * pad_src->cols;
        current_index_in_origin = (y - 4) * gray.cols;
        for (int x = roi.x; x < roi.width; x++, current_index++, current_index_in_origin++) {
            for (int j=0;j<neighbood_num;j++) {
                neighbood_index = current_index+neighbood_offset[j];
                hist_count[array[neighbood_index]]++;
            }
            //get entropy
            e = 0;
            for (int k = 0; k < 256; k++){
                if (hist_count[k] != 0){
                    //                                        int frequency=hist_count[k];
                    e -= entroy_table[hist_count[k]];
                    hist_count[k] = 0;
                }
            }
            ((float *)entropy.data)[current_index_in_origin] = e;
        }
    }
    free(neighbood_offset);
    free(image_cumprod);
    free(cumprod);
    free(neighbood_corrds_array);

    func_end = clock();
    double func_time = (double)(func_end - func_begin) / CLOCKS_PER_SEC;
    std::cout << "func time" << func_time << std::endl;
}

void GrassAnalyzer::ind_to_sub(int p, int num_dims, int *cumprod, int *coords)
{
    int j;

    assert(num_dims > 0);
    assert(coords != NULL);
    assert(cumprod != NULL);

    for (j = num_dims-1; j >= 0; j--)
    {
        coords[j] = p / cumprod[j];
        p = p % cumprod[j];

    }

}

int32_t GrassAnalyzer::sub_to_ind(int32_t *coords, int32_t *cumprod, int32_t num_dims)
{
    int index = 0;
    int k;

    assert(coords != NULL);
    assert(cumprod != NULL);
    assert(num_dims > 0);

    for (k = 0; k < num_dims; k++)
    {
        index += coords[k] * cumprod[k];

    }

    return index;

}

void GrassAnalyzer::removeSmallBlobs(cv::Mat& im, double size)
{
    unsigned int value = 1;
    if (im.channels() != value || im.type() != CV_8U)
        return;
    std::vector<std::vector<cv::Point> > contours;
    cv::findContours(im.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    for (int i = 0; i < contours.size(); i++)
    {
        // Calculate contour area
        double area = cv::contourArea(contours[i]);

        // Remove small objects by drawing the contour with black color
        if (area > 0 && area <= size)
            cv::drawContours(im, contours, i, CV_RGB(0,0,0), -1);
    }
}
