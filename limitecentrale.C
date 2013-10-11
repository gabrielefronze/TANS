#if !defined(__CINT__) || defined(__MAKECINT__) 
#include <TRandom.h>
#include <TH1D.h> 
#include <TCanvas.h> 
#include <TStyle.h> 
#endif


const double x1=0.,x2=0.2,x3=0.8,x4=1.;
const double x5=x3-1;
const double x6=x4-1;
const unsigned int len=8;
const unsigned int prove[len]={1,2,5,10,50,100,500,1000};
double rndmbuffer;

double randomgen(){
	rndmbuffer=gRandom->Rndm();
	if(rndmbuffer<0.5){
		return (x1+(gRandom->Rndm()*(x2-x1)));
	}
	else if(rndmbuffer>0.5){
		return (x3+(gRandom->Rndm()*(x4-x3)));
	}
	else if(rndmbuffer==0.5)randomgen();
}

double randomgen1(){
	rndmbuffer=x5+(gRandom->Rndm()*(x2-x5));
	if(rndmbuffer<0){
		return rndmbuffer+1;
	}
	else return rndmbuffer;
}

void limitecentrale(UInt_t lanci, Bool_t Animated=kFALSE){
	gRandom->SetSeed(time(0));
	gStyle->SetOptStat(210);
	gStyle->SetOptFit(100);
	TH1D *histo[len];
	TCanvas *canv=new TCanvas("somma v.a. su dominio sconnesso");
	canv->SetTitle("somma v.a. su dominio sconnesso");
	canv->SetWindowSize(12000,8000);
	canv->cd();
	canv->Divide(4,2);	

	for(UInt_t bui=0;bui<len;bui++){
		histo[bui]=new TH1D(Form("Histo%d",prove[bui]),Form("gaussiana con %d v.a. sommate",prove[bui]),250,0.,prove[bui]);
		histo[bui]->SetFillColor(38);
	};

	if(Animated){
		for(UInt_t i=0;i<len;i++){
			canv->cd(i+1);
			for(UInt_t j=0;j<lanci;j++){
				Double_t buffer=0.;
				for(UInt_t sum=0;sum<prove[i];sum++){
					buffer+=randomgen1();
				}
				histo[i]->Fill(buffer);
				histo[i]->Draw();	
				canv->Modified();
				canv->Update();
			}

			for(UInt_t fit=0;fit<len;fit++){
				histo[fit]->Fit("gaus","Q");
			};
			histo[i]->Draw();
			canv->Modified();
			canv->Update();		
		}
	}
	else{
		for(UInt_t i=0;i<len;i++){
			canv->cd(i+1);
			for(UInt_t j=0;j<lanci;j++){
				Double_t buffer=0.;
				for(UInt_t sum=0;sum<prove[i];sum++){
					buffer+=randomgen1();
				}
				histo[i]->Fill(buffer);
			}

			for(UInt_t fit=0;fit<len;fit++){
				histo[fit]->Fit("gaus","Q");
			};
			histo[i]->Draw();
			canv->Modified();
			canv->Update();		
		}
	}
}