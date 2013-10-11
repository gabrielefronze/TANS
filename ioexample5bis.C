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
  
  Double_t xmin=0.,xmax=0.;
  Double_t x;
  Int_t count = 0;
  vector <Double_t> v;

	in>>x;
	count++;
	xmin=x;
	xmax=x;
  v.push_back(x);

  while((in>>x)){
    count++;
    v.push_back(x);

    if(x<xmin) xmin=x;
    else if(x>xmax) xmax=x;
  }

  Double_t span = (-xmin+xmax)/20;

  TH1D *hist = new TH1D("hist","Istogramma",100,xmin-span,xmax+span);

  for(int i=0;i<count;i++){
    x=v[i];
    hist->Fill(x);
  }

  cout<<"Dati letti: "<<count<<endl;
  cout<<"Il dato piu' piccolo e': "<<xmin<<endl;
  cout<<"Il dato piu' grande e': "<<xmax<<endl;

  in.close();
  hist->Draw();
  TFile file(histName,"recreate");
  file.cd();
  hist->Write();
  file.Close();
}

