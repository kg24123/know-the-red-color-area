#ifndef _HISTGRAM__H
#define _HISTGRAM__H
#include "cv.h"
#include "highgui.h"
#include "imgproc/imgproc.hpp"
#include "tinyxml2.h"
#include <iostream>
#include <fstream>
#include <stdio.h>

int ReadHsvStandValue(int *pnHmin, int *pnHmax,int *pnSmin, int *pnSmax, int *pnVmin, int *pnVmax);
#endif