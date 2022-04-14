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
  int ci[5];
  TColor* color[5];
  ci[0] = TColor::GetFreeColorIndex();
  color[0] = new TColor(ci[0],  24/255.,  63/255.,  94/255.);//深蓝
  ci[1] = TColor::GetFreeColorIndex();
  color[1] = new TColor(ci[1],  33/255.,  99/255., 154/255.);//浅蓝
  ci[2] = TColor::GetFreeColorIndex();
  color[2] = new TColor(ci[2], 246/255., 213/255., 101/255.);//黄
  ci[3] = TColor::GetFreeColorIndex();
  color[3] = new TColor(ci[3],  62/255., 174/255., 164/255.);//绿
  ci[4] = TColor::GetFreeColorIndex();
  color[4] = new TColor(ci[4], 236/255.,  85/255.,  60/255.);//红

  gStyle->SetOptStat(0);
  TFile* outputFile[3];
  TList* outputList[3];
  for (int i = 0; i < 3; i++) {
    outputFile[i] = TFile::Open("AnalysisResults.root", "READ");
    outputList[i] = (TList*) outputFile[i]->Get("output_"); 
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

  char chPlaneType[5];
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

  double xbins[12] = {0,5,10,20,30,40,50,60,70,80,90,100};
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
  }

  TH1D* hDeltaGammaLambdaHadron[5];
  TH1D* hDeltaGammaLambdaProton[5];
  for (int i = 0; i < 5; i++){
    hDeltaGammaLambdaHadron[i] = new TH1D(Form("hDeltaGammaLambdaHadron_%s",chPlaneType),"",11,xbins);
    hDeltaGammaLambdaProton[i] = new TH1D(Form("hDeltaGammaLambdaProton_%s",chPlaneType),"",11,xbins);
    hDeltaGammaLambdaHadron[i] ->Add(hGammaLambdaHadronOppo[i],hGammaLambdaHadronSame[i],1,-1);
    hDeltaGammaLambdaProton[i] ->Add(hGammaLambdaProtonOppo[i],hGammaLambdaProtonSame[i],1,-1);
  }

  TLegend *legend1 = new TLegend(0.1,0.7,0.48,0.9);
  legend1->AddEntry(fProfileGammaLambdaHadronOppo[0],"TPC","lp");
  legend1->AddEntry(fProfileGammaLambdaHadronOppo[1],"V0C","lp");
  legend1->AddEntry(fProfileGammaLambdaHadronOppo[2],"V0A","lp");
  legend1->AddEntry(fProfileGammaLambdaHadronOppo[3],"ZNC","lp");
  legend1->AddEntry(fProfileGammaLambdaHadronOppo[4],"ZNA","lp");

  TCanvas* cDeltaCent = new TCanvas("cDeltaCent","v_{2} vs. Centrality",10,10,1000,400);
  cDeltaCent->cd();
  cDeltaCent->Divide(2,1);
  cDeltaCent->cd(1);
  TH2D* dummyDeltaCent = new TH2D("","",1,0,70,1,-0.015,0.015);
  dummyDeltaCent->GetXaxis()->SetTitle("");
  dummyDeltaCent->GetXaxis()->SetTitle("Centrality (%)");
  dummyDeltaCent->GetYaxis()->SetTitle("v_{2}");
  dummyDeltaCent->GetYaxis()->SetTitleOffset(1.2);
  dummyDeltaCent->Draw("SAME");
  SetStyle(hDeltaLambdaHadronOppo ,kBlue, kFullCircle,1.2,1.1);
  SetStyle(hDeltaLambdaHadronSame ,kBlue, kOpenSquare,1.2,1.1);
  hDeltaLambdaHadronOppo -> Draw("SAME");
  hDeltaLambdaHadronSame -> Draw("SAME");
  SetStyle(hDeltaLambdaProtonOppo ,kRed, kFullCircle,1.2,1.1);
  SetStyle(hDeltaLambdaProtonSame ,kRed, kOpenSquare,1.2,1.1);
  hDeltaLambdaProtonOppo -> Draw("SAME");
  hDeltaLambdaProtonSame -> Draw("SAME");
  cDeltaCent->cd(2);
  TH2D* dummyDeltaDeltaCent = new TH2D("","",1,0,70,1,-0.002,0.015);
  dummyDeltaDeltaCent->Draw("same");
  hDeltaDeltaLambdaProton->Draw("SAME");
  hDeltaDeltaLambdaHadron->Draw("SAME");
  

  TCanvas* cGammaCent = new TCanvas("cGammaCent","v_{2} vs. Centrality",10,10,1000,800);
  cGammaCent->Divide(2,2);
  cGammaCent->cd(1);
  TH2D* dummyGammaCent = new TH2D("","",1,0,70,1,-0.001,0.001);
  dummyGammaCent->GetXaxis()->SetTitle("");
  dummyGammaCent->GetXaxis()->SetTitle("Centrality (%)");
  dummyGammaCent->GetYaxis()->SetTitle("v_{2}");
  dummyGammaCent->GetYaxis()->SetTitleOffset(1.2);
  dummyGammaCent->Draw("SAME");
  for (int i = 0; i < 3; i++){
    SetStyle(hGammaLambdaHadronOppo[i] ,ci[i], kFullCircle,1.2,1.1);
    SetStyle(hGammaLambdaHadronSame[i] ,ci[i], kOpenSquare,1.2,1.1);
    hGammaLambdaHadronOppo[i] -> Draw("SAME");
    hGammaLambdaHadronSame[i] -> Draw("SAME");
  }
  cGammaCent->cd(2);
  for (int i = 0; i < 3; i++){
    SetStyle(hGammaLambdaProtonOppo[i] ,ci[i], kFullCircle,1.2,1.1);
    SetStyle(hGammaLambdaProtonSame[i] ,ci[i], kOpenSquare,1.2,1.1);
    hGammaLambdaProtonOppo[i] -> Draw("SAME");
    hGammaLambdaProtonSame[i] -> Draw("SAME");
  }
  cGammaCent->cd(3);
  for (int i = 0; i < 3; i++){
    SetStyle(hDeltaGammaLambdaHadron[i] ,ci[i], kFullCircle,1.2,1.1);
    hDeltaGammaLambdaHadron[i] -> Draw("SAME");
  }
  cGammaCent->cd(4);
  for (int i = 0; i < 3; i++){
    SetStyle(hDeltaGammaLambdaProton[i] ,ci[i], kOpenSquare,1.2,1.1);
    hDeltaGammaLambdaProton[i] -> Draw("SAME");
  }
}