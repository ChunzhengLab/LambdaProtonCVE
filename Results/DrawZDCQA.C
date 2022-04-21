#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TProfile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TLegend.h"


template <class TH>
void SetStyle(TH &hist, unsigned int color, unsigned int markerStyle, double markerSize = 1, double lineWidth = 1) 
{
  hist->SetLineColor(color);
  hist->SetMarkerColor(color);
  hist->SetMarkerStyle(markerStyle);
  hist->SetMarkerSize(markerSize);
  hist->SetLineWidth(lineWidth);
}

void DrawZDCQA() {
  //gStyle->SetErrorX(0.0001);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetOptStat(0);

  int ci[4];
  TColor* color[4];
  ci[0] = TColor::GetFreeColorIndex();
  color[0] = new TColor(ci[0],   0/255.,  24/255., 113/255.);//blue
  ci[1] = TColor::GetFreeColorIndex();
  color[1] = new TColor(ci[1], 255/255.,  88/255.,  93/255.);//red
  ci[2] = TColor::GetFreeColorIndex();
  color[2] = new TColor(ci[2], 255/255., 181/255.,  73/255.);//yellow
  ci[3] = TColor::GetFreeColorIndex();
  color[3] = new TColor(ci[3], 65/255.,  182/255., 230/255.);//light blue

  TList* inputList = nullptr;
  TString fPeriod = "LHC18q";
  TFile* inputFile = nullptr;
  if(fPeriod.EqualTo("LHC10h")) inputFile = TFile::Open("./LHC10h/AnalysisResults_Run139507.root", "READ");
  if(fPeriod.EqualTo("LHC18q")) inputFile = TFile::Open("./LHC18q/AnalysisResults_Run295791.root", "READ");
  if(fPeriod.EqualTo("LHC18r")) inputFile = TFile::Open("./LHC18r/AnalysisResults_18r_PlanePt5_ProtonPt3.root", "READ");
  inputList = (TList*) inputFile->Get("output_"); 

  TProfile* XX_gain = (TProfile*) inputList->FindObject("fProfileZDCQxAQxCCentGE");
  TProfile* XY_gain = (TProfile*) inputList->FindObject("fProfileZDCQxAQyCCentGE");
  TProfile* YX_gain = (TProfile*) inputList->FindObject("fProfileZDCQyAQxCCentGE");
  TProfile* YY_gain = (TProfile*) inputList->FindObject("fProfileZDCQyAQyCCentGE");

  XX_gain->Rebin(5);
  XY_gain->Rebin(5);
  YX_gain->Rebin(5);
  YY_gain->Rebin(5);

  SetStyle(XX_gain ,ci[0], kFullCircle,1,1);
  SetStyle(XY_gain ,ci[1], kFullCircle,1,1);
  SetStyle(YX_gain ,ci[2], kFullCircle,1,1);
  SetStyle(YY_gain ,ci[3], kFullCircle,1,1);

  TProfile* XX_recenter = (TProfile*) inputList->FindObject("fProfileZDCQxAQxCCentRC");
  TProfile* XY_recenter = (TProfile*) inputList->FindObject("fProfileZDCQxAQyCCentRC");
  TProfile* YX_recenter = (TProfile*) inputList->FindObject("fProfileZDCQyAQxCCentRC");
  TProfile* YY_recenter = (TProfile*) inputList->FindObject("fProfileZDCQyAQyCCentRC");

  XX_recenter->Rebin(5);
  XY_recenter->Rebin(5);
  YX_recenter->Rebin(5);
  YY_recenter->Rebin(5);

  SetStyle(XX_recenter ,ci[0], kOpenCircle,1,1);
  SetStyle(XY_recenter ,ci[1], kOpenCircle,1,1);
  SetStyle(YX_recenter ,ci[2], kOpenCircle,1,1);
  SetStyle(YY_recenter ,ci[3], kOpenCircle,1,1);

  TCanvas* cGE = new TCanvas("","",400,400);
  XX_gain->Draw("SAME");
  XY_gain->Draw("SAME");
  YX_gain->Draw("SAME");
  YY_gain->Draw("SAME");

  TCanvas* cRC = new TCanvas("","",400,400);
  XX_recenter->Draw("SAME");
  XY_recenter->Draw("SAME");
  YX_recenter->Draw("SAME");
  YY_recenter->Draw("SAME");
  
  // TH2D* fHist2DCalibPsi1ZNCCent = (TH2D*) inputList->FindObject("fHist2DCalibPsi1ZNCCentRC");
  // TH2D* fHist2DCalibPsi1ZNACent = (TH2D*) inputList->FindObject("fHist2DCalibPsi1ZNACentRC");
  // fHist2DCalibPsi1ZNCCent ->Draw("lego");
  // fHist2DCalibPsi1ZNACent ->Draw("lego");
}
