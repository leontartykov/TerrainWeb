#ifndef _BMP_STRUCTURE_H_
#define _BMP_STRUCTURE_H_

typedef int FXPT2DOT30;

typedef struct tagCIEXYZ {
  FXPT2DOT30 ciexyzX;
  FXPT2DOT30 ciexyzY;
  FXPT2DOT30 ciexyzZ;
} CIEXYZ;

typedef struct {
    CIEXYZ  ciexyzRed;
    CIEXYZ  ciexyzGreen;
    CIEXYZ  ciexyzBlue;
} CIEXYZTRIPLE;

typedef struct {
    unsigned short bfType;
    unsigned int   bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int   bfOffBits;
} BITMAPFILEHEADER;

typedef struct
{
    unsigned int        bSize;
    unsigned int        bWidth;
    unsigned int        bHeight;
    unsigned short    bPlanes;
    unsigned short    bBitCount;
    unsigned int        bCompression;
    unsigned int        bSizeImage;
    unsigned int        bXPelsPerMeter;
    unsigned int        bYPelsPerMeter;
    unsigned int        bClrUsed;
    unsigned int        bClrImportant;
    unsigned int        bRedMask;
    unsigned int        bGreenMask;
    unsigned int        bBlueMask;
    unsigned int        bAlphaMask;
    unsigned int        bCSType;
    CIEXYZTRIPLE      bEndpoints;
    unsigned int        bGammaRed;
    unsigned int        bGammaGreen;
    unsigned int        bGammaBlue;
    unsigned int        bIntent;
    unsigned int        bProfileData;
    unsigned int        bProfileSize;
    unsigned int        bReserved;
} BITMAPV5HEADER;

typedef struct {
    unsigned char  rgbBlue;
    unsigned char  rgbGreen;
    unsigned char  rgbRed;
    unsigned char  rgbReserved;
} RGBQUAD;

typedef struct {
    unsigned char  rgbBlue;
    unsigned char  rgbGreen;
    unsigned char  rgbRed;
} RGB_COLORS;

#endif
