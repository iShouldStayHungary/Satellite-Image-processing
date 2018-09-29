#include "StdAfx.h"
#include<iostream>
using namespace std;
#include"./gdal/gdal_priv.h"
#pragma comment(lib,"gdal_i.lib")

int main()
{
	//ͼ������
	GDALDataset*  poSrcDS;
	//ͼ�����
	GDALDataset* poDstDS;
   //ͼ��ĸ߶ȣ����
	int imgx,imgy;
	//����ͼ��·��
	char* srcPath  = "daxiang.jpg";
	//���ͼ��·��
	char * dstPath = "two.tif";
	//ͼ����ڴ�ռ�
	GByte* bufferTmp;
	int i, bandNum;

	//ע������
	GDALAllRegister();

	//��ͼ��
	poSrcDS = (GDALDataset *)GDALOpenShared(srcPath,GA_ReadOnly);

	//��ȡͼ��ĸ߶ȣ���ȣ�������
	imgx = poSrcDS->GetRasterXSize();
	imgy = poSrcDS->GetRasterYSize();
    bandNum = poSrcDS->GetRasterCount();

	//�����ȡ���
	cout<<"Image x width:"<<imgx<<endl;
	cout<<"Image y height:"<<imgy<<endl;
	cout<<"Band Number:"<<bandNum<<endl;

	//�����ڴ�
	bufferTmp = (GByte*)CPLMalloc(imgx*imgy*sizeof(GByte));

	//�������ͼ��
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
		dstPath, imgx, imgy, bandNum, GDT_Byte,NULL);

	//�ֲ������
	for( i  = 0; i < bandNum; i++)
	{
		poSrcDS->GetRasterBand(i + 1)->RasterIO(GF_Read,
			0,0, imgx, imgy ,bufferTmp, imgx, imgy, GDT_Byte, 0,0);

		poDstDS->GetRasterBand(i + 1)->RasterIO(GF_Write,
			0,0, imgx, imgy ,bufferTmp, imgx, imgy, GDT_Byte, 0,0);
		cout<<"band  "<<i<<"   processing....."<<endl;
	}

	//�������
	CPLFree(bufferTmp);
	//�ر����������
	GDALClose(poSrcDS);
	GDALClose(poDstDS);

	system("pause");
	return 0;


}