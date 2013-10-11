#if !defined(__CINT__) || defined(__MAKECINT__) 
#include <TRandom.h>
#include <TH1D.h> 
#include <TCanvas.h> 
#include <TStyle.h> 
#endif

void radiodecay(Double_t alpha, UInt_t pop, Double_t ttot, Double_t res){

	if(res<0||res>1)res=1;

	Double_t binbuffer;
	TH1D* histo=new TH1D("histo","plot lineare",(ttot/res),0.,ttot);


	histo->SetBinContent(1,pop);
	gRandom->SetSeed(time(0));

	for(Double_t i=0;i<=(ttot/res)&&i+2<=ttot;i+=res){
		binbuffer=histo->GetBinContent(i+1);
		for(UInt_t j=0;j<=binbuffer;j++){
			if(gRandom->Rndm()<=(alpha*res)){
				binbuffer--;
			}
		}
		histo->SetBinContent(i+2,binbuffer);
	}

	TH1D* histolog=new TH1D(*histo);
	histolog->SetName("histolog");
	histolog->SetTitle("plot logaritmico");



	TCanvas *canv=new TCanvas("decadimento radioattivo");
	canv->SetWindowSize(1000,600);
	canv->Divide(1,2);

	canv->cd(1);
	histo->Draw();
	histo->Fit("expo","Q");
	canv->cd(2);
	gPad->SetLogy();
	histolog->Draw();
	histolog->Fit("expo","Q");

}