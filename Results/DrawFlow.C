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
  int ci[4];
  TColor* color[4];
  ci[0] = TColor::GetFreeColorIndex();
  color[0] = new TColor(ci[0],   0/255.,  24/255., 113/255.);//dark blue
  ci[1] = TColor::GetFreeColorIndex();
  color[1] = new TColor(ci[1], 255/255.,  88/255.,  93/255.);//red
  ci[2] = TColor::GetFreeColorIndex();
  color[2] = new TColor(ci[2], 255/255., 181/255.,  73/255.);//yellow
  ci[3] = TColor::GetFreeColorIndex();
  color[3] = new TColor(ci[3], 65/255.,  182/255., 230/255.);//light blue
  gStyle->SetOptStat(0);

  TFile* outputFile = TFile::Open("AnalysisResults.root", "READ");
  // TDirectoryFile* MyTask = (TDirectoryFile*) inputFile->GetDirectory("MyTask");
  // MyTask->cd();
  TList* outputList = nullptr;
  outputList = (TList*) outputFile->Get("output"); 
  //MyTask->GetObject("MyOutputContainer",outputList);

  cout<<"Loaded in"<<endl;

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

  TH1D* hRes[5];
  for (int i = 0; i < 5; i++) {
    if (i==0) sprintf(chPlaneType,"TPC");
    if (i==1) sprintf(chPlaneType,"V0C");
    if (i==2) sprintf(chPlaneType,"V0A");
    if (i==3) sprintf(chPlaneType,"ZNC");
    if (i==4) sprintf(chPlaneType,"ZNA");
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

  cout<<"Get the resonlution"<<endl;

  hRes[0] -> Multiply(hV0CTPCNegPsi2Correlation, hV0ATPCNegPsi2Correlation,1,1);
  hRes[0] -> Divide(hV0MPsi2Correlation);
  hRes[1] -> Multiply(hV0CTPCNegPsi2Correlation, hV0MPsi2Correlation,1,1);
  hRes[1] -> Divide(hV0ATPCNegPsi2Correlation);
  hRes[2] -> Multiply(hV0ATPCNegPsi2Correlation, hV0MPsi2Correlation,1,1);
  hRes[2] -> Divide(hV0CTPCNegPsi2Correlation);

  for (int i = 0; i < 2; i++) {
    for (int iBin = 1; iBin < 8; iBin++) {
      double resSquare = hRes[i] -> GetBinContent(iBin);
      hRes[i] -> SetBinContent(iBin, TMath::Sqrt(resSquare));
    }
  }

  TProfile*  fProfileRawFlowCenthPos[5];
  TProfile*  fProfileRawFlowCenthNeg[5];
  TProfile*  fProfileRawFlowCentProton[5];
  TProfile*  fProfileRawFlowCentAntiProton[5];
  TProfile*  fProfileRawFlowCentLambda[5];
  TProfile*  fProfileRawFlowCentAntiLambda[5];

  for (int i = 0; i < 3; i++){
    if (i==0) sprintf(chPlaneType,"TPC");
    if (i==1) sprintf(chPlaneType,"V0C");
    if (i==2) sprintf(chPlaneType,"V0A");
    if (i==3) sprintf(chPlaneType,"ZNC");
    if (i==4) sprintf(chPlaneType,"ZNA");
    fProfileRawFlowCenthPos[i]       = fProfile2DRawFlowCentPthPos[i]       -> ProfileX(Form("fProfileFlowCenthPos_%s",chPlaneType),11,25);
    fProfileRawFlowCenthNeg[i]       = fProfile2DRawFlowCentPthNeg[i]       -> ProfileX(Form("fProfileFlowCenthNeg_%s",chPlaneType),11,25);
    fProfileRawFlowCentProton[i]     = fProfile2DRawFlowCentPtProton[i]     -> ProfileX(Form("fProfileFlowCentProton_%s",chPlaneType),11,25);
    fProfileRawFlowCentAntiProton[i] = fProfile2DRawFlowCentPtAntiProton[i] -> ProfileX(Form("fProfileFlowCentAntiProton_%s",chPlaneType),11,25);
    fProfileRawFlowCentLambda[i]     = fProfile2DRawFlowCentPtLambda[i]     -> ProfileX(Form("fProfileFlowCentLambda_%s",chPlaneType),11,25);
    fProfileRawFlowCentAntiLambda[i] = fProfile2DRawFlowCentPtAntiLambda[i] -> ProfileX(Form("fProfileFlowCentAntiLambda_%s",chPlaneType),11,25);
  }

  TH1D*  hFlowCenthPos[5];
  TH1D*  hFlowCenthNeg[5];
  TH1D*  hFlowCentProton[5];
  TH1D*  hFlowCentAntiProton[5];
  TH1D*  hFlowCentLambda[5];
  TH1D*  hFlowCentAntiLambda[5];

  for (int i = 0; i < 3; i++){
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


  TLegend *legend = new TLegend(0.1,0.7,0.48,0.9);
  legend->AddEntry(hRes[0],"TPC","lp");
  legend->AddEntry(hRes[1],"V0C","lp");
  legend->AddEntry(hRes[2],"V0A","lp");

  TCanvas* cRes = new TCanvas("cRes","Resolution",10,10,500,400);
  cRes->cd();
  TH2D* dummyRes = new TH2D("","",1,0,80,1,0,1.);
  dummyRes->SetXTitle("Centrality (%)");
  dummyRes->SetYTitle("Resolution");
  dummyRes->GetYaxis()->SetTitleOffset(1.2);
  dummyRes->Draw("SAME");
  for (int i = 0; i < 3; i++){
    SetStyle(hRes[i],ci[i],kFullCircle,1.3,1.3);
    hRes[i]->Draw("P SAME");
  }
  //legend->Draw("SAME");

  TCanvas* cV2Cent = new TCanvas("cV2Cent","v_{2} vs. Centrality",10,10,500,400);
  cV2Cent->cd();
  TH2D* dummyV2Cent = new TH2D("","",1,0,70,1,0.,0.2);
  dummyV2Cent->GetXaxis()->SetTitle("");
  dummyV2Cent->GetXaxis()->SetTitle("Centrality (%)");
  dummyV2Cent->GetYaxis()->SetTitle("v_{2}");
  dummyV2Cent->GetYaxis()->SetTitleOffset(1.2);
  //dummyV2Cent->Draw("SAME");
  for (int i = 0; i < 3; i++){
    SetStyle(hFlowCentProton[i],ci[i], kFullCircle,1.3,0);
    SetStyle(hFlowCentAntiProton[i],ci[i], kOpenCircle,1.3,0);
    hFlowCentProton[i]->Draw("SAME");
    hFlowCentAntiProton[i]->Draw("SAME");
  }
  //legend->Draw("SAME");
}

  // TProfile* fProfileRawFlowZNCVsPt_step_cent[4][10];
  // TProfile* fProfileRawFlowZNAVsPt_step_cent[4][10];

  // for (int iStep = 0; iStep < 4; iStep++){
  //   for (int iCent = 1; iCent <= 6; iCent++){
  //     fProfileRawFlowZNCVsPt_step_cent[iStep][iCent-1] = fProfile2DFlowZNCCentPtStep[iStep]->ProfileY(Form("fProfileRawFlowZNCVsPt_step%i_cent%i",iStep,iCent-1),iCent,iCent);
  //     fProfileRawFlowZNAVsPt_step_cent[iStep][iCent-1] = fProfile2DFlowZNACentPtStep[iStep]->ProfileY(Form("fProfileRawFlowZNAVsPt_step%i_cent%i",iStep,iCent-1),iCent,iCent);
  //   }
  // }

  // TH1D* hFlowZNCVsPt_step_cent[4][10];
  // TH1D* hFlowZNAVsPt_step_cent[4][10];

  // for (int iStep = 0; iStep < 4; iStep++){
  //   for (int iCent = 1; iCent <= 6; iCent++){
  //     hFlowZNCVsPt_step_cent[iStep][iCent-1] = fProfileRawFlowZNCVsPt_step_cent[iStep][iCent-1]->ProjectionX(Form("hFlowZNCVsPt_step%i_cent%i",iStep,iCent-1));
  //     hFlowZNAVsPt_step_cent[iStep][iCent-1] = fProfileRawFlowZNAVsPt_step_cent[iStep][iCent-1]->ProjectionX(Form("hFlowZNAVsPt_step%i_cent%i",iStep,iCent-1));

  //     hFlowZNCVsPt_step_cent[iStep][iCent-1] -> Scale(1./hResStep[iStep]->GetBinContent(iCent));
  //     hFlowZNAVsPt_step_cent[iStep][iCent-1] -> Scale(1./hResStep[iStep]->GetBinContent(iCent));  
  //   }
  // }

  // //这里计算fit来的flow
  // TH3F* fHist3DdNdPhiCentPthNegZNC;
  // TH3F* fHist3DdNdPhiCentPthNegZNA;
  // fHist3DdNdPhiCentPthNegZNC = (TH3F*)MyOutputContainer->FindObject("fHist3DdNdPhiCentPthNegZNC");
  // fHist3DdNdPhiCentPthNegZNA = (TH3F*)MyOutputContainer->FindObject("fHist3DdNdPhiCentPthNegZNA");
  // TH2F* fHist2DdNdPhiCentZNC = (TH2F*)fHist3DdNdPhiCentPthNegZNC -> Project3D("xz");
  // TH2F* fHist2DdNdPhiCentZNA = (TH2F*)fHist3DdNdPhiCentPthNegZNA -> Project3D("xz");
  // TH1D* hdNdPhiCenthZNC[7];
  // TH1D* hdNdPhiCenthZNA[7];
  // for (int iCent = 0; iCent < 7; iCent++) {
  //   hdNdPhiCenthZNC[iCent] = fHist2DdNdPhiCentZNC -> ProjectionX(Form("hdNdPhiCenthZNC_cent%i",iCent),iCent + 1, iCent + 1);
  //   hdNdPhiCenthZNA[iCent] = fHist2DdNdPhiCentZNA -> ProjectionX(Form("hdNdPhiCenthZNA_cent%i",iCent),iCent + 1, iCent + 1);
  // }
  // TH1D* hRawFlowVsCentZNC = new TH1D("hRawFlowVsCentZNC", "hRawFlowVsCentZNC", 7, 0., 70.);
  // TH1D* hRawFlowVsCentZNA = new TH1D("hRawFlowVsCentZNA", "hRawFlowVsCentZNA", 7, 0., 70.);

  // Double_t v2Err = -999;

  // for (int iCent = 0; iCent < 7; iCent++) {
  //   Double_t v2Err = -999;
  //   hRawFlowVsCentZNC -> SetBinContent(iCent+1, GetFlowParameter(hdNdPhiCenthZNC[iCent],v2Err));
  //   hRawFlowVsCentZNC -> SetBinError(iCent+1, v2Err);
  //   hRawFlowVsCentZNA -> SetBinContent(iCent+1, GetFlowParameter(hdNdPhiCenthZNA[iCent],v2Err)); 
  //   hRawFlowVsCentZNA -> SetBinError(iCent+1, v2Err);
  // }

  // TLegend *legend = new TLegend(0.1,0.7,0.48,0.9);
  // legend->AddEntry(hZNCZNAPsi1CorrelationStep[0],"Raw","lp");
  // legend->AddEntry(hZNCZNAPsi1CorrelationStep[1],"Gain Equalization","lp");
  // legend->AddEntry(hZNCZNAPsi1CorrelationStep[2],"Recentering","lp");
  // legend->AddEntry(hZNCZNAPsi1CorrelationStep[3],"Shift","lp");


  // TCanvas* cZNCZNACorr = new TCanvas("cZNCZNACorr","ZNC-ZNA Corr",10,10,800,600);
  // cZNCZNACorr->cd();
  // TH2D* dummyCorr = new TH2D("","",1,0,70,1,-0.2,0.2);
  // dummyCorr->SetXTitle("Centrality (%)");
  // dummyCorr->SetYTitle("<cos(#Psi_{ZNC}-#Psi_{ZNA})>");
  // dummyCorr->GetYaxis()->SetTitleOffset(1.2);
  // dummyCorr->Draw("SAME");
  // for (int i = 0; i < 4; i++){
  //   SetStyle(hZNCZNAPsi1CorrelationStep[i],ci[i],kFullCircle,1.5,1.5);
  //   hZNCZNAPsi1CorrelationStep[i]->Draw("SAME");
  // }
  // legend->Draw("SAME");
  // //cZNCZNACorr->SaveAs("./Results/cZNCZNACorr.pdf");

  // TLegend *legend2 = new TLegend(0.1,0.7,0.48,0.9);
  // legend2->AddEntry(hZNCZNAPsi1CorrelationStep[1],"Gain Equalization","lp");
  // legend2->AddEntry(hZNCZNAPsi1CorrelationStep[2],"Recentering","lp");
  // legend2->AddEntry(hZNCZNAPsi1CorrelationStep[3],"Shift","lp");


  // TCanvas* cRes = new TCanvas("cRes","ZDC Resolution",10,10,500,400);
  // cRes->cd();
  // TH2D* dummyRes = new TH2D("","",1,0,70,1,0.1,0.6);
  // dummyRes->SetXTitle("Centrality (%)");
  // dummyRes->SetYTitle("Resolution");
  // dummyRes->GetYaxis()->SetTitleOffset(1.2);
  // dummyRes->Draw("SAME");
  // for (int i = 1; i < 4; i++){
  //   SetStyle(hResStep[i],ci[i],kFullCircle,1.3,1.3);
  //   hResStep[i]->Draw("P SAME");
  // }
  // legend2->Draw("SAME");
  // //cRes->SaveAs("./Results/cRes.pdf");

  // TCanvas* cV2Cent = new TCanvas("cV2Cent","V_{2}{ZDC} vs. Centrality",10,10,500,400);
  // cV2Cent->cd();
  // TH2D* dummyV2Cent = new TH2D("","",1,0,70,1,0.,0.115);
  // dummyV2Cent->GetXaxis()->SetTitle("");
  // dummyV2Cent->GetXaxis()->SetTitle("Centrality (%)");
  // dummyV2Cent->GetYaxis()->SetTitle("v_{2}{SP}");
  // dummyV2Cent->GetYaxis()->SetTitleOffset(1.2);
  // dummyV2Cent->Draw("SAME");
  // for (int i = 1; i < 4; i++){
  //   SetStyle(hFlowZNCCentStep[i],ci[i],kFullCircle,1.3,0);
  //   SetStyle(hFlowZNACentStep[i],ci[i],kOpenCircle,1.3,0);
  //   hFlowZNCCentStep[i]->Draw("SAME");
  //   hFlowZNACentStep[i]->Draw("SAME");
  // }
  // legend2->Draw("SAME");
  // //cV2Cent->SaveAs("./Results/cV2Cent.pdf");

  // TCanvas* cV2Pt = new TCanvas("cV2Pt","V_{2}{ZDC} vs. p_{T}",1400,300);
  // cV2Pt->Divide(6,1);
  // TH2D* dummyV2Pt = new TH2D("","",1,0,5,1,0.,0.225);
  // dummyV2Pt->SetTitle("");
  // dummyV2Pt->SetXTitle("p_{T} (GeV/c)");
  // dummyV2Pt->SetYTitle("v_{2}{ZDC}");
  // dummyV2Pt->GetYaxis()->SetTitleOffset(1.2);
  // for (int iCent = 0; iCent < 6; iCent++){
  //   cV2Pt->cd(iCent+1);
  //   dummyV2Pt->Draw("SAME");
  //   for (int iStep = 1; iStep < 4; iStep++){
  //     SetStyle(hFlowZNCVsPt_step_cent[iStep][iCent],ci[iStep],kFullCircle,1,1);
  //     SetStyle(hFlowZNAVsPt_step_cent[iStep][iCent],ci[iStep],kOpenCircle,1,1);
  //     hFlowZNCVsPt_step_cent[iStep][iCent]->Draw("SAME");
  //     hFlowZNAVsPt_step_cent[iStep][iCent]->Draw("SAME");
  //   }
  //   legend2->Draw("SAME");
  // }
  // //cV2Pt->SaveAs("./Results/cV2Pt.pdf");