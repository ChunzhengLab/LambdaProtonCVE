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

bool isZDCR2fromR1 = 0;
bool isZDCR2fromData = 0;
TString fPeriod = "LHC18q";

template <class TH>
void SetStyle(TH &hist, unsigned int color, unsigned int markerStyle, double markerSize = 1, double lineWidth = 1) 
{
  hist->SetLineColor(color);
  hist->SetMarkerColor(color);
  hist->SetMarkerStyle(markerStyle);
  hist->SetMarkerSize(markerSize);
  hist->SetLineWidth(lineWidth);
}

void DrawProtonFlow(){
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

  TFile* inputFile_IncFlow_sqrtsNN276 = TFile::Open("/Users/wangchunzheng/Documents/PublishedResults/Flow/Flow_2.76TeV_HEPData-ins877822-v1-root.root");
  TFile* inputFile_PIDFlow_sqrtsNN276 = TFile::Open("/Users/wangchunzheng/Documents/PublishedResults/Flow/PIDFlow_2.76TeV_HEPData-ins1297103-v1-root.root");
  TFile* inputFile_IncFlow_sqrtsNN502 = TFile::Open("/Users/wangchunzheng/Documents/PublishedResults/Flow/Flow_5.02TeV_HEPData-ins1419244-v2-root.root");
  TFile* inputFile_PIDFlow_sqrtsNN502 = TFile::Open("/Users/wangchunzheng/Documents/PublishedResults/Flow/PIDFlow_5.02TeV_HEPData-ins1672822-v1-root.root");

  //inc
  TDirectoryFile* dir_v2_C2_cent_sqrtsNN276 = (TDirectoryFile*)inputFile_IncFlow_sqrtsNN276->Get("Table 3");
  TDirectoryFile* dir_v2_C2_cent_sqrtsNN502 = (TDirectoryFile*)inputFile_IncFlow_sqrtsNN502->Get("Table 1");
  
  TDirectoryFile* dir_v2_C2_charge_pt_cent4050_sqrtsNN276 = (TDirectoryFile*)inputFile_IncFlow_sqrtsNN276->Get("Table 1");
  TDirectoryFile* dir_v2_SP_proton_pt_cent4050_sqrtsNN276 = (TDirectoryFile*)inputFile_PIDFlow_sqrtsNN276->Get("Table 34");
  TDirectoryFile* dir_v2_IM_lambda_pt_cent4050_sqrtsNN276 = (TDirectoryFile*)inputFile_PIDFlow_sqrtsNN276->Get("Table 46");

  TDirectoryFile* dir_v2_C2_charge_pt_cent3040_sqrtsNN502 = (TDirectoryFile*)inputFile_IncFlow_sqrtsNN502->Get("Table 8");
  TDirectoryFile* dir_v2_SP_proton_pt_cent3040_sqrtsNN502 = (TDirectoryFile*)inputFile_PIDFlow_sqrtsNN502->Get("Table 51");
  TDirectoryFile* dir_v2_IM_lambda_pt_cent3040_sqrtsNN502 = (TDirectoryFile*)inputFile_PIDFlow_sqrtsNN502->Get("Table 87");

  TGraphAsymmErrors* v2_C2_cent_sqrtsNN276 = (TGraphAsymmErrors*)dir_v2_C2_cent_sqrtsNN276->Get("Graph1D_y1"); 
  TGraphAsymmErrors* v2_C2_cent_sqrtsNN502 = (TGraphAsymmErrors*)dir_v2_C2_cent_sqrtsNN502->Get("Graph1D_y1"); 

  TGraphAsymmErrors* v2_C2_charge_pt_cent4050_sqrtsNN276 = (TGraphAsymmErrors*)dir_v2_C2_charge_pt_cent4050_sqrtsNN276->Get("Graph1D_y1");
  TGraphAsymmErrors* v2_SP_proton_pt_cent4050_sqrtsNN276 = (TGraphAsymmErrors*)dir_v2_SP_proton_pt_cent4050_sqrtsNN276->Get("Graph1D_y1");
  TGraphAsymmErrors* v2_IM_lambda_pt_cent4050_sqrtsNN276 = (TGraphAsymmErrors*)dir_v2_IM_lambda_pt_cent4050_sqrtsNN276->Get("Graph1D_y1");

  TGraphAsymmErrors* v2_C2_charge_pt_cent3040_sqrtsNN502 = (TGraphAsymmErrors*)dir_v2_C2_charge_pt_cent3040_sqrtsNN502->Get("Graph1D_y1");
  TGraphAsymmErrors* v2_SP_proton_pt_cent3040_sqrtsNN502 = (TGraphAsymmErrors*)dir_v2_SP_proton_pt_cent3040_sqrtsNN502->Get("Graph1D_y1");
  TGraphAsymmErrors* v2_IM_lambda_pt_cent3040_sqrtsNN502 = (TGraphAsymmErrors*)dir_v2_IM_lambda_pt_cent3040_sqrtsNN502->Get("Graph1D_y1");

  TList* inputList = nullptr;
  TFile* inputFile = inputFile = TFile::Open("AnalysisResults.root", "READ");
  inputList = (TList*) inputFile->Get("output_"); 

  TProfile2D* fProfile2DRawFlowCentPthPos_TPC = (TProfile2D*)inputList->FindObject("fProfile2DRawFlowCentPthPos_TPC");
  TProfile*  fProfileTPCPsi2Correlation = (TProfile*)inputList -> FindObject("fProfileTPCPsi2Correlation");

  fProfileTPCPsi2Correlation -> Rebin(10);
  TH1D* hRes = new TH1D ("hRes","",10,0.,100.);
  TH1D* hTPCPsi2Correlation       = fProfileTPCPsi2Correlation -> ProjectionX("hProfileTPCPsi2Correlation");


  for (int i = 0; i < 10; i++) {
    hRes->SetBinContent(i+1, TMath::Sqrt(hTPCPsi2Correlation->GetBinContent(i+1)));
  }
  std::cout<<"Get the resonlution"<<std::endl;



  TProfile2D*  fProfile2DRawFlowCentPtProton     = (TProfile2D*)inputList->FindObject("fProfile2DRawFlowCentPtProton_TPC");
  TProfile2D*  fProfile2DRawFlowCentPtAntiProton = (TProfile2D*)inputList->FindObject("fProfile2DRawFlowCentPtAntiProton_TPC");

  TProfile* fProfileRawFlowCentProton     = (TProfile*) fProfile2DRawFlowCentPtProton     -> ProfileX("fProfileFlowCentProton",1,25);
  TProfile* fProfileRawFlowCentAntiProton = (TProfile*) fProfile2DRawFlowCentPtAntiProton -> ProfileX("fProfileFlowCentAntiProton",1,25);

  TH1D*  hFlowCentProton     = fProfileRawFlowCentProton     -> ProjectionX("hFlowCentProton");
  TH1D*  hFlowCentAntiProton = fProfileRawFlowCentAntiProton -> ProjectionX("hFlowCentAntiProton");

  hFlowCentProton     -> Divide(hRes);
  hFlowCentAntiProton -> Divide(hRes);
  std::cout<<"Get the flow"<<std::endl;

  TLegend *legendRes = new TLegend(0.7,0.63,0.85,0.88);
  legendRes->SetBorderSize(0);
  legendRes->AddEntry(hRes,"TPC Res_{2}","lp");


  TLegend *legendV2 = new TLegend(0.15,0.6,0.35,0.88);
  legendV2->SetBorderSize(0);
  legendV2->AddEntry(hRes,"TPC","lp");
  legendV2->AddEntry(v2_C2_cent_sqrtsNN502 ,"Published","lp");

  TCanvas* cRes = new TCanvas("cRes","Resolution",10,10,500,400);
  cRes->cd();
  TH2D* dummyRes = new TH2D("","",1,0,80,1,-0.2,1.);
  dummyRes->SetXTitle("Centrality (%)");
  dummyRes->SetYTitle("Resolution");
  dummyRes->GetYaxis()->SetTitleOffset(1.2);
  dummyRes->Draw("SAME");
  SetStyle(hRes,ci[0],kFullCircle,1,1.3);
  hRes->Draw("P SAME");
  legendRes->Draw("SAME");


  TCanvas* cV2Cent = new TCanvas("cV2Cent","v_{2} vs. Centrality",10,10,500,400);
  cV2Cent->cd();
  TH2D* dummyV2Cent = new TH2D("","",1,0,80,1,-0.01,0.2);
  dummyV2Cent -> SetTitle("v_{2} vs. Centrality");
  dummyV2Cent->GetXaxis()->SetTitle("");
  dummyV2Cent->GetXaxis()->SetTitle("Centrality (%)");
  dummyV2Cent->GetYaxis()->SetTitle("v_{2}");
  dummyV2Cent->GetYaxis()->SetTitleOffset(1.2);
  dummyV2Cent->Draw("SAME");
  SetStyle(hFlowCentProton,ci[0], kFullCircle,1,0);
  SetStyle(hFlowCentAntiProton,ci[0], kOpenCircle,1,0);
  hFlowCentProton    ->Draw("SAME");
  hFlowCentAntiProton->Draw("SAME");
  v2_C2_cent_sqrtsNN502->Draw("SAME");
  legendV2->Draw("SAME");
}