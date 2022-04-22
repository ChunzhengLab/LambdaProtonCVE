#include "TFile.h"

void ReNameList(){
  TFile* inputFile = TFile::Open("10hNUAFB1.root");
  TList* list = (TList*)inputFile->Get("10hListNUAFB1");
  TFile* outputFile = new TFile("10hNUAFB1New.root","Recreate");
  list->Write("10hListNUA",TObject::kSingleKey);
}