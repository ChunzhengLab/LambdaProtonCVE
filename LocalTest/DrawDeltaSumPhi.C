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

template <class TH>
void SetStyle(TH &hist, unsigned int color, unsigned int markerStyle, double markerSize = 1, double lineWidth = 1) 
{
  hist->SetLineColor(color);
  hist->SetMarkerColor(color);
  hist->SetMarkerStyle(markerStyle);
  hist->SetMarkerSize(markerSize);
  hist->SetLineWidth(lineWidth);
}

void DrawDeltaSumPhi(){
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


  //gStyle->SetOptStat(0);

  TList* inputList = nullptr;
  TFile* inputFile = nullptr;
  inputFile = TFile::Open("AnalysisResults.root", "READ");
  inputList = (TList*) inputFile->Get("output_"); 

  TH2F* fHistDelPhi_Lambda_hPos       = (TH2F*)inputList->FindObject("fHistDelPhi_Lambda_hPos");
  TH2F* fHistDelPhi_Lambda_hNeg       = (TH2F*)inputList->FindObject("fHistDelPhi_Lambda_hNeg");
  TH2F* fHistDelPhi_Lambda_Proton     = (TH2F*)inputList->FindObject("fHistDelPhi_Lambda_Proton");
  TH2F* fHistDelPhi_Lambda_AntiProton = (TH2F*)inputList->FindObject("fHistDelPhi_Lambda_AntiProton");

  TH2F* fHistSumPhiTPC_Lambda_hPos       = (TH2F*)inputList->FindObject("fHistSumPhiTPC_Lambda_hPos");
  TH2F* fHistSumPhiTPC_Lambda_hNeg       = (TH2F*)inputList->FindObject("fHistSumPhiTPC_Lambda_hNeg");
  TH2F* fHistSumPhiTPC_Lambda_Proton     = (TH2F*)inputList->FindObject("fHistSumPhiTPC_Lambda_Proton");
  TH2F* fHistSumPhiTPC_Lambda_AntiProton = (TH2F*)inputList->FindObject("fHistSumPhiTPC_Lambda_AntiProton");

  TH1F* hLambdaPosDelPhiCent[8];
  TH1F* hLambdaNegDelPhiCent[8];
  TH1F* hLambdaProtonDelPhiCent[8];
  TH1F* hLambdaAntiProtonDelPhiCent[8];

  TH1F* hLambdaPosSumPhiTPCCent[8];
  TH1F* hLambdaNegSumPhiTPCCent[8];
  TH1F* hLambdaProtonSumPhiTPCCent[8];
  TH1F* hLambdaAntiProtonSumPhiTPCCent[8];


  //Delta Phi
  for (size_t i = 0; i < 8; i++) {
    hLambdaProtonDelPhiCent[i]     = (TH1F*)fHistDelPhi_Lambda_Proton     ->ProjectionY(Form("hLambdaProtonDelPhiCent%zu",i)    ,i+1,i+1);
    hLambdaAntiProtonDelPhiCent[i] = (TH1F*)fHistDelPhi_Lambda_AntiProton ->ProjectionY(Form("hLambdaAntiProtonDelPhiCent%zu",i),i+1,i+1);
    hLambdaPosDelPhiCent[i]        = (TH1F*)fHistDelPhi_Lambda_hPos       ->ProjectionY(Form("hLambdaPosDelPhiCent%zu",i)       ,i+1,i+1);
    hLambdaNegDelPhiCent[i]        = (TH1F*)fHistDelPhi_Lambda_hNeg       ->ProjectionY(Form("hLambdaNegDelPhiCent%zu",i)       ,i+1,i+1);
  }

  for (size_t i = 0; i < 8; i++) {
    hLambdaProtonDelPhiCent[i]     ->Scale(64./hLambdaProtonDelPhiCent[i]    ->Integral(1,hLambdaProtonDelPhiCent[i]    ->GetNbinsX()));
    hLambdaAntiProtonDelPhiCent[i] ->Scale(64./hLambdaAntiProtonDelPhiCent[i]->Integral(1,hLambdaAntiProtonDelPhiCent[i]->GetNbinsX()));
    hLambdaAntiProtonDelPhiCent[i] ->SetLineColor(kRed);
    hLambdaPosDelPhiCent[i]        ->Scale(64./hLambdaPosDelPhiCent[i]       ->Integral(1,hLambdaPosDelPhiCent[i]       ->GetNbinsX()));
    hLambdaNegDelPhiCent[i]        ->Scale(64./hLambdaNegDelPhiCent[i]       ->Integral(1,hLambdaNegDelPhiCent[i]       ->GetNbinsX()));
    hLambdaNegDelPhiCent[i]        ->SetLineColor(kRed);
  }

  //Sum Phi
  for (size_t i = 0; i < 8; i++) {
    hLambdaProtonSumPhiTPCCent[i]     = (TH1F*)fHistSumPhiTPC_Lambda_Proton     ->ProjectionY(Form("hLambdaProtonSumPhiTPCCent%zu",i)    ,i+1,i+1);
    hLambdaAntiProtonSumPhiTPCCent[i] = (TH1F*)fHistSumPhiTPC_Lambda_AntiProton ->ProjectionY(Form("hLambdaAntiProtonSumPhiTPCCent%zu",i),i+1,i+1);
    hLambdaPosSumPhiTPCCent[i]        = (TH1F*)fHistSumPhiTPC_Lambda_hPos       ->ProjectionY(Form("hLambdaPosSumPhiTPCCent%zu",i)       ,i+1,i+1);
    hLambdaNegSumPhiTPCCent[i]        = (TH1F*)fHistSumPhiTPC_Lambda_hNeg       ->ProjectionY(Form("hLambdaNegSumPhiTPCCent%zu",i)       ,i+1,i+1);
  }

  for (size_t i = 0; i < 8; i++) {
    hLambdaProtonSumPhiTPCCent[i]     ->Scale(64./hLambdaProtonSumPhiTPCCent[i]    ->Integral(1,hLambdaProtonSumPhiTPCCent[i]    ->GetNbinsX()));
    hLambdaAntiProtonSumPhiTPCCent[i] ->Scale(64./hLambdaAntiProtonSumPhiTPCCent[i]->Integral(1,hLambdaAntiProtonSumPhiTPCCent[i]->GetNbinsX()));
    hLambdaAntiProtonSumPhiTPCCent[i] ->SetLineColor(kRed);
    hLambdaPosSumPhiTPCCent[i]        ->Scale(64./hLambdaPosSumPhiTPCCent[i]       ->Integral(1,hLambdaPosSumPhiTPCCent[i]       ->GetNbinsX()));
    hLambdaNegSumPhiTPCCent[i]        ->Scale(64./hLambdaNegSumPhiTPCCent[i]       ->Integral(1,hLambdaNegSumPhiTPCCent[i]       ->GetNbinsX()));
    hLambdaNegSumPhiTPCCent[i]        ->SetLineColor(kRed);
  }

  hLambdaPosDelPhiCent[5]->Rebin();
  hLambdaNegDelPhiCent[5]->Rebin();
  hLambdaProtonDelPhiCent[5]->Rebin();
  hLambdaAntiProtonDelPhiCent[5]->Rebin();

  hLambdaPosSumPhiTPCCent[5]->Rebin();
  hLambdaNegSumPhiTPCCent[5]->Rebin();
  hLambdaProtonSumPhiTPCCent[5]->Rebin();
  hLambdaAntiProtonSumPhiTPCCent[5]->Rebin();


  TCanvas* cDel = new TCanvas("cDel","",1000,500);
  cDel->Divide(3);
  cDel->cd(1);
  hLambdaProtonDelPhiCent[4] -> Draw("SAME");
  hLambdaAntiProtonDelPhiCent[4] -> Draw("SAME");
  cDel->cd(2);
  hLambdaPosDelPhiCent[4] -> Draw("SAME");
  hLambdaNegDelPhiCent[4] -> Draw("SAME");
  TH1F* hDelDivideLamPro = (TH1F*)hLambdaProtonDelPhiCent[4]->Clone("hDelDivideLamPro");
  hDelDivideLamPro->Divide(hLambdaAntiProtonDelPhiCent[4]);
  TH1F* hDelDivideLamHad = (TH1F*)hLambdaPosDelPhiCent[4]->Clone("hDelDivideLamHad");
  hDelDivideLamHad->Divide(hLambdaNegDelPhiCent[4]);
  cDel->cd(3);
  hDelDivideLamPro->SetLineColor(kRed);
  hDelDivideLamPro->Draw("SAME");
  hDelDivideLamHad->Draw("SAME");


  TCanvas* cSum = new TCanvas("cSum","",1000,500);
  cSum->Divide(3);
  cSum->cd(1);
  hLambdaProtonSumPhiTPCCent[4] -> Draw("SAME");
  hLambdaAntiProtonSumPhiTPCCent[4] -> Draw("SAME");
  cSum->cd(2);
  hLambdaPosSumPhiTPCCent[4] -> Draw("SAME");
  hLambdaNegSumPhiTPCCent[4] -> Draw("SAME");
  TH1F* hSumDivideLamPro = (TH1F*)hLambdaProtonSumPhiTPCCent[4]->Clone("hSumDivideLamPro");
  hSumDivideLamPro->Divide(hLambdaAntiProtonSumPhiTPCCent[4]);
  TH1F* hSumDivideLamHad = (TH1F*)hLambdaPosSumPhiTPCCent[4]->Clone("hSumDivideLamHad");
  hSumDivideLamHad->Divide(hLambdaNegSumPhiTPCCent[4]);
  cSum->cd(3);
  hSumDivideLamPro->SetLineColor(kRed);
  hSumDivideLamPro->Draw("SAME");
  hSumDivideLamHad->Draw("SAME");

  // //diff pt
  // TProfile*              fProfileDelta_dpt_Lambda_hPos = (TProfile*)inputList->FindObject("fProfileDelta_dpt_Lambda_hPos");
  // TProfile*              fProfileDelta_dpt_Lambda_hNeg = (TProfile*)inputList->FindObject("fProfileDelta_dpt_Lambda_hNeg");
  // TProfile*            fProfileDelta_dpt_Lambda_Proton = (TProfile*)inputList->FindObject("fProfileDelta_dpt_Lambda_Proton");
  // TProfile*        fProfileDelta_dpt_Lambda_AntiProton = (TProfile*)inputList->FindObject("fProfileDelta_dpt_Lambda_AntiProton");
  // TProfile*          fProfileDelta_dpt_AntiLambda_hPos = (TProfile*)inputList->FindObject("fProfileDelta_dpt_AntiLambda_hPos");
  // TProfile*          fProfileDelta_dpt_AntiLambda_hNeg = (TProfile*)inputList->FindObject("fProfileDelta_dpt_AntiLambda_hNeg");
  // TProfile*        fProfileDelta_dpt_AntiLambda_Proton = (TProfile*)inputList->FindObject("fProfileDelta_dpt_AntiLambda_Proton");
  // TProfile*    fProfileDelta_dpt_AntiLambda_AntiProton = (TProfile*)inputList->FindObject("fProfileDelta_dpt_AntiLambda_AntiProton");

  // //diff eta
  // TProfile*              fProfileDelta_deta_Lambda_hPos = (TProfile*)inputList->FindObject("fProfileDelta_deta_Lambda_hPos");
  // TProfile*              fProfileDelta_deta_Lambda_hNeg = (TProfile*)inputList->FindObject("fProfileDelta_deta_Lambda_hNeg");
  // TProfile*            fProfileDelta_deta_Lambda_Proton = (TProfile*)inputList->FindObject("fProfileDelta_deta_Lambda_Proton");
  // TProfile*        fProfileDelta_deta_Lambda_AntiProton = (TProfile*)inputList->FindObject("fProfileDelta_deta_Lambda_AntiProton");
  // TProfile*          fProfileDelta_deta_AntiLambda_hPos = (TProfile*)inputList->FindObject("fProfileDelta_deta_AntiLambda_hPos");
  // TProfile*          fProfileDelta_deta_AntiLambda_hNeg = (TProfile*)inputList->FindObject("fProfileDelta_deta_AntiLambda_hNeg");
  // TProfile*        fProfileDelta_deta_AntiLambda_Proton = (TProfile*)inputList->FindObject("fProfileDelta_deta_AntiLambda_Proton");
  // TProfile*    fProfileDelta_deta_AntiLambda_AntiProton = (TProfile*)inputList->FindObject("fProfileDelta_deta_AntiLambda_AntiProton");

  // //mean pt
  // TProfile*              fProfileDelta_mpt_Lambda_hPos = (TProfile*)inputList->FindObject("fProfileDelta_mpt_Lambda_hPos");
  // TProfile*              fProfileDelta_mpt_Lambda_hNeg = (TProfile*)inputList->FindObject("fProfileDelta_mpt_Lambda_hNeg");
  // TProfile*            fProfileDelta_mpt_Lambda_Proton = (TProfile*)inputList->FindObject("fProfileDelta_mpt_Lambda_Proton");
  // TProfile*        fProfileDelta_mpt_Lambda_AntiProton = (TProfile*)inputList->FindObject("fProfileDelta_mpt_Lambda_AntiProton");
  // TProfile*          fProfileDelta_mpt_AntiLambda_hPos = (TProfile*)inputList->FindObject("fProfileDelta_mpt_AntiLambda_hPos");
  // TProfile*          fProfileDelta_mpt_AntiLambda_hNeg = (TProfile*)inputList->FindObject("fProfileDelta_mpt_AntiLambda_hNeg");
  // TProfile*        fProfileDelta_mpt_AntiLambda_Proton = (TProfile*)inputList->FindObject("fProfileDelta_mpt_AntiLambda_Proton");
  // TProfile*    fProfileDelta_mpt_AntiLambda_AntiProton = (TProfile*)inputList->FindObject("fProfileDelta_mpt_AntiLambda_AntiProton");

  // //diff pt
  // TH1D*              hDelta_dpt_Lambda_hPos = (TH1D*)fProfileDelta_dpt_Lambda_hPos->ProjectionX();
  // TH1D*              hDelta_dpt_Lambda_hNeg = (TH1D*)fProfileDelta_dpt_Lambda_hNeg->ProjectionX();
  // TH1D*            hDelta_dpt_Lambda_Proton = (TH1D*)fProfileDelta_dpt_Lambda_Proton->ProjectionX();
  // TH1D*        hDelta_dpt_Lambda_AntiProton = (TH1D*)fProfileDelta_dpt_Lambda_AntiProton->ProjectionX();
  // TH1D*          hDelta_dpt_AntiLambda_hPos = (TH1D*)fProfileDelta_dpt_AntiLambda_hPos->ProjectionX();
  // TH1D*          hDelta_dpt_AntiLambda_hNeg = (TH1D*)fProfileDelta_dpt_AntiLambda_hNeg->ProjectionX();
  // TH1D*        hDelta_dpt_AntiLambda_Proton = (TH1D*)fProfileDelta_dpt_AntiLambda_Proton->ProjectionX();
  // TH1D*    hDelta_dpt_AntiLambda_AntiProton = (TH1D*)fProfileDelta_dpt_AntiLambda_AntiProton->ProjectionX();

  // //diff eta
  // TH1D*              hDelta_deta_Lambda_hPos = (TH1D*)fProfileDelta_deta_Lambda_hPos->ProjectionX();
  // TH1D*              hDelta_deta_Lambda_hNeg = (TH1D*)fProfileDelta_deta_Lambda_hNeg->ProjectionX();
  // TH1D*            hDelta_deta_Lambda_Proton = (TH1D*)fProfileDelta_deta_Lambda_Proton->ProjectionX();
  // TH1D*        hDelta_deta_Lambda_AntiProton = (TH1D*)fProfileDelta_deta_Lambda_AntiProton->ProjectionX();
  // TH1D*          hDelta_deta_AntiLambda_hPos = (TH1D*)fProfileDelta_deta_AntiLambda_hPos->ProjectionX();
  // TH1D*          hDelta_deta_AntiLambda_hNeg = (TH1D*)fProfileDelta_deta_AntiLambda_hNeg->ProjectionX();
  // TH1D*        hDelta_deta_AntiLambda_Proton = (TH1D*)fProfileDelta_deta_AntiLambda_Proton->ProjectionX();
  // TH1D*    hDelta_deta_AntiLambda_AntiProton = (TH1D*)fProfileDelta_deta_AntiLambda_AntiProton->ProjectionX();

  // //mean pt
  // TH1D*              hDelta_mpt_Lambda_hPos = (TH1D*)fProfileDelta_mpt_Lambda_hPos->ProjectionX();
  // TH1D*              hDelta_mpt_Lambda_hNeg = (TH1D*)fProfileDelta_mpt_Lambda_hNeg->ProjectionX();
  // TH1D*            hDelta_mpt_Lambda_Proton = (TH1D*)fProfileDelta_mpt_Lambda_Proton->ProjectionX();
  // TH1D*        hDelta_mpt_Lambda_AntiProton = (TH1D*)fProfileDelta_mpt_Lambda_AntiProton->ProjectionX();
  // TH1D*          hDelta_mpt_AntiLambda_hPos = (TH1D*)fProfileDelta_mpt_AntiLambda_hPos->ProjectionX();
  // TH1D*          hDelta_mpt_AntiLambda_hNeg = (TH1D*)fProfileDelta_mpt_AntiLambda_hNeg->ProjectionX();
  // TH1D*        hDelta_mpt_AntiLambda_Proton = (TH1D*)fProfileDelta_mpt_AntiLambda_Proton->ProjectionX();
  // TH1D*    hDelta_mpt_AntiLambda_AntiProton = (TH1D*)fProfileDelta_mpt_AntiLambda_AntiProton->ProjectionX();


  // // //diff pt
  // //           hDelta_dpt_Lambda_hPos ->SetMinimum(-0.03);
  // //           hDelta_dpt_Lambda_hNeg ->SetMinimum(-0.03);
  // //         hDelta_dpt_Lambda_Proton ->SetMinimum(-0.03);
  // //     hDelta_dpt_Lambda_AntiProton ->SetMinimum(-0.03);
  // //       hDelta_dpt_AntiLambda_hPos ->SetMinimum(-0.03);
  // //       hDelta_dpt_AntiLambda_hNeg ->SetMinimum(-0.03);
  // //     hDelta_dpt_AntiLambda_Proton ->SetMinimum(-0.03);
  // // hDelta_dpt_AntiLambda_AntiProton ->SetMinimum(-0.03);

  // // //diff eta
  // //           hDelta_deta_Lambda_hPos->SetMinimum(-0.03);
  // //           hDelta_deta_Lambda_hNeg->SetMinimum(-0.03);
  // //         hDelta_deta_Lambda_Proton->SetMinimum(-0.03);
  // //     hDelta_deta_Lambda_AntiProton->SetMinimum(-0.03);
  // //       hDelta_deta_AntiLambda_hPos->SetMinimum(-0.03);
  // //       hDelta_deta_AntiLambda_hNeg->SetMinimum(-0.03);
  // //     hDelta_deta_AntiLambda_Proton->SetMinimum(-0.03);
  // // hDelta_deta_AntiLambda_AntiProton->SetMinimum(-0.03);

  // // //mean pt
  // //           hDelta_mpt_Lambda_hPos ->SetMinimum(-0.03);
  // //           hDelta_mpt_Lambda_hNeg ->SetMinimum(-0.03);
  // //         hDelta_mpt_Lambda_Proton ->SetMinimum(-0.03);
  // //     hDelta_mpt_Lambda_AntiProton ->SetMinimum(-0.03);
  // //       hDelta_mpt_AntiLambda_hPos ->SetMinimum(-0.03);
  // //       hDelta_mpt_AntiLambda_hNeg ->SetMinimum(-0.03);
  // //     hDelta_mpt_AntiLambda_Proton ->SetMinimum(-0.03);
  // // hDelta_mpt_AntiLambda_AntiProton ->SetMinimum(-0.03);


  // //   //diff pt
  // //           hDelta_dpt_Lambda_hPos ->SetMinimum(0.03);
  // //           hDelta_dpt_Lambda_hNeg ->SetMinimum(0.03);
  // //         hDelta_dpt_Lambda_Proton ->SetMinimum(0.03);
  // //     hDelta_dpt_Lambda_AntiProton ->SetMinimum(0.03);
  // //       hDelta_dpt_AntiLambda_hPos ->SetMinimum(0.03);
  // //       hDelta_dpt_AntiLambda_hNeg ->SetMinimum(0.03);
  // //     hDelta_dpt_AntiLambda_Proton ->SetMinimum(0.03);
  // // hDelta_dpt_AntiLambda_AntiProton ->SetMinimum(0.03);

  // // //diff eta
  // //           hDelta_deta_Lambda_hPos->SetMinimum(0.03);
  // //           hDelta_deta_Lambda_hNeg->SetMinimum(0.03);
  // //         hDelta_deta_Lambda_Proton->SetMinimum(0.03);
  // //     hDelta_deta_Lambda_AntiProton->SetMinimum(0.03);
  // //       hDelta_deta_AntiLambda_hPos->SetMinimum(0.03);
  // //       hDelta_deta_AntiLambda_hNeg->SetMinimum(0.03);
  // //     hDelta_deta_AntiLambda_Proton->SetMinimum(0.03);
  // // hDelta_deta_AntiLambda_AntiProton->SetMinimum(0.03);

  // // //mean pt
  // //           hDelta_mpt_Lambda_hPos ->SetMinimum(0.03);
  // //           hDelta_mpt_Lambda_hNeg ->SetMinimum(0.03);
  // //         hDelta_mpt_Lambda_Proton ->SetMinimum(0.03);
  // //     hDelta_mpt_Lambda_AntiProton ->SetMinimum(0.03);
  // //       hDelta_mpt_AntiLambda_hPos ->SetMinimum(0.03);
  // //       hDelta_mpt_AntiLambda_hNeg ->SetMinimum(0.03);
  // //     hDelta_mpt_AntiLambda_Proton ->SetMinimum(0.03);
  // // hDelta_mpt_AntiLambda_AntiProton ->SetMinimum(0.03);

  // TH1D* hDeltaDelta_dpt = (TH1D*)hDelta_dpt_Lambda_AntiProton->Clone();
  // hDeltaDelta_dpt->Add(hDelta_dpt_Lambda_Proton,-1);

  // TH1D* hDeltaDelta_mpt = (TH1D*)hDelta_mpt_Lambda_AntiProton->Clone();
  // hDeltaDelta_mpt->Add(hDelta_mpt_Lambda_Proton,-1);

  // TH1D* hDeltaDelta_deta = (TH1D*)hDelta_deta_Lambda_AntiProton->Clone();
  // hDeltaDelta_deta->Add(hDelta_deta_Lambda_Proton,-1);

  // hDelta_dpt_Lambda_Proton->SetLineColor(kRed);
  // hDelta_mpt_Lambda_Proton->SetLineColor(kRed);
  // hDelta_deta_Lambda_Proton->SetLineColor(kRed);

  // hDelta_dpt_Lambda_Proton->SetMaximum(0.02);
  // hDelta_mpt_Lambda_Proton->SetMaximum(0.02);
  // hDelta_deta_Lambda_Proton->SetMaximum(0.02);

  // hDelta_dpt_Lambda_Proton->SetMinimum(-0.02);
  // hDelta_mpt_Lambda_Proton->SetMinimum(-0.02);
  // hDelta_deta_Lambda_Proton->SetMinimum(-0.02);
  
  // TCanvas* cDpt = new TCanvas("cDpt","",10,10,800,400);
  // cDpt->Divide(2);
  // cDpt->cd(1);
  // hDelta_dpt_Lambda_Proton->Draw("SAME");
  // hDelta_dpt_Lambda_AntiProton->Draw("SAME");
  // cDpt->cd(2);
  // hDeltaDelta_dpt->Draw();

  // TCanvas* cMpt = new TCanvas("cMpt","",10,10,800,400);
  // cMpt->Divide(2);
  // cMpt->cd(1);
  // hDelta_mpt_Lambda_Proton->Draw("SAME");
  // hDelta_mpt_Lambda_AntiProton->Draw("SAME");
  // cMpt->cd(2);
  // hDeltaDelta_mpt->Draw();

  // TCanvas* cDeta = new TCanvas("cDeta","",10,10,800,400);
  // cDeta->Divide(2);
  // cDeta->cd(1);
  // hDelta_deta_Lambda_Proton->Draw("SAME");
  // hDelta_deta_Lambda_AntiProton->Draw("SAME");
  // cDeta->cd(2);
  // hDeltaDelta_deta->Draw();
}
