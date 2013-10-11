#if !defined(__CINT__) || defined(__MAKECINT__) 
#include <TRandom.h>
#include <TH1D.h> 
#include <TCanvas.h> 
#include <TStyle.h> 
#endif

void radiodecay3(Double_t alpha, UInt_t pop, Double_t ttot, Double_t res, UInt_t repetition){

	if(res<0||res>1)res=1;

	Double_t binbuffer1,binbuffer2;

	TH1D* histodecnumber=new TH1D("histodecnumber","distribuzione dei decadimenti",alpha*pop*ttot*2*0.5,alpha*pop*ttot*(1-0.5),alpha*pop*ttot*(1+0.5));

	gRandom->SetSeed(time(0));

	for(UInt_t g=0;g<repetition;g++){
		binbuffer1=pop;
		for(Double_t i=0;i<=(ttot/res);i+=res){
			binbuffer2=0.;
			for(UInt_t j=0;j<=binbuffer1;j++){
				if(gRandom->Rndm()<=(alpha*res)){
					binbuffer2++;
				}
			}
			binbuffer1-=binbuffer2;
		}
		histodecnumber->Fill(pop-binbuffer1);
	}

	TCanvas *canv=new TCanvas("decadimento radioattivo");
	canv->SetWindowSize(800,600);
	canv->Divide(1,2);

	//canv->cd(1);
	histodecnumber->Draw();
	histodecnumber->Fit("pois");
	cout<<"ciao cava"<<endl;
	//canv->cd(2);
	//gPad->SetLogy();
	//histodecnumber->Draw();
}