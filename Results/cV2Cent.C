#ifdef __CLING__
#pragma cling optimize(0)
#endif
void cV2Cent()
{
//=========Macro generated from canvas: cV2Cent/v_{2} vs. Centrality
//=========  (Wed Sep 14 16:27:07 2022) by ROOT version 6.26/04
   TCanvas *cV2Cent = new TCanvas("cV2Cent", "v_{2} vs. Centrality",237,150,500,400);
   gStyle->SetOptStat(0);
   cV2Cent->Range(-8.750001,-0.03,78.75,0.17);
   cV2Cent->SetFillColor(0);
   cV2Cent->SetBorderMode(0);
   cV2Cent->SetBorderSize(2);
   cV2Cent->SetFrameBorderMode(0);
   cV2Cent->SetFrameBorderMode(0);
   
   TH2D *__1 = new TH2D("__1","v_{2} vs. Centrality of 18q",1,0,70,1,-0.01,0.15);
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
   __1->GetYaxis()->SetRange(1,1);
   __1->GetYaxis()->SetLabelFont(42);
   __1->GetYaxis()->SetTitleOffset(1.2);
   __1->GetYaxis()->SetTitleFont(42);
   __1->GetZaxis()->SetLabelFont(42);
   __1->GetZaxis()->SetTitleOffset(1);
   __1->GetZaxis()->SetTitleFont(42);
   __1->Draw("");
   
   TH1D *hFlowCenthPos_TPC__2 = new TH1D("hFlowCenthPos_TPC__2","",10,0,100);
   hFlowCenthPos_TPC__2->SetBinContent(1,0.03918024);
   hFlowCenthPos_TPC__2->SetBinContent(2,0.06652428);
   hFlowCenthPos_TPC__2->SetBinContent(3,0.08614387);
   hFlowCenthPos_TPC__2->SetBinContent(4,0.09894549);
   hFlowCenthPos_TPC__2->SetBinContent(5,0.1062875);
   hFlowCenthPos_TPC__2->SetBinContent(6,0.1085364);
   hFlowCenthPos_TPC__2->SetBinContent(7,0.1075081);
   hFlowCenthPos_TPC__2->SetBinContent(8,0.3996144);
   hFlowCenthPos_TPC__2->SetBinError(1,3.964564e-05);
   hFlowCenthPos_TPC__2->SetBinError(2,4.094263e-05);
   hFlowCenthPos_TPC__2->SetBinError(3,4.861956e-05);
   hFlowCenthPos_TPC__2->SetBinError(4,6.221512e-05);
   hFlowCenthPos_TPC__2->SetBinError(5,8.422068e-05);
   hFlowCenthPos_TPC__2->SetBinError(6,0.0001204966);
   hFlowCenthPos_TPC__2->SetBinError(7,0.0001920871);
   hFlowCenthPos_TPC__2->SetBinError(8,0.004342691);
   hFlowCenthPos_TPC__2->SetMinimum(0.07506667);
   hFlowCenthPos_TPC__2->SetMaximum(0.1209333);
   hFlowCenthPos_TPC__2->SetEntries(54189.52);
   hFlowCenthPos_TPC__2->SetStats(0);

   ci = TColor::GetColor("#f06646");
   hFlowCenthPos_TPC__2->SetLineColor(ci);
   hFlowCenthPos_TPC__2->SetLineWidth(0);

   ci = TColor::GetColor("#f06646");
   hFlowCenthPos_TPC__2->SetMarkerColor(ci);
   hFlowCenthPos_TPC__2->SetMarkerStyle(20);
   hFlowCenthPos_TPC__2->GetXaxis()->SetLabelFont(42);
   hFlowCenthPos_TPC__2->GetXaxis()->SetTitleOffset(1);
   hFlowCenthPos_TPC__2->GetXaxis()->SetTitleFont(42);
   hFlowCenthPos_TPC__2->GetYaxis()->SetLabelFont(42);
   hFlowCenthPos_TPC__2->GetYaxis()->SetTitleFont(42);
   hFlowCenthPos_TPC__2->GetZaxis()->SetLabelFont(42);
   hFlowCenthPos_TPC__2->GetZaxis()->SetTitleOffset(1);
   hFlowCenthPos_TPC__2->GetZaxis()->SetTitleFont(42);
   hFlowCenthPos_TPC__2->Draw("SAME");
   
   TH1D *hFlowCenthNeg_TPC__3 = new TH1D("hFlowCenthNeg_TPC__3","",10,0,100);
   hFlowCenthNeg_TPC__3->SetBinContent(1,0.03920872);
   hFlowCenthNeg_TPC__3->SetBinContent(2,0.06655544);
   hFlowCenthNeg_TPC__3->SetBinContent(3,0.08619797);
   hFlowCenthNeg_TPC__3->SetBinContent(4,0.09895069);
   hFlowCenthNeg_TPC__3->SetBinContent(5,0.1062953);
   hFlowCenthNeg_TPC__3->SetBinContent(6,0.1085375);
   hFlowCenthNeg_TPC__3->SetBinContent(7,0.1075258);
   hFlowCenthNeg_TPC__3->SetBinContent(8,0.3981833);
   hFlowCenthNeg_TPC__3->SetBinError(1,3.968623e-05);
   hFlowCenthNeg_TPC__3->SetBinError(2,4.097307e-05);
   hFlowCenthNeg_TPC__3->SetBinError(3,4.866182e-05);
   hFlowCenthNeg_TPC__3->SetBinError(4,6.223732e-05);
   hFlowCenthNeg_TPC__3->SetBinError(5,8.425367e-05);
   hFlowCenthNeg_TPC__3->SetBinError(6,0.0001205447);
   hFlowCenthNeg_TPC__3->SetBinError(7,0.0001922121);
   hFlowCenthNeg_TPC__3->SetBinError(8,0.004327968);
   hFlowCenthNeg_TPC__3->SetMinimum(0.07506667);
   hFlowCenthNeg_TPC__3->SetMaximum(0.1209333);
   hFlowCenthNeg_TPC__3->SetEntries(54418.86);
   hFlowCenthNeg_TPC__3->SetStats(0);

   ci = TColor::GetColor("#f06646");
   hFlowCenthNeg_TPC__3->SetLineColor(ci);
   hFlowCenthNeg_TPC__3->SetLineWidth(0);

   ci = TColor::GetColor("#f06646");
   hFlowCenthNeg_TPC__3->SetMarkerColor(ci);
   hFlowCenthNeg_TPC__3->SetMarkerStyle(24);
   hFlowCenthNeg_TPC__3->GetXaxis()->SetLabelFont(42);
   hFlowCenthNeg_TPC__3->GetXaxis()->SetTitleOffset(1);
   hFlowCenthNeg_TPC__3->GetXaxis()->SetTitleFont(42);
   hFlowCenthNeg_TPC__3->GetYaxis()->SetLabelFont(42);
   hFlowCenthNeg_TPC__3->GetYaxis()->SetTitleFont(42);
   hFlowCenthNeg_TPC__3->GetZaxis()->SetLabelFont(42);
   hFlowCenthNeg_TPC__3->GetZaxis()->SetTitleOffset(1);
   hFlowCenthNeg_TPC__3->GetZaxis()->SetTitleFont(42);
   hFlowCenthNeg_TPC__3->Draw("SAME");
   
   TH1D *hFlowCenthPos_V0C__4 = new TH1D("hFlowCenthPos_V0C__4","",10,0,100);
   hFlowCenthPos_V0C__4->SetBinContent(1,0.03503292);
   hFlowCenthPos_V0C__4->SetBinContent(2,0.06397448);
   hFlowCenthPos_V0C__4->SetBinContent(3,0.08359029);
   hFlowCenthPos_V0C__4->SetBinContent(4,0.09596786);
   hFlowCenthPos_V0C__4->SetBinContent(5,0.1020661);
   hFlowCenthPos_V0C__4->SetBinContent(6,0.1015063);
   hFlowCenthPos_V0C__4->SetBinContent(7,0.09450394);
   hFlowCenthPos_V0C__4->SetBinContent(8,0.3496382);
   hFlowCenthPos_V0C__4->SetBinError(1,3.55462e-05);
   hFlowCenthPos_V0C__4->SetBinError(2,3.920319e-05);
   hFlowCenthPos_V0C__4->SetBinError(3,4.682637e-05);
   hFlowCenthPos_V0C__4->SetBinError(4,5.955845e-05);
   hFlowCenthPos_V0C__4->SetBinError(5,7.911302e-05);
   hFlowCenthPos_V0C__4->SetBinError(6,0.0001094512);
   hFlowCenthPos_V0C__4->SetBinError(7,0.0001666536);
   hFlowCenthPos_V0C__4->SetBinError(8,0.003894393);
   hFlowCenthPos_V0C__4->SetMinimum(0.07506667);
   hFlowCenthPos_V0C__4->SetMaximum(0.1209333);
   hFlowCenthPos_V0C__4->SetEntries(56369.72);
   hFlowCenthPos_V0C__4->SetStats(0);

   ci = TColor::GetColor("#4fc2d8");
   hFlowCenthPos_V0C__4->SetLineColor(ci);
   hFlowCenthPos_V0C__4->SetLineWidth(0);

   ci = TColor::GetColor("#4fc2d8");
   hFlowCenthPos_V0C__4->SetMarkerColor(ci);
   hFlowCenthPos_V0C__4->SetMarkerStyle(20);
   hFlowCenthPos_V0C__4->GetXaxis()->SetLabelFont(42);
   hFlowCenthPos_V0C__4->GetXaxis()->SetTitleOffset(1);
   hFlowCenthPos_V0C__4->GetXaxis()->SetTitleFont(42);
   hFlowCenthPos_V0C__4->GetYaxis()->SetLabelFont(42);
   hFlowCenthPos_V0C__4->GetYaxis()->SetTitleFont(42);
   hFlowCenthPos_V0C__4->GetZaxis()->SetLabelFont(42);
   hFlowCenthPos_V0C__4->GetZaxis()->SetTitleOffset(1);
   hFlowCenthPos_V0C__4->GetZaxis()->SetTitleFont(42);
   hFlowCenthPos_V0C__4->Draw("SAME");
   
   TH1D *hFlowCenthNeg_V0C__5 = new TH1D("hFlowCenthNeg_V0C__5","",10,0,100);
   hFlowCenthNeg_V0C__5->SetBinContent(1,0.03503003);
   hFlowCenthNeg_V0C__5->SetBinContent(2,0.0639771);
   hFlowCenthNeg_V0C__5->SetBinContent(3,0.08361912);
   hFlowCenthNeg_V0C__5->SetBinContent(4,0.09597362);
   hFlowCenthNeg_V0C__5->SetBinContent(5,0.1020964);
   hFlowCenthNeg_V0C__5->SetBinContent(6,0.1014788);
   hFlowCenthNeg_V0C__5->SetBinContent(7,0.09452811);
   hFlowCenthNeg_V0C__5->SetBinContent(8,0.348747);
   hFlowCenthNeg_V0C__5->SetBinError(1,3.55628e-05);
   hFlowCenthNeg_V0C__5->SetBinError(2,3.921926e-05);
   hFlowCenthNeg_V0C__5->SetBinError(3,4.685692e-05);
   hFlowCenthNeg_V0C__5->SetBinError(4,5.958272e-05);
   hFlowCenthNeg_V0C__5->SetBinError(5,7.916465e-05);
   hFlowCenthNeg_V0C__5->SetBinError(6,0.0001094879);
   hFlowCenthNeg_V0C__5->SetBinError(7,0.0001668287);
   hFlowCenthNeg_V0C__5->SetBinError(8,0.003885956);
   hFlowCenthNeg_V0C__5->SetMinimum(0.07506667);
   hFlowCenthNeg_V0C__5->SetMaximum(0.1209333);
   hFlowCenthNeg_V0C__5->SetEntries(56512.15);
   hFlowCenthNeg_V0C__5->SetStats(0);

   ci = TColor::GetColor("#4fc2d8");
   hFlowCenthNeg_V0C__5->SetLineColor(ci);
   hFlowCenthNeg_V0C__5->SetLineWidth(0);

   ci = TColor::GetColor("#4fc2d8");
   hFlowCenthNeg_V0C__5->SetMarkerColor(ci);
   hFlowCenthNeg_V0C__5->SetMarkerStyle(24);
   hFlowCenthNeg_V0C__5->GetXaxis()->SetLabelFont(42);
   hFlowCenthNeg_V0C__5->GetXaxis()->SetTitleOffset(1);
   hFlowCenthNeg_V0C__5->GetXaxis()->SetTitleFont(42);
   hFlowCenthNeg_V0C__5->GetYaxis()->SetLabelFont(42);
   hFlowCenthNeg_V0C__5->GetYaxis()->SetTitleFont(42);
   hFlowCenthNeg_V0C__5->GetZaxis()->SetLabelFont(42);
   hFlowCenthNeg_V0C__5->GetZaxis()->SetTitleOffset(1);
   hFlowCenthNeg_V0C__5->GetZaxis()->SetTitleFont(42);
   hFlowCenthNeg_V0C__5->Draw("SAME");
   
   TH1D *hFlowCenthPos_V0A__6 = new TH1D("hFlowCenthPos_V0A__6","",10,0,100);
   hFlowCenthPos_V0A__6->SetBinContent(1,0.03591081);
   hFlowCenthPos_V0A__6->SetBinContent(2,0.06485573);
   hFlowCenthPos_V0A__6->SetBinContent(3,0.08468354);
   hFlowCenthPos_V0A__6->SetBinContent(4,0.09729552);
   hFlowCenthPos_V0A__6->SetBinContent(5,0.1036437);
   hFlowCenthPos_V0A__6->SetBinContent(6,0.1034037);
   hFlowCenthPos_V0A__6->SetBinContent(7,0.0970773);
   hFlowCenthPos_V0A__6->SetBinContent(8,0.5123744);
   hFlowCenthPos_V0A__6->SetBinError(1,3.295491e-05);
   hFlowCenthPos_V0A__6->SetBinError(2,3.631282e-05);
   hFlowCenthPos_V0A__6->SetBinError(3,4.351999e-05);
   hFlowCenthPos_V0A__6->SetBinError(4,5.505837e-05);
   hFlowCenthPos_V0A__6->SetBinError(5,7.265079e-05);
   hFlowCenthPos_V0A__6->SetBinError(6,0.0001018217);
   hFlowCenthPos_V0A__6->SetBinError(7,0.0001674231);
   hFlowCenthPos_V0A__6->SetBinError(8,0.005857202);
   hFlowCenthPos_V0A__6->SetMinimum(0.07506667);
   hFlowCenthPos_V0A__6->SetMaximum(0.1209333);
   hFlowCenthPos_V0A__6->SetEntries(35169.24);
   hFlowCenthPos_V0A__6->SetStats(0);

   ci = TColor::GetColor("#fec665");
   hFlowCenthPos_V0A__6->SetLineColor(ci);
   hFlowCenthPos_V0A__6->SetLineWidth(0);

   ci = TColor::GetColor("#fec665");
   hFlowCenthPos_V0A__6->SetMarkerColor(ci);
   hFlowCenthPos_V0A__6->SetMarkerStyle(20);
   hFlowCenthPos_V0A__6->GetXaxis()->SetLabelFont(42);
   hFlowCenthPos_V0A__6->GetXaxis()->SetTitleOffset(1);
   hFlowCenthPos_V0A__6->GetXaxis()->SetTitleFont(42);
   hFlowCenthPos_V0A__6->GetYaxis()->SetLabelFont(42);
   hFlowCenthPos_V0A__6->GetYaxis()->SetTitleFont(42);
   hFlowCenthPos_V0A__6->GetZaxis()->SetLabelFont(42);
   hFlowCenthPos_V0A__6->GetZaxis()->SetTitleOffset(1);
   hFlowCenthPos_V0A__6->GetZaxis()->SetTitleFont(42);
   hFlowCenthPos_V0A__6->Draw("SAME");
   
   TH1D *hFlowCenthNeg_V0A__7 = new TH1D("hFlowCenthNeg_V0A__7","",10,0,100);
   hFlowCenthNeg_V0A__7->SetBinContent(1,0.03591582);
   hFlowCenthNeg_V0A__7->SetBinContent(2,0.06487426);
   hFlowCenthNeg_V0A__7->SetBinContent(3,0.08471728);
   hFlowCenthNeg_V0A__7->SetBinContent(4,0.09729927);
   hFlowCenthNeg_V0A__7->SetBinContent(5,0.1035922);
   hFlowCenthNeg_V0A__7->SetBinContent(6,0.1033394);
   hFlowCenthNeg_V0A__7->SetBinContent(7,0.09724949);
   hFlowCenthNeg_V0A__7->SetBinContent(8,0.512544);
   hFlowCenthNeg_V0A__7->SetBinError(1,3.298829e-05);
   hFlowCenthNeg_V0A__7->SetBinError(2,3.634163e-05);
   hFlowCenthNeg_V0A__7->SetBinError(3,4.355669e-05);
   hFlowCenthNeg_V0A__7->SetBinError(4,5.509044e-05);
   hFlowCenthNeg_V0A__7->SetBinError(5,7.267214e-05);
   hFlowCenthNeg_V0A__7->SetBinError(6,0.0001018809);
   hFlowCenthNeg_V0A__7->SetBinError(7,0.0001677843);
   hFlowCenthNeg_V0A__7->SetBinError(8,0.005860673);
   hFlowCenthNeg_V0A__7->SetMinimum(0.07506667);
   hFlowCenthNeg_V0A__7->SetMaximum(0.1209333);
   hFlowCenthNeg_V0A__7->SetEntries(35145.86);
   hFlowCenthNeg_V0A__7->SetStats(0);

   ci = TColor::GetColor("#fec665");
   hFlowCenthNeg_V0A__7->SetLineColor(ci);
   hFlowCenthNeg_V0A__7->SetLineWidth(0);

   ci = TColor::GetColor("#fec665");
   hFlowCenthNeg_V0A__7->SetMarkerColor(ci);
   hFlowCenthNeg_V0A__7->SetMarkerStyle(24);
   hFlowCenthNeg_V0A__7->GetXaxis()->SetLabelFont(42);
   hFlowCenthNeg_V0A__7->GetXaxis()->SetTitleOffset(1);
   hFlowCenthNeg_V0A__7->GetXaxis()->SetTitleFont(42);
   hFlowCenthNeg_V0A__7->GetYaxis()->SetLabelFont(42);
   hFlowCenthNeg_V0A__7->GetYaxis()->SetTitleFont(42);
   hFlowCenthNeg_V0A__7->GetZaxis()->SetLabelFont(42);
   hFlowCenthNeg_V0A__7->GetZaxis()->SetTitleOffset(1);
   hFlowCenthNeg_V0A__7->GetZaxis()->SetTitleFont(42);
   hFlowCenthNeg_V0A__7->Draw("SAME");
   
   TH1D *hFlowCenthPos_ZNC__8 = new TH1D("hFlowCenthPos_ZNC__8","",10,0,100);
   hFlowCenthPos_ZNC__8->SetBinContent(1,0.1930439);
   hFlowCenthPos_ZNC__8->SetBinContent(2,-5.500836);
   hFlowCenthPos_ZNC__8->SetBinContent(3,-5.671343);
   hFlowCenthPos_ZNC__8->SetBinContent(4,-3.423588);
   hFlowCenthPos_ZNC__8->SetBinContent(5,-1.023311);
   hFlowCenthPos_ZNC__8->SetBinContent(6,-0.8936332);
   hFlowCenthPos_ZNC__8->SetBinContent(7,0.005096368);
   hFlowCenthPos_ZNC__8->SetBinContent(8,0.0007364184);
   hFlowCenthPos_ZNC__8->SetBinError(1,0.0117375);
   hFlowCenthPos_ZNC__8->SetBinError(2,2.514242);
   hFlowCenthPos_ZNC__8->SetBinError(3,2.230299);
   hFlowCenthPos_ZNC__8->SetBinError(4,0.9773783);
   hFlowCenthPos_ZNC__8->SetBinError(5,0.1337446);
   hFlowCenthPos_ZNC__8->SetBinError(6,0.2113338);
   hFlowCenthPos_ZNC__8->SetBinError(7,0.0004958682);
   hFlowCenthPos_ZNC__8->SetBinError(8,0.003150116);
   hFlowCenthPos_ZNC__8->SetMinimum(0.07506667);
   hFlowCenthPos_ZNC__8->SetMaximum(0.1209333);
   hFlowCenthPos_ZNC__8->SetEntries(16.31384);
   hFlowCenthPos_ZNC__8->SetStats(0);

   ci = TColor::GetColor("#92648c");
   hFlowCenthPos_ZNC__8->SetLineColor(ci);
   hFlowCenthPos_ZNC__8->SetLineWidth(0);

   ci = TColor::GetColor("#92648c");
   hFlowCenthPos_ZNC__8->SetMarkerColor(ci);
   hFlowCenthPos_ZNC__8->SetMarkerStyle(20);
   hFlowCenthPos_ZNC__8->GetXaxis()->SetLabelFont(42);
   hFlowCenthPos_ZNC__8->GetXaxis()->SetTitleOffset(1);
   hFlowCenthPos_ZNC__8->GetXaxis()->SetTitleFont(42);
   hFlowCenthPos_ZNC__8->GetYaxis()->SetLabelFont(42);
   hFlowCenthPos_ZNC__8->GetYaxis()->SetTitleFont(42);
   hFlowCenthPos_ZNC__8->GetZaxis()->SetLabelFont(42);
   hFlowCenthPos_ZNC__8->GetZaxis()->SetTitleOffset(1);
   hFlowCenthPos_ZNC__8->GetZaxis()->SetTitleFont(42);
   hFlowCenthPos_ZNC__8->Draw("SAME");
   
   TH1D *hFlowCenthNeg_ZNC__9 = new TH1D("hFlowCenthNeg_ZNC__9","",10,0,100);
   hFlowCenthNeg_ZNC__9->SetBinContent(1,0.1894295);
   hFlowCenthNeg_ZNC__9->SetBinContent(2,-5.435049);
   hFlowCenthNeg_ZNC__9->SetBinContent(3,-5.620968);
   hFlowCenthNeg_ZNC__9->SetBinContent(4,-3.403152);
   hFlowCenthNeg_ZNC__9->SetBinContent(5,-1.010395);
   hFlowCenthNeg_ZNC__9->SetBinContent(6,-0.9101156);
   hFlowCenthNeg_ZNC__9->SetBinContent(7,0.004810041);
   hFlowCenthNeg_ZNC__9->SetBinContent(8,-0.0005505873);
   hFlowCenthNeg_ZNC__9->SetBinError(1,0.01152452);
   hFlowCenthNeg_ZNC__9->SetBinError(2,2.484174);
   hFlowCenthNeg_ZNC__9->SetBinError(3,2.210491);
   hFlowCenthNeg_ZNC__9->SetBinError(4,0.9715465);
   hFlowCenthNeg_ZNC__9->SetBinError(5,0.1320673);
   hFlowCenthNeg_ZNC__9->SetBinError(6,0.2151912);
   hFlowCenthNeg_ZNC__9->SetBinError(7,0.0004970356);
   hFlowCenthNeg_ZNC__9->SetBinError(8,0.003157754);
   hFlowCenthNeg_ZNC__9->SetMinimum(0.07506667);
   hFlowCenthNeg_ZNC__9->SetMaximum(0.1209333);
   hFlowCenthNeg_ZNC__9->SetEntries(16.18599);
   hFlowCenthNeg_ZNC__9->SetStats(0);

   ci = TColor::GetColor("#92648c");
   hFlowCenthNeg_ZNC__9->SetLineColor(ci);
   hFlowCenthNeg_ZNC__9->SetLineWidth(0);

   ci = TColor::GetColor("#92648c");
   hFlowCenthNeg_ZNC__9->SetMarkerColor(ci);
   hFlowCenthNeg_ZNC__9->SetMarkerStyle(24);
   hFlowCenthNeg_ZNC__9->GetXaxis()->SetLabelFont(42);
   hFlowCenthNeg_ZNC__9->GetXaxis()->SetTitleOffset(1);
   hFlowCenthNeg_ZNC__9->GetXaxis()->SetTitleFont(42);
   hFlowCenthNeg_ZNC__9->GetYaxis()->SetLabelFont(42);
   hFlowCenthNeg_ZNC__9->GetYaxis()->SetTitleFont(42);
   hFlowCenthNeg_ZNC__9->GetZaxis()->SetLabelFont(42);
   hFlowCenthNeg_ZNC__9->GetZaxis()->SetTitleOffset(1);
   hFlowCenthNeg_ZNC__9->GetZaxis()->SetTitleFont(42);
   hFlowCenthNeg_ZNC__9->Draw("SAME");
   
   TH1D *hFlowCenthPos_ZNA__10 = new TH1D("hFlowCenthPos_ZNA__10","",10,0,100);
   hFlowCenthPos_ZNA__10->SetBinContent(1,0.2122406);
   hFlowCenthPos_ZNA__10->SetBinContent(2,-5.821455);
   hFlowCenthPos_ZNA__10->SetBinContent(3,-5.988682);
   hFlowCenthPos_ZNA__10->SetBinContent(4,-3.590601);
   hFlowCenthPos_ZNA__10->SetBinContent(5,-1.113926);
   hFlowCenthPos_ZNA__10->SetBinContent(6,-1.055694);
   hFlowCenthPos_ZNA__10->SetBinContent(7,0.006482869);
   hFlowCenthPos_ZNA__10->SetBinContent(8,-0.0007069997);
   hFlowCenthPos_ZNA__10->SetBinError(1,0.01287499);
   hFlowCenthPos_ZNA__10->SetBinError(2,2.660778);
   hFlowCenthPos_ZNA__10->SetBinError(3,2.355087);
   hFlowCenthPos_ZNA__10->SetBinError(4,1.025044);
   hFlowCenthPos_ZNA__10->SetBinError(5,0.1455277);
   hFlowCenthPos_ZNA__10->SetBinError(6,0.2492319);
   hFlowCenthPos_ZNA__10->SetBinError(7,0.000496061);
   hFlowCenthPos_ZNA__10->SetBinError(8,0.003150269);
   hFlowCenthPos_ZNA__10->SetMinimum(0.07506667);
   hFlowCenthPos_ZNA__10->SetMaximum(0.1209333);
   hFlowCenthPos_ZNA__10->SetEntries(17.35234);
   hFlowCenthPos_ZNA__10->SetStats(0);

   ci = TColor::GetColor("#7dc8a5");
   hFlowCenthPos_ZNA__10->SetLineColor(ci);
   hFlowCenthPos_ZNA__10->SetLineWidth(0);

   ci = TColor::GetColor("#7dc8a5");
   hFlowCenthPos_ZNA__10->SetMarkerColor(ci);
   hFlowCenthPos_ZNA__10->SetMarkerStyle(20);
   hFlowCenthPos_ZNA__10->GetXaxis()->SetLabelFont(42);
   hFlowCenthPos_ZNA__10->GetXaxis()->SetTitleOffset(1);
   hFlowCenthPos_ZNA__10->GetXaxis()->SetTitleFont(42);
   hFlowCenthPos_ZNA__10->GetYaxis()->SetLabelFont(42);
   hFlowCenthPos_ZNA__10->GetYaxis()->SetTitleFont(42);
   hFlowCenthPos_ZNA__10->GetZaxis()->SetLabelFont(42);
   hFlowCenthPos_ZNA__10->GetZaxis()->SetTitleOffset(1);
   hFlowCenthPos_ZNA__10->GetZaxis()->SetTitleFont(42);
   hFlowCenthPos_ZNA__10->Draw("SAME");
   
   TH1D *hFlowCenthNeg_ZNA__11 = new TH1D("hFlowCenthNeg_ZNA__11","",10,0,100);
   hFlowCenthNeg_ZNA__11->SetBinContent(1,0.2114205);
   hFlowCenthNeg_ZNA__11->SetBinContent(2,-5.807372);
   hFlowCenthNeg_ZNA__11->SetBinContent(3,-6.045138);
   hFlowCenthNeg_ZNA__11->SetBinContent(4,-3.635447);
   hFlowCenthNeg_ZNA__11->SetBinContent(5,-1.133037);
   hFlowCenthNeg_ZNA__11->SetBinContent(6,-1.122507);
   hFlowCenthNeg_ZNA__11->SetBinContent(7,0.007282529);
   hFlowCenthNeg_ZNA__11->SetBinContent(8,0.001684436);
   hFlowCenthNeg_ZNA__11->SetBinError(1,0.01282711);
   hFlowCenthNeg_ZNA__11->SetBinError(2,2.654342);
   hFlowCenthNeg_ZNA__11->SetBinError(3,2.377287);
   hFlowCenthNeg_ZNA__11->SetBinError(4,1.037844);
   hFlowCenthNeg_ZNA__11->SetBinError(5,0.1480149);
   hFlowCenthNeg_ZNA__11->SetBinError(6,0.2648774);
   hFlowCenthNeg_ZNA__11->SetBinError(7,0.0004974158);
   hFlowCenthNeg_ZNA__11->SetBinError(8,0.003158059);
   hFlowCenthNeg_ZNA__11->SetMinimum(0.07506667);
   hFlowCenthNeg_ZNA__11->SetMaximum(0.1209333);
   hFlowCenthNeg_ZNA__11->SetEntries(17.52311);
   hFlowCenthNeg_ZNA__11->SetStats(0);

   ci = TColor::GetColor("#7dc8a5");
   hFlowCenthNeg_ZNA__11->SetLineColor(ci);
   hFlowCenthNeg_ZNA__11->SetLineWidth(0);

   ci = TColor::GetColor("#7dc8a5");
   hFlowCenthNeg_ZNA__11->SetMarkerColor(ci);
   hFlowCenthNeg_ZNA__11->SetMarkerStyle(24);
   hFlowCenthNeg_ZNA__11->GetXaxis()->SetLabelFont(42);
   hFlowCenthNeg_ZNA__11->GetXaxis()->SetTitleOffset(1);
   hFlowCenthNeg_ZNA__11->GetXaxis()->SetTitleFont(42);
   hFlowCenthNeg_ZNA__11->GetYaxis()->SetLabelFont(42);
   hFlowCenthNeg_ZNA__11->GetYaxis()->SetTitleFont(42);
   hFlowCenthNeg_ZNA__11->GetZaxis()->SetLabelFont(42);
   hFlowCenthNeg_ZNA__11->GetZaxis()->SetTitleOffset(1);
   hFlowCenthNeg_ZNA__11->GetZaxis()->SetTitleFont(42);
   hFlowCenthNeg_ZNA__11->Draw("SAME");
   
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
   TLegendEntry *entry=leg->AddEntry("hRes_TPC Res_{2}","TPC","lp");

   ci = TColor::GetColor("#f06646");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#f06646");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("hRes_V0C Res_{2}","V0C","lp");

   ci = TColor::GetColor("#4fc2d8");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#4fc2d8");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("hRes_V0A Res_{2}","V0A","lp");

   ci = TColor::GetColor("#fec665");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#fec665");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("hRes_ZNC","ZNC","lp");

   ci = TColor::GetColor("#92648c");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#92648c");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("hRes_ZNA","ZNA","lp");

   ci = TColor::GetColor("#7dc8a5");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#7dc8a5");
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
   
   TPaveText *pt = new TPaveText(0.2881928,0.9342,0.7118072,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("v_{2} vs. Centrality of 18q");
   pt->Draw();
   cV2Cent->Modified();
   cV2Cent->cd();
   cV2Cent->SetSelected(cV2Cent);
}
