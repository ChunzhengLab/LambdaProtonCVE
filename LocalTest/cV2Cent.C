#ifdef __CLING__
#pragma cling optimize(0)
#endif
void cV2Cent()
{
//=========Macro generated from canvas: cV2Cent/v_{2} vs. Centrality
//=========  (Tue Oct  4 01:29:16 2022) by ROOT version 6.26/04
   TCanvas *cV2Cent = new TCanvas("cV2Cent", "v_{2} vs. Centrality",520,201,500,400);
   gStyle->SetOptStat(0);
   cV2Cent->Range(-10,-0.03625,90,0.22625);
   cV2Cent->SetFillColor(0);
   cV2Cent->SetBorderMode(0);
   cV2Cent->SetBorderSize(2);
   cV2Cent->SetFrameBorderMode(0);
   cV2Cent->SetFrameBorderMode(0);
   
   TH2D *__1 = new TH2D("__1","v_{2} vs. Centrality",1,0,80,1,-0.01,0.2);
   __1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   __1->SetLineColor(ci);
   __1->GetXaxis()->SetTitle("Centrality (%)");
   __1->GetXaxis()->SetLabelFont(42);
   __1->GetXaxis()->SetTitleOffset(1);
   __1->GetXaxis()->SetTitleFont(42);
   __1->GetYaxis()->SetTitle("v_{2}");
   __1->GetYaxis()->SetLabelFont(42);
   __1->GetYaxis()->SetTitleOffset(1.2);
   __1->GetYaxis()->SetTitleFont(42);
   __1->GetZaxis()->SetLabelFont(42);
   __1->GetZaxis()->SetTitleOffset(1);
   __1->GetZaxis()->SetTitleFont(42);
   __1->Draw("");
   
   TH1D *hFlowCentProton__2 = new TH1D("hFlowCentProton__2","",10,0,100);
   hFlowCentProton__2->SetBinContent(1,0.04067104);
   hFlowCentProton__2->SetBinContent(2,0.07237397);
   hFlowCentProton__2->SetBinContent(3,0.09611436);
   hFlowCentProton__2->SetBinContent(4,0.1153647);
   hFlowCentProton__2->SetBinContent(5,0.1290177);
   hFlowCentProton__2->SetBinContent(6,0.1354798);
   hFlowCentProton__2->SetBinContent(7,0.1417386);
   hFlowCentProton__2->SetBinContent(8,0.1415841);
   hFlowCentProton__2->SetBinError(1,0.051052);
   hFlowCentProton__2->SetBinError(2,0.0817899);
   hFlowCentProton__2->SetBinError(3,0.1069806);
   hFlowCentProton__2->SetBinError(4,0.1305748);
   hFlowCentProton__2->SetBinError(5,0.1524419);
   hFlowCentProton__2->SetBinError(6,0.1738216);
   hFlowCentProton__2->SetBinError(7,0.2079803);
   hFlowCentProton__2->SetBinError(8,0.2543429);
   hFlowCentProton__2->SetEntries(3.820413);
   hFlowCentProton__2->SetStats(0);

   ci = TColor::GetColor("#f06646");
   hFlowCentProton__2->SetLineColor(ci);
   hFlowCentProton__2->SetLineWidth(0);

   ci = TColor::GetColor("#f06646");
   hFlowCentProton__2->SetMarkerColor(ci);
   hFlowCentProton__2->SetMarkerStyle(20);
   hFlowCentProton__2->GetXaxis()->SetLabelFont(42);
   hFlowCentProton__2->GetXaxis()->SetTitleOffset(1);
   hFlowCentProton__2->GetXaxis()->SetTitleFont(42);
   hFlowCentProton__2->GetYaxis()->SetLabelFont(42);
   hFlowCentProton__2->GetYaxis()->SetTitleFont(42);
   hFlowCentProton__2->GetZaxis()->SetLabelFont(42);
   hFlowCentProton__2->GetZaxis()->SetTitleOffset(1);
   hFlowCentProton__2->GetZaxis()->SetTitleFont(42);
   hFlowCentProton__2->Draw("SAME");
   
   TH1D *hFlowCentAntiProton__3 = new TH1D("hFlowCentAntiProton__3","",10,0,100);
   hFlowCentAntiProton__3->SetBinContent(1,0.04303868);
   hFlowCentAntiProton__3->SetBinContent(2,0.07566281);
   hFlowCentAntiProton__3->SetBinContent(3,0.1006924);
   hFlowCentAntiProton__3->SetBinContent(4,0.1194275);
   hFlowCentAntiProton__3->SetBinContent(5,0.1349712);
   hFlowCentAntiProton__3->SetBinContent(6,0.1425139);
   hFlowCentAntiProton__3->SetBinContent(7,0.1447933);
   hFlowCentAntiProton__3->SetBinContent(8,0.1401964);
   hFlowCentAntiProton__3->SetBinError(1,0.05402405);
   hFlowCentAntiProton__3->SetBinError(2,0.08550668);
   hFlowCentAntiProton__3->SetBinError(3,0.1120763);
   hFlowCentAntiProton__3->SetBinError(4,0.1351733);
   hFlowCentAntiProton__3->SetBinError(5,0.1594765);
   hFlowCentAntiProton__3->SetBinError(6,0.1828467);
   hFlowCentAntiProton__3->SetBinError(7,0.212464);
   hFlowCentAntiProton__3->SetBinError(8,0.2518575);
   hFlowCentAntiProton__3->SetEntries(3.896058);
   hFlowCentAntiProton__3->SetStats(0);

   ci = TColor::GetColor("#f06646");
   hFlowCentAntiProton__3->SetLineColor(ci);
   hFlowCentAntiProton__3->SetLineWidth(0);

   ci = TColor::GetColor("#f06646");
   hFlowCentAntiProton__3->SetMarkerColor(ci);
   hFlowCentAntiProton__3->SetMarkerStyle(24);
   hFlowCentAntiProton__3->GetXaxis()->SetLabelFont(42);
   hFlowCentAntiProton__3->GetXaxis()->SetTitleOffset(1);
   hFlowCentAntiProton__3->GetXaxis()->SetTitleFont(42);
   hFlowCentAntiProton__3->GetYaxis()->SetLabelFont(42);
   hFlowCentAntiProton__3->GetYaxis()->SetTitleFont(42);
   hFlowCentAntiProton__3->GetZaxis()->SetLabelFont(42);
   hFlowCentAntiProton__3->GetZaxis()->SetTitleOffset(1);
   hFlowCentAntiProton__3->GetZaxis()->SetTitleFont(42);
   hFlowCentAntiProton__3->Draw("SAME");
   
   Double_t Graph1D_y1_fx3001[9] = {
   2.5,
   7.5,
   15,
   25,
   35,
   45,
   55,
   65,
   75};
   Double_t Graph1D_y1_fy3001[9] = {
   0.02839,
   0.04566,
   0.06551,
   0.08707,
   0.0991,
   0.10414,
   0.10286,
   0.09746,
   0.08881};
   Double_t Graph1D_y1_felx3001[9] = {
   2.5,
   2.5,
   5,
   5,
   5,
   5,
   5,
   5,
   5};
   Double_t Graph1D_y1_fely3001[9] = {
   0.0007140028,
   0.0009411164,
   0.001047521,
   0.001381919,
   0.001588269,
   0.001722353,
   0.001875233,
   0.002364572,
   0.004577477};
   Double_t Graph1D_y1_fehx3001[9] = {
   2.5,
   2.5,
   5,
   5,
   5,
   5,
   5,
   5,
   5};
   Double_t Graph1D_y1_fehy3001[9] = {
   0.0007140028,
   0.0009411164,
   0.001047521,
   0.001381919,
   0.001588269,
   0.001722353,
   0.001875233,
   0.002364572,
   0.004577477};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(9,Graph1D_y1_fx3001,Graph1D_y1_fy3001,Graph1D_y1_felx3001,Graph1D_y1_fehx3001,Graph1D_y1_fely3001,Graph1D_y1_fehy3001);
   grae->SetName("Graph1D_y1");
   grae->SetTitle("doi:10.17182/hepdata.72886.v2/t1");
   grae->SetFillStyle(1000);
   
   TH1F *Graph_Graph1D_y13001 = new TH1F("Graph_Graph1D_y13001","doi:10.17182/hepdata.72886.v2/t1",100,0,88);
   Graph_Graph1D_y13001->SetMinimum(0.01985736);
   Graph_Graph1D_y13001->SetMaximum(0.113681);
   Graph_Graph1D_y13001->SetDirectory(0);
   Graph_Graph1D_y13001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1D_y13001->SetLineColor(ci);
   Graph_Graph1D_y13001->GetXaxis()->SetTitle("CENTRALITY [PCT]");
   Graph_Graph1D_y13001->GetXaxis()->SetLabelFont(42);
   Graph_Graph1D_y13001->GetXaxis()->SetTitleOffset(1);
   Graph_Graph1D_y13001->GetXaxis()->SetTitleFont(42);
   Graph_Graph1D_y13001->GetYaxis()->SetTitle("V2{2, |DELTAETA|>1}");
   Graph_Graph1D_y13001->GetYaxis()->SetLabelFont(42);
   Graph_Graph1D_y13001->GetYaxis()->SetTitleFont(42);
   Graph_Graph1D_y13001->GetZaxis()->SetLabelFont(42);
   Graph_Graph1D_y13001->GetZaxis()->SetTitleOffset(1);
   Graph_Graph1D_y13001->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph1D_y13001);
   
   grae->Draw("");
   
   TLegend *leg = new TLegend(0.15,0.6,0.35,0.88,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("hRes","TPC","lp");

   ci = TColor::GetColor("#f06646");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#f06646");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph1D_y1","Published","lp");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   TPaveText *pt = new TPaveText(0.3494378,0.9342,0.6505622,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("v_{2} vs. Centrality");
   pt->Draw();
   cV2Cent->Modified();
   cV2Cent->cd();
   cV2Cent->SetSelected(cV2Cent);
}
