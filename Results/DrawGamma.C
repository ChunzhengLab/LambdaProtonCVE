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

TString fPeriod = "LHC18r";
bool isZDCR2fromR1 = 0;
bool isZDCR2fromData = 1;
int  points = 11;
double xbins[12] = {0,5,10,20,30,40,50,60,70,80,90,100};
//double xbins[9] = {0,5,10,20,30,40,50,70,100};

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
  if(fPeriod.EqualTo("LHC10h")) {
    inputFile = TFile::Open("./LHC10h/AnalysisResults_10h_FB1_withNUA_PlanePt5.root", "READ");
    inputList = (TList*) inputFile->Get("output"); 
  }
  if(fPeriod.EqualTo("LHC18q")) { 
    inputFile = TFile::Open("./LHC18q/AnalysisResults_18q_PlanePt5_ProtonPt3.root", "READ");
    inputList = (TList*) inputFile->Get("output_"); 
  }
  if(fPeriod.EqualTo("LHC18r")) {
    inputFile = TFile::Open("./LHC18r/AnalysisResults_18r_PlanePt5_ProtonPt3.root", "READ");
    inputList = (TList*) inputFile->Get("output_"); 
  }

//==============================================Res==============================================
  TProfile*  fProfileTPCPsi2Correlation = (TProfile*)inputList -> FindObject("fProfileTPCPsi2Correlation");
  TProfile*  fProfileV0MPsi2Correlation = (TProfile*)inputList -> FindObject("fProfileV0MPsi2Correlation");
  TProfile*  fProfileZDCPsi1Correlation = (TProfile*)inputList -> FindObject("fProfileZDCPsi1Correlation");
  TProfile*  fProfileZDCPsi2Correlation = (TProfile*)inputList -> FindObject("fProfileZDCPsi2Correlation");
  TProfile*  fProfileV0CTPCPosPsi2Correlation = (TProfile*)inputList -> FindObject("fProfileV0CTPCPosPsi2Correlation");
  TProfile*  fProfileV0ATPCPosPsi2Correlation = (TProfile*)inputList -> FindObject("fProfileV0ATPCPosPsi2Correlation");
  TProfile*  fProfileV0CTPCNegPsi2Correlation = (TProfile*)inputList -> FindObject("fProfileV0CTPCNegPsi2Correlation");
  TProfile*  fProfileV0ATPCNegPsi2Correlation = (TProfile*)inputList -> FindObject("fProfileV0ATPCNegPsi2Correlation");

  //fProfileTPCPsi2Correlation       = (TProfile*)fProfileTPCPsi2Correlation       -> Rebin(points,"fProfileTPCPsi2Correlation",xbins);
  //fProfileV0MPsi2Correlation       = (TProfile*)fProfileV0MPsi2Correlation       -> Rebin(points,"fProfileV0MPsi2Correlation",xbins);
  //fProfileZDCPsi1Correlation       = (TProfile*)fProfileZDCPsi1Correlation       -> Rebin(points,"fProfileZDCPsi1Correlation",xbins);
  //fProfileZDCPsi2Correlation       = (TProfile*)fProfileZDCPsi2Correlation       -> Rebin(points,"fProfileZDCPsi2Correlation",xbins);
  //fProfileV0CTPCPosPsi2Correlation = (TProfile*)fProfileV0CTPCPosPsi2Correlation -> Rebin(points,"fProfileV0CTPCPosPsi2Correlation",xbins);
  //fProfileV0ATPCPosPsi2Correlation = (TProfile*)fProfileV0ATPCPosPsi2Correlation -> Rebin(points,"fProfileV0ATPCPosPsi2Correlation",xbins);
  //fProfileV0CTPCNegPsi2Correlation = (TProfile*)fProfileV0CTPCNegPsi2Correlation -> Rebin(points,"fProfileV0CTPCNegPsi2Correlation",xbins);
  //fProfileV0ATPCNegPsi2Correlation = (TProfile*)fProfileV0ATPCNegPsi2Correlation -> Rebin(points,"fProfileV0ATPCNegPsi2Correlation",xbins);

  fProfileTPCPsi2Correlation       = (TProfile*)fProfileTPCPsi2Correlation       -> Rebin(10);
  fProfileV0MPsi2Correlation       = (TProfile*)fProfileV0MPsi2Correlation       -> Rebin(10);
  fProfileZDCPsi1Correlation       = (TProfile*)fProfileZDCPsi1Correlation       -> Rebin(10);
  fProfileZDCPsi2Correlation       = (TProfile*)fProfileZDCPsi2Correlation       -> Rebin(10);
  fProfileV0CTPCPosPsi2Correlation = (TProfile*)fProfileV0CTPCPosPsi2Correlation -> Rebin(10);
  fProfileV0ATPCPosPsi2Correlation = (TProfile*)fProfileV0ATPCPosPsi2Correlation -> Rebin(10);
  fProfileV0CTPCNegPsi2Correlation = (TProfile*)fProfileV0CTPCNegPsi2Correlation -> Rebin(10);
  fProfileV0ATPCNegPsi2Correlation = (TProfile*)fProfileV0ATPCNegPsi2Correlation -> Rebin(10);

  TH1D* hTPCPsi2Correlation       = fProfileTPCPsi2Correlation -> ProjectionX("hProfileTPCPsi2Correlation");
  TH1D* hV0MPsi2Correlation       = fProfileV0MPsi2Correlation -> ProjectionX("hProfileV0MPsi2Correlation");
  TH1D* hZDCPsi1Correlation       = fProfileZDCPsi1Correlation -> ProjectionX("hProfileZDCPsi1Correlation");
  TH1D* hZDCPsi2Correlation       = fProfileZDCPsi2Correlation -> ProjectionX("hProfileZDCPsi2Correlation");
  TH1D* hV0CTPCPosPsi2Correlation = fProfileV0CTPCPosPsi2Correlation -> ProjectionX("hProfileV0CTPCPosPsi2Correlation");
  TH1D* hV0ATPCPosPsi2Correlation = fProfileV0ATPCPosPsi2Correlation -> ProjectionX("hProfileV0ATPCPosPsi2Correlation");
  TH1D* hV0CTPCNegPsi2Correlation = fProfileV0CTPCNegPsi2Correlation -> ProjectionX("hProfileV0CTPCNegPsi2Correlation");
  TH1D* hV0ATPCNegPsi2Correlation = fProfileV0ATPCNegPsi2Correlation -> ProjectionX("hProfileV0ATPCNegPsi2Correlation");

  //hTPCPsi2Correlation->Draw();

  TH1D* hRes[6];
  char chPlaneType[10];
  for (int i = 0; i < 5; i++) {
    if (i==0) sprintf(chPlaneType,"TPC");
    if (i==1) sprintf(chPlaneType,"V0C");
    if (i==2) sprintf(chPlaneType,"V0A");
    if (i==3) sprintf(chPlaneType,"ZNC");
    if (i==4) sprintf(chPlaneType,"ZNA");
    if (i==5) sprintf(chPlaneType,"ZDC");
    hRes[i] = new TH1D (Form("hRes_%s",chPlaneType),"",10,0,10);
  }

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
  } else {
    std::cout<<"Wrong ZDC R2 option"<<std::endl;
    return;
  }

//==============================================DeltaGamma==============================================

  ///Lambda-X correlators
  ///Delta Correlators:
  ///Lambda - X
  TProfile* fProfileDelta_Lambda_hPos = (TProfile*) inputList->FindObject("fProfileDelta_Lambda_hPos");
  TProfile* fProfileDelta_Lambda_hNeg = (TProfile*) inputList->FindObject("fProfileDelta_Lambda_hNeg");
  TProfile* fProfileDelta_Lambda_Proton = (TProfile*) inputList->FindObject("fProfileDelta_Lambda_Proton");
  TProfile* fProfileDelta_Lambda_AntiProton = (TProfile*) inputList->FindObject("fProfileDelta_Lambda_AntiProton");

  ///AntiLambda - X
  TProfile* fProfileDelta_AntiLambda_hPos = (TProfile*) inputList->FindObject("fProfileDelta_AntiLambda_hPos");
  TProfile* fProfileDelta_AntiLambda_hNeg = (TProfile*) inputList->FindObject("fProfileDelta_AntiLambda_hNeg");
  TProfile* fProfileDelta_AntiLambda_Proton = (TProfile*) inputList->FindObject("fProfileDelta_AntiLambda_Proton");
  TProfile* fProfileDelta_AntiLambda_AntiProton = (TProfile*) inputList->FindObject("fProfileDelta_AntiLambda_AntiProton");
  

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
  fProfileGamma_Lambda_hPos[0]       = (TProfile*) inputList->FindObject("fProfileGammaTPC_Lambda_hPos");
  fProfileGamma_Lambda_hNeg[0]       = (TProfile*) inputList->FindObject("fProfileGammaTPC_Lambda_hNeg");
  fProfileGamma_Lambda_Proton[0]     = (TProfile*) inputList->FindObject("fProfileGammaTPC_Lambda_Proton");
  fProfileGamma_Lambda_AntiProton[0] = (TProfile*) inputList->FindObject("fProfileGammaTPC_Lambda_AntiProton");

  ///AntiLambda - X
  fProfileGamma_AntiLambda_hPos[0]       = (TProfile*) inputList->FindObject("fProfileGammaTPC_AntiLambda_hPos");
  fProfileGamma_AntiLambda_hNeg[0]       = (TProfile*) inputList->FindObject("fProfileGammaTPC_AntiLambda_hNeg");
  fProfileGamma_AntiLambda_Proton[0]     = (TProfile*) inputList->FindObject("fProfileGammaTPC_AntiLambda_Proton");
  fProfileGamma_AntiLambda_AntiProton[0] = (TProfile*) inputList->FindObject("fProfileGammaTPC_AntiLambda_AntiProton");

  //V0C Plane
  ///Lambda - X
  fProfileGamma_Lambda_hPos[1] = (TProfile*) inputList->FindObject("fProfileGammaV0C_Lambda_hPos");
  fProfileGamma_Lambda_hNeg[1] = (TProfile*) inputList->FindObject("fProfileGammaV0C_Lambda_hNeg");
  fProfileGamma_Lambda_Proton[1] = (TProfile*) inputList->FindObject("fProfileGammaV0C_Lambda_Proton");
  fProfileGamma_Lambda_AntiProton[1] = (TProfile*) inputList->FindObject("fProfileGammaV0C_Lambda_AntiProton");

  ///AntiLambda - X
  fProfileGamma_AntiLambda_hPos[1] = (TProfile*) inputList->FindObject("fProfileGammaV0C_AntiLambda_hPos");
  fProfileGamma_AntiLambda_hNeg[1] = (TProfile*) inputList->FindObject("fProfileGammaV0C_AntiLambda_hNeg");
  fProfileGamma_AntiLambda_Proton[1] = (TProfile*) inputList->FindObject("fProfileGammaV0C_AntiLambda_Proton");
  fProfileGamma_AntiLambda_AntiProton[1] = (TProfile*) inputList->FindObject("fProfileGammaV0C_AntiLambda_AntiProton");

  //V0A Plane
  ///Lambda - X
  fProfileGamma_Lambda_hPos[2] = (TProfile*) inputList->FindObject("fProfileGammaV0A_Lambda_hPos");
  fProfileGamma_Lambda_hNeg[2] = (TProfile*) inputList->FindObject("fProfileGammaV0A_Lambda_hNeg");
  fProfileGamma_Lambda_Proton[2] = (TProfile*) inputList->FindObject("fProfileGammaV0A_Lambda_Proton");
  fProfileGamma_Lambda_AntiProton[2] = (TProfile*) inputList->FindObject("fProfileGammaV0A_Lambda_AntiProton");

  ///AntiLambda - X
  fProfileGamma_AntiLambda_hPos[2] = (TProfile*) inputList->FindObject("fProfileGammaV0A_AntiLambda_hPos");
  fProfileGamma_AntiLambda_hNeg[2] = (TProfile*) inputList->FindObject("fProfileGammaV0A_AntiLambda_hNeg");
  fProfileGamma_AntiLambda_Proton[2] = (TProfile*) inputList->FindObject("fProfileGammaV0A_AntiLambda_Proton");
  fProfileGamma_AntiLambda_AntiProton[2] = (TProfile*) inputList->FindObject("fProfileGammaV0A_AntiLambda_AntiProton");

  //ZNC Plane
  ///Lambda - X
  fProfileGamma_Lambda_hPos[3] = (TProfile*) inputList->FindObject("fProfileGammaZNC_Lambda_hPos");
  fProfileGamma_Lambda_hNeg[3] = (TProfile*) inputList->FindObject("fProfileGammaZNC_Lambda_hNeg");
  fProfileGamma_Lambda_Proton[3] = (TProfile*) inputList->FindObject("fProfileGammaZNC_Lambda_Proton");
  fProfileGamma_Lambda_AntiProton[3] = (TProfile*) inputList->FindObject("fProfileGammaZNC_Lambda_AntiProton");

  ///AntiLambda - X
  fProfileGamma_AntiLambda_hPos[3] = (TProfile*) inputList->FindObject("fProfileGammaZNC_AntiLambda_hPos");
  fProfileGamma_AntiLambda_hNeg[3] = (TProfile*) inputList->FindObject("fProfileGammaZNC_AntiLambda_hNeg");
  fProfileGamma_AntiLambda_Proton[3] = (TProfile*) inputList->FindObject("fProfileGammaZNC_AntiLambda_Proton");
  fProfileGamma_AntiLambda_AntiProton[3] = (TProfile*) inputList->FindObject("fProfileGammaZNC_AntiLambda_AntiProton");

  //ZNA Plane
  ///Lambda - X
  fProfileGamma_Lambda_hPos[4] = (TProfile*) inputList->FindObject("fProfileGammaZNA_Lambda_hPos");
  fProfileGamma_Lambda_hNeg[4] = (TProfile*) inputList->FindObject("fProfileGammaZNA_Lambda_hNeg");
  fProfileGamma_Lambda_Proton[4] = (TProfile*) inputList->FindObject("fProfileGammaZNA_Lambda_Proton");
  fProfileGamma_Lambda_AntiProton[4] = (TProfile*) inputList->FindObject("fProfileGammaZNA_Lambda_AntiProton");

  ///AntiLambda - X
  fProfileGamma_AntiLambda_hPos[4] = (TProfile*) inputList->FindObject("fProfileGammaZNA_AntiLambda_hPos");
  fProfileGamma_AntiLambda_hNeg[4] = (TProfile*) inputList->FindObject("fProfileGammaZNA_AntiLambda_hNeg");
  fProfileGamma_AntiLambda_Proton[4] = (TProfile*) inputList->FindObject("fProfileGammaZNA_AntiLambda_Proton");
  fProfileGamma_AntiLambda_AntiProton[4] = (TProfile*) inputList->FindObject("fProfileGammaZNA_AntiLambda_AntiProton");


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

  //fProfileDeltaLambdaHadronOppo->Add(fProfileDelta_AntiLambda_hPos);
  fProfileDeltaLambdaHadronOppo->Add(fProfileDelta_Lambda_hNeg);
  fProfileDeltaLambdaHadronSame->Add(fProfileDelta_Lambda_hPos);
  fProfileDeltaLambdaHadronSame->Add(fProfileDelta_AntiLambda_hNeg);

  //fProfileDeltaLambdaProtonOppo->Add(fProfileDelta_AntiLambda_Proton);
  fProfileDeltaLambdaProtonOppo->Add(fProfileDelta_Lambda_AntiProton);
  fProfileDeltaLambdaProtonSame->Add(fProfileDelta_Lambda_Proton);
  fProfileDeltaLambdaProtonSame->Add(fProfileDelta_AntiLambda_AntiProton);

  
  fProfileDeltaLambdaHadronOppo = (TProfile*)fProfileDeltaLambdaHadronOppo -> Rebin(points,"",xbins);
  fProfileDeltaLambdaHadronSame = (TProfile*)fProfileDeltaLambdaHadronSame -> Rebin(points,"",xbins);
  fProfileDeltaLambdaProtonOppo = (TProfile*)fProfileDeltaLambdaProtonOppo -> Rebin(points,"",xbins);
  fProfileDeltaLambdaProtonSame = (TProfile*)fProfileDeltaLambdaProtonSame -> Rebin(points,"",xbins);

  TH1D* hDeltaLambdaHadronOppo = (TH1D*)fProfileDeltaLambdaHadronOppo -> ProjectionX("hDeltaLambdaHadronOppo");
  TH1D* hDeltaLambdaHadronSame = (TH1D*)fProfileDeltaLambdaHadronSame -> ProjectionX("hDeltaLambdaHadronSame");
  TH1D* hDeltaLambdaProtonOppo = (TH1D*)fProfileDeltaLambdaProtonOppo -> ProjectionX("hDeltaLambdaProtonOppo");
  TH1D* hDeltaLambdaProtonSame = (TH1D*)fProfileDeltaLambdaProtonSame -> ProjectionX("hDeltaLambdaProtonSame");

  TH1D* hDeltaDeltaLambdaHadron = new TH1D("hDeltaDeltaHadron","",points,xbins);
  TH1D* hDeltaDeltaLambdaProton = new TH1D("hDeltaDeltaProton","",points,xbins);
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

    //fProfileGammaLambdaHadronOppo[i] = (TProfile*)fProfileGammaLambdaHadronOppo[i]->Rebin(points,"",xbins);
    //fProfileGammaLambdaHadronSame[i] = (TProfile*)fProfileGammaLambdaHadronSame[i]->Rebin(points,"",xbins);
    //fProfileGammaLambdaProtonOppo[i] = (TProfile*)fProfileGammaLambdaProtonOppo[i]->Rebin(points,"",xbins);
    //fProfileGammaLambdaProtonSame[i] = (TProfile*)fProfileGammaLambdaProtonSame[i]->Rebin(points,"",xbins);

    fProfileGammaLambdaHadronOppo[i] = (TProfile*)fProfileGammaLambdaHadronOppo[i]->Rebin(2);
    fProfileGammaLambdaHadronSame[i] = (TProfile*)fProfileGammaLambdaHadronSame[i]->Rebin(2);
    fProfileGammaLambdaProtonOppo[i] = (TProfile*)fProfileGammaLambdaProtonOppo[i]->Rebin(2);
    fProfileGammaLambdaProtonSame[i] = (TProfile*)fProfileGammaLambdaProtonSame[i]->Rebin(2);

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
    //hDeltaGammaLambdaHadron[i] = new TH1D(Form("hDeltaGammaLambdaHadron_%s",chPlaneType),"",points,xbins);
    //hDeltaGammaLambdaProton[i] = new TH1D(Form("hDeltaGammaLambdaProton_%s",chPlaneType),"",points,xbins);
    hDeltaGammaLambdaHadron[i] = new TH1D(Form("hDeltaGammaLambdaHadron_%s",chPlaneType),"",10,0,100);
    hDeltaGammaLambdaProton[i] = new TH1D(Form("hDeltaGammaLambdaProton_%s",chPlaneType),"",10,0,100);
    hDeltaGammaLambdaHadron[i] ->Add(hGammaLambdaHadronOppo[i],hGammaLambdaHadronSame[i],1,-1);
    hDeltaGammaLambdaProton[i] ->Add(hGammaLambdaProtonOppo[i],hGammaLambdaProtonSame[i],1,-1);
  }

  TLegend *legend1 = new TLegend(0.1,0.7,0.48,0.9);
  legend1->AddEntry(fProfileGammaLambdaHadronOppo[0],"TPC","lp");
  legend1->AddEntry(fProfileGammaLambdaHadronOppo[1],"V0C","lp");
  legend1->AddEntry(fProfileGammaLambdaHadronOppo[2],"V0A","lp");
  legend1->AddEntry(fProfileGammaLambdaHadronOppo[3],"ZNC","lp");
  legend1->AddEntry(fProfileGammaLambdaHadronOppo[4],"ZNA","lp");


  TLegend *legendDeltaCent = new TLegend(0.15,0.68,0.5,0.85);
  legendDeltaCent->SetBorderSize(0);
  legendDeltaCent->AddEntry(hDeltaLambdaHadronOppo,"#Lambda(#bar{#Lambda}) - h^{+}(h^{-})","lp");
  legendDeltaCent->AddEntry(hDeltaLambdaHadronSame,"#Lambda(#bar{#Lambda}) - h^{-}(h^{+})","lp");
  legendDeltaCent->AddEntry(hDeltaLambdaProtonOppo,"#Lambda(#bar{#Lambda}) - p^{+}(p^{-})","lp");
  legendDeltaCent->AddEntry(hDeltaLambdaProtonSame,"#Lambda(#bar{#Lambda}) - p^{-}(p^{+})","lp");
  TLegend *legendDeltaDeltaCent = new TLegend(0.15,0.7,0.48,0.85);
  legendDeltaDeltaCent->SetBorderSize(0);
  legendDeltaDeltaCent->AddEntry(hDeltaDeltaLambdaHadron,"#Lambda - h","lp");
  legendDeltaDeltaCent->AddEntry(hDeltaDeltaLambdaProton,"#Lambda - p","lp");
  TCanvas* cDeltaCent = new TCanvas("cDeltaCent","v_{2} vs. Centrality",10,10,1100,400);
  cDeltaCent->cd();
  cDeltaCent->Divide(2,1);
  cDeltaCent->cd(1);
  TH2D* dummyDeltaCent = new TH2D("","",1,0,70,1,-0.015,0.015);
  dummyDeltaCent->GetXaxis()->SetTitle("");
  dummyDeltaCent->GetXaxis()->SetTitle("Centrality (%)");
  dummyDeltaCent->GetYaxis()->SetTitle("#delta = #LT cos(#phi_{#Lambda} - #phi_{p}) #GT");
  dummyDeltaCent->GetYaxis()->SetTitleOffset(1.5);
  dummyDeltaCent->Draw("SAME");
  SetStyle(hDeltaLambdaHadronOppo ,kBlue, kFullCircle,1,1);
  SetStyle(hDeltaLambdaHadronSame ,kRed, kOpenCircle,1,1);
  hDeltaLambdaHadronOppo -> Draw("SAME");
  hDeltaLambdaHadronSame -> Draw("SAME");
  SetStyle(hDeltaLambdaProtonOppo ,kBlue, kFullSquare,1,1);
  SetStyle(hDeltaLambdaProtonSame ,kRed, kOpenSquare,1,1);
  hDeltaLambdaProtonOppo -> Draw("SAME");
  hDeltaLambdaProtonSame -> Draw("SAME");
  legendDeltaCent->Draw("SAME");
  cDeltaCent->cd(2);
  TH2D* dummyDeltaDeltaCent = new TH2D("","",1,0,70,1,-0.01,0.015);
  dummyDeltaDeltaCent->GetXaxis()->SetTitle("Centrality (%)");
  dummyDeltaDeltaCent->GetYaxis()->SetTitle("OS-SS");
  dummyDeltaDeltaCent->GetYaxis()->SetTitleOffset(1.5);
  dummyDeltaDeltaCent->Draw("same");
  SetStyle(hDeltaDeltaLambdaHadron ,kGray, kFullCircle,1,1);
  SetStyle(hDeltaDeltaLambdaProton ,kBlack, kFullSquare,1,1);
  hDeltaDeltaLambdaHadron->Draw("SAME");
  hDeltaDeltaLambdaProton->Draw("SAME");
  legendDeltaDeltaCent->Draw("SAME");
  // if(fPeriod.EqualTo("LHC10h")) cDeltaCent->SaveAs("DeltaCent10h.pdf");
  // if(fPeriod.EqualTo("LHC18q")) cDeltaCent->SaveAs("DeltaCent18q.pdf");
  // if(fPeriod.EqualTo("LHC18r")) cDeltaCent->SaveAs("DeltaCent18r.pdf");
  

  // TCanvas* cGammaCent = new TCanvas("cGammaCent","v_{2} vs. Centrality",10,10,1000,800);
  // cGammaCent->Divide(2,2);
  // cGammaCent->cd(1);
  // TH2D* dummyGammaLambdaHardonCent = new TH2D("","",1,0,70,1,-0.001,0.001);
  // dummyGammaLambdaHardonCent->GetXaxis()->SetTitle("");
  // dummyGammaLambdaHardonCent->GetXaxis()->SetTitle("Centrality (%)");
  // dummyGammaLambdaHardonCent->GetYaxis()->SetTitle("#gamma = #LT cos(#phi_{#Lambda} + #phi_{h} - 2#Psi_{2}) #GT");
  // dummyGammaLambdaHardonCent->GetYaxis()->SetTitleOffset(1.2);
  // dummyGammaLambdaHardonCent->Draw("SAME");
  // for (int i = 0; i < 5; i++){
  //   SetStyle(hGammaLambdaHadronOppo[i] ,ci[i], kFullCircle,1.2,1.1);
  //   SetStyle(hGammaLambdaHadronSame[i] ,ci[i], kOpenSquare,1.2,1.1);
  //   hGammaLambdaHadronOppo[i] -> Draw("SAME");
  //   hGammaLambdaHadronSame[i] -> Draw("SAME");
  // }

  // cGammaCent->cd(2);
  // TH2D* dummyDeltaGammaLambdaHadronCent = new TH2D("","",1,0,70,1,-0.001,0.002);
  // dummyDeltaGammaLambdaHadronCent->GetXaxis()->SetTitle("");
  // dummyDeltaGammaLambdaHadronCent->GetXaxis()->SetTitle("Centrality (%)");
  // dummyDeltaGammaLambdaHadronCent->GetYaxis()->SetTitle("OS-SS");
  // dummyDeltaGammaLambdaHadronCent->GetYaxis()->SetTitleOffset(1.2);
  // dummyDeltaGammaLambdaHadronCent->Draw("SAME");
  // for (int i = 0; i < 5; i++){
  //   SetStyle(hDeltaGammaLambdaHadron[i] ,ci[i], kFullCircle,1.2,1.1);
  //   hDeltaGammaLambdaHadron[i] -> Draw("SAME");
  // }
  // dummyDeltaGammaLambdaHadronCent->Draw("SAME");

  // cGammaCent->cd(3);
  // TH2D* dummyGammaLambdaProtonCent = new TH2D("","",1,0,70,1,-0.005,0.001);
  // dummyGammaLambdaProtonCent->GetXaxis()->SetTitle("");
  // dummyGammaLambdaProtonCent->GetXaxis()->SetTitle("Centrality (%)");
  // dummyGammaLambdaProtonCent->GetYaxis()->SetTitle("#gamma = #LT cos(#phi_{#Lambda} + #phi_{p} - 2#Psi_{2}) #GT");
  // dummyGammaLambdaProtonCent->GetYaxis()->SetTitleOffset(1.2);
  // dummyGammaLambdaProtonCent->Draw("SAME");
  // for (int i = 0; i < 5; i++){
  //   SetStyle(hGammaLambdaProtonOppo[i] ,ci[i], kFullCircle,1.2,1.1);
  //   SetStyle(hGammaLambdaProtonSame[i] ,ci[i], kOpenSquare,1.2,1.1);
  //   hGammaLambdaProtonOppo[i] -> Draw("SAME");
  //   hGammaLambdaProtonSame[i] -> Draw("SAME");
  // }

  // cGammaCent->cd(4);
  // TH2D* dummyDeltaGammaLambdaProtonCent = new TH2D("","",1,0,70,1,-0.001,0.002);
  // dummyDeltaGammaLambdaProtonCent->GetXaxis()->SetTitle("");
  // dummyDeltaGammaLambdaProtonCent->GetXaxis()->SetTitle("Centrality (%)");
  // dummyDeltaGammaLambdaProtonCent->GetYaxis()->SetTitle("OS-SS");
  // dummyDeltaGammaLambdaProtonCent->GetYaxis()->SetTitleOffset(1.2);
  // dummyDeltaGammaLambdaProtonCent->Draw("SAME");
  // for (int i = 0; i < 5; i++){
  //   SetStyle(hDeltaGammaLambdaProton[i] ,ci[i], kFullSquare,1.2,1.1);
  //   hDeltaGammaLambdaProton[i] -> Draw("SAME");
  // }
  TH2D* dummyGammaLambdaHardonCent = new TH2D("","",1,0,70,1,-0.008,0.001);
  TH2D* dummyDeltaGammaLambdaHadronCent = new TH2D("","",1,0,70,1,-0.001,0.004);
  TCanvas* cGamma[5];
  TLegend *legendGamma[5];
  TLegend *legendDeltaGamma[5];

  for (int i = 0; i < 5; i++) {
    if (i==0) sprintf(chPlaneType,"TPC");
    if (i==1) sprintf(chPlaneType,"V0C");
    if (i==2) sprintf(chPlaneType,"V0A");
    if (i==3) sprintf(chPlaneType,"ZNC");
    if (i==4) sprintf(chPlaneType,"ZNA");
    if (i==5) sprintf(chPlaneType,"ZDC");
    
    legendGamma[i] = new TLegend(0.15,0.2,0.48,0.5);
    legendGamma[i] -> SetBorderSize(0);
    legendGamma[i]->AddEntry(hGammaLambdaHadronOppo[i], Form("#Lambda(#bar{#Lambda}) - h^{+}(h^{-}) %s Plane",chPlaneType),"lp");
    legendGamma[i]->AddEntry(hGammaLambdaHadronSame[i], Form("#Lambda(#bar{#Lambda}) - h^{-}(h^{+}) %s Plane",chPlaneType),"lp");
    legendGamma[i]->AddEntry(hGammaLambdaProtonOppo[i], Form("#Lambda(#bar{#Lambda}) - p^{+}(p^{-}) %s Plane",chPlaneType),"lp");
    legendGamma[i]->AddEntry(hGammaLambdaProtonSame[i], Form("#Lambda(#bar{#Lambda}) - p^{-}(p^{+}) %s Plane",chPlaneType),"lp");

    legendDeltaGamma[i] = new TLegend(0.15,0.6,0.48,0.8);
    legendDeltaGamma[i] -> SetBorderSize(0);
    legendDeltaGamma[i]->AddEntry(hDeltaGammaLambdaHadron[i], Form("#Lambda - h %s Plane",chPlaneType),"lp");
    legendDeltaGamma[i]->AddEntry(hDeltaGammaLambdaProton[i], Form("#Lambda - p %s Plane",chPlaneType),"lp");

    cGamma[i] = new TCanvas("","gamma vs. Centrality",10,10,500,1000);
    cGamma[i]->Divide(1,2);
    cGamma[i]->cd(1);
    dummyGammaLambdaHardonCent->GetXaxis()->SetTitle(chPlaneType);
    dummyGammaLambdaHardonCent->GetXaxis()->SetTitle("Centrality (%)");
    dummyGammaLambdaHardonCent->GetYaxis()->SetTitle("#gamma = #LT cos(#phi_{#Lambda} + #phi_{h} - 2#Psi_{RP}) #GT");
    dummyGammaLambdaHardonCent->GetYaxis()->SetTitleOffset(1.5);
    dummyGammaLambdaHardonCent->Draw("SAME");
    SetStyle(hGammaLambdaHadronOppo[i] ,kBlue, kFullCircle,1,1);
    SetStyle(hGammaLambdaHadronSame[i] ,kRed,  kOpenCircle,1,1);
    SetStyle(hGammaLambdaProtonOppo[i] ,kBlue, kFullSquare,1,1);
    SetStyle(hGammaLambdaProtonSame[i] ,kRed,  kOpenSquare,1,1);
  
    hGammaLambdaHadronOppo[i] -> Draw("SAME");
    hGammaLambdaHadronSame[i] -> Draw("SAME");
    hGammaLambdaProtonOppo[i] -> Draw("SAME");
    hGammaLambdaProtonSame[i] -> Draw("SAME");
    legendGamma[i]->Draw("SAME");
  

    cGamma[i]->cd(2);
    dummyDeltaGammaLambdaHadronCent->GetXaxis()->SetTitle(chPlaneType);
    dummyDeltaGammaLambdaHadronCent->GetXaxis()->SetTitle("Centrality (%)");
    dummyDeltaGammaLambdaHadronCent->GetYaxis()->SetTitle("OS-SS");
    dummyDeltaGammaLambdaHadronCent->GetYaxis()->SetTitleOffset(1.5);
    dummyDeltaGammaLambdaHadronCent->Draw("SAME");
  
    SetStyle(hDeltaGammaLambdaHadron[i] ,kGray, kFullCircle,1,1);
    SetStyle(hDeltaGammaLambdaProton[i] ,kBlack, kFullCircle,1,1);
    hDeltaGammaLambdaHadron[i] -> Draw("SAME");
    hDeltaGammaLambdaProton[i] -> Draw("SAME");
    legendDeltaGamma[i]->Draw("SAME");

    // if(fPeriod.EqualTo("LHC10h")) cGamma[i]->SaveAs(Form("Gamma%sCent10h.pdf",chPlaneType));
    // if(fPeriod.EqualTo("LHC18q")) cGamma[i]->SaveAs(Form("Gamma%sCent18q.pdf",chPlaneType));
    // if(fPeriod.EqualTo("LHC18r")) cGamma[i]->SaveAs(Form("Gamma%sCent18r.pdf",chPlaneType));
  }
  TLegend *legendRes = new TLegend(0.15,0.4,0.35,0.88);
  legendRes->SetBorderSize(0);
  legendRes->AddEntry(hDeltaGammaLambdaHadron[0],"#Lambda - h #gamma_{TPC} OS-SS","lp");
  legendRes->AddEntry(hDeltaGammaLambdaHadron[1],"#Lambda - h #gamma_{V0C} OS-SS","lp");
  legendRes->AddEntry(hDeltaGammaLambdaHadron[2],"#Lambda - h #gamma_{V0A} OS-SS","lp");

  legendRes->AddEntry(hDeltaGammaLambdaProton[0],"#Lambda - p #gamma_{TPC} OS-SS","lp");
  legendRes->AddEntry(hDeltaGammaLambdaProton[1],"#Lambda - p #gamma_{V0C} OS-SS","lp");
  legendRes->AddEntry(hDeltaGammaLambdaProton[2],"#Lambda - p #gamma_{V0A} OS-SS","lp");


  TCanvas* cDeltaGamma = new TCanvas("","DeltaGamma vs. Centrality",10,10,600,400);
  cDeltaGamma->cd();
  dummyDeltaGammaLambdaHadronCent->Draw("SAME");
  for (int i = 0; i < 3; i++) {
    SetStyle(hDeltaGammaLambdaHadron[i] ,ci[i], kOpenCircle,1.2,1);
    SetStyle(hDeltaGammaLambdaProton[i] ,ci[i], kFullSquare,1.2,1);
    hDeltaGammaLambdaHadron[i] -> Draw("SAME");
    hDeltaGammaLambdaProton[i] -> Draw("SAME");
  }
  legendRes->Draw("SAME");
  if(fPeriod.EqualTo("LHC10h")) cDeltaGamma->SaveAs(Form("DeltaGammaTPCV0Cent10h.pdf"));
  if(fPeriod.EqualTo("LHC18q")) cDeltaGamma->SaveAs(Form("DeltaGammaTPCV0Cent18q.pdf"));
  if(fPeriod.EqualTo("LHC18r")) cDeltaGamma->SaveAs(Form("DeltaGammaTPCV0Cent18r.pdf"));

  TH2D* dummyDeltaGammaLambdaHadronCentZDC = new TH2D("","ZNA/C Plane",1,0,70,1,-0.005,0.01);
  TLegend *legendResZDC = new TLegend(0.15,0.7,0.35,0.88);
  legendResZDC->SetBorderSize(0);
  legendResZDC->AddEntry(hRes[3],"ZNC #gamma OS-SS","lp");
  legendResZDC->AddEntry(hRes[4],"ZNA #gamma OS-SS","lp");
  TCanvas* cDeltaGammaZDC = new TCanvas("","DeltaGamma vs. Centrality",10,10,600,400);
  cDeltaGammaZDC->cd();
  dummyDeltaGammaLambdaHadronCentZDC->Draw();
  for (int i = 3; i < 5; i++) {
    SetStyle(hDeltaGammaLambdaHadron[i] ,ci[i], kOpenCircle,1,1);
    SetStyle(hDeltaGammaLambdaProton[i] ,ci[i], kFullSquare,1,1);
    hDeltaGammaLambdaHadron[i] -> Draw("SAME");
    hDeltaGammaLambdaProton[i] -> Draw("SAME");
  }
  legendResZDC->Draw("SAME");
  // if(fPeriod.EqualTo("LHC10h")) cDeltaGamma->SaveAs(Form("DeltaGammaZDCCent10h.pdf"));
  // if(fPeriod.EqualTo("LHC18q")) cDeltaGamma->SaveAs(Form("DeltaGammaZDCCent18q.pdf"));
  // if(fPeriod.EqualTo("LHC18r")) cDeltaGamma->SaveAs(Form("DeltaGammaZDCCent18r.pdf"));
}