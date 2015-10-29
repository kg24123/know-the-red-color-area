#include "JudgedRedColor.h"
int main(int argc, char** argv)
{
	using namespace cv;
	int nI = 0, nJ = 0, nHval = 0, nSval = 0, nVval = 0, nRedPixCount = 0;
	int nHmin = 0, nHmax = 0, nSmin = 0, nSmax = 0, nVmin = 0, nVmax = 0;
	if (ReadHsvStandValue(&nHmin, &nHmax, &nSmin, &nSmax, &nVmin, &nVmax))
	{
		return -1;
	}
	IplImage *pHSV = NULL, *pHimg = NULL, *pSimg = NULL, *pVimg = NULL, *pSrcImg = NULL;
	std::ofstream fOut("RedPixelRecord.txt",std::ios::app);
    pSrcImg = cvLoadImage("test1.jpg", 3);
	if (!pSrcImg)
	{
		return -1;
	}
	CvSize srcSize = cvGetSize(pSrcImg);
	pHSV = cvCreateImage(srcSize, 8, 3);
	pHimg = cvCreateImage(srcSize, 8, 1);
	pSimg = cvCreateImage(srcSize, 8, 1);
	pVimg = cvCreateImage(srcSize, 8, 1);
	cvCvtColor(pSrcImg, pHSV, CV_BGR2HSV);
	cvSplit(pHSV, pHimg, pSimg, pVimg, NULL);
	
	for (nI = 0; nI < pHimg->height; nI++)
	{
		for (nJ = 0; nJ < pHimg->width; nJ++)
		{
			nHval = (int)cvGetReal2D(pHimg, nI, nJ);
			if (nHval >= nHmin && nHval <= nHmax)
			{
				nSval = (int)cvGetReal2D(pSimg, nI, nJ);
				if (nSval >= nSmin && nSval <= nSmax)
				{
					nVval = (int)cvGetReal2D(pVimg, nI, nJ);
					if (nVval >= nVmin && nVval <= nVmax)
					{
						nRedPixCount++;
						fOut << "Red Pixel Coordinate,X:"<<nJ <<",Y:"<<nI<<"\n";
					}
				}
			}
		}
	}
	if (fOut.is_open())
	{
		fOut <<"all red pixel num:"<<nRedPixCount << "all pixel num:"<<pHimg->height*pHimg->width<<"\n";
		fOut.close();
	}
	waitKey(0);
	return 0;
}

int ReadHsvStandValue(int *pnHmin, int *pnHmax,int *pnSmin, int *pnSmax, int *pnVmin, int *pnVmax)
{
	std::ifstream fExit("HSVvalue.xml");
	if (fExit)
	{
		fExit.close();
		using namespace tinyxml2;
		XMLDocument xmlDoc;
		xmlDoc.LoadFile("HSVvalue.xml");
		XMLElement *pRoot = xmlDoc.RootElement();
		XMLElement *pNode = pRoot->FirstChildElement("HminValue");
		const char* strContent = NULL;
		strContent = pNode->GetText();
		*pnHmin = atoi(strContent);
		pNode = pRoot->FirstChildElement("HmaxValue");
		strContent = pNode->GetText();
		*pnHmax = atoi(strContent);

		pNode = pRoot->FirstChildElement("SminValue");
		strContent = pNode->GetText();
		*pnSmin = atoi(strContent);

		pNode = pRoot->FirstChildElement("SmaxValue");
		strContent = pNode->GetText();
		*pnSmax = atoi(strContent);

		pNode = pRoot->FirstChildElement("VminValue");
		strContent = pNode->GetText();
		*pnVmin = atoi(strContent);

		pNode = pRoot->FirstChildElement("VmaxValue");
		strContent = pNode->GetText();
		*pnVmax = atoi(strContent);
	}
	else 
	{
		return -1;
	}
	return 0;
}