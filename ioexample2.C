#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include <TH1D.h>
#include <TFile.h>
#include <TCanvas.h>
#endif
void ioexample(char *fimpName, char *histName){
  ifstream in(fimpName);
  if(!in){
    cout<<"Il file "<<fimpName<<" non esiste "<<endl;
    return;
  }
  TH1D *hist = new TH1D("hist","Istogramma",100,-5.,5.);
  int count = 0;
  double x;
  while((in>>x)){
    count++;
    hist->Fill(x);
  }
  cout<<"Dati letti: "<<count<<endl;
  in.close();
  hist->Draw();
  TFile file(histName,"recreate");
  hist->Write();
  file.Close();
}
