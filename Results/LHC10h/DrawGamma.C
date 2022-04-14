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
void DrawGamma(){
  double xbins[12] = {0,5,10,20,30,40,50,60,70,80,90,100};
  char chPlaneType[5];

  int ci[5];
  TColor* color[5];
  ci[0] = TColor::GetFreeColorIndex();
  color[0] = new TColor(ci[0],  24/255.,  63/255.,  94/255.);//深蓝
  ci[1] = TColor::GetFreeColorIndex();
  color[1] = new TColor(ci[1], 236/255.,  85/255.,  60/255.);//红
  ci[2] = TColor::GetFreeColorIndex();
  color[2] = new TColor(ci[2], 246/255., 213/255., 101/255.);//黄
  ci[3] = TColor::GetFreeColorIndex();
  color[3] = new TColor(ci[3],  62/255., 174/255., 164/255.);//绿
  ci[4] = TColor::GetFreeColorIndex();
  color[4] = new TColor(ci[4],  33/255.,  99/255., 154/255.);//浅蓝

  int ci2[5];
  TColor* color2[2];
  ci2[0] = TColor::GetFreeColorIndex();
  color2[0] = new TColor(ci2[0],   1/255.,  65/255., 148/255.);//蓝
  ci2[1] = TColor::GetFreeColorIndex();
  color2[1] = new TColor(ci2[1], 227/255.,   2/255.,  55/255.);//红

  gStyle->SetOptStat(0);
  TFile* outputFile = TFile::Open("AnalysisResults_10h_withNUA_PlanePt5.root", "READ");
  TList* outputList = (TList*) outputFile->Get("output"); 

  TProfile2D*  fProfile2DRawFlowCentPthPos[5];
  TProfile2D*  fProfile2DRawFlowCentPthNeg[5];
  TProfile2D*  fProfile2DRawFlowCentPtProton[5];
  TProfile2D*  fProfile2DRawFlowCentPtAntiProton[5];
  TProfile2D*  fProfile2DRawFlowCentPtLambda[5];
  TProfile2D*  fProfile2DRawFlowCentPtAntiLambda[5];

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

  
  fProfileTPCPsi2Correlation       = (TProfile*)fProfileTPCPsi2Correlation       -> Rebin(11,"fProfileTPCPsi2Correlation",xbins);
  fProfileV0MPsi2Correlation       = (TProfile*)fProfileV0MPsi2Correlation       -> Rebin(11,"fProfileV0MPsi2Correlation",xbins);
  fProfileZDCPsi1Correlation       = (TProfile*)fProfileZDCPsi1Correlation       -> Rebin(11,"fProfileZDCPsi1Correlation",xbins);
  fProfileZDCPsi2Correlation       = (TProfile*)fProfileZDCPsi2Correlation       -> Rebin(11,"fProfileZDCPsi2Correlation",xbins);
  fProfileV0CTPCPosPsi2Correlation = (TProfile*)fProfileV0CTPCPosPsi2Correlation -> Rebin(11,"fProfileV0CTPCPosPsi2Correlation",xbins);
  fProfileV0ATPCPosPsi2Correlation = (TProfile*)fProfileV0ATPCPosPsi2Correlation -> Rebin(11,"fProfileV0ATPCPosPsi2Correlation",xbins);
  fProfileV0CTPCNegPsi2Correlation = (TProfile*)fProfileV0CTPCNegPsi2Correlation -> Rebin(11,"fProfileV0CTPCNegPsi2Correlation",xbins);
  fProfileV0ATPCNegPsi2Correlation = (TProfile*)fProfileV0ATPCNegPsi2Correlation -> Rebin(11,"fProfileV0ATPCNegPsi2Correlation",xbins);

  TH1D* hTPCPsi2Correlation       = fProfileTPCPsi2Correlation -> ProjectionX("hTPCPsi2Correlation");
  TH1D* hV0MPsi2Correlation       = fProfileV0MPsi2Correlation -> ProjectionX("hV0MPsi2Correlation");
  TH1D* hZDCPsi1Correlation       = fProfileZDCPsi1Correlation -> ProjectionX("hZDCPsi1Correlation");
  TH1D* hZDCPsi2Correlation       = fProfileZDCPsi2Correlation -> ProjectionX("hZDCPsi2Correlation");
  TH1D* hV0CTPCPosPsi2Correlation = fProfileV0CTPCPosPsi2Correlation -> ProjectionX("hV0CTPCPosPsi2Correlation");
  TH1D* hV0ATPCPosPsi2Correlation = fProfileV0ATPCPosPsi2Correlation -> ProjectionX("hV0ATPCPosPsi2Correlation");
  TH1D* hV0CTPCNegPsi2Correlation = fProfileV0CTPCNegPsi2Correlation -> ProjectionX("hV0CTPCNegPsi2Correlation");
  TH1D* hV0ATPCNegPsi2Correlation = fProfileV0ATPCNegPsi2Correlation -> ProjectionX("hV0ATPCNegPsi2Correlation");

  std::cout<<"Get the resonlution"<<std::endl;
  TH1D* hRes[5];
  for (int i = 0; i < 5; i++) {
    if (i==0) sprintf(chPlaneType,"TPC");
    if (i==1) sprintf(chPlaneType,"V0C");
    if (i==2) sprintf(chPlaneType,"V0A");
    if (i==3) sprintf(chPlaneType,"ZNC");
    if (i==4) sprintf(chPlaneType,"ZNA");
    hRes[i] = new TH1D (Form("hRes_%s",chPlaneType),"",11,xbins);
  }
  hRes[0] -> Multiply(hV0CTPCNegPsi2Correlation, hV0ATPCNegPsi2Correlation,1,1);
  hRes[0] -> Divide(hV0MPsi2Correlation);
  hRes[1] -> Multiply(hV0CTPCNegPsi2Correlation, hV0MPsi2Correlation,1,1);
  hRes[1] -> Divide(hV0ATPCNegPsi2Correlation);
  hRes[2] -> Multiply(hV0ATPCNegPsi2Correlation, hV0MPsi2Correlation,1,1);
  hRes[2] -> Divide(hV0CTPCNegPsi2Correlation);
  hRes[3] = (TH1D*)hZDCPsi2Correlation -> Clone("hRes_ZNC");
  hRes[4] = (TH1D*)hZDCPsi2Correlation -> Clone("hRes_ZNA");
  for (int i = 0; i < 5; i++) {
    for (int iBin = 1; iBin < 8; iBin++) {
      double resSquare = hRes[i] -> GetBinContent(iBin);
      if (resSquare < 0.) continue;
      hRes[i] -> SetBinContent(iBin, TMath::Sqrt(resSquare));
    }
  }

  ///Lambda-X correlators
  ///Delta Correlators:
  ///Lambda - X
  TProfile* fProfileDelta_Lambda_hPos = (TProfile*) outputList->FindObject("fProfileDelta_Lambda_hPos");
  TProfile* fProfileDelta_Lambda_hNeg = (TProfile*) outputList->FindObject("fProfileDelta_Lambda_hNeg");
  TProfile* fProfileDelta_Lambda_Proton = (TProfile*) outputList->FindObject("fProfileDelta_Lambda_Proton");
  TProfile* fProfileDelta_Lambda_AntiProton = (TProfile*) outputList->FindObject("fProfileDelta_Lambda_AntiProton");

  ///AntiLambda - X
  TProfile* fProfileDelta_AntiLambda_hPos = (TProfile*) outputList->FindObject("fProfileDelta_AntiLambda_hPos");
  TProfile* fProfileDelta_AntiLambda_hNeg = (TProfile*) outputList->FindObject("fProfileDelta_AntiLambda_hNeg");
  TProfile* fProfileDelta_AntiLambda_Proton = (TProfile*) outputList->FindObject("fProfileDelta_AntiLambda_Proton");
  TProfile* fProfileDelta_AntiLambda_AntiProton = (TProfile*) outputList->FindObject("fProfileDelta_AntiLambda_AntiProton");
  

  TProfile* fProfileGamma_Lambda_hPos[5];       
  TProfile* fProfileGamma_Lambda_hNeg[5];       
  TProfile* fProfileGamma_Lambda_Proton[5];     
  TProfile* fProfileGamma_Lambda_AntiProton[5]; 

  TProfile* fProfileGamma_AntiLambda_hPos[5];       
  TProfile* fProfileGamma_AntiLambda_hNeg[5];       
  TProfile* fProfileGamma_AntiLambda_Proton[5];     
  TProfile* fProfileGamma_AntiLambda_AntiProton[5]; 

  ///Gamma Correlators:
  //TPC Plane
  ///Lambda - X
  fProfileGamma_Lambda_hPos[0]       = (TProfile*) outputList->FindObject("fProfileGammaTPC_Lambda_hPos");
  fProfileGamma_Lambda_hNeg[0]       = (TProfile*) outputList->FindObject("fProfileGammaTPC_Lambda_hNeg");
  fProfileGamma_Lambda_Proton[0]     = (TProfile*) outputList->FindObject("fProfileGammaTPC_Lambda_Proton");
  fProfileGamma_Lambda_AntiProton[0] = (TProfile*) outputList->FindObject("fProfileGammaTPC_Lambda_AntiProton");

  ///AntiLambda - X
  fProfileGamma_AntiLambda_hPos[0]       = (TProfile*) outputList->FindObject("fProfileGammaTPC_AntiLambda_hPos");
  fProfileGamma_AntiLambda_hNeg[0]       = (TProfile*) outputList->FindObject("fProfileGammaTPC_AntiLambda_hNeg");
  fProfileGamma_AntiLambda_Proton[0]     = (TProfile*) outputList->FindObject("fProfileGammaTPC_AntiLambda_Proton");
  fProfileGamma_AntiLambda_AntiProton[0] = (TProfile*) outputList->FindObject("fProfileGammaTPC_AntiLambda_AntiProton");

  //V0C Plane
  ///Lambda - X
  fProfileGamma_Lambda_hPos[1] = (TProfile*) outputList->FindObject("fProfileGammaV0C_Lambda_hPos");
  fProfileGamma_Lambda_hNeg[1] = (TProfile*) outputList->FindObject("fProfileGammaV0C_Lambda_hNeg");
  fProfileGamma_Lambda_Proton[1] = (TProfile*) outputList->FindObject("fProfileGammaV0C_Lambda_Proton");
  fProfileGamma_Lambda_AntiProton[1] = (TProfile*) outputList->FindObject("fProfileGammaV0C_Lambda_AntiProton");

  ///AntiLambda - X
  fProfileGamma_AntiLambda_hPos[1] = (TProfile*) outputList->FindObject("fProfileGammaV0C_AntiLambda_hPos");
  fProfileGamma_AntiLambda_hNeg[1] = (TProfile*) outputList->FindObject("fProfileGammaV0C_AntiLambda_hNeg");
  fProfileGamma_AntiLambda_Proton[1] = (TProfile*) outputList->FindObject("fProfileGammaV0C_AntiLambda_Proton");
  fProfileGamma_AntiLambda_AntiProton[1] = (TProfile*) outputList->FindObject("fProfileGammaV0C_AntiLambda_AntiProton");

  //V0A Plane
  ///Lambda - X
  fProfileGamma_Lambda_hPos[2] = (TProfile*) outputList->FindObject("fProfileGammaV0A_Lambda_hPos");
  fProfileGamma_Lambda_hNeg[2] = (TProfile*) outputList->FindObject("fProfileGammaV0A_Lambda_hNeg");
  fProfileGamma_Lambda_Proton[2] = (TProfile*) outputList->FindObject("fProfileGammaV0A_Lambda_Proton");
  fProfileGamma_Lambda_AntiProton[2] = (TProfile*) outputList->FindObject("fProfileGammaV0A_Lambda_AntiProton");

  ///AntiLambda - X
  fProfileGamma_AntiLambda_hPos[2] = (TProfile*) outputList->FindObject("fProfileGammaV0A_AntiLambda_hPos");
  fProfileGamma_AntiLambda_hNeg[2] = (TProfile*) outputList->FindObject("fProfileGammaV0A_AntiLambda_hNeg");
  fProfileGamma_AntiLambda_Proton[2] = (TProfile*) outputList->FindObject("fProfileGammaV0A_AntiLambda_Proton");
  fProfileGamma_AntiLambda_AntiProton[2] = (TProfile*) outputList->FindObject("fProfileGammaV0A_AntiLambda_AntiProton");

  //ZNC Plane
  ///Lambda - X
  fProfileGamma_Lambda_hPos[3] = (TProfile*) outputList->FindObject("fProfileGammaZNC_Lambda_hPos");
  fProfileGamma_Lambda_hNeg[3] = (TProfile*) outputList->FindObject("fProfileGammaZNC_Lambda_hNeg");
  fProfileGamma_Lambda_Proton[3] = (TProfile*) outputList->FindObject("fProfileGammaZNC_Lambda_Proton");
  fProfileGamma_Lambda_AntiProton[3] = (TProfile*) outputList->FindObject("fProfileGammaZNC_Lambda_AntiProton");

  ///AntiLambda - X
  fProfileGamma_AntiLambda_hPos[3] = (TProfile*) outputList->FindObject("fProfileGammaZNC_AntiLambda_hPos");
  fProfileGamma_AntiLambda_hNeg[3] = (TProfile*) outputList->FindObject("fProfileGammaZNC_AntiLambda_hNeg");
  fProfileGamma_AntiLambda_Proton[3] = (TProfile*) outputList->FindObject("fProfileGammaZNC_AntiLambda_Proton");
  fProfileGamma_AntiLambda_AntiProton[3] = (TProfile*) outputList->FindObject("fProfileGammaZNC_AntiLambda_AntiProton");

  //ZNA Plane
  ///Lambda - X
  fProfileGamma_Lambda_hPos[4] = (TProfile*) outputList->FindObject("fProfileGammaZNA_Lambda_hPos");
  fProfileGamma_Lambda_hNeg[4] = (TProfile*) outputList->FindObject("fProfileGammaZNA_Lambda_hNeg");
  fProfileGamma_Lambda_Proton[4] = (TProfile*) outputList->FindObject("fProfileGammaZNA_Lambda_Proton");
  fProfileGamma_Lambda_AntiProton[4] = (TProfile*) outputList->FindObject("fProfileGammaZNA_Lambda_AntiProton");

  ///AntiLambda - X
  fProfileGamma_AntiLambda_hPos[4] = (TProfile*) outputList->FindObject("fProfileGammaZNA_AntiLambda_hPos");
  fProfileGamma_AntiLambda_hNeg[4] = (TProfile*) outputList->FindObject("fProfileGammaZNA_AntiLambda_hNeg");
  fProfileGamma_AntiLambda_Proton[4] = (TProfile*) outputList->FindObject("fProfileGammaZNA_AntiLambda_Proton");
  fProfileGamma_AntiLambda_AntiProton[4] = (TProfile*) outputList->FindObject("fProfileGammaZNA_AntiLambda_AntiProton");


  TProfile* fProfileDeltaLambdaHadronOppo = new TProfile("fProfileDeltaLambdaHadronOppo","",20,0,100);
  TProfile* fProfileDeltaLambdaHadronSame = new TProfile("fProfileDeltaLambdaHadronSame","",20,0,100);
  TProfile* fProfileDeltaLambdaProtonOppo = new TProfile("fProfileDeltaLambdaProtonOppo","",20,0,100);
  TProfile* fProfileDeltaLambdaProtonSame = new TProfile("fProfileDeltaLambdaProtonSame","",20,0,100);

  TProfile* fProfileGammaLambdaHadronOppo[5];
  TProfile* fProfileGammaLambdaHadronSame[5];
  TProfile* fProfileGammaLambdaProtonOppo[5];
  TProfile* fProfileGammaLambdaProtonSame[5];

  for (Int_t i = 0; i < 5; i++){
    if (i==0) sprintf(chPlaneType,"TPC");
    if (i==1) sprintf(chPlaneType,"V0C");
    if (i==2) sprintf(chPlaneType,"V0A");
    if (i==3) sprintf(chPlaneType,"ZNC");
    if (i==4) sprintf(chPlaneType,"ZNA");
    fProfileGammaLambdaHadronOppo[i] = new TProfile(Form("fProfileGammaLambdaHadronOppo_%s",chPlaneType),"",20,0,100);
    fProfileGammaLambdaHadronSame[i] = new TProfile(Form("fProfileGammaLambdaHadronSame_%s",chPlaneType),"",20,0,100);
  }

  for (Int_t i = 0; i < 5; i++){
    if (i==0) sprintf(chPlaneType,"TPC");
    if (i==1) sprintf(chPlaneType,"V0C");
    if (i==2) sprintf(chPlaneType,"V0A");
    if (i==3) sprintf(chPlaneType,"ZNC");
    if (i==4) sprintf(chPlaneType,"ZNA");
    fProfileGammaLambdaProtonOppo[i] = new TProfile(Form("fProfileGammaLambdaProtonOppo_%s",chPlaneType),"",20,0,100);
    fProfileGammaLambdaProtonSame[i] = new TProfile(Form("fProfileGammaLambdaProtonSame_%s",chPlaneType),"",20,0,100);
  }

  fProfileDeltaLambdaHadronOppo->Add(fProfileDelta_AntiLambda_hPos);
  fProfileDeltaLambdaHadronOppo->Add(fProfileDelta_Lambda_hNeg);
  fProfileDeltaLambdaHadronSame->Add(fProfileDelta_Lambda_hPos);
  fProfileDeltaLambdaHadronSame->Add(fProfileDelta_AntiLambda_hNeg);

  fProfileDeltaLambdaProtonOppo->Add(fProfileDelta_AntiLambda_Proton);
  fProfileDeltaLambdaProtonOppo->Add(fProfileDelta_Lambda_AntiProton);
  fProfileDeltaLambdaProtonSame->Add(fProfileDelta_Lambda_Proton);
  fProfileDeltaLambdaProtonSame->Add(fProfileDelta_AntiLambda_AntiProton);

  fProfileDeltaLambdaHadronOppo = (TProfile*)fProfileDeltaLambdaHadronOppo -> Rebin(11,"",xbins);
  fProfileDeltaLambdaHadronSame = (TProfile*)fProfileDeltaLambdaHadronSame -> Rebin(11,"",xbins);
  fProfileDeltaLambdaProtonOppo = (TProfile*)fProfileDeltaLambdaProtonOppo -> Rebin(11,"",xbins);
  fProfileDeltaLambdaProtonSame = (TProfile*)fProfileDeltaLambdaProtonSame -> Rebin(11,"",xbins);

  TH1D* hDeltaLambdaHadronOppo = (TH1D*)fProfileDeltaLambdaHadronOppo -> ProjectionX("hDeltaLambdaHadronOppo");
  TH1D* hDeltaLambdaHadronSame = (TH1D*)fProfileDeltaLambdaHadronSame -> ProjectionX("hDeltaLambdaHadronSame");
  TH1D* hDeltaLambdaProtonOppo = (TH1D*)fProfileDeltaLambdaProtonOppo -> ProjectionX("hDeltaLambdaProtonOppo");
  TH1D* hDeltaLambdaProtonSame = (TH1D*)fProfileDeltaLambdaProtonSame -> ProjectionX("hDeltaLambdaProtonSame");

  TH1D* hDeltaDeltaLambdaHadron = new TH1D("hDeltaDeltaHadron","",11,xbins);
  TH1D* hDeltaDeltaLambdaProton = new TH1D("hDeltaDeltaProton","",11,xbins);
  hDeltaDeltaLambdaHadron->Add(hDeltaLambdaHadronOppo,hDeltaLambdaHadronSame,1,-1);
  hDeltaDeltaLambdaProton->Add(hDeltaLambdaProtonOppo,hDeltaLambdaProtonSame,1,-1);

  TH1D* hGammaLambdaHadronOppo[5];
  TH1D* hGammaLambdaHadronSame[5];
  TH1D* hGammaLambdaProtonOppo[5];
  TH1D* hGammaLambdaProtonSame[5];

  for (int i = 0; i < 5; i++){
    fProfileGammaLambdaHadronOppo[i] -> Add(fProfileGamma_AntiLambda_hPos[i]);
    fProfileGammaLambdaHadronOppo[i] -> Add(fProfileGamma_Lambda_hNeg[i]);
    fProfileGammaLambdaHadronSame[i] -> Add(fProfileGamma_Lambda_hPos[i]);
    fProfileGammaLambdaHadronSame[i] -> Add(fProfileGamma_AntiLambda_hNeg[i]);
    fProfileGammaLambdaProtonOppo[i] -> Add(fProfileGamma_AntiLambda_Proton[i]);
    fProfileGammaLambdaProtonOppo[i] -> Add(fProfileGamma_Lambda_AntiProton[i]);
    fProfileGammaLambdaProtonSame[i] -> Add(fProfileGamma_Lambda_Proton[i]);
    fProfileGammaLambdaProtonSame[i] -> Add(fProfileGamma_AntiLambda_AntiProton[i]);

    fProfileGammaLambdaHadronOppo[i] = (TProfile*)fProfileGammaLambdaHadronOppo[i]->Rebin(11,"",xbins);
    fProfileGammaLambdaHadronSame[i] = (TProfile*)fProfileGammaLambdaHadronSame[i]->Rebin(11,"",xbins);
    fProfileGammaLambdaProtonOppo[i] = (TProfile*)fProfileGammaLambdaProtonOppo[i]->Rebin(11,"",xbins);
    fProfileGammaLambdaProtonSame[i] = (TProfile*)fProfileGammaLambdaProtonSame[i]->Rebin(11,"",xbins);

    if (i==0) sprintf(chPlaneType,"TPC");
    if (i==1) sprintf(chPlaneType,"V0C");
    if (i==2) sprintf(chPlaneType,"V0A");
    if (i==3) sprintf(chPlaneType,"ZNC");
    if (i==4) sprintf(chPlaneType,"ZNA");
    hGammaLambdaHadronOppo[i] = (TH1D*) fProfileGammaLambdaHadronOppo[i]->ProjectionX(Form("hGammaLambdaHadronOppo_%s",chPlaneType));
    hGammaLambdaHadronSame[i] = (TH1D*) fProfileGammaLambdaHadronSame[i]->ProjectionX(Form("hGammaLambdaHadronSame_%s",chPlaneType));
    hGammaLambdaProtonOppo[i] = (TH1D*) fProfileGammaLambdaProtonOppo[i]->ProjectionX(Form("hGammaLambdaProtonOppo_%s",chPlaneType));
    hGammaLambdaProtonSame[i] = (TH1D*) fProfileGammaLambdaProtonSame[i]->ProjectionX(Form("hGammaLambdaProtonSame_%s",chPlaneType));
    hGammaLambdaHadronOppo[i] -> Divide(hRes[i]);
    hGammaLambdaHadronSame[i] -> Divide(hRes[i]);
    hGammaLambdaProtonOppo[i] -> Divide(hRes[i]);
    hGammaLambdaProtonSame[i] -> Divide(hRes[i]);
  }

  TH1D* hDeltaGammaLambdaHadron[5];
  TH1D* hDeltaGammaLambdaProton[5];
  for (int i = 0; i < 5; i++){
    if (i==0) sprintf(chPlaneType,"TPC");
    if (i==1) sprintf(chPlaneType,"V0C");
    if (i==2) sprintf(chPlaneType,"V0A");
    if (i==3) sprintf(chPlaneType,"ZNC");
    if (i==4) sprintf(chPlaneType,"ZNA");
    hDeltaGammaLambdaHadron[i] = new TH1D(Form("hDeltaGammaLambdaHadron_%s",chPlaneType),"",11,xbins);
    hDeltaGammaLambdaProton[i] = new TH1D(Form("hDeltaGammaLambdaProton_%s",chPlaneType),"",11,xbins);
    hDeltaGammaLambdaHadron[i] ->Add(hGammaLambdaHadronOppo[i],hGammaLambdaHadronSame[i],1,-1);
    hDeltaGammaLambdaProton[i] ->Add(hGammaLambdaProtonOppo[i],hGammaLambdaProtonSame[i],1,-1);
  }


  TCanvas* cDeltaCent = new TCanvas("cDeltaCent","delta vs. Centrality",10,10,1000,400);
  cDeltaCent->cd();
  cDeltaCent->Divide(2,1);

  cDeltaCent->cd(1);
  TH2D* dummyDeltaCent = new TH2D("","",1,0,70,1,-0.015,0.015);
  dummyDeltaCent->GetXaxis()->SetTitle("");
  dummyDeltaCent->GetXaxis()->SetTitle("Centrality (%)");
  dummyDeltaCent->GetYaxis()->SetTitle("#delta");
  dummyDeltaCent->GetYaxis()->SetTitleOffset(1.5);
  dummyDeltaCent->Draw("SAME");
  SetStyle(hDeltaLambdaHadronOppo ,ci2[0], kFullCircle,1.0,1.1);
  SetStyle(hDeltaLambdaHadronSame ,ci2[1], kFullCircle,1.0,1.1);
  hDeltaLambdaHadronOppo -> Draw("SAME");
  hDeltaLambdaHadronSame -> Draw("SAME");
  SetStyle(hDeltaLambdaProtonOppo ,ci2[0], kFullSquare,1.0,1.1);
  SetStyle(hDeltaLambdaProtonSame ,ci2[1], kFullSquare,1.0,1.1);
  hDeltaLambdaProtonOppo -> Draw("SAME");
  hDeltaLambdaProtonSame -> Draw("SAME");
  TLegend *legendDeltaCent = new TLegend(0.15,0.65,0.48,0.85);
  legendDeltaCent->AddEntry(hDeltaLambdaHadronOppo,"#Lambda-h OS","lp");
  legendDeltaCent->AddEntry(hDeltaLambdaHadronSame,"#Lambda-h SS","lp");
  legendDeltaCent->AddEntry(hDeltaLambdaProtonOppo,"#Lambda-p OS","lp");
  legendDeltaCent->AddEntry(hDeltaLambdaProtonSame,"#Lambda-p SS","lp");
  legendDeltaCent->SetBorderSize(0);
  legendDeltaCent->Draw("SAME");

  cDeltaCent->cd(2);
  TH2D* dummyDeltaDeltaCent = new TH2D("","",1,0,70,1,-0.003,0.03);
  dummyDeltaDeltaCent->GetXaxis()->SetTitle("");
  dummyDeltaDeltaCent->GetXaxis()->SetTitle("Centrality (%)");
  dummyDeltaDeltaCent->GetYaxis()->SetTitle("#Delta#delta");
  dummyDeltaDeltaCent->GetYaxis()->SetTitleOffset(1.5);
  dummyDeltaDeltaCent->Draw("SAME");
  SetStyle(hDeltaDeltaLambdaProton ,kBlack, kFullSquare,1.0,1.1);
  hDeltaDeltaLambdaProton->Draw("SAME");
  SetStyle(hDeltaDeltaLambdaHadron ,kGray, kFullCircle,1.0,1.1);
  hDeltaDeltaLambdaHadron->Draw("SAME");
  TLegend *legendDeltaDeltaCent = new TLegend(0.15,0.70,0.48,0.80);
  legendDeltaDeltaCent->AddEntry(hDeltaDeltaLambdaHadron,"#Lambda-h OS-SS","lp");
  legendDeltaDeltaCent->AddEntry(hDeltaDeltaLambdaProton,"#Lambda-h OS-SS","lp");
  legendDeltaDeltaCent->SetBorderSize(0);
  legendDeltaDeltaCent->Draw("SAME");
  

  TCanvas* cGammaCent = new TCanvas("cGammaCent","v_{2} vs. Centrality",10,10,1000,800);
  cGammaCent->Divide(2,2);
  cGammaCent->cd(1);
  TH2D* dummyGammaCent = new TH2D("","",1,0,70,1,-0.0008,0.0004);
  dummyGammaCent->GetXaxis()->SetTitle("");
  dummyGammaCent->GetXaxis()->SetTitle("Centrality (%)");
  dummyGammaCent->GetYaxis()->SetTitle("#gamma");
  dummyGammaCent->GetYaxis()->SetTitleOffset(1.2);
  dummyGammaCent->Draw("SAME");
  for (int i = 2; i < 3; i++){
    SetStyle(hGammaLambdaHadronOppo[i] ,ci[i], kFullCircle,1.0,1.1);
    SetStyle(hGammaLambdaHadronSame[i] ,ci[i], kOpenSquare,1.0,1.1);
    hGammaLambdaHadronOppo[i] -> Draw("SAME");
    hGammaLambdaHadronSame[i] -> Draw("SAME");
  }
  TLegend *legend1 = new TLegend(0.1,0.7,0.48,0.9);
  legend1->AddEntry(hGammaLambdaHadronOppo[0],"TPC","lp");
  legend1->AddEntry(hGammaLambdaHadronOppo[1],"V0C","lp");
  legend1->AddEntry(hGammaLambdaHadronOppo[2],"V0A","lp");
  legend1->AddEntry(hGammaLambdaHadronOppo[3],"ZNC","lp");
  legend1->AddEntry(hGammaLambdaHadronOppo[4],"ZNA","lp");
  legend1->Draw("SAME");
  cGammaCent->cd(2);
  TH2D* dummyDeltaGammaLambdaHadronCent = new TH2D("","",1,0,70,1,-0.0002,0.0004);
  dummyDeltaGammaLambdaHadronCent->GetXaxis()->SetTitle("");
  dummyDeltaGammaLambdaHadronCent->GetXaxis()->SetTitle("Centrality (%)");
  dummyDeltaGammaLambdaHadronCent->GetYaxis()->SetTitle("#Delta#gamma");
  dummyDeltaGammaLambdaHadronCent->GetYaxis()->SetTitleOffset(1.5);
  dummyDeltaGammaLambdaHadronCent->Draw("SAME");
  for (int i = 0; i < 5; i++){
    SetStyle(hDeltaGammaLambdaHadron[i] ,ci[i], kFullCircle,1.0,1.1);
    hDeltaGammaLambdaHadron[i] -> Draw("SAME");
  }
  cGammaCent->cd(3);
  TH2D* dummyGammaLambdaProtonCent = new TH2D("","",1,0,70,1,-0.004,0.002);
  dummyGammaLambdaProtonCent->GetXaxis()->SetTitle("");
  dummyGammaLambdaProtonCent->GetXaxis()->SetTitle("Centrality (%)");
  dummyGammaLambdaProtonCent->GetYaxis()->SetTitle("#gamma");
  dummyGammaLambdaProtonCent->GetYaxis()->SetTitleOffset(1.5);
  dummyGammaLambdaProtonCent->Draw("SAME");
  for (int i = 0; i < 5; i++){
    SetStyle(hGammaLambdaProtonOppo[i] ,ci[i], kFullCircle,1.0,1.1);
    SetStyle(hGammaLambdaProtonSame[i] ,ci[i], kOpenSquare,1.0,1.1);
    hGammaLambdaProtonOppo[i] -> Draw("SAME");
    hGammaLambdaProtonSame[i] -> Draw("SAME");
  }
  cGammaCent->cd(4);
  TH2D* dummyDeltaGammaLambdaProtonCent = new TH2D("","",1,0,80,1,-0.001,0.005);
  dummyDeltaGammaLambdaProtonCent->GetXaxis()->SetTitle("");
  dummyDeltaGammaLambdaProtonCent->GetXaxis()->SetTitle("Centrality (%)");
  dummyDeltaGammaLambdaProtonCent->GetYaxis()->SetTitle("#Delta#gamma");
  dummyDeltaGammaLambdaProtonCent->GetYaxis()->SetTitleOffset(1.5);
  dummyDeltaGammaLambdaProtonCent->Draw("SAME");
  for (int i = 0; i < 5; i++){
    SetStyle(hDeltaGammaLambdaProton[i] ,ci[i], kFullCircle,1.0,1.1);
    hDeltaGammaLambdaProton[i] -> Draw("SAME");
  }
}