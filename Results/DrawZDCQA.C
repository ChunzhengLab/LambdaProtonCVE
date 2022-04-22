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
  TString fPeriod = "LHC18r";
  TFile* inputFile = nullptr;
  if(fPeriod.EqualTo("LHC10h")) inputFile = TFile::Open("./LHC10h/AnalysisResults_Run139507.root", "READ");
  if(fPeriod.EqualTo("LHC18q")) inputFile = TFile::Open("./LHC18q/AnalysisResults_Run295791.root", "READ");
  if(fPeriod.EqualTo("LHC18r")) inputFile = TFile::Open("./LHC18r/AnalysisResults_Run297479.root", "READ");
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

  SetStyle(XX_recenter ,ci[0], kFullCircle,1,1);
  SetStyle(XY_recenter ,ci[1], kFullCircle,1,1);
  SetStyle(YX_recenter ,ci[2], kFullCircle,1,1);
  SetStyle(YY_recenter ,ci[3], kFullCircle,1,1);

  TLegend *legend = new TLegend(0.2,0.65,0.48,0.85);
  legend->AddEntry(XX_gain,"XAXC","lp");
  legend->AddEntry(XY_gain,"XAYC","lp");
  legend->AddEntry(YX_gain,"YAXC","lp");
  legend->AddEntry(YY_gain,"YAYC","lp");

  TH2D* dummy_XX;
  if(fPeriod.EqualTo("LHC10h")) dummy_XX = new TH2D("","",1,0,80,1,-0.02,0.02);
  if(fPeriod.EqualTo("LHC18q")) dummy_XX = new TH2D("","",1,0,80,1,-0.003,0.008);
  if(fPeriod.EqualTo("LHC18r")) dummy_XX = new TH2D("","",1,0,80,1,-0.002,0.002);
  dummy_XX->SetXTitle("Centrality (%)");
  dummy_XX->SetYTitle("QQ");

  TCanvas* cXX = new TCanvas("","",800,300);
  cXX->Divide(2,1);
  cXX->cd(1);
  dummy_XX->Draw("SAME");
  XX_gain->Draw("SAME");
  XY_gain->Draw("SAME");
  YX_gain->Draw("SAME");
  YY_gain->Draw("SAME");
  legend->Draw("SAME");

  cXX->cd(2);
  dummy_XX->Draw("SAME");
  XX_recenter->Draw("SAME");
  XY_recenter->Draw("SAME");
  YX_recenter->Draw("SAME");
  YY_recenter->Draw("SAME");
  legend->Draw("SAME");

  if(fPeriod.EqualTo("LHC10h")) cXX->SaveAs("ZDCXX10h.pdf");
  if(fPeriod.EqualTo("LHC18q")) cXX->SaveAs("ZDCXX18q.pdf");
  if(fPeriod.EqualTo("LHC18r")) cXX->SaveAs("ZDCXX18r.pdf");

  TH2D* fHist2DPsi1ZNCCent= (TH2D*) inputList->FindObject("fHist2DPsi1ZNCCent");
  TH2D* fHist2DPsi1ZNACent= (TH2D*) inputList->FindObject("fHist2DPsi1ZNACent");

  TH1D* hPsi1ZNCCent3040 = (TH1D*) fHist2DPsi1ZNCCent -> ProjectionY("hPsi1V0CCent3040",5,8);
  TH1D* hPsi1ZNACent3040 = (TH1D*) fHist2DPsi1ZNCCent -> ProjectionY("hPsi1V0ACent3040",5,8);

  hPsi1ZNCCent3040 ->GetXaxis()->SetRangeUser(0,TMath::TwoPi());
  hPsi1ZNACent3040 ->GetXaxis()->SetRangeUser(0,TMath::TwoPi());

  hPsi1ZNCCent3040 ->SetMinimum(0);
  hPsi1ZNACent3040 ->SetMinimum(0);

  hPsi1ZNCCent3040->SetXTitle("#Psi_{1}");
  hPsi1ZNCCent3040->SetXTitle("#Psi_{1}");

  TCanvas* c3040 = new TCanvas("","",800,300);
  c3040->Divide(2,1);
  c3040->cd(1);
  hPsi1ZNCCent3040 -> Draw();
  c3040->cd(2);
  hPsi1ZNACent3040 -> Draw();

  if(fPeriod.EqualTo("LHC10h")) c3040->SaveAs("PsiZDC304010h.pdf");
  if(fPeriod.EqualTo("LHC18q")) c3040->SaveAs("PsiZDC304018q.pdf");
  if(fPeriod.EqualTo("LHC18r")) c3040->SaveAs("PsiZDC304018r.pdf");
}
