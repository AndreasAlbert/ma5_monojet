#include "SampleAnalyzer/User/Analyzer/cms_monojet_run2.h"
using namespace MA5;
using namespace std;

// -----------------------------------------------------------------------------
// Initialize
// function called one time at the beginning of the analysis
// -----------------------------------------------------------------------------
bool cms_monojet_run2::Initialize(const MA5::Configuration& cfg, const std::map<std::string,std::string>& parameters)
{
  cout << "BEGIN Initialization" << endl;

  // Set up analysis bins
  std::vector<int> bin_edges = {250,280,310};
  int nbins = 2;
  for(int i=0; i<nbins; i++) {
    // Bin definition
    char name[20];
    char cut[20];
    sprintf(name, "bin%d", i);
    Manager()->AddRegionSelection(name);

    // Cut definition for this bin
    sprintf(cut, "%d < MET < %d GeV", bin_edges.at(i), bin_edges.at(i+1));
    Manager()->AddCut(cut,name);
  }
  
  Manager()->AddCut("Veto_Electron");
  Manager()->AddCut("Veto_Muon");
  Manager()->AddCut("Veto_Tau");
  Manager()->AddCut("Veto_B");
  Manager()->AddCut("Veto_Photon");
  Manager()->AddCut("DeltaPhi(jet, MET) > 0.5");
  Manager()->AddCut("MET > 250 GeV");
  Manager()->AddCut("LeadJet_pt");
  Manager()->AddCut("LeadJet_eta");
  Manager()->AddCut("LeadJet_ID");


  cout << "END   Initialization" << endl;
  return true;
}

// -----------------------------------------------------------------------------
// Finalize
// function called one time at the end of the analysis
// -----------------------------------------------------------------------------
void cms_monojet_run2::Finalize(const SampleFormat& summary, const std::vector<SampleFormat>& files)
{
  cout << "BEGIN Finalization" << endl;
  // saving histos
  cout << "END   Finalization" << endl;
}

// -----------------------------------------------------------------------------
// Execute
// function called each time one event is read
// -----------------------------------------------------------------------------
bool cms_monojet_run2::Execute(SampleFormat& sample, const EventFormat& event)
{
  float CUT_ELECTRON_PT_MIN = 10;
  float CUT_ELECTRON_ETA_MAX = 10;
  double weight=1.;
  if (!Configuration().IsNoEventWeight() && event.mc()!=0) {
    weight=event.mc()->weight();
  }

  Manager()->InitializeForNewEvent(weight);

  if (event.rec()==0) {return true;}
  
  vector<const RecJetFormat*> jets, bjets;
  vector<const RecLeptonFormat*> muons, electrons;
  vector<const RecTauFormat*> taus;
  vector<const RecPhotonFormat*> photons;

  // Electrons
  for(auto electron: event.rec()->electrons()){
    if (electron.pt() < CUT_ELECTRON_PT_MIN) continue;
    if (fabs(electron.eta()) > CUT_ELECTRON_ETA_MAX) continue;
    // TODO: ISO
    electrons.push_back(&electron);
  }

  // // B Jets
  // for(auto const jet: event.rec()->jets()) {
  //   if (jet->pt() < CUT_BJET_PT_MIN) continue;
  //   if (fabs(jet->eta()) > CUT_BJET_ETA_MAX) continue;
  //   if (jet->btag)
  // }

  return true;
}

