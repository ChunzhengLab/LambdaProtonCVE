#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TProfile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TLegend.h"

void DrawLambdaQA() {
  gStyle->SetErrorX(0.0001);
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
  TString fPeriod = "LHC10h";
  TFile* inputFile = nullptr;
  if(fPeriod.EqualTo("LHC10h")) inputFile = TFile::Open("./LHC10h/AnalysisResults_10h_PlanePt5_ProtonPt3.root", "READ");
  if(fPeriod.EqualTo("LHC18q")) inputFile = TFile::Open("./LHC18q/AnalysisResults_18q_PlanePt5_ProtonPt3.root", "READ");
  if(fPeriod.EqualTo("LHC18r")) inputFile = TFile::Open("./LHC18r/AnalysisResults_18r_PlanePt5_ProtonPt3.root", "READ");

  inputList = (TList*) inputFile->Get("output_"); 

  TH1D*      fHistLambdaPt[2];
  TH1D*      fHistLambdaEta[2];
  TH1D*      fHistLambdaPhi[2];
  TH1D*      fHistLambdaDcaToPrimVertex[2];
  TH1D*      fHistLambdaCPA[2];
  TH1D*      fHistLambdaDecayLength[2];
  TH1D*      fHistLambdaMass[2];
  TH1D*      fHistAntiLambdaPt[2];
  TH1D*      fHistAntiLambdaEta[2];
  TH1D*      fHistAntiLambdaPhi[2];
  TH1D*      fHistAntiLambdaDcaToPrimVertex[2];
  TH1D*      fHistAntiLambdaCPA[2];
  TH1D*      fHistAntiLambdaDecayLength[2];
  TH1D*      fHistAntiLambdaMass[2];
  TProfile*  fProfileLambdaMassVsPt[2];
  TProfile*  fProfileAntiLambdaMassVsPt[2];

  for (size_t i = 0; i < 2; i++)
  {
    fHistLambdaPt[i]                  = nullptr;
    fHistLambdaEta[i]                 = nullptr;
    fHistLambdaPhi[i]                 = nullptr;
    fHistLambdaDcaToPrimVertex[i]     = nullptr;
    fHistLambdaCPA[i]                 = nullptr;
    fHistLambdaDecayLength[i]         = nullptr;
    fHistLambdaMass[i]                = nullptr;
    fHistAntiLambdaPt[i]              = nullptr;
    fHistAntiLambdaEta[i]             = nullptr;
    fHistAntiLambdaPhi[i]             = nullptr;
    fHistAntiLambdaDcaToPrimVertex[i] = nullptr;
    fHistAntiLambdaCPA[i]             = nullptr;
    fHistAntiLambdaDecayLength[i]     = nullptr;
    fHistAntiLambdaMass[i]            = nullptr;
    fProfileLambdaMassVsPt[i]         = nullptr;
    fProfileAntiLambdaMassVsPt[i]     = nullptr;
  }

  fHistLambdaPt[0]                  = (TH1D*)inputList->FindObject("hLambdaPt_BfMassCut");
  fHistLambdaEta[0]                 = (TH1D*)inputList->FindObject("hLambdaEta_BfMassCut");
  fHistLambdaPhi[0]                 = (TH1D*)inputList->FindObject("hLambdaPhi_BfMassCut");
  fHistLambdaDcaToPrimVertex[0]     = (TH1D*)inputList->FindObject("hLambdaDcaToPrimVertex_BfMassCut");
  fHistLambdaCPA[0]                 = (TH1D*)inputList->FindObject("hLambdaCPA_BfMassCut");
  fHistLambdaDecayLength[0]         = (TH1D*)inputList->FindObject("hLambdaDecayLength_BfMassCut");
  fHistLambdaMass[0]                = (TH1D*)inputList->FindObject("hLambdaMass_BfMassCut");
  fHistAntiLambdaPt[0]              = (TH1D*)inputList->FindObject("hAntiLambdaPt_BfMassCut");
  fHistAntiLambdaEta[0]             = (TH1D*)inputList->FindObject("hAntiLambdaEta_BfMassCut");
  fHistAntiLambdaPhi[0]             = (TH1D*)inputList->FindObject("hAntiLambdaPhi_BfMassCut");
  fHistAntiLambdaDcaToPrimVertex[0] = (TH1D*)inputList->FindObject("hAntiLambdaDcaToPrimVertex_BfMassCut");
  fHistAntiLambdaCPA[0]             = (TH1D*)inputList->FindObject("hAntiLambdaCPA_BfMassCut");
  fHistAntiLambdaDecayLength[0]     = (TH1D*)inputList->FindObject("hAntiLambdaDecayLength_BfMassCut");
  fHistAntiLambdaMass[0]            = (TH1D*)inputList->FindObject("hAntiLambdaMass_BfMassCut");
  fProfileLambdaMassVsPt[0]         = (TProfile*)inputList->FindObject("pLambdaMassVsPt_BfMassCut");
  fProfileAntiLambdaMassVsPt[0]     = (TProfile*)inputList->FindObject("pAntiLambdaMassVsPt_BfMassCut");

  fHistLambdaPt[1]                  = (TH1D*)inputList->FindObject("hLambdaPt_AfMassCut");
  fHistLambdaEta[1]                 = (TH1D*)inputList->FindObject("hLambdaEta_AfMassCut");
  fHistLambdaPhi[1]                 = (TH1D*)inputList->FindObject("hLambdaPhi_AfMassCut");
  fHistLambdaDcaToPrimVertex[1]     = (TH1D*)inputList->FindObject("hLambdaDcaToPrimVertex_AfMassCut");
  fHistLambdaCPA[1]                 = (TH1D*)inputList->FindObject("hLambdaCPA_AfMassCut");
  fHistLambdaDecayLength[1]         = (TH1D*)inputList->FindObject("hLambdaDecayLength_AfMassCut");
  fHistLambdaMass[1]                = (TH1D*)inputList->FindObject("hLambdaMass_AfMassCut");
  fHistAntiLambdaPt[1]              = (TH1D*)inputList->FindObject("hAntiLambdaPt_AfMassCut");
  fHistAntiLambdaEta[1]             = (TH1D*)inputList->FindObject("hAntiLambdaEta_AfMassCut");
  fHistAntiLambdaPhi[1]             = (TH1D*)inputList->FindObject("hAntiLambdaPhi_AfMassCut");
  fHistAntiLambdaDcaToPrimVertex[1] = (TH1D*)inputList->FindObject("hAntiLambdaDcaToPrimVertex_AfMassCut");
  fHistAntiLambdaCPA[1]             = (TH1D*)inputList->FindObject("hAntiLambdaCPA_AfMassCut");
  fHistAntiLambdaDecayLength[1]     = (TH1D*)inputList->FindObject("hAntiLambdaDecayLength_AfMassCut");
  fHistAntiLambdaMass[1]            = (TH1D*)inputList->FindObject("hAntiLambdaMass_AfMassCut");
  fProfileLambdaMassVsPt[1]         = (TProfile*)inputList->FindObject("pLambdaMassVsPt_AfMassCut");
  fProfileAntiLambdaMassVsPt[1]     = (TProfile*)inputList->FindObject("pAntiLambdaMassVsPt_AfMassCut");

  //Set Mass Style
  fHistLambdaMass[0]     -> SetMarkerColor(ci[1]);
  fHistLambdaMass[0]     -> SetLineColor(ci[1]);
  fHistAntiLambdaMass[0] -> SetMarkerColor(ci[0]);
  fHistAntiLambdaMass[0] -> SetLineColor(ci[0]);

  fHistLambdaMass[0]     -> SetLineWidth(1);
  fHistAntiLambdaMass[0] -> SetLineWidth(1);

  //Set phi style
  fHistLambdaPhi[1]->SetLineColor(ci[1]);
  fHistLambdaPhi[1]->SetMarkerColor(ci[1]);
  fHistAntiLambdaPhi[1]->SetMarkerColor(ci[0]);
  fHistAntiLambdaPhi[1]->SetLineColor(ci[0]);

  fHistLambdaPhi[1]     -> SetLineWidth(1);
  fHistAntiLambdaPhi[1] -> SetLineWidth(1);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  TLegend* legend = new TLegend(0.15,0.75,0.45,0.85);
  legend->AddEntry(fHistLambdaMass[0],"#Lambda","lp");
  legend->AddEntry(fHistAntiLambdaMass[0],"#bar{#Lambda}","lp");

  TCanvas* cLambdaQA = new TCanvas("LambdaQA","LambdaQA",1200,400);
  cLambdaQA->Divide(2,1);

  cLambdaQA->cd(1);
  if(fPeriod.EqualTo("LHC10h")) fHistLambdaMass[0] -> SetTitle("M_{inv} distribution of #Lambda(#bar{#Lambda}) of 10h");
  if(fPeriod.EqualTo("LHC18q")) fHistLambdaMass[0] -> SetTitle("M_{inv} distribution of #Lambda(#bar{#Lambda}) of 18q");
  if(fPeriod.EqualTo("LHC18r")) fHistLambdaMass[0] -> SetTitle("M_{inv} distribution of #Lambda(#bar{#Lambda}) of 18r");
  fHistLambdaMass[0] -> GetXaxis() -> SetTitle("M_{inv}");
  fHistLambdaMass[0] -> GetYaxis() -> SetTitle("Counts");
  fHistLambdaMass[0] -> GetXaxis() -> SetRangeUser(1.1,1.13);
  fHistLambdaMass[0]     -> Draw("same");
  fHistAntiLambdaMass[0] -> Draw("same");
  legend->Draw("same");


  cLambdaQA->cd(2);
  if(fPeriod.EqualTo("LHC10h")) fHistLambdaPhi[1] -> SetTitle("#phi distribution of #Lambda(#bar{#Lambda})(before mass cut) of 10h");
  if(fPeriod.EqualTo("LHC18q")) fHistLambdaPhi[1] -> SetTitle("#phi distribution of #Lambda(#bar{#Lambda})(before mass cut) of 18q");
  if(fPeriod.EqualTo("LHC18r")) fHistLambdaPhi[1] -> SetTitle("#phi distribution of #Lambda(#bar{#Lambda})(before mass cut) of 18r");
  fHistLambdaPhi[1]->GetXaxis() -> SetTitle("#phi");
  fHistLambdaPhi[1]->GetYaxis() -> SetTitle("Counts");
  fHistLambdaPhi[1]     -> SetMinimum(0);
  fHistLambdaPhi[1]     -> Rebin(2);
  fHistAntiLambdaPhi[1] -> Rebin(2);
  fHistLambdaPhi[1]     -> Draw("same");
  fHistAntiLambdaPhi[1] -> Draw("same");
  
  if(fPeriod.EqualTo("LHC10h")) cLambdaQA->SaveAs("LambdaQA10h.pdf");  
  if(fPeriod.EqualTo("LHC18q")) cLambdaQA->SaveAs("LambdaQA18q.pdf");  
  if(fPeriod.EqualTo("LHC18r")) cLambdaQA->SaveAs("LambdaQA18r.pdf");  
}