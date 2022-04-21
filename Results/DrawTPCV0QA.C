#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TProfile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TLegend.h"
#include "TMath.h"

void DrawTPCV0QA() {
  //gStyle->SetErrorX(0.0001);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetOptStat(0);

  TList* inputList = nullptr;
  TString fPeriod = "LHC18q";
  TFile* inputFile = nullptr;
  if(fPeriod.EqualTo("LHC10h")) inputFile = TFile::Open("./LHC10h/AnalysisResults_Run139507.root", "READ");
  if(fPeriod.EqualTo("LHC18q")) inputFile = TFile::Open("./LHC18q/AnalysisResults_Run295791.root", "READ");
  if(fPeriod.EqualTo("LHC18r")) inputFile = TFile::Open("./LHC18r/AnalysisResults_18r_PlanePt5_ProtonPt3.root", "READ");
  inputList = (TList*) inputFile->Get("output_"); 


  TH2D* fHist2DPsi2TPCPosCent = (TH2D*) inputList->FindObject("fHist2DPsi2TPCPosCent");
  TH2D* fHist2DPsi2TPCNegCent = (TH2D*) inputList->FindObject("fHist2DPsi2TPCNegCent");
  TH2D* fHist2DCalibPsi2V0CCent = (TH2D*) inputList->FindObject("fHist2DCalibPsi2V0CCentRC");
  TH2D* fHist2DCalibPsi2V0ACent = (TH2D*) inputList->FindObject("fHist2DCalibPsi2V0ACentRC");

  TH1D* hPsi2TPCCent2030 = (TH1D*) fHist2DPsi2TPCPosCent   -> ProjectionY("hPsi2TPCCent2030",5,6);
  TH1D* hPsi2V0CCent2030 = (TH1D*) fHist2DCalibPsi2V0CCent -> ProjectionY("hPsi2V0CCent2030",5,6);
  TH1D* hPsi2V0ACent2030 = (TH1D*) fHist2DCalibPsi2V0ACent -> ProjectionY("hPsi2V0ACent2030",5,6);

  TH1D* hPsi2TPCCent6070 = (TH1D*) fHist2DPsi2TPCPosCent   -> ProjectionY("hPsi2TPCCent6070",13,14);
  TH1D* hPsi2V0CCent6070 = (TH1D*) fHist2DCalibPsi2V0CCent -> ProjectionY("hPsi2V0CCent6070",13,14);
  TH1D* hPsi2V0ACent6070 = (TH1D*) fHist2DCalibPsi2V0ACent -> ProjectionY("hPsi2V0ACent6070",13,14);

  hPsi2TPCCent2030 ->GetXaxis()->SetRangeUser(0,TMath::Pi());
  hPsi2V0CCent2030 ->GetXaxis()->SetRangeUser(0,TMath::Pi());
  hPsi2V0ACent2030 ->GetXaxis()->SetRangeUser(0,TMath::Pi());

  hPsi2TPCCent6070 ->GetXaxis()->SetRangeUser(0,TMath::Pi());
  hPsi2V0CCent6070 ->GetXaxis()->SetRangeUser(0,TMath::Pi());
  hPsi2V0ACent6070 ->GetXaxis()->SetRangeUser(0,TMath::Pi());

  hPsi2TPCCent2030 ->SetMinimum(0);
  hPsi2V0CCent2030 ->SetMinimum(0);
  hPsi2V0ACent2030 ->SetMinimum(0);

  hPsi2TPCCent6070 ->SetMinimum(0);
  hPsi2V0CCent6070 ->SetMinimum(0);
  hPsi2V0ACent6070 ->SetMinimum(0);

  TCanvas* c2030 = new TCanvas("","",600,200);
  c2030->Divide(3,1);
  c2030->cd(1);
  hPsi2TPCCent2030 -> Draw();
  c2030->cd(2);
  hPsi2V0CCent2030 -> Draw();
  c2030->cd(3);
  hPsi2V0ACent2030 -> Draw();

  TCanvas* c6070 = new TCanvas("","",600,200);
  c6070->Divide(3,1);
  c6070->cd(1);
  hPsi2TPCCent6070 -> Draw();
  c6070->cd(2);
  hPsi2V0CCent6070 -> Draw();
  c6070->cd(3);
  hPsi2V0ACent6070 -> Draw();

  if(fPeriod.EqualTo("LHC10h")) {
    c2030->SaveAs("PsiTPCV02030_10h.pdf");
    c6070->SaveAs("PsiTPCV06070_10h.pdf");
  }
  if(fPeriod.EqualTo("LHC18q")) {
    c2030->SaveAs("PsiTPCV02030_18q.pdf");
    c6070->SaveAs("PsiTPCV06070_18q.pdf");
  }
  if(fPeriod.EqualTo("LHC18r")) {
    c2030->SaveAs("PsiTPCV02030_18r.pdf");
    c6070->SaveAs("PsiTPCV06070_18r.pdf");
  }
}
