
#include "C_Mat2File.h"

#define SameWithMatLab

C_Mat2File::~C_Mat2File(void){};
C_Mat2File::C_Mat2File(){}

void C_Mat2File::saveMat(Mat m, string path)
{
	FILE *fp = fopen(path.c_str(), "wt");

	for (int i = 0; i < m.rows; i ++){
		//		if (i%3==0){
		//fprintf(fp,"\n");
		//		}
		for (int j = 0; j < m.cols; j ++ ){
			if (m.type() == 0){
				fprintf(fp,"%-12d",m.at<uchar>(i,j));
			}else if (m.type() == 1){
				fprintf(fp,"%-12d",m.at<char>(i,j));
			}else if (m.type() == 2){
				fprintf(fp,"%-12d",m.at<ushort>(i,j));
			}else if (m.type() == 3){
				fprintf(fp,"%-12d",m.at<short>(i,j));
			}else if (m.type() < 5){
				fprintf(fp,"%-12d",m.at<int>(i,j));
			}else if(m.type() == 5){
				fprintf(fp,"%-12.2f",m.at<float>(i,j));				
			}else if(m.type() == 6){
				fprintf(fp,"%-20.0f",m.at<double>(i,j));				
			}else{
				fprintf(fp,"%-12d",m.at<double>(i,j));
			}			
		}
		fprintf(fp,"\n");
	}
	fprintf(fp,"\n");
	fclose(fp);
	/**********************************************************************************
	// 下面是对多通道数据的显示
	Mat m = points;
	FILE *fp = fopen("e:\\mat.txt","at");
	for (int i = 0; i < m.rows; i ++){
	for (int j = 0; j < m.cols; j ++ ){
	Vec2f p = m.at<Vec2f>(i,j);
	fprintf(fp,"%f,%f",p[0],p[1]);
	}
	fprintf(fp,"\n");
	}   
	**********************************************************************************/
}

void C_Mat2File::saveMatB(Mat savedMat, string path)
{
	FILE* pFile = fopen(path.c_str(), "wb");
	fwrite(&savedMat.rows, sizeof(int), 1, pFile);
	fwrite(&savedMat.cols, sizeof(int), 1, pFile);
	for(int r = 0; r < savedMat.rows; r++)
	{
		for(int c = 0; c < savedMat.cols; c++)
		{
			if ((savedMat.type() == 5) || (savedMat.type() == 6))
			{
				float matValue = savedMat.at<float>(r, c);
				fwrite(&matValue, sizeof(float), 1, pFile);
			}
			if (savedMat.type() == 0)
			{
				unsigned char matValue = savedMat.at<unsigned char>(r, c);
				fwrite(&matValue, sizeof(unsigned char), 1, pFile);
			}
		}
	}
	fclose(pFile);
}

Mat C_Mat2File::readMatB(string path, int matType)
{
	int matC;
	int matR;
	FILE* pFile = fopen(path.c_str(), "rb");
	fread(&matR, sizeof(int), 1, pFile);
	fread(&matC, sizeof(int), 1, pFile);	
	Mat re_mat = Mat(matR, matC, matType);
	for(int r = 0; r < matR; r++)
	{
		for(int c = 0; c < matC; c++)
		{
			if ((matType == 5) || (matType == 6))
			{
				float matValue;
				fread(&matValue, sizeof(float), 1, pFile);
				re_mat.at<float>(r, c) = matValue;
			}
			if ((matType == 0))
			{
				unsigned char matValue;
				fread(&matValue, sizeof(unsigned char), 1, pFile);
				re_mat.at<unsigned char>(r, c) = matValue;
			}
		}
	}
	fclose(pFile);
	return re_mat;
}