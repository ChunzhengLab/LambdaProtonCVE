#include "TFile.h"
#include "TDirectoryFile.h"
#include "TList.h"
#include "TTree.h"
#include "TString.h"
#include "TObject.h"
#include "TKey.h"
#include "TIterator.h"
void FillList(){
  TFile* inputFile = TFile::Open("calibV015oP2.root");
  TList* ZDCCalibList = new TList();

  TObject *obj;
  TKey *key;
  TIter next(inputFile->GetListOfKeys());
  while ((key = (TKey *) next())) {
   obj = inputFile->Get(key->GetName()); // copy object to memory
   ZDCCalibList->Add(obj);
   printf(" found object:%s\n",key->GetName());
  }

  TFile* OutputFile = new TFile("VZEROCalibFile.root","RECREATE");
  ZDCCalibList->Write("VZEROCalibList",TObject::kSingleKey);
  inputFile->Close();
  OutputFile->Close();
}