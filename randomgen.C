#include <TRandom.h>
#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TRandom3.h>
#include <TH1I.h>
#include <TH2I.h>
#include <TCanvas.h>
#include <Riostream.h>
#endif

void sommadadi(UInt_t nlanci, Bool_t animated=kFALSE, UInt_t seed1=time(0)){

	gRandom->SetSeed(seed1);

    	TH1I *hist = new TH1I("histsum","distribuzione dado1+dado2",11,1.5,12.5);
 	TH1I *histdado1 = new TH1I("hist1","distribuzione dado1",6,0.5,6.5);
	TH1I *histdado2 = new TH1I("hist2","distribuzione dado2",6,0.5,6.5);
	TH2I *legoplot = new TH2I("hist2d","distribuzione (dado1,dado2)",6,0.5,6.5,6,0.5,6.5);

	TCanvas *canv = new TCanvas("Somma dadi");
	canv->SetTitle(Form("Analisi somma dadi con %d lanci",nlanci));
	canv->SetWindowSize(800,600);
	canv->cd();
	canv->Divide(2,2);

	Int_t buffer1,buffer2;

	canv->cd(1);
	histdado1->SetMinimum(0);
	histdado1->SetStats(kFALSE);
	histdado1->SetLineColor(38);
	histdado1->SetMarkerStyle(20);
	histdado1->SetMarkerSize(0.5);
	histdado1->SetMarkerColor(kBlue);
	histdado1->Draw("pe");
	canv->cd(2);
	histdado2->SetMinimum(0);
	histdado2->SetStats(kFALSE);
	histdado2->SetLineColor(38);
	histdado2->SetMarkerStyle(20);
	histdado2->SetMarkerSize(0.5);
	histdado2->SetMarkerColor(kBlue);
	histdado2->Draw("pe");
	canv->cd(3);
	hist->SetMinimum(0);
	hist->SetStats(kFALSE);
	hist->SetLineColor(38);
	hist->SetMarkerStyle(20);
	hist->SetMarkerSize(0.5);
	hist->SetMarkerColor(kBlue);
	hist->Draw("pe");
	canv->cd(4);
	legoplot->SetMinimum(0);
	legoplot->SetStats(kFALSE);
	legoplot->Draw("LEGO2Z");

	for(UInt_t i=0;i<nlanci;i++){
		buffer1=(Int_t)(gRandom->Rndm()*6)+1;
		buffer2=(Int_t)(gRandom->Rndm()*6)+1;
		//std::cout<<"dado1: "<<buffer1<<"     dado2: "<<buffer2<<"   somma: "<<buffer1+buffer2<<endl;
		histdado1->Fill(buffer1);
		histdado2->Fill(buffer2);
		hist->Fill(buffer1+buffer2);
		legoplot->Fill(buffer1,buffer2);
		if(i%5000==0 && animated){
			canv->cd(1);
			histdado1->Fit("pol0","Q");
			histdado1->Draw("pe");
			canv->cd(2);
			histdado2->Fit("pol0","Q");
			histdado2->Draw("pe");
			canv->cd(3);
			hist->Fit("gaus","Q");
			hist->Draw("pe");
			canv->cd(4);
			legoplot->Draw("LEGO2Z");	
			canv->cd();
			canv->SetTitle(Form("Analisi somma dadi con %d/%d lanci",i,nlanci));
			canv->Modified();
			canv->Update();	
		}
	}

	canv->SetTitle(Form("Analisi somma dadi con %d/%d lanci",nlanci,nlanci));
	canv->cd(1);
	histdado1->Draw("pe");
	histdado1->Fit("pol0");
	canv->cd(2);
	histdado2->Draw("pe");
	histdado2->Fit("pol0");
	canv->cd(3);
	hist->Fit("gaus");
	hist->Draw("pe");
	canv->cd(4);
	legoplot->Draw("LEGO2Z");
	canv->cd();
	canv->Modified();
	canv->Update();	
}
