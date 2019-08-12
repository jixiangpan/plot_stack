void set_hs(TH1D *h1, int fstyle, int color, int width)
{
  h1->SetFillStyle(fstyle);
  h1->SetFillColor(color);
  h1->SetLineColor(color);
  h1->SetLineWidth(width);
}

void plot_stack()
{
  gROOT->ProcessLine(".x DrawOption.cc");

  TString roostr = ""; 
  TFile *file_bnb = new TFile("file_bnb_no826_noFC_noLM.root", "read");
  TH1D *h1_bnb = (TH1D*)file_bnb->Get("h1_candi");
  h1_bnb->SetName("h1_bnb");

  TFile *file_extbnb = new TFile("file_extbnb_no826_noFC_noLM.root", "read");
  TH1D *h1_extbnb = (TH1D*)file_extbnb->Get("h1_candi");
  h1_extbnb->SetName("h1_extbnb");

  TFile *file_overlay = new TFile("file_overlay_no826_noFC_noLM.root", "read");
  TH1D *h1_overlay = (TH1D*)file_overlay->Get("h1_candi");
  h1_overlay->SetName("h1_overlay");

  ////////////////////

  h1_bnb->Sumw2();
  h1_extbnb->Sumw2();
  h1_overlay->Sumw2();

  h1_extbnb->Scale(1.1473);
  h1_overlay->Scale(0.53*1.2);

  ////
  double scale_F = 0.235;// ---> 1.3e19 POT
  h1_bnb->Scale(scale_F);
  h1_extbnb->Scale(scale_F);
  h1_overlay->Scale(scale_F);
  
  ////
  
  h1_extbnb->SetFillStyle(3004);
  h1_extbnb->SetFillColor(kRed);
  h1_extbnb->SetLineColor(kRed);
  h1_extbnb->SetMarkerColor(kRed);
  
  h1_overlay->SetFillStyle(3004);
  h1_overlay->SetFillColor(kBlue);
  h1_overlay->SetLineColor(kBlue);
  h1_overlay->SetMarkerColor(kBlue);
 
  ////////////////////
  
  THStack *hs = new THStack("hs","");
  hs->Add( h1_extbnb );
  hs->Add( h1_overlay );

  TCanvas *canv_ = new TCanvas("canv_", "canv_", 900, 650);
  canv_->SetBottomMargin(0.2);
  canv_->SetLeftMargin(0.15);
  
  h1_bnb->Draw("hist E");
  h1_bnb->SetXTitle("E^{vis} [MeV]");
  h1_bnb->GetXaxis()->SetTitleOffset(1.1);
    
  hs->Draw("hist E same");

  h1_bnb->Draw("same axis");

  TLegend *lg = new TLegend(0.5,0.6,0.85,0.9);
  lg->AddEntry(h1_bnb, "BNB", "lp");
  lg->AddEntry(h1_overlay, "OVERLAY", "lF");
  lg->AddEntry(h1_extbnb, "EXT", "lF");  
  lg->Draw();
  
  canv_->SaveAs("canv_.png");
  
  /*
  ////////////////////////////////////////////////////////////////////

  TFile *file_breakdown_overlay = new TFile("file_breakdown_overlay.root", "read");
  TH1D *h1_overlay2 = (TH1D*)file_breakdown_overlay->Get("h1_FC"); h1_overlay2->Sumw2(); h1_overlay2->Scale(0.53*1.2*scale_F);
  TH1D *h1_cosmic = (TH1D*)file_breakdown_overlay->Get("h1_cosmic"); h1_cosmic->Scale(0.53*1.2*scale_F);
  TH1D *h1_numuCC_FV = (TH1D*)file_breakdown_overlay->Get("h1_numuCC_FV"); h1_numuCC_FV->Scale(0.53*1.2*scale_F);
  TH1D *h1_numuCC_nFV = (TH1D*)file_breakdown_overlay->Get("h1_numuCC_nFV"); h1_numuCC_nFV->Scale(0.53*1.2*scale_F);
  TH1D *h1_numuNC_FV = (TH1D*)file_breakdown_overlay->Get("h1_numuNC_FV"); h1_numuNC_FV->Scale(0.53*1.2*scale_F);
  TH1D *h1_numuNC_nFV = (TH1D*)file_breakdown_overlay->Get("h1_numuNC_nFV"); h1_numuNC_nFV->Scale(0.53*1.2*scale_F);  
  TH1D *h1_numubar = (TH1D*)file_breakdown_overlay->Get("h1_numubar"); h1_numubar->Scale(0.53*1.2*scale_F);
  TH1D *h1_nue = (TH1D*)file_breakdown_overlay->Get("h1_nue"); h1_nue->Scale(0.53*1.2*scale_F);
  TH1D *h1_nuebar = (TH1D*)file_breakdown_overlay->Get("h1_nuebar"); h1_nuebar->Scale(0.53*1.2*scale_F);


  /////////

  TH1D *h1_others = (TH1D*)h1_numubar->Clone("h1_others");
  h1_others->Add(h1_nuebar);
  
  THStack *hs2 = new THStack("hs2","");
  
  hs2->Add( h1_extbnb ); set_hs(h1_extbnb, 1001, kGray+1, 1);

  hs2->Add( h1_others ); set_hs(h1_others, 1001, 38, 1);
  
  hs2->Add( h1_nue ); set_hs(h1_nue, 1001, kRed, 1);
  
  hs2->Add( h1_numuNC_nFV ); set_hs(h1_numuNC_nFV, 1001, kGreen+1, 1);
  
  hs2->Add( h1_numuCC_nFV ); set_hs(h1_numuCC_nFV, 1001, kOrange+1, 1);
  
  hs2->Add( h1_cosmic ); set_hs(h1_cosmic, 1001, kMagenta+1, 1);
  
  hs2->Add( h1_numuNC_FV ); set_hs(h1_numuNC_FV, 1001, kBlue, 1);
  
  hs2->Add( h1_numuCC_FV ); set_hs(h1_numuCC_FV, 3004, kOrange+2, 1);
  

  TCanvas *canv_2 = new TCanvas("canv_2", "canv_2", 900, 650);
  canv_2->SetBottomMargin(0.2);
  canv_2->SetLeftMargin(0.15);
  
  h1_bnb->Draw("hist E");
  h1_bnb->SetXTitle("E^{vis} [MeV]");
  h1_bnb->GetXaxis()->SetTitleOffset(1.1);
    
  hs2->Draw("hist same");


  TH1D *h1_sum = (TH1D*)h1_overlay2->Clone("h1_sum");
  h1_sum->Sumw2();
  h1_sum->Add( h1_extbnb );
  h1_sum->Draw("same E2");
  h1_sum->SetFillColor(2);
  h1_sum->SetFillStyle(3002);
  h1_sum->SetLineWidth(0);
  h1_sum->SetLineColor(2);
  h1_sum->SetMarkerColor(0);
  h1_sum->SetMarkerSize(0);
  //h1_sum->SetMarkerColor(kOrange+2);
  //h1_sum->SetLineColor(kOrange+2);

  
  h1_bnb->Draw("same hist E");
  h1_bnb->Draw("same axis");

  TLegend *lg2 = new TLegend(0.5,0.4,0.85,0.9);
  lg2->AddEntry(h1_bnb, "BNB", "lp");

  lg2->AddEntry(h1_sum, "Stat. error", "F");
  
  lg2->AddEntry(h1_numuCC_FV, "#nu_{#mu} CC in FV", "F");
  lg2->AddEntry(h1_numuNC_FV, "#nu_{#mu} NC in FV", "F");
  lg2->AddEntry(h1_cosmic, "Cosmic", "F");
  lg2->AddEntry(h1_numuCC_nFV, "#nu_{#mu} CC out FV", "F");
  lg2->AddEntry(h1_numuNC_nFV, "#nu_{#mu} NC out FV", "F");
  lg2->AddEntry(h1_nue, "#nu_{e}", "F");
  lg2->AddEntry(h1_others, "#bar{#nu}_{e} and #bar{#nu}_{#mu}", "F");

  lg2->AddEntry(h1_extbnb, "EXT", "F");

  lg2->Draw();
  
  canv_2->SaveAs("canv_2.png");
  */
}
