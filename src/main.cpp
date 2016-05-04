#include <stdio.h>
#include <winsock.h>

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

#include "common/common.h"

int main(int argc, char **argv)
{
  fprintf(stdout, "Hello World");
  
  const char *language = "eng";
  const char *datapath = "../tessdata/";
  const char* filename = NULL;
  PIX  *pix;

  tesseract::TessBaseAPI *tAPI = new tesseract::TessBaseAPI();

  printf("Tesseract-ocr version: %s\n",
         tesseract::TessBaseAPI::Version());
  printf("Leptonica version: %s\n",
         getLeptonicaVersion());

  if (argv[1] == NULL) {
      filename = "../phototest.tif";
  } else {
      filename = argv[1];
  }

  // Create pix
  FILE *fp = fopen(filename, "r");
  if (fp) {
    fclose(fp);
    pix = pixRead(filename);
    if (pix == NULL) {
        printf("Unsupported image type.\n");
        exit(3);
    }
    else {
        printf("Pix created\n");
    }
  } else {
    printf("file '%s' doesn't exist.\n", filename);
    exit(3);
  }

  // Initalize tesseract
  int rc = tAPI->Init(datapath, language, tesseract::OEM_DEFAULT, NULL, 0, NULL, NULL, false);
  if (rc) {
    fprintf(stderr, "Could not initialize tesseract.\n");
    exit(1);
  }

  // Set PIX for OCR
  tAPI->SetImage(pix);

  // Optional: set rectangle to OCR
  //BUILD OF MATERIALS section when rendered at 600 zoom
  int x1 = 5086, y1 = 175, x2 = 6835, y2 = 4165;
  tAPI->SetRectangle(x1, y1, x2-x1, y2-y1);

  // run ocr
  char* outText = tAPI->GetUTF8Text();
  printf("OCR output:\n\n");
  printf(outText);

  tAPI->Clear();
  tAPI->End();
  delete [] outText;
  pixDestroy(&pix);
  return 0;
}
