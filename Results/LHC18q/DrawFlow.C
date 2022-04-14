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
  // int ci[4];
  // TColor* color[4];
  // ci[0] = TColor::GetFreeColorIndex();
  // color[0] = new TColor(ci[0],   0/255.,  24/255., 113/255.);//dark blue
  // ci[1] = TColor::GetFreeColorIndex();
  // color[1] = new TColor(ci[1], 255/255.,  88/255.,  93/255.);//red
  // ci[2] = TColor::GetFreeColorIndex();
  // color[2] = new TColor(ci[2], 255/255., 181/255.,  73/255.);//yellow
  // ci[3] = TColor::GetFreeColorIndex();
  // color[3] = new TColor(ci[3], 65/255.,  182/255., 230/255.);//light blue

  // int ci[5];
  // TColor* color[5];
  // ci[0] = TColor::GetFreeColorIndex();
  // color[0] = new TColor(ci[0],  24/255.,  63/255.,  94/255.);//深蓝
  // ci[1] = TColor::GetFreeColorIndex();
  // color[1] = new TColor(ci[1],  33/255.,  99/255., 154/255.);//浅蓝
  // ci[2] = TColor::GetFreeColorIndex();
  // color[2] = new TColor(ci[2], 246/255., 213/255., 101/255.);//黄
  // ci[3] = TColor::GetFreeColorIndex();
  // color[3] = new TColor(ci[3],  62/255., 174/255., 164/255.);//绿
  // ci[4] = TColor::GetFreeColorIndex();
  // color[4] = new TColor(ci[4], 236/255.,  85/255.,  60/255.);//红
  
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

  // TFile* HEPDataFile_table1 = TFile::Open("runAnalysis.root", "READ");
  // TFile* HEPDataFile_table3 = TFile::Open("HEPData-ins877822-v1-Table_3.root", "READ");
  // TFile* HEPDataFile_table34 = TFile::Open("HEPData-ins1297103-v1-Table_34.root", "READ");
  // TFile* HEPDataFile_table46 = TFile::Open("HEPData-ins1297103-v1-Table_46.root", "READ");

  // TDirectoryFile* Table1 = (TDirectoryFile*) HEPDataFile_table1->GetDirectory("Table 1");
  // TDirectoryFile* Table3 = (TDirectoryFile*) HEPDataFile_table3->GetDirectory("Table 3");
  // TDirectoryFile* Table34 = (TDirectoryFile*) HEPDataFile_table34->GetDirectory("Table 34");
  // TDirectoryFile* Table46 = (TDirectoryFile*) HEPDataFile_table46->GetDirectory("Table 46");

  // TGraphAsymmErrors* v2Cent;
  // Table3->cd();
  // Table3->GetObject("Graph1D_y1",v2Cent);
  // TGraphAsymmErrors* v2PtCent4050;
  // Table1->cd();
  // Table1->GetObject("Graph1D_y1",v2PtCent4050);
  // TGraphAsymmErrors* v2ProtonPtCent4050;
  // Table34->cd();
  // Table34->GetObject("Graph1D_y1",v2ProtonPtCent4050);
  // TGraphAsymmErrors* v2LambdaPtCent4050;
  // Table46->cd();
  // Table46->GetObject("Graph1D_y1",v2LambdaPtCent4050);

  TList* outputList = nullptr;
  TFile* outputFile = TFile::Open("AnalysisResults.root", "READ");
  outputList = (TList*) outputFile->Get("output_"); 

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
    fProfile2DRawFlowCentPthPos[i] = (TProfile2D*)outputList->FindObject(Form("fProfile2DRawFlowCentPthPos_%s",chPlaneType));
    fProfile2DRawFlowCentPthNeg[i] = (TProfile2D*)outputList->FindObject(Form("fProfile2DRawFlowCentPthNeg_%s",chPlaneType));
    fProfile2DRawFlowCentPtProton[i] = (TProfile2D*)outputList->FindObject(Form("fProfile2DRawFlowCentPtProton_%s",chPlaneType));
    fProfile2DRawFlowCentPtAntiProton[i] = (TProfile2D*)outputList->FindObject(Form("fProfile2DRawFlowCentPtAntiProton_%s",chPlaneType));
    fProfile2DRawFlowCentPtLambda[i] = (TProfile2D*)outputList->FindObject(Form("fProfile2DRawFlowCentPtLambda_%s",chPlaneType));
    fProfile2DRawFlowCentPtAntiLambda[i] = (TProfile2D*)outputList->FindObject(Form("fProfile2DRawFlowCentPtAntiLambda_%s",chPlaneType));
  }

  TProfile*  fProfileTPCPsi2Correlation = (TProfile*)outputList -> FindObject("fProfileTPCPsi2Correlation");
  TProfile*  fProfileV0MPsi2Correlation = (TProfile*)outputList -> FindObject("fProfileV0MPsi2Correlation");
  TProfile*  fProfileZDCPsi1Correlation = (TProfile*)outputList -> FindObject("fProfileZDCPsi1Correlation");
  TProfile*  fProfileZDCPsi2Correlation = (TProfile*)outputList -> FindObject("fProfileZDCPsi2Correlation");
  TProfile*  fProfileV0CTPCPosPsi2Correlation = (TProfile*)outputList -> FindObject("fProfileV0CTPCPosPsi2Correlation");
  TProfile*  fProfileV0ATPCPosPsi2Correlation = (TProfile*)outputList -> FindObject("fProfileV0ATPCPosPsi2Correlation");
  TProfile*  fProfileV0CTPCNegPsi2Correlation = (TProfile*)outputList -> FindObject("fProfileV0CTPCNegPsi2Correlation");
  TProfile*  fProfileV0ATPCNegPsi2Correlation = (TProfile*)outputList -> FindObject("fProfileV0ATPCNegPsi2Correlation");

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
    if (i==0) sprintf(chPlaneType,"TPC");
    if (i==1) sprintf(chPlaneType,"V0C");
    if (i==2) sprintf(chPlaneType,"V0A");
    if (i==3) sprintf(chPlaneType,"ZNC");
    if (i==4) sprintf(chPlaneType,"ZNA");
    if (i==5) sprintf(chPlaneType,"ZDCR1");
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

    // hFlowCenthPos[2]       = fProfileRawFlowCenthPos[2]       -> ProjectionX(Form("hFlowCenthPos_%s","V0A"));
    // hFlowCenthNeg[2]       = fProfileRawFlowCenthNeg[2]       -> ProjectionX(Form("hFlowCenthNeg_%s","V0A"));
    // hFlowCentProton[2]     = fProfileRawFlowCentProton[2]     -> ProjectionX(Form("hFlowCentProton_%s","V0A"));
    // hFlowCentAntiProton[2] = fProfileRawFlowCentAntiProton[2] -> ProjectionX(Form("hFlowCentAntiProton_%s","V0A"));
    // hFlowCentLambda[2]     = fProfileRawFlowCentLambda[2]     -> ProjectionX(Form("hFlowCentLambda_%s","V0A"));
    // hFlowCentAntiLambda[2] = fProfileRawFlowCentAntiLambda[2] -> ProjectionX(Form("hFlowCentAntiLambda_%s","V0A"));

    // hFlowCenthPos[2]       -> Divide(hRes[1]);
    // hFlowCenthNeg[2]       -> Divide(hRes[1]);
    // hFlowCentProton[2]     -> Divide(hRes[1]);
    // hFlowCentAntiProton[2] -> Divide(hRes[1]);
    // hFlowCentLambda[2]     -> Divide(hRes[1]);
    // hFlowCentAntiLambda[2] -> Divide(hRes[1]);

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
  
  // //QC
  // TProfile* fProfileC2Cent = (TProfile*) outputList->FindObject("fProfileC2Cent");
  // TH1D* hFlowCent = new TH1D("hFlowCent", "hFlowCent", 10, 0, 100);
  // for (int iBin = 0; iBin < 10; iBin++) {
  //   double c2 = fProfileC2Cent->GetBinContent(iBin+1);
  //   double c2Err = fProfileC2Cent->GetBinError(iBin+1);
  //   hFlowCent -> SetBinContent(iBin+1, TMath::Sqrt(c2));
  //   hFlowCent -> SetBinError(iBin+1, c2Err);
  // }


  TLegend *legendRes = new TLegend(0.7,0.6,0.9,0.88);
  legendRes->SetBorderSize(0);
  legendRes->AddEntry(hRes[0],"TPC","lp");
  legendRes->AddEntry(hRes[1],"V0C","lp");
  legendRes->AddEntry(hRes[2],"V0A","lp");
  legendRes->AddEntry(hRes[3],"ZNC","lp");
  legendRes->AddEntry(hRes[4],"ZNA","lp");
  legendRes->AddEntry(hRes[5],"ZNA R1","lp");

  TLegend *legendV2 = new TLegend(0.15,0.6,0.3,0.88);
  legendV2->SetBorderSize(0);
  legendV2->AddEntry(hRes[0],"TPC","lp");
  legendV2->AddEntry(hRes[1],"V0C","lp");
  legendV2->AddEntry(hRes[2],"V0A","lp");
  legendV2->AddEntry(hRes[3],"ZNC","lp");
  legendV2->AddEntry(hRes[4],"ZNA","lp");
  //legendV2->AddEntry(v2Cent ,"Published","lp");

  TLegend *legendV2Diff = new TLegend(0.15,0.6,0.3,0.85);
  legendV2Diff->SetBorderSize(0);
  legendV2Diff->AddEntry(hRes[0],"TPC","lp");
  legendV2Diff->AddEntry(hRes[1],"V0C","lp");
  legendV2Diff->AddEntry(hRes[2],"V0A","lp");


  TCanvas* cRes = new TCanvas("cRes","Resolution",10,10,500,400);
  cRes->cd();
  TH2D* dummyRes = new TH2D("","",1,0,80,1,0,1.);
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
  //v2Cent->Draw("SAME");
  legendV2->Draw("SAME");


  TCanvas* cV2Pt = new TCanvas("cV2Pt","v_{2} vs. pt cent40-50",10,10,1200,400);
  cV2Pt->Divide(3,1);
  TH2D* dummyV2Pt = new TH2D("","",1,0,5,1,0.,0.35);
  dummyV2Pt->GetXaxis()->SetTitle("");
  dummyV2Pt->GetXaxis()->SetTitle("p_{T}");
  dummyV2Pt->GetYaxis()->SetTitle("v_{2}");
  dummyV2Pt->GetYaxis()->SetTitleOffset(1.2);

  cV2Pt->cd(1);
  TH2D* dummyV2PtHadron = (TH2D*)dummyV2Pt->Clone("dummyV2PtHadron");
  dummyV2PtHadron ->SetTitle("Hadron Cent 40-50");
  dummyV2PtHadron->Draw("SAME");
  for (int i = 0; i < 5; i++){
    SetStyle(hFlowPt_hPos_Cent[4][i],ci[i], kFullCircle,1,0);
    SetStyle(hFlowPt_hNeg_Cent[4][i],ci[i], kOpenCircle,1,0);
    hFlowPt_hPos_Cent[4][i]->Draw("SAME");
    hFlowPt_hNeg_Cent[4][i]->Draw("SAME");
  }
  //v2PtCent4050->Draw("same");
  legendV2->Draw("SAME");

  cV2Pt->cd(2);
  TH2D* dummyV2PtProton = (TH2D*)dummyV2Pt->Clone("dummyV2PtProton");
  dummyV2PtProton ->SetTitle("Proton Cent 40-50");
  dummyV2PtProton->Draw("SAME");
  for (int i = 0; i < 5; i++){
    SetStyle(hFlowPt_Proton_Cent[4][i],ci[i], kFullCircle,1,0);
    SetStyle(hFlowPt_AntiProton_Cent[4][i],ci[i], kOpenCircle,1,0);
    hFlowPt_Proton_Cent[4][i]->Draw("SAME");
    hFlowPt_AntiProton_Cent[4][i]->Draw("SAME");
  }
  //v2ProtonPtCent4050->Draw("same");
  legendV2->Draw("SAME");

  cV2Pt->cd(3);
  TH2D* dummyV2PtLambda = (TH2D*)dummyV2Pt->Clone("dummyV2PtLambda");
  dummyV2PtLambda ->SetTitle("Lambda Cent 40-50");
  dummyV2PtLambda->Draw("SAME");
  for (int i = 0; i < 5; i++){
    SetStyle(hFlowPt_Lambda_Cent[4][i],ci[i], kFullCircle,1,0);
    SetStyle(hFlowPt_AntiLambda_Cent[4][i],ci[i], kOpenCircle,1,0);
    hFlowPt_Lambda_Cent[4][i]->Draw("SAME");
    hFlowPt_AntiLambda_Cent[4][i]->Draw("SAME");
    legendV2->Draw("SAME");
  }
  //v2LambdaPtCent4050->Draw("same");
  legendV2->Draw("SAME");


  TCanvas* cV2PtCent = new TCanvas("cV2PtCent","v_{2} vs. pt",10,10,1200,600);
  cV2PtCent->Divide(3,2);
  TH2D* dummyV2PtCent[6];
  for (int i = 0; i < 6; i++){
    dummyV2PtCent[i] = new TH2D("",Form("Centrality %i0-%i0 %",i,i+1),1,0,5,1,0.,0.32);
    dummyV2PtCent[i]->GetXaxis()->SetTitle("");
    dummyV2PtCent[i]->GetXaxis()->SetTitle("p_{T}");
    dummyV2PtCent[i]->GetYaxis()->SetTitle("v_{2}");
    dummyV2PtCent[i]->GetYaxis()->SetTitleOffset(1.2);
  }
  
  for (int iCent = 1; iCent <= 6; iCent++)
  {
    cV2PtCent->cd(iCent);
    dummyV2PtCent[iCent-1]->Draw("SAME");
    for (int iPlane = 0; iPlane < 3; iPlane++){
      SetStyle(hFlowPt_hPos_Cent[iCent-1][iPlane],ci[iPlane], kFullCircle,1,0);
      SetStyle(hFlowPt_hNeg_Cent[iCent-1][iPlane],ci[iPlane], kOpenCircle,1,0);
      hFlowPt_hPos_Cent[iCent-1][iPlane]->Draw("SAME");
      hFlowPt_hNeg_Cent[iCent-1][iPlane]->Draw("SAME");
    }
    legendV2Diff->Draw("SAME");
  } 
}