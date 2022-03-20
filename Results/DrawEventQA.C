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
void DrawEventQA(){  
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

  TFile* outputFile = TFile::Open("AnalysisResults_default.root", "READ");
  TList* outputList = (TList*) outputFile->Get("output"); 


  TH2D* fHist2DCentQA[8];
  fHist2DCentQA[0] = (TH2D*) outputList->FindObject("fHist2DCentQA_V0M_SPD1_BfCut");
  fHist2DCentQA[1] = (TH2D*) outputList->FindObject("fHist2DCentQA_V0M_SPD1_AfCut");
  fHist2DCentQA[2] = (TH2D*) outputList->FindObject("fHist2DCentQA_V0M_TRK_BfCut");
  fHist2DCentQA[3] = (TH2D*) outputList->FindObject("fHist2DCentQA_V0M_TRK_AfCut");
  fHist2DCentQA[4] = (TH2D*) outputList->FindObject("fHist2DCentQA_V0M_SPD0_BfCut");
  fHist2DCentQA[5] = (TH2D*) outputList->FindObject("fHist2DCentQA_V0M_SPD0_AfCut");
  fHist2DCentQA[6] = (TH2D*) outputList->FindObject("fHist2DCentQA_SPD1_SPD0_BfCut");
  fHist2DCentQA[7] = (TH2D*) outputList->FindObject("fHist2DCentQA_SPD1_SPD0_AfCut");
  fHist2DCentQA[1]->SetXTitle("Centrality Percentile (V0M)");
  fHist2DCentQA[1]->SetYTitle("Centrality Percentile (SPD1)");
  fHist2DCentQA[3]->SetXTitle("Centrality Percentile (V0M)");
  fHist2DCentQA[3]->SetYTitle("Centrality Percentile (TRK)");
  fHist2DCentQA[5]->SetXTitle("Centrality Percentile (V0M)");
  fHist2DCentQA[5]->SetYTitle("Centrality Percentile (SPD0)");
  fHist2DCentQA[7]->SetXTitle("Centrality Percentile (SPD1)");
  fHist2DCentQA[7]->SetYTitle("Centrality Percentile (SPD0)");

  fHist2DCentQA[0]->SetXTitle("Centrality Percentile (V0M)");
  fHist2DCentQA[0]->SetYTitle("Centrality Percentile (SPD1)");
  fHist2DCentQA[2]->SetXTitle("Centrality Percentile (V0M)");
  fHist2DCentQA[2]->SetYTitle("Centrality Percentile (TRK)");
  fHist2DCentQA[4]->SetXTitle("Centrality Percentile (V0M)");
  fHist2DCentQA[4]->SetYTitle("Centrality Percentile (SPD0)");
  fHist2DCentQA[6]->SetXTitle("Centrality Percentile (SPD1)");
  fHist2DCentQA[6]->SetYTitle("Centrality Percentile (SPD0)");


  // TLegend *legend1 = new TLegend(0.1,0.7,0.48,0.9);
  // legend1->AddEntry(fProfileGammaLambdaHadronOppo[0],"TPC","lp");
  // legend1->AddEntry(fProfileGammaLambdaHadronOppo[1],"V0C","lp");
  // legend1->AddEntry(fProfileGammaLambdaHadronOppo[2],"V0A","lp");
  // legend1->AddEntry(fProfileGammaLambdaHadronOppo[3],"ZNC","lp");
  // legend1->AddEntry(fProfileGammaLambdaHadronOppo[4],"ZNA","lp");

  TCanvas* cCentQA = new TCanvas("cCentQA","v_{2} vs. Centrality",10,10,1000,500);
  cCentQA->Divide(4,2);
  cCentQA->cd(1)->SetLogz();
  fHist2DCentQA[0]->Draw("colz");
  cCentQA->cd(2)->SetLogz();
  fHist2DCentQA[2]->Draw("colz");
  cCentQA->cd(3)->SetLogz();
  fHist2DCentQA[4]->Draw("colz");
  cCentQA->cd(4)->SetLogz();
  fHist2DCentQA[6]->Draw("colz");

  cCentQA->cd(5)->SetLogz();
  fHist2DCentQA[1]->Draw("colz");
  cCentQA->cd(6)->SetLogz();
  fHist2DCentQA[3]->Draw("colz");
  cCentQA->cd(7)->SetLogz();
  fHist2DCentQA[5]->Draw("colz");
  cCentQA->cd(8)->SetLogz();
  fHist2DCentQA[7]->Draw("colz");

  // TH2D* dummyCentQA = new TH2D("","",1,0,100,1,0,100);
  // dummyCentQA->GetXaxis()->SetTitle("");
  // dummyCentQA->GetXaxis()->SetTitle("Centrality (%)");
  // dummyCentQA->GetYaxis()->SetTitle("v_{2}");
  // dummyCentQA->GetYaxis()->SetTitleOffset(1.2);
  // dummyCentQA->Draw("SAME");
}
