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
bool isZDCR2fromData = 1;
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

void DrawFlow(){
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
  TFile* inputFile = nullptr;哲学学院资料室虞锋书室
  if(fPeriod.EqualTo("LHC10h")) inputFile = TFile::Open("./LHC10h/AnalysisResults_10h_PlanePt5_ProtonPt3.root", "READ");
  if(fPeriod.EqualTo("LHC18q")) inputFile = TFile::Open("./LHC18q/AnalysisResults_18q_PlanePt5_ProtonPt3.root", "READ");
  if(fPeriod.EqualTo("LHC18r")) inputFile = TFile::Open("./LHC18r/AnalysisResults_18r_PlanePt5_ProtonPt3.root", "READ");
  inputList = (TList*) inputFile->Find
  ("output_"); 

  TProfile2D*  fProfile2DRawFlowCentPthPos[5];
  TProfile2D*  fProfile2DRawFlowCentPthNeg[5];
  TProfile2D*  fProfile2DRawFlowCentPtProton[5];
  TProfile2D*  fProfile2DRawFlowCentPtAntiProton[5];
  TProfile2D*  fProfile2DRawFlowCentPtLambda[5];
  TProfile2D*  fProfile2DRawFlowCentPtAntiLambda[5];

  char chPlaneType[5];
  for (int i = 0; i < 5; i++) {
    if (i==0) sprintf(chPlaneType,"TPC");
    if (i==1) sprintf(chPlaneType,"V0C");
    if (i==2) sprintf(chPlaneType,"V0A");
    if (i==3) sprintf(chPlaneType,"ZNC");
    if (i==4) sprintf(chPlaneType,"ZNA");
    fProfile2DRawFlowCentPthPos[i] = (TProfile2D*)inputList->FindObject(Form("fProfile2DRawFlowCentPthPos_%s",chPlaneType));
    fProfile2DRawFlowCentPthNeg[i] = (TProfile2D*)inputList->FindObject(Form("fProfile2DRawFlowCentPthNeg_%s",chPlaneType));
    fProfile2DRawFlowCentPtProton[i] = (TProfile2D*)inputList->FindObject(Form("fProfile2DRawFlowCentPtProton_%s",chPlaneType));
    fProfile2DRawFlowCentPtAntiProton[i] = (TProfile2D*)inputList->FindObject(Form("fProfile2DRawFlowCentPtAntiProton_%s",chPlaneType));
    fProfile2DRawFlowCentPtLambda[i] = (TProfile2D*)inputList->FindObject(Form("fProfile2DRawFlowCentPtLambda_%s",chPlaneType));
    fProfile2DRawFlowCentPtAntiLambda[i] = (TProfile2D*)inputList->FindObject(Form("fProfile2DRawFlowCentPtAntiLambda_%s",chPlaneType));
  }

  TProfile*  fProfileTPCPsi2Correlation = (TProfile*)inputList -> FindObject("fProfileTPCPsi2Correlation");
  TProfile*  fProfileV0MPsi2Correlation = (TProfile*)inputList -> FindObject("fProfileV0MPsi2Correlation");
  TProfile*  fProfileZDCPsi1Correlation = (TProfile*)inputList -> FindObject("fProfileZDCPsi1Correlation");
  TProfile*  fProfileZDCPsi2Correlation = (TProfile*)inputList -> FindObject("fProfileZDCPsi2Correlation");
  TProfile*  fProfileV0CTPCPosPsi2Correlation = (TProfile*)inputList -> FindObject("fProfileV0CTPCPosPsi2Correlation");
  TProfile*  fProfileV0ATPCPosPsi2Correlation = (TProfile*)inputList -> FindObject("fProfileV0ATPCPosPsi2Correlation");
  TProfile*  fProfileV0CTPCNegPsi2Correlation = (TProfile*)inputList -> FindObject("fProfileV0CTPCNegPsi2Correlation");
  TProfile*  fProfileV0ATPCNegPsi2Correlation = (TProfile*)inputList -> FindObject("fProfileV0ATPCNegPsi2Correlation");

  fProfileTPCPsi2Correlation -> Rebin(10);
  fProfileV0MPsi2Correlation -> Rebin(10);
  fProfileZDCPsi1Correlation -> Rebin(10);
  fProfileZDCPsi2Correlation -> Rebin(10);
  fProfileV0CTPCPosPsi2Correlation -> Rebin(10);
  fProfileV0ATPCPosPsi2Correlation -> Rebin(10);
  fProfileV0CTPCNegPsi2Correlation -> Rebin(10);
  fProfileV0ATPCNegPsi2Correlation -> Rebin(10);

  TH1D* hRes[6];
  for (int i = 0; i < 5; i++) {
    if (i==0) sprintf(chPlaneType,"TPC Res_{2}");
    if (i==1) sprintf(chPlaneType,"V0C Res_{2}");
    if (i==2) sprintf(chPlaneType,"V0A Res_{2}");
    if (i==3) sprintf(chPlaneType,"ZNC Res_{2}");
    if (i==4) sprintf(chPlaneType,"ZNA Res_{2}");
    if (i==5) sprintf(chPlaneType,"ZDC Res_{1}");
    hRes[i] = new TH1D (Form("hRes_%s",chPlaneType),"",10,0.,100.);
  }

  TH1D* hTPCPsi2Correlation       = fProfileTPCPsi2Correlation -> ProjectionX("hProfileTPCPsi2Correlation");
  TH1D* hV0MPsi2Correlation       = fProfileV0MPsi2Correlation -> ProjectionX("hProfileV0MPsi2Correlation");
  TH1D* hZDCPsi1Correlation       = fProfileZDCPsi1Correlation -> ProjectionX("hProfileZDCPsi1Correlation");
  TH1D* hZDCPsi2Correlation       = fProfileZDCPsi2Correlation -> ProjectionX("hProfileZDCPsi2Correlation");
  TH1D* hV0CTPCPosPsi2Correlation = fProfileV0CTPCPosPsi2Correlation -> ProjectionX("hProfileV0CTPCPosPsi2Correlation");
  TH1D* hV0ATPCPosPsi2Correlation = fProfileV0ATPCPosPsi2Correlation -> ProjectionX("hProfileV0ATPCPosPsi2Correlation");
  TH1D* hV0CTPCNegPsi2Correlation = fProfileV0CTPCNegPsi2Correlation -> ProjectionX("hProfileV0CTPCNegPsi2Correlation");
  TH1D* hV0ATPCNegPsi2Correlation = fProfileV0ATPCNegPsi2Correlation -> ProjectionX("hProfileV0ATPCNegPsi2Correlation");

  std::cout<<"Get the resonlution"<<std::endl;

  hRes[0] -> Multiply(hV0CTPCNegPsi2Correlation, hV0ATPCNegPsi2Correlation,1,1);
  hRes[0] -> Divide(hV0MPsi2Correlation);
  hRes[1] -> Multiply(hV0CTPCNegPsi2Correlation, hV0MPsi2Correlation,1,1);
  hRes[1] -> Divide(hV0ATPCNegPsi2Correlation);
  hRes[2] -> Multiply(hV0ATPCNegPsi2Correlation, hV0MPsi2Correlation,1,1);
  hRes[2] -> Divide(hV0CTPCNegPsi2Correlation);

  hRes[5] = (TH1D*)hZDCPsi1Correlation -> Clone("hRes_ZDCR1");
  hRes[5] -> Scale(-1);


  if(isZDCR2fromData) {
    hRes[3] = (TH1D*)hZDCPsi2Correlation -> Clone("hRes_ZNC");
    hRes[4] = (TH1D*)hZDCPsi2Correlation -> Clone("hRes_ZNA");
    for (int i = 0; i < 6; i++) {
      for (int iBin = 1; iBin < 8; iBin++) {
        double resSquare = hRes[i] -> GetBinContent(iBin);
        if (resSquare < 0.) continue;
        hRes[i] -> SetBinContent(iBin, TMath::Sqrt(resSquare));
      }
    }
  } else if (isZDCR2fromR1) {
    for (int i = 0; i < 3; i++) {
      for (int iBin = 1; iBin < 8; iBin++) {
        double resSquare = hRes[i] -> GetBinContent(iBin);
        if (resSquare < 0.) continue;
        hRes[i] -> SetBinContent(iBin, TMath::Sqrt(resSquare));
      }
    }
    hRes[3] = (TH1D*)hRes[5] -> Clone("hRes_ZNC");
    hRes[3] -> Scale(2./TMath::Pi());
    hRes[4] = (TH1D*)hRes[5] -> Clone("hRes_ZNA");
    hRes[4] -> Scale(2./TMath::Pi());
    for (int iBin = 1; iBin < 8; iBin++) {
      double resSquare = hRes[5] -> GetBinContent(iBin);
      if (resSquare < 0.) continue;
      hRes[5] -> SetBinContent(iBin, TMath::Sqrt(resSquare));
    }
  } else return;

  TProfile*  fProfileRawFlowCenthPos[5];
  TProfile*  fProfileRawFlowCenthNeg[5];
  TProfile*  fProfileRawFlowCentProton[5];
  TProfile*  fProfileRawFlowCentAntiProton[5];
  TProfile*  fProfileRawFlowCentLambda[5];
  TProfile*  fProfileRawFlowCentAntiLambda[5];

  for (int i = 0; i < 5; i++){
    if (i==0) sprintf(chPlaneType,"TPC");
    if (i==1) sprintf(chPlaneType,"V0C");
    if (i==2) sprintf(chPlaneType,"V0A");
    if (i==3) sprintf(chPlaneType,"ZNC");
    if (i==4) sprintf(chPlaneType,"ZNA");
    fProfileRawFlowCenthPos[i]       = fProfile2DRawFlowCentPthPos[i]       -> ProfileX(Form("fProfileFlowCenthPos_%s",chPlaneType),1,25);
    fProfileRawFlowCenthNeg[i]       = fProfile2DRawFlowCentPthNeg[i]       -> ProfileX(Form("fProfileFlowCenthNeg_%s",chPlaneType),1,25);
    fProfileRawFlowCentProton[i]     = fProfile2DRawFlowCentPtProton[i]     -> ProfileX(Form("fProfileFlowCentProton_%s",chPlaneType),1,25);
    fProfileRawFlowCentAntiProton[i] = fProfile2DRawFlowCentPtAntiProton[i] -> ProfileX(Form("fProfileFlowCentAntiProton_%s",chPlaneType),1,25);
    fProfileRawFlowCentLambda[i]     = fProfile2DRawFlowCentPtLambda[i]     -> ProfileX(Form("fProfileFlowCentLambda_%s",chPlaneType),1,25);
    fProfileRawFlowCentAntiLambda[i] = fProfile2DRawFlowCentPtAntiLambda[i] -> ProfileX(Form("fProfileFlowCentAntiLambda_%s",chPlaneType),1,25);
  }


  TH1D*  hFlowCenthPos[5];
  TH1D*  hFlowCenthNeg[5];
  TH1D*  hFlowCentProton[5];
  TH1D*  hFlowCentAntiProton[5];
  TH1D*  hFlowCentLambda[5];
  TH1D*  hFlowCentAntiLambda[5];

  for (int i = 0; i < 5; i++){
    if (i==0) sprintf(chPlaneType,"TPC");
    if (i==1) sprintf(chPlaneType,"V0C");
    if (i==2) sprintf(chPlaneType,"V0A");
    if (i==3) sprintf(chPlaneType,"ZNC");
    if (i==4) sprintf(chPlaneType,"ZNA");

    hFlowCenthPos[i]       = fProfileRawFlowCenthPos[i]       -> ProjectionX(Form("hFlowCenthPos_%s",chPlaneType));
    hFlowCenthNeg[i]       = fProfileRawFlowCenthNeg[i]       -> ProjectionX(Form("hFlowCenthNeg_%s",chPlaneType));
    hFlowCentProton[i]     = fProfileRawFlowCentProton[i]     -> ProjectionX(Form("hFlowCentProton_%s",chPlaneType));
    hFlowCentAntiProton[i] = fProfileRawFlowCentAntiProton[i] -> ProjectionX(Form("hFlowCentAntiProton_%s",chPlaneType));
    hFlowCentLambda[i]     = fProfileRawFlowCentLambda[i]     -> ProjectionX(Form("hFlowCentLambda_%s",chPlaneType));
    hFlowCentAntiLambda[i] = fProfileRawFlowCentAntiLambda[i] -> ProjectionX(Form("hFlowCentAntiLambda_%s",chPlaneType));

    hFlowCenthPos[i]       -> Divide(hRes[i]);
    hFlowCenthNeg[i]       -> Divide(hRes[i]);
    hFlowCentProton[i]     -> Divide(hRes[i]);
    hFlowCentAntiProton[i] -> Divide(hRes[i]);
    hFlowCentLambda[i]     -> Divide(hRes[i]);
    hFlowCentAntiLambda[i] -> Divide(hRes[i]);
  }

  TH1D*  hFlowPt_hPos_Cent[7][5];
  TH1D*  hFlowPt_hNeg_Cent[7][5];
  TH1D*  hFlowPt_Proton_Cent[7][5];
  TH1D*  hFlowPt_AntiProton_Cent[7][5];
  TH1D*  hFlowPt_Lambda_Cent[7][5];
  TH1D*  hFlowPt_AntiLambda_Cent[7][5];


  TProfile*  fProfileRawFlowPt_hPos_Cent[7][5];
  TProfile*  fProfileRawFlowPt_hNeg_Cent[7][5];
  TProfile*  fProfileRawFlowPt_Proton_Cent[7][5];
  TProfile*  fProfileRawFlowPt_AntiProton_Cent[7][5];
  TProfile*  fProfileRawFlowPt_Lambda_Cent[7][5];
  TProfile*  fProfileRawFlowPt_AntiLambda_Cent[7][5];


  for (int iPlane = 0; iPlane < 5; iPlane++) {
    for (int iCent = 1; iCent < 7; iCent++) {
        fProfileRawFlowPt_hPos_Cent[iCent-1][iPlane]       = (TProfile*)fProfile2DRawFlowCentPthPos[iPlane]       -> ProfileY(Form("fProfileRawFlowPt_hPos_Cent%i_Plane%i      ",iCent,iPlane),iCent,iCent);
        fProfileRawFlowPt_hNeg_Cent[iCent-1][iPlane]       = (TProfile*)fProfile2DRawFlowCentPthNeg[iPlane]       -> ProfileY(Form("fProfileRawFlowPt_hNeg_Cent%i_Plane%i      ",iCent,iPlane),iCent,iCent);
        fProfileRawFlowPt_Proton_Cent[iCent-1][iPlane]     = (TProfile*)fProfile2DRawFlowCentPtProton[iPlane]     -> ProfileY(Form("fProfileRawFlowPt_Proton_Cent%i_Plane%i    ",iCent,iPlane),iCent,iCent);
        fProfileRawFlowPt_AntiProton_Cent[iCent-1][iPlane] = (TProfile*)fProfile2DRawFlowCentPtAntiProton[iPlane] -> ProfileY(Form("fProfileRawFlowPt_AntiProton_Cent%i_Plane%i",iCent,iPlane),iCent,iCent);
        fProfileRawFlowPt_Lambda_Cent[iCent-1][iPlane]     = (TProfile*)fProfile2DRawFlowCentPtLambda[iPlane]     -> ProfileY(Form("fProfileRawFlowPt_Lambda_Cent%i_Plane%i    ",iCent,iPlane),iCent,iCent);
        fProfileRawFlowPt_AntiLambda_Cent[iCent-1][iPlane] = (TProfile*)fProfile2DRawFlowCentPtAntiLambda[iPlane] -> ProfileY(Form("fProfileRawFlowPt_AntiLambda_Cent%i_Plane%i",iCent,iPlane),iCent,iCent);
    }
  }

  for (int iPlane = 0; iPlane < 5; iPlane++) {
    for (int iCent = 1; iCent < 7; iCent++) {
      hFlowPt_hPos_Cent[iCent-1][iPlane] =        fProfileRawFlowPt_hPos_Cent[iCent-1][iPlane]       -> ProjectionX(Form("hFlowPt_hPos_Cent%i_Plane%i      ",iCent,iPlane));
      hFlowPt_hNeg_Cent[iCent-1][iPlane] =        fProfileRawFlowPt_hNeg_Cent[iCent-1][iPlane]       -> ProjectionX(Form("hFlowPt_hNeg_Cent%i_Plane%i      ",iCent,iPlane));
      hFlowPt_Proton_Cent[iCent-1][iPlane] =      fProfileRawFlowPt_Proton_Cent[iCent-1][iPlane]     -> ProjectionX(Form("hFlowPt_Proton_Cent%i_Plane%i    ",iCent,iPlane));
      hFlowPt_AntiProton_Cent[iCent-1][iPlane] =  fProfileRawFlowPt_AntiProton_Cent[iCent-1][iPlane] -> ProjectionX(Form("hFlowPt_AntiProton_Cent%i_Plane%i",iCent,iPlane));
      hFlowPt_Lambda_Cent[iCent-1][iPlane] =      fProfileRawFlowPt_Lambda_Cent[iCent-1][iPlane]     -> ProjectionX(Form("hFlowPt_Lambda_Cent%i_Plane%i    ",iCent,iPlane));
      hFlowPt_AntiLambda_Cent[iCent-1][iPlane] =  fProfileRawFlowPt_AntiLambda_Cent[iCent-1][iPlane] -> ProjectionX(Form("hFlowPt_AntiLambda_Cent%i_Plane%i",iCent,iPlane));
    }
  }

  for (int iPlane = 0; iPlane < 5; iPlane++) {
    for (int iCent = 1; iCent < 7; iCent++) {
      hFlowPt_hPos_Cent[iCent-1][iPlane]        -> Scale(1./hRes[iPlane]->GetBinContent(iCent));
      hFlowPt_hNeg_Cent[iCent-1][iPlane]        -> Scale(1./hRes[iPlane]->GetBinContent(iCent));
      hFlowPt_Proton_Cent[iCent-1][iPlane]      -> Scale(1./hRes[iPlane]->GetBinContent(iCent));
      hFlowPt_AntiProton_Cent[iCent-1][iPlane]  -> Scale(1./hRes[iPlane]->GetBinContent(iCent));
      hFlowPt_Lambda_Cent[iCent-1][iPlane]      -> Scale(1./hRes[iPlane]->GetBinContent(iCent));
      hFlowPt_AntiLambda_Cent[iCent-1][iPlane]  -> Scale(1./hRes[iPlane]->GetBinContent(iCent));
    }
  }

  TLegend *legendRes = new TLegend(0.7,0.63,0.85,0.88);
  legendRes->SetBorderSize(0);
  legendRes->AddEntry(hRes[0],"TPC Res_{2}","lp");
  legendRes->AddEntry(hRes[1],"V0C Res_{2}","lp");
  legendRes->AddEntry(hRes[2],"V0A Res_{2}","lp");
  legendRes->AddEntry(hRes[3],"ZNC Res_{2}","lp");
  legendRes->AddEntry(hRes[4],"ZNA Res_{2}","lp");
  legendRes->AddEntry(hRes[5],"ZNA Res_{1}","lp");

  TLegend *legendV2 = new TLegend(0.15,0.6,0.35,0.88);
  legendV2->SetBorderSize(0);
  legendV2->AddEntry(hRes[0],"TPC","lp");
  legendV2->AddEntry(hRes[1],"V0C","lp");
  legendV2->AddEntry(hRes[2],"V0A","lp");
  legendV2->AddEntry(hRes[3],"ZNC","lp");
  legendV2->AddEntry(hRes[4],"ZNA","lp");
  legendV2->AddEntry(v2_C2_cent_sqrtsNN276 ,"Published","lp");

  TLegend *legendV2Diff = new TLegend(0.15,0.6,0.3,0.85);
  legendV2Diff->SetBorderSize(0);
  legendV2Diff->AddEntry(hRes[0],"TPC","lp");
  legendV2Diff->AddEntry(hRes[1],"V0C","lp");
  legendV2Diff->AddEntry(hRes[2],"V0A","lp");


  TCanvas* cRes = new TCanvas("cRes","Resolution",10,10,500,400);
  cRes->cd();
  TH2D* dummyRes = new TH2D("","",1,0,80,1,-0.2,1.);
  if(fPeriod.EqualTo("LHC10h")) dummyRes -> SetTitle("Resolution of 10h");
  if(fPeriod.EqualTo("LHC18q")) dummyRes -> SetTitle("Resolution of 18q");
  if(fPeriod.EqualTo("LHC18r")) dummyRes -> SetTitle("Resolution of 18r");
  dummyRes->SetXTitle("Centrality (%)");
  dummyRes->SetYTitle("Resolution");
  dummyRes->GetYaxis()->SetTitleOffset(1.2);
  dummyRes->Draw("SAME");
  for (int i = 0; i < 6; i++){
    SetStyle(hRes[i],ci[i],kFullCircle,1,1.3);
    hRes[i]->Draw("P SAME");
  }
  legendRes->Draw("SAME");


  TCanvas* cV2Cent = new TCanvas("cV2Cent","v_{2} vs. Centrality",10,10,500,400);
  cV2Cent->cd();
  TH2D* dummyV2Cent = new TH2D("","",1,0,70,1,-0.01,0.15);
  if(fPeriod.EqualTo("LHC10h")) dummyV2Cent -> SetTitle("v_{2} vs. Centrality of 10h");
  if(fPeriod.EqualTo("LHC18q")) dummyV2Cent -> SetTitle("v_{2} vs. Centrality of 18q");
  if(fPeriod.EqualTo("LHC18r")) dummyV2Cent -> SetTitle("v_{2} vs. Centrality of 18r");
  dummyV2Cent->GetXaxis()->SetTitle("");
  dummyV2Cent->GetXaxis()->SetTitle("Centrality (%)");
  dummyV2Cent->GetYaxis()->SetTitle("v_{2}");
  dummyV2Cent->GetYaxis()->SetTitleOffset(1.2);
  dummyV2Cent->Draw("SAME");
  for (int i = 0; i < 5; i++){
    SetStyle(hFlowCenthPos[i],ci[i], kFullCircle,1,0);
    SetStyle(hFlowCenthNeg[i],ci[i], kOpenCircle,1,0);
    hFlowCenthPos[i]->Draw("SAME");
    hFlowCenthNeg[i]->Draw("SAME");
  }
  if(fPeriod.EqualTo("LHC10h")) v2_C2_cent_sqrtsNN276->Draw("SAME");
  if(fPeriod.EqualTo("LHC18q")) v2_C2_cent_sqrtsNN502->Draw("SAME");
  if(fPeriod.EqualTo("LHC18r")) v2_C2_cent_sqrtsNN502->Draw("SAME");
  legendV2->Draw("SAME");


  TCanvas* cV2Pt = new TCanvas("cV2Pt","",10,10,1200,400);
  cV2Pt->Divide(3,1);
  TH2D* dummyV2Pt = new TH2D("","",1,0,5,1,0.,0.35);
  dummyV2Pt->GetXaxis()->SetTitle("");
  dummyV2Pt->GetXaxis()->SetTitle("p_{T}");
  dummyV2Pt->GetYaxis()->SetTitle("v_{2}");
  //dummyV2Pt->GetYaxis()->SetTitleOffset(1.2);

  cV2Pt->cd(1);
  TH2D* dummyV2PtHadron = (TH2D*)dummyV2Pt->Clone("dummyV2PtHadron");
  dummyV2PtHadron ->SetTitle("Hadron Centrality 40-50");
  if(fPeriod.EqualTo("LHC10h")) dummyV2PtHadron -> SetTitle("Hadron v_{2} vs. p_{T} in Centrality 40-50% of 10h");
  if(fPeriod.EqualTo("LHC18q")) dummyV2PtHadron -> SetTitle("Hadron v_{2} vs. p_{T} in Centrality 30-40% of 18q");
  if(fPeriod.EqualTo("LHC18r")) dummyV2PtHadron -> SetTitle("Hadron v_{2} vs. p_{T} in Centrality 30-40% of 18r");
  dummyV2PtHadron->Draw("SAME");
  for (int i = 0; i < 3; i++){
    SetStyle(hFlowPt_hPos_Cent[3][i],ci[i], kFullCircle,1,0);
    SetStyle(hFlowPt_hNeg_Cent[3][i],ci[i], kOpenCircle,1,0);
    SetStyle(hFlowPt_hPos_Cent[4][i],ci[i], kFullCircle,1,0);
    SetStyle(hFlowPt_hNeg_Cent[4][i],ci[i], kOpenCircle,1,0);
    if(fPeriod.EqualTo("LHC10h")) hFlowPt_hPos_Cent[4][i]->Draw("SAME");
    if(fPeriod.EqualTo("LHC10h")) hFlowPt_hNeg_Cent[4][i]->Draw("SAME");
    if(fPeriod.EqualTo("LHC18q")||fPeriod.EqualTo("LHC18r")) hFlowPt_hPos_Cent[3][i]->Draw("SAME");
    if(fPeriod.EqualTo("LHC18q")||fPeriod.EqualTo("LHC18r")) hFlowPt_hNeg_Cent[3][i]->Draw("SAME");
  }
  if(fPeriod.EqualTo("LHC10h")) v2_C2_charge_pt_cent4050_sqrtsNN276->Draw("SAME");
  if(fPeriod.EqualTo("LHC18q")) v2_C2_charge_pt_cent3040_sqrtsNN502->Draw("SAME");
  if(fPeriod.EqualTo("LHC18r")) v2_C2_charge_pt_cent3040_sqrtsNN502->Draw("SAME");
  legendV2Diff->Draw("SAME");

  cV2Pt->cd(2);
  TH2D* dummyV2PtProton = (TH2D*)dummyV2Pt->Clone("dummyV2PtProton");
  if(fPeriod.EqualTo("LHC10h")) dummyV2PtProton -> SetTitle("Proton v_{2} vs. p_{T} in Centrality 40-50% of 10h");
  if(fPeriod.EqualTo("LHC18q")) dummyV2PtProton -> SetTitle("Proton v_{2} vs. p_{T} in Centrality 30-40% of 18q");
  if(fPeriod.EqualTo("LHC18r")) dummyV2PtProton -> SetTitle("Proton v_{2} vs. p_{T} in Centrality 30-40% of 18r");
  dummyV2PtProton ->GetXaxis()->SetLimits(0.6,3.0);
  dummyV2PtProton->Draw("SAME");
  for (int i = 0; i < 3; i++){
    SetStyle(hFlowPt_Proton_Cent[3][i],ci[i], kFullCircle,1,0);
    SetStyle(hFlowPt_AntiProton_Cent[3][i],ci[i], kOpenCircle,1,0);
    SetStyle(hFlowPt_Proton_Cent[4][i],ci[i], kFullCircle,1,0);
    SetStyle(hFlowPt_AntiProton_Cent[4][i],ci[i], kOpenCircle,1,0);
    if(fPeriod.EqualTo("LHC10h")) hFlowPt_Proton_Cent[4][i]->Draw("SAME");
    if(fPeriod.EqualTo("LHC10h")) hFlowPt_AntiProton_Cent[4][i]->Draw("SAME");
    if(fPeriod.EqualTo("LHC18q")||fPeriod.EqualTo("LHC18r")) hFlowPt_Proton_Cent[3][i]->Draw("SAME");
    if(fPeriod.EqualTo("LHC18q")||fPeriod.EqualTo("LHC18r")) hFlowPt_AntiProton_Cent[3][i]->Draw("SAME");
  }
  if(fPeriod.EqualTo("LHC10h")) v2_SP_proton_pt_cent4050_sqrtsNN276->Draw("SAME");
  if(fPeriod.EqualTo("LHC18q")) v2_SP_proton_pt_cent3040_sqrtsNN502->Draw("SAME");
  if(fPeriod.EqualTo("LHC18r")) v2_SP_proton_pt_cent3040_sqrtsNN502->Draw("SAME");
  legendV2Diff->Draw("SAME");

  cV2Pt->cd(3);
  TH2D* dummyV2PtLambda = (TH2D*)dummyV2Pt->Clone("dummyV2PtLambda");
  if(fPeriod.EqualTo("LHC10h")) dummyV2PtLambda -> SetTitle("Lambda v_{2} vs. p_{T} in Centrality 40-50% of 10h");
  if(fPeriod.EqualTo("LHC18q")) dummyV2PtLambda -> SetTitle("Lambda v_{2} vs. p_{T} in Centrality 30-40% of 18q");
  if(fPeriod.EqualTo("LHC18r")) dummyV2PtLambda -> SetTitle("Lambda v_{2} vs. p_{T} in Centrality 30-40% of 18r");
  dummyV2PtLambda->Draw("SAME");
  for (int i = 0; i < 3; i++){
    SetStyle(hFlowPt_Lambda_Cent[3][i],ci[i], kFullCircle,1,0);
    SetStyle(hFlowPt_AntiLambda_Cent[3][i],ci[i], kOpenCircle,1,0);
    SetStyle(hFlowPt_Lambda_Cent[4][i],ci[i], kFullCircle,1,0);
    SetStyle(hFlowPt_AntiLambda_Cent[4][i],ci[i], kOpenCircle,1,0);
    if(fPeriod.EqualTo("LHC10h")) hFlowPt_Lambda_Cent[4][i]->Draw("SAME");
    if(fPeriod.EqualTo("LHC10h")) hFlowPt_AntiLambda_Cent[4][i]->Draw("SAME");
    if(fPeriod.EqualTo("LHC18q")||fPeriod.EqualTo("LHC18r")) hFlowPt_Lambda_Cent[3][i]->Draw("SAME");
    if(fPeriod.EqualTo("LHC18q")||fPeriod.EqualTo("LHC18r")) hFlowPt_AntiLambda_Cent[3][i]->Draw("SAME");
  }
  if(fPeriod.EqualTo("LHC10h")) v2_IM_lambda_pt_cent4050_sqrtsNN276->Draw("SAME");
  if(fPeriod.EqualTo("LHC18q")) v2_IM_lambda_pt_cent3040_sqrtsNN502->Draw("SAME");
  if(fPeriod.EqualTo("LHC18r")) v2_IM_lambda_pt_cent3040_sqrtsNN502->Draw("SAME");
  legendV2Diff->Draw("SAME");


  if(fPeriod.EqualTo("LHC10h")) {
    cRes->SaveAs("Resolution10h.pdf");
    cV2Cent->SaveAs("V2Cent10h.pdf");
    cV2Pt->SaveAs("V2Pt10h.pdf");
  }
  if(fPeriod.EqualTo("LHC18q")) {
    cRes->SaveAs("Resolution18q.pdf");
    cV2Cent->SaveAs("V2Cent18q.pdf");
    cV2Pt->SaveAs("V2Pt18q.pdf");
  }
  if(fPeriod.EqualTo("LHC18r")) {
    cRes->SaveAs("Resolution18r.pdf");
    cV2Cent->SaveAs("V2Cent18r.pdf");
    cV2Pt->SaveAs("V2Pt18r.pdf");
  }
}