#ifndef analysis_cms_monojet_run2_h
#define analysis_cms_monojet_run2_h

#include "SampleAnalyzer/Process/Analyzer/AnalyzerBase.h"

namespace MA5
{
class cms_monojet_run2 : public AnalyzerBase
{
  INIT_ANALYSIS(cms_monojet_run2,"cms_monojet_run2")

 public:
  virtual bool Initialize(const MA5::Configuration& cfg, const std::map<std::string,std::string>& parameters);
  virtual void Finalize(const SampleFormat& summary, const std::vector<SampleFormat>& files);
  virtual bool Execute(SampleFormat& sample, const EventFormat& event);

 private:
};
}

#endif