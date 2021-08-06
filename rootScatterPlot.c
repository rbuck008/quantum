//
//  main.cpp
//  dumpPractice
//
//  Created by Ryan Buckley on 7/12/21.
//

#include <iostream>
#define dump1_cxx
#include "dump1.h"
#include <TH2.h>
#include <TH3.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>

char pname[100] ;

const char* mcname( int pdgid ) ;

double calcDr( double eta1, double eta2, double phi1, double phi2 ) ;

void dump1::Loop( int display_event, float rhophi_scale )
{
    //make scatter plot or heat map of all phi vs eta points of generated particles
    
    //some initializaaton stuff
    gStyle -> SetOptStat(0) ;

      bool skip_sl_top_events(true) ;

      if (fChain == 0) return;

      Long64_t nentries = fChain->GetEntries();

      TCanvas* can1 = (TCanvas*) gDirectory -> FindObject( "can1" ) ;
      if ( can1 == 0x0 ) {
        can1 = new TCanvas( "can1", "phi vs eta plane", 200,10,500,300 ) ;
    }

    Long64_t nbytes = 0, nb = 0; //idk what this does
    
    //some entry loop necessities
    int first_event ;
      int last_event ;
      if ( display_event > 0 ) {
         first_event = display_event ;
         last_event = display_event ;
      } else {
         first_event = 1 ;
         last_event = nentries-1 ;
         printf("\n\n Running in loop mode.  %d to %d\n\n", first_event, last_event) ;
      }
    
    //definte arrays of phi and eta values
    
    double x_eta[100000];
    double y_phi[100000];
    int i = 0;
    
    
    for ( int jentry=first_event; jentry<=last_event; jentry++ ) {
        Long64_t ientry = LoadTree(jentry);
             if (ientry < 0) break;
             nb = fChain->GetEntry(jentry);   nbytes += nb;
        
        //nested gnerated particle for loop (multiple generated particles per event
        for ( unsigned int gpi=0; gpi < GenParticles->size() ; gpi++ ) {
            double eta = 99. ;
            if ( GenParticles->at(gpi).Pt() > 0 ) eta = GenParticles->at(gpi).Eta();
            double phi = GenParticles->at(gpi).Phi() ;
            x_eta[i] = eta;
            y_phi[i] = phi;
            printf("%lf", x_eta[i]);
            i++;
        }//gpi loop end
        char answer[100] ;
             printf("\n\n Type n for next, q to quit: ") ;
            scanf( "%s", answer ) ;
             if ( strcmp( answer, "q") == 0 ) return ;
    }//jentry loop end
    TGraph *g = new TGraph(i,x_eta,y_phi);
    g->Draw("ap");
    can1 -> Update() ; can1 -> Draw() ;






}// loop

const char* mcname( int pdgid ) {

   sprintf( pname, "" ) ;

   if ( pdgid == 1 ) sprintf( pname, "d" ) ;
   if ( pdgid == 2 ) sprintf( pname, "u" ) ;
   if ( pdgid == 3 ) sprintf( pname, "s" ) ;
   if ( pdgid == 4 ) sprintf( pname, "c" ) ;
   if ( pdgid == 5 ) sprintf( pname, "b" ) ;
   if ( pdgid == 6 ) sprintf( pname, "t" ) ;

   if ( pdgid == -1 ) sprintf( pname, "d-bar" ) ;
   if ( pdgid == -2 ) sprintf( pname, "u-bar" ) ;
   if ( pdgid == -3 ) sprintf( pname, "s-bar" ) ;
   if ( pdgid == -4 ) sprintf( pname, "c-bar" ) ;
   if ( pdgid == -5 ) sprintf( pname, "b-bar" ) ;
   if ( pdgid == -6 ) sprintf( pname, "t-bar" ) ;

   if ( pdgid == 11 ) sprintf( pname, "e-" ) ;
   if ( pdgid == 12 ) sprintf( pname, "nu_e" ) ;
   if ( pdgid == 13 ) sprintf( pname, "mu-" ) ;
   if ( pdgid == 14 ) sprintf( pname, "nu_mu" ) ;
   if ( pdgid == 15 ) sprintf( pname, "tau-" ) ;
   if ( pdgid == 16 ) sprintf( pname, "nu_tau" ) ;

   if ( pdgid == -11 ) sprintf( pname, "e+" ) ;
   if ( pdgid == -12 ) sprintf( pname, "nu_e-bar" ) ;
   if ( pdgid == -13 ) sprintf( pname, "mu+" ) ;
   if ( pdgid == -14 ) sprintf( pname, "nu_mu-bar" ) ;
   if ( pdgid == -15 ) sprintf( pname, "tau+" ) ;
   if ( pdgid == -16 ) sprintf( pname, "nu_tau-bar" ) ;

   if ( pdgid == 21 ) sprintf( pname, "gluon" ) ;
   if ( pdgid == 22 ) sprintf( pname, "photon" ) ;
   if ( pdgid == 23 ) sprintf( pname, "Z0" ) ;
   if ( pdgid == 24 ) sprintf( pname, "W+" ) ;
   if ( pdgid ==-24 ) sprintf( pname, "W-" ) ;
   if ( pdgid == 25 ) sprintf( pname, "h" ) ;
   if ( pdgid == 35 ) sprintf( pname, "H" ) ;
   if ( pdgid == 36 ) sprintf( pname, "a" ) ;


   if ( pdgid == 1000001 ) sprintf( pname, "~dL" ) ;
   if ( pdgid == 1000002 ) sprintf( pname, "~uL" ) ;
   if ( pdgid == 1000003 ) sprintf( pname, "~sL" ) ;
   if ( pdgid == 1000004 ) sprintf( pname, "~cL" ) ;
   if ( pdgid == 1000005 ) sprintf( pname, "~b1" ) ;
   if ( pdgid == 1000006 ) sprintf( pname, "~t1" ) ;

   if ( pdgid == -1000001 ) sprintf( pname, "~dL*" ) ;
   if ( pdgid == -1000002 ) sprintf( pname, "~uL*" ) ;
   if ( pdgid == -1000003 ) sprintf( pname, "~sL*" ) ;
   if ( pdgid == -1000004 ) sprintf( pname, "~cL*" ) ;
   if ( pdgid == -1000005 ) sprintf( pname, "~b1*" ) ;
   if ( pdgid == -1000006 ) sprintf( pname, "~t1*" ) ;

   if ( pdgid == 1000022 ) sprintf( pname, "~chi01" ) ;

   return pname ;


} // mcname

double calcDr( double eta1, double eta2, double phi1, double phi2 ) {

   double deta = fabs( eta1 - eta2 ) ;

   double dphi = phi1 - phi2 ;
   if ( dphi > 3.1415926 ) dphi -= 2*3.1415926 ;
   if ( dphi <-3.1415926 ) dphi += 2*3.1415926 ;

   return sqrt( dphi*dphi + deta*deta ) ;

} // calcDr

