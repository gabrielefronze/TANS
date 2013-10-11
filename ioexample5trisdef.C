#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include <TH1D.h>
#include <TFile.h>
#include <TCanvas.h>
#include <vector>
#endif

using std::vector;

void ioexample(char *fimpName, char *histName){

  ifstream in(fimpName);
  if(!in){
    cout<<"Il file "<<fimpName<<" non esiste "<<endl;
    return;
  }
  
  Double_t xmin,xmax;
  Double_t x;

	in>>x;
	xmin=xmax=x;

  while((in>>x)){
    if(x<xmin) xmin=x;
    else if(x>xmax) xmax=x;
  }

  Double_t span = (-xmin+xmax)/20;

  TH1D *hist = new TH1D("hist","Istogramma",100,xmin-span,xmax+span);

  in.clear();
  in.seekg(0,ios::beg);

  while(in>>x){
    hist->Fill(x);
  }

  cout<<"Il dato piu' piccolo e': "<<xmin<<endl;
  cout<<"Il dato piu' grande e': "<<xmax<<endl;

  in.close();
  hist->Draw();
  TFile file(histName,"recreate");
  file.cd();
  hist->Write();
  file.Close();
}

