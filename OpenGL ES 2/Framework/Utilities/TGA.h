#pragma once

char * LoadTGA( const char * szFileName, int * width, int * height, int * bpp );
char *ExtractFace(char * pSrc, int textureWidth, int textureHeight, int faceWidth, int faceHeight, int offsetX, int offsetY, int bpp);
