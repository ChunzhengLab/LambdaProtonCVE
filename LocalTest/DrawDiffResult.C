#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TProfile.h"
#include "TLegend.h"
#include "TColor.h"
#include "TStyle.h"
#include "TProfile2D.h"
#include "TMath.h"
#include "TF1.h"
#include "TGraphAsymmErrors.h"

TString fPeriod = "LHC10h";

template <class TH>
void SetStyle(TH &hist, unsigned int color, unsigned int markerStyle, double markerSize = 1, double lineWidth = 1) 
{
  hist->SetLineColor(color);
  hist->SetMarkerColor(color);
  hist->SetMarkerStyle(markerStyle);
  hist->SetMarkerSize(markerSize);
  hist->SetLineWidth(lineWidth);
}

void DrawDiffResult(){
  int ci[6];
  TColor* color[6];
  ci[0] = TColor::GetFreeColorIndex();
  color[0] = new TColor(ci[0],  240/255.,  102/255.,   70/255.);//红
  ci[1] = TColor::GetFreeColorIndex();
  color[1] = new TColor(ci[1],   79/255.,  194/255.,  216/255.);//蓝
  ci[2] = TColor::GetFreeColorIndex();
  color[2] = new TColor(ci[2],  254/255.,  198/255.,  101/255.);//黄
  ci[3] = TColor::GetFreeColorIndex();
  color[3] = new TColor(ci[3],  146/255.,  100/255.,  140/255.);//紫
  ci[4] = TColor::GetFreeColorIndex();
  color[4] = new TColor(ci[4],  125/255.,  200/255.,  165/255.);//绿
  ci[5] = TColor::GetFreeColorIndex();
  color[5] = new TColor(ci[5],   64/255.,   64/255.,   64/255.);//黑


  gStyle->SetOptStat(0);

  TList* inputList = nullptr;
  TFile* inputFile = nullptr;
  inputFile = TFile::Open("AnalysisResults.root", "READ");
  inputList = (TList*) inputFile->Get("output_"); 

  //diff pt
  TProfile*              fProfileDelta_dpt_Lambda_hPos = (TProfile*)inputList->FindObject("fProfileDelta_dpt_Lambda_hPos");
  TProfile*              fProfileDelta_dpt_Lambda_hNeg = (TProfile*)inputList->FindObject("fProfileDelta_dpt_Lambda_hNeg");
  TProfile*            fProfileDelta_dpt_Lambda_Proton = (TProfile*)inputList->FindObject("fProfileDelta_dpt_Lambda_Proton");
  TProfile*        fProfileDelta_dpt_Lambda_AntiProton = (TProfile*)inputList->FindObject("fProfileDelta_dpt_Lambda_AntiProton");
  TProfile*          fProfileDelta_dpt_AntiLambda_hPos = (TProfile*)inputList->FindObject("fProfileDelta_dpt_AntiLambda_hPos");
  TProfile*          fProfileDelta_dpt_AntiLambda_hNeg = (TProfile*)inputList->FindObject("fProfileDelta_dpt_AntiLambda_hNeg");
  TProfile*        fProfileDelta_dpt_AntiLambda_Proton = (TProfile*)inputList->FindObject("fProfileDelta_dpt_AntiLambda_Proton");
  TProfile*    fProfileDelta_dpt_AntiLambda_AntiProton = (TProfile*)inputList->FindObject("fProfileDelta_dpt_AntiLambda_AntiProton");

  //diff eta
  TProfile*              fProfileDelta_deta_Lambda_hPos = (TProfile*)inputList->FindObject("fProfileDelta_deta_Lambda_hPos");
  TProfile*              fProfileDelta_deta_Lambda_hNeg = (TProfile*)inputList->FindObject("fProfileDelta_deta_Lambda_hNeg");
  TProfile*            fProfileDelta_deta_Lambda_Proton = (TProfile*)inputList->FindObject("fProfileDelta_deta_Lambda_Proton");
  TProfile*        fProfileDelta_deta_Lambda_AntiProton = (TProfile*)inputList->FindObject("fProfileDelta_deta_Lambda_AntiProton");
  TProfile*          fProfileDelta_deta_AntiLambda_hPos = (TProfile*)inputList->FindObject("fProfileDelta_deta_AntiLambda_hPos");
  TProfile*          fProfileDelta_deta_AntiLambda_hNeg = (TProfile*)inputList->FindObject("fProfileDelta_deta_AntiLambda_hNeg");
  TProfile*        fProfileDelta_deta_AntiLambda_Proton = (TProfile*)inputList->FindObject("fProfileDelta_deta_AntiLambda_Proton");
  TProfile*    fProfileDelta_deta_AntiLambda_AntiProton = (TProfile*)inputList->FindObject("fProfileDelta_deta_AntiLambda_AntiProton");

  //mean pt
  TProfile*              fProfileDelta_mpt_Lambda_hPos = (TProfile*)inputList->FindObject("fProfileDelta_mpt_Lambda_hPos");
  TProfile*              fProfileDelta_mpt_Lambda_hNeg = (TProfile*)inputList->FindObject("fProfileDelta_mpt_Lambda_hNeg");
  TProfile*            fProfileDelta_mpt_Lambda_Proton = (TProfile*)inputList->FindObject("fProfileDelta_mpt_Lambda_Proton");
  TProfile*        fProfileDelta_mpt_Lambda_AntiProton = (TProfile*)inputList->FindObject("fProfileDelta_mpt_Lambda_AntiProton");
  TProfile*          fProfileDelta_mpt_AntiLambda_hPos = (TProfile*)inputList->FindObject("fProfileDelta_mpt_AntiLambda_hPos");
  TProfile*          fProfileDelta_mpt_AntiLambda_hNeg = (TProfile*)inputList->FindObject("fProfileDelta_mpt_AntiLambda_hNeg");
  TProfile*        fProfileDelta_mpt_AntiLambda_Proton = (TProfile*)inputList->FindObject("fProfileDelta_mpt_AntiLambda_Proton");
  TProfile*    fProfileDelta_mpt_AntiLambda_AntiProton = (TProfile*)inputList->FindObject("fProfileDelta_mpt_AntiLambda_AntiProton");


  // //diff pt
  //             fProfileDelta_dpt_Lambda_hPos -> Rebin();
  //             fProfileDelta_dpt_Lambda_hNeg -> Rebin();
  //           fProfileDelta_dpt_Lambda_Proton -> Rebin();
  //       fProfileDelta_dpt_Lambda_AntiProton -> Rebin();
  //         fProfileDelta_dpt_AntiLambda_hPos -> Rebin();
  //         fProfileDelta_dpt_AntiLambda_hNeg -> Rebin();
  //       fProfileDelta_dpt_AntiLambda_Proton -> Rebin();
  //   fProfileDelta_dpt_AntiLambda_AntiProton -> Rebin();

  // //diff eta
  //             fProfileDelta_deta_Lambda_hPos -> Rebin();
  //             fProfileDelta_deta_Lambda_hNeg -> Rebin();
  //           fProfileDelta_deta_Lambda_Proton -> Rebin();
  //       fProfileDelta_deta_Lambda_AntiProton -> Rebin();
  //         fProfileDelta_deta_AntiLambda_hPos -> Rebin();
  //         fProfileDelta_deta_AntiLambda_hNeg -> Rebin();
  //       fProfileDelta_deta_AntiLambda_Proton -> Rebin();
  //   fProfileDelta_deta_AntiLambda_AntiProton -> Rebin();

  // //mean pt
  //             fProfileDelta_mpt_Lambda_hPos -> Rebin();
  //             fProfileDelta_mpt_Lambda_hNeg -> Rebin();
  //           fProfileDelta_mpt_Lambda_Proton -> Rebin();
  //       fProfileDelta_mpt_Lambda_AntiProton -> Rebin();
  //         fProfileDelta_mpt_AntiLambda_hPos -> Rebin();
  //         fProfileDelta_mpt_AntiLambda_hNeg -> Rebin();
  //       fProfileDelta_mpt_AntiLambda_Proton -> Rebin();
  //   fProfileDelta_mpt_AntiLambda_AntiProton -> Rebin();


  //diff pt
  TH1D*              hDelta_dpt_Lambda_hPos = (TH1D*)fProfileDelta_dpt_Lambda_hPos->ProjectionX();
  TH1D*              hDelta_dpt_Lambda_hNeg = (TH1D*)fProfileDelta_dpt_Lambda_hNeg->ProjectionX();
  TH1D*            hDelta_dpt_Lambda_Proton = (TH1D*)fProfileDelta_dpt_Lambda_Proton->ProjectionX();
  TH1D*        hDelta_dpt_Lambda_AntiProton = (TH1D*)fProfileDelta_dpt_Lambda_AntiProton->ProjectionX();
  TH1D*          hDelta_dpt_AntiLambda_hPos = (TH1D*)fProfileDelta_dpt_AntiLambda_hPos->ProjectionX();
  TH1D*          hDelta_dpt_AntiLambda_hNeg = (TH1D*)fProfileDelta_dpt_AntiLambda_hNeg->ProjectionX();
  TH1D*        hDelta_dpt_AntiLambda_Proton = (TH1D*)fProfileDelta_dpt_AntiLambda_Proton->ProjectionX();
  TH1D*    hDelta_dpt_AntiLambda_AntiProton = (TH1D*)fProfileDelta_dpt_AntiLambda_AntiProton->ProjectionX();

  //diff eta
  TH1D*              hDelta_deta_Lambda_hPos = (TH1D*)fProfileDelta_deta_Lambda_hPos->ProjectionX();
  TH1D*              hDelta_deta_Lambda_hNeg = (TH1D*)fProfileDelta_deta_Lambda_hNeg->ProjectionX();
  TH1D*            hDelta_deta_Lambda_Proton = (TH1D*)fProfileDelta_deta_Lambda_Proton->ProjectionX();
  TH1D*        hDelta_deta_Lambda_AntiProton = (TH1D*)fProfileDelta_deta_Lambda_AntiProton->ProjectionX();
  TH1D*          hDelta_deta_AntiLambda_hPos = (TH1D*)fProfileDelta_deta_AntiLambda_hPos->ProjectionX();
  TH1D*          hDelta_deta_AntiLambda_hNeg = (TH1D*)fProfileDelta_deta_AntiLambda_hNeg->ProjectionX();
  TH1D*        hDelta_deta_AntiLambda_Proton = (TH1D*)fProfileDelta_deta_AntiLambda_Proton->ProjectionX();
  TH1D*    hDelta_deta_AntiLambda_AntiProton = (TH1D*)fProfileDelta_deta_AntiLambda_AntiProton->ProjectionX();

  //mean pt
  TH1D*              hDelta_mpt_Lambda_hPos = (TH1D*)fProfileDelta_mpt_Lambda_hPos->ProjectionX();
  TH1D*              hDelta_mpt_Lambda_hNeg = (TH1D*)fProfileDelta_mpt_Lambda_hNeg->ProjectionX();
  TH1D*            hDelta_mpt_Lambda_Proton = (TH1D*)fProfileDelta_mpt_Lambda_Proton->ProjectionX();
  TH1D*        hDelta_mpt_Lambda_AntiProton = (TH1D*)fProfileDelta_mpt_Lambda_AntiProton->ProjectionX();
  TH1D*          hDelta_mpt_AntiLambda_hPos = (TH1D*)fProfileDelta_mpt_AntiLambda_hPos->ProjectionX();
  TH1D*          hDelta_mpt_AntiLambda_hNeg = (TH1D*)fProfileDelta_mpt_AntiLambda_hNeg->ProjectionX();
  TH1D*        hDelta_mpt_AntiLambda_Proton = (TH1D*)fProfileDelta_mpt_AntiLambda_Proton->ProjectionX();
  TH1D*    hDelta_mpt_AntiLambda_AntiProton = (TH1D*)fProfileDelta_mpt_AntiLambda_AntiProton->ProjectionX();


  // //diff pt
  //           hDelta_dpt_Lambda_hPos ->SetMinimum(-0.03);
  //           hDelta_dpt_Lambda_hNeg ->SetMinimum(-0.03);
  //         hDelta_dpt_Lambda_Proton ->SetMinimum(-0.03);
  //     hDelta_dpt_Lambda_AntiProton ->SetMinimum(-0.03);
  //       hDelta_dpt_AntiLambda_hPos ->SetMinimum(-0.03);
  //       hDelta_dpt_AntiLambda_hNeg ->SetMinimum(-0.03);
  //     hDelta_dpt_AntiLambda_Proton ->SetMinimum(-0.03);
  // hDelta_dpt_AntiLambda_AntiProton ->SetMinimum(-0.03);

  // //diff eta
  //           hDelta_deta_Lambda_hPos->SetMinimum(-0.03);
  //           hDelta_deta_Lambda_hNeg->SetMinimum(-0.03);
  //         hDelta_deta_Lambda_Proton->SetMinimum(-0.03);
  //     hDelta_deta_Lambda_AntiProton->SetMinimum(-0.03);
  //       hDelta_deta_AntiLambda_hPos->SetMinimum(-0.03);
  //       hDelta_deta_AntiLambda_hNeg->SetMinimum(-0.03);
  //     hDelta_deta_AntiLambda_Proton->SetMinimum(-0.03);
  // hDelta_deta_AntiLambda_AntiProton->SetMinimum(-0.03);

  // //mean pt
  //           hDelta_mpt_Lambda_hPos ->SetMinimum(-0.03);
  //           hDelta_mpt_Lambda_hNeg ->SetMinimum(-0.03);
  //         hDelta_mpt_Lambda_Proton ->SetMinimum(-0.03);
  //     hDelta_mpt_Lambda_AntiProton ->SetMinimum(-0.03);
  //       hDelta_mpt_AntiLambda_hPos ->SetMinimum(-0.03);
  //       hDelta_mpt_AntiLambda_hNeg ->SetMinimum(-0.03);
  //     hDelta_mpt_AntiLambda_Proton ->SetMinimum(-0.03);
  // hDelta_mpt_AntiLambda_AntiProton ->SetMinimum(-0.03);


  //   //diff pt
  //           hDelta_dpt_Lambda_hPos ->SetMinimum(0.03);
  //           hDelta_dpt_Lambda_hNeg ->SetMinimum(0.03);
  //         hDelta_dpt_Lambda_Proton ->SetMinimum(0.03);
  //     hDelta_dpt_Lambda_AntiProton ->SetMinimum(0.03);
  //       hDelta_dpt_AntiLambda_hPos ->SetMinimum(0.03);
  //       hDelta_dpt_AntiLambda_hNeg ->SetMinimum(0.03);
  //     hDelta_dpt_AntiLambda_Proton ->SetMinimum(0.03);
  // hDelta_dpt_AntiLambda_AntiProton ->SetMinimum(0.03);

  // //diff eta
  //           hDelta_deta_Lambda_hPos->SetMinimum(0.03);
  //           hDelta_deta_Lambda_hNeg->SetMinimum(0.03);
  //         hDelta_deta_Lambda_Proton->SetMinimum(0.03);
  //     hDelta_deta_Lambda_AntiProton->SetMinimum(0.03);
  //       hDelta_deta_AntiLambda_hPos->SetMinimum(0.03);
  //       hDelta_deta_AntiLambda_hNeg->SetMinimum(0.03);
  //     hDelta_deta_AntiLambda_Proton->SetMinimum(0.03);
  // hDelta_deta_AntiLambda_AntiProton->SetMinimum(0.03);

  // //mean pt
  //           hDelta_mpt_Lambda_hPos ->SetMinimum(0.03);
  //           hDelta_mpt_Lambda_hNeg ->SetMinimum(0.03);
  //         hDelta_mpt_Lambda_Proton ->SetMinimum(0.03);
  //     hDelta_mpt_Lambda_AntiProton ->SetMinimum(0.03);
  //       hDelta_mpt_AntiLambda_hPos ->SetMinimum(0.03);
  //       hDelta_mpt_AntiLambda_hNeg ->SetMinimum(0.03);
  //     hDelta_mpt_AntiLambda_Proton ->SetMinimum(0.03);
  // hDelta_mpt_AntiLambda_AntiProton ->SetMinimum(0.03);

  TH1D* hDeltaDelta_dpt = (TH1D*)hDelta_dpt_Lambda_AntiProton->Clone();
  hDeltaDelta_dpt->Add(hDelta_dpt_Lambda_Proton,-1);

  TH1D* hDeltaDelta_mpt = (TH1D*)hDelta_mpt_Lambda_AntiProton->Clone();
  hDeltaDelta_mpt->Add(hDelta_mpt_Lambda_Proton,-1);

  TH1D* hDeltaDelta_deta = (TH1D*)hDelta_deta_Lambda_AntiProton->Clone();
  hDeltaDelta_deta->Add(hDelta_deta_Lambda_Proton,-1);

  hDelta_dpt_Lambda_Proton->SetLineColor(kRed);
  hDelta_mpt_Lambda_Proton->SetLineColor(kRed);
  hDelta_deta_Lambda_Proton->SetLineColor(kRed);

  hDelta_dpt_Lambda_Proton->SetMaximum(0.02);
  hDelta_mpt_Lambda_Proton->SetMaximum(0.02);
  hDelta_deta_Lambda_Proton->SetMaximum(0.02);

  hDelta_dpt_Lambda_Proton->SetMinimum(-0.02);
  hDelta_mpt_Lambda_Proton->SetMinimum(-0.02);
  hDelta_deta_Lambda_Proton->SetMinimum(-0.02);
  
  TCanvas* cDpt = new TCanvas("cDpt","",10,10,800,400);
  cDpt->Divide(2);
  cDpt->cd(1);
  hDelta_dpt_Lambda_Proton->Draw("SAME");
  hDelta_dpt_Lambda_AntiProton->Draw("SAME");
  cDpt->cd(2);
  hDeltaDelta_dpt->Draw();

  TCanvas* cMpt = new TCanvas("cMpt","",10,10,800,400);
  cMpt->Divide(2);
  cMpt->cd(1);
  hDelta_mpt_Lambda_Proton->Draw("SAME");
  hDelta_mpt_Lambda_AntiProton->Draw("SAME");
  cMpt->cd(2);
  hDeltaDelta_mpt->Draw();

  TCanvas* cDeta = new TCanvas("cDeta","",10,10,800,400);
  cDeta->Divide(2);
  cDeta->cd(1);
  hDelta_deta_Lambda_Proton->Draw("SAME");
  hDelta_deta_Lambda_AntiProton->Draw("SAME");
  cDeta->cd(2);
  hDeltaDelta_deta->Draw();
}
