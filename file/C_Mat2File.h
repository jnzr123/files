#pragma once
#include <vector>
#include <iosfwd>
#include <fstream>
#include "opencv2//opencv.hpp"

using namespace std;
using namespace cv;

class C_Mat2File
{
private:
public:
	~C_Mat2File(void);
	C_Mat2File();

	void saveMat(Mat m, string path);
	Mat readMatB(string path, int matType);
	void saveMatB(Mat savedMat, string path);
};
