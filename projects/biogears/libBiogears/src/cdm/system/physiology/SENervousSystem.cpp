/**************************************************************************************
Copyright 2015 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/
#include <biogears/cdm/system/physiology/SENervousSystem.h>

#include <biogears/cdm/properties/SEScalarFrequency.h>
#include <biogears/cdm/properties/SEScalarLength.h>
#include <biogears/cdm/properties/SEScalarPressurePerVolume.h>
#include <biogears/cdm/substance/SESubstanceManager.h>
#include <biogears/container/Tree.tci.h>

namespace biogears {
  constexpr char idBaroreceptorHeartRateScale[] = "BaroreceptorHeartRateScale";
  constexpr char idBaroreceptorHeartElastanceScale[] = "BaroreceptorHeartElastanceScale";
  constexpr char idBaroreceptorResistanceScale[] = "BaroreceptorResistanceScale";
  constexpr char idBaroreceptorComplianceScale[] = "BaroreceptorComplianceScale";
  constexpr char idChemoreceptorHeartRateScale[] = "ChemoreceptorHeartRateScale";
  constexpr char idChemoreceptorHeartElastanceScale[] = "ChemoreceptorHeartElastanceScale";
  constexpr char idPainVisualAnalogueScale[] = "PainVisualAnalogueScale";
  constexpr char idLeftEyePupillaryResponse[] = "LeftEyePupillaryResponse";
  constexpr char idRightEyePupillaryResponse[] = "RightEyePupillaryResponse";

SENervousSystem::SENervousSystem(Logger* logger)
  : SESystem(logger)
{
  m_BaroreceptorHeartRateScale = nullptr;
  m_BaroreceptorHeartElastanceScale = nullptr;
  m_BaroreceptorResistanceScale = nullptr;
  m_BaroreceptorComplianceScale = nullptr;
  m_ChemoreceptorHeartRateScale = nullptr;
  m_ChemoreceptorHeartElastanceScale = nullptr;
  m_LeftEyePupillaryResponse = nullptr;
  m_RightEyePupillaryResponse = nullptr;
  m_PainVisualAnalogueScale = nullptr;
}
//-------------------------------------------------------------------------------

SENervousSystem::~SENervousSystem()
{
  Clear();
}
//-------------------------------------------------------------------------------

void SENervousSystem::Clear()
{
  SESystem::Clear();
  SAFE_DELETE(m_BaroreceptorHeartRateScale);
  SAFE_DELETE(m_BaroreceptorHeartElastanceScale);
  SAFE_DELETE(m_BaroreceptorResistanceScale);
  SAFE_DELETE(m_BaroreceptorComplianceScale);
  SAFE_DELETE(m_ChemoreceptorHeartRateScale);
  SAFE_DELETE(m_ChemoreceptorHeartElastanceScale);
  SAFE_DELETE(m_LeftEyePupillaryResponse);
  SAFE_DELETE(m_RightEyePupillaryResponse);
  SAFE_DELETE(m_PainVisualAnalogueScale);
}
//-------------------------------------------------------------------------------
const SEScalar* SENervousSystem::GetScalar(const char* name)
{
  return GetScalar(std::string{ name });
}
//-------------------------------------------------------------------------------
const SEScalar* SENervousSystem::GetScalar(const std::string& name)
{
  if (name == idBaroreceptorHeartRateScale)
    return &GetBaroreceptorHeartRateScale();
  if (name == idBaroreceptorHeartElastanceScale)
    return &GetBaroreceptorHeartElastanceScale();
  if (name == idBaroreceptorResistanceScale)
    return &GetBaroreceptorResistanceScale();
  if (name == idBaroreceptorComplianceScale)
    return &GetBaroreceptorComplianceScale();
  if (name == idChemoreceptorHeartRateScale)
    return &GetChemoreceptorHeartRateScale();
  if (name == idChemoreceptorHeartElastanceScale)
    return &GetChemoreceptorHeartElastanceScale();
  if (name == idPainVisualAnalogueScale)
    return &GetPainVisualAnalogueScale();

  size_t split = name.find('-');
  if (split != name.npos) {
    std::string child = name.substr(0, split);
    std::string prop = name.substr(split + 1, name.npos);
    if (child == idLeftEyePupillaryResponse)
      return GetLeftEyePupillaryResponse().GetScalar(prop);
    if (child == idRightEyePupillaryResponse)
      return GetRightEyePupillaryResponse().GetScalar(prop);
  }
  return nullptr;
}
//-------------------------------------------------------------------------------

bool SENervousSystem::Load(const CDM::NervousSystemData& in)
{
  SESystem::Load(in);
  if (in.BaroreceptorHeartRateScale().present())
    GetBaroreceptorHeartRateScale().Load(in.BaroreceptorHeartRateScale().get());
  if (in.BaroreceptorHeartElastanceScale().present())
    GetBaroreceptorHeartElastanceScale().Load(in.BaroreceptorHeartElastanceScale().get());
  if (in.BaroreceptorResistanceScale().present())
    GetBaroreceptorResistanceScale().Load(in.BaroreceptorResistanceScale().get());
  if (in.BaroreceptorComplianceScale().present())
    GetBaroreceptorComplianceScale().Load(in.BaroreceptorComplianceScale().get());
  if (in.ChemoreceptorHeartRateScale().present())
    GetChemoreceptorHeartRateScale().Load(in.ChemoreceptorHeartRateScale().get());
  if (in.ChemoreceptorHeartElastanceScale().present())
    GetChemoreceptorHeartElastanceScale().Load(in.ChemoreceptorHeartElastanceScale().get());
  if (in.PainVisualAnalogueScale().present())
    GetPainVisualAnalogueScale().Load(in.PainVisualAnalogueScale().get());
  if (in.LeftEyePupillaryResponse().present())
    GetLeftEyePupillaryResponse().Load(in.LeftEyePupillaryResponse().get());
  if (in.RightEyePupillaryResponse().present())
    GetRightEyePupillaryResponse().Load(in.RightEyePupillaryResponse().get());
  return true;
}
//-------------------------------------------------------------------------------

CDM::NervousSystemData* SENervousSystem::Unload() const
{
  CDM::NervousSystemData* data = new CDM::NervousSystemData();
  Unload(*data);
  return data;
}
//-------------------------------------------------------------------------------

void SENervousSystem::Unload(CDM::NervousSystemData& data) const
{
  SESystem::Unload(data);
  if (m_BaroreceptorHeartRateScale != nullptr)
    data.BaroreceptorHeartRateScale(std::unique_ptr<CDM::ScalarData>(m_BaroreceptorHeartRateScale->Unload()));
  if (m_BaroreceptorHeartElastanceScale != nullptr)
    data.BaroreceptorHeartElastanceScale(std::unique_ptr<CDM::ScalarData>(m_BaroreceptorHeartElastanceScale->Unload()));
  if (m_BaroreceptorResistanceScale != nullptr)
    data.BaroreceptorResistanceScale(std::unique_ptr<CDM::ScalarData>(m_BaroreceptorResistanceScale->Unload()));
  if (m_BaroreceptorComplianceScale != nullptr)
    data.BaroreceptorComplianceScale(std::unique_ptr<CDM::ScalarData>(m_BaroreceptorComplianceScale->Unload()));
  if (m_ChemoreceptorHeartRateScale != nullptr)
    data.ChemoreceptorHeartRateScale(std::unique_ptr<CDM::ScalarData>(m_ChemoreceptorHeartRateScale->Unload()));
  if (m_ChemoreceptorHeartElastanceScale != nullptr)
    data.ChemoreceptorHeartElastanceScale(std::unique_ptr<CDM::ScalarData>(m_ChemoreceptorHeartElastanceScale->Unload()));
  if (m_PainVisualAnalogueScale != nullptr)
    data.PainVisualAnalogueScale(std::unique_ptr<CDM::ScalarData>(m_PainVisualAnalogueScale->Unload()));
  if (m_LeftEyePupillaryResponse != nullptr)
    data.LeftEyePupillaryResponse(std::unique_ptr<CDM::PupillaryResponseData>(m_LeftEyePupillaryResponse->Unload()));
  if (m_RightEyePupillaryResponse != nullptr)
    data.RightEyePupillaryResponse(std::unique_ptr<CDM::PupillaryResponseData>(m_RightEyePupillaryResponse->Unload()));
}
//-------------------------------------------------------------------------------

bool SENervousSystem::HasBaroreceptorHeartRateScale() const
{
  return m_BaroreceptorHeartRateScale == nullptr ? false : m_BaroreceptorHeartRateScale->IsValid();
}
//-------------------------------------------------------------------------------
SEScalar& SENervousSystem::GetBaroreceptorHeartRateScale()
{
  if (m_BaroreceptorHeartRateScale == nullptr)
    m_BaroreceptorHeartRateScale = new SEScalar();
  return *m_BaroreceptorHeartRateScale;
}
//-------------------------------------------------------------------------------
double SENervousSystem::GetBaroreceptorHeartRateScale() const
{
  if (m_BaroreceptorHeartRateScale == nullptr)
    return SEScalar::dNaN();
  return m_BaroreceptorHeartRateScale->GetValue();
}
//-------------------------------------------------------------------------------

bool SENervousSystem::HasBaroreceptorHeartElastanceScale() const
{
  return m_BaroreceptorHeartElastanceScale == nullptr ? false : m_BaroreceptorHeartElastanceScale->IsValid();
}
//-------------------------------------------------------------------------------
SEScalar& SENervousSystem::GetBaroreceptorHeartElastanceScale()
{
  if (m_BaroreceptorHeartElastanceScale == nullptr)
    m_BaroreceptorHeartElastanceScale = new SEScalar();
  return *m_BaroreceptorHeartElastanceScale;
}
//-------------------------------------------------------------------------------
double SENervousSystem::GetBaroreceptorHeartElastanceScale() const
{
  if (m_BaroreceptorHeartElastanceScale == nullptr)
    return SEScalar::dNaN();
  return m_BaroreceptorHeartElastanceScale->GetValue();
}
//-------------------------------------------------------------------------------

bool SENervousSystem::HasBaroreceptorResistanceScale() const
{
  return m_BaroreceptorResistanceScale == nullptr ? false : m_BaroreceptorResistanceScale->IsValid();
}
//-------------------------------------------------------------------------------
SEScalar& SENervousSystem::GetBaroreceptorResistanceScale()
{
  if (m_BaroreceptorResistanceScale == nullptr)
    m_BaroreceptorResistanceScale = new SEScalar();
  return *m_BaroreceptorResistanceScale;
}
//-------------------------------------------------------------------------------
double SENervousSystem::GetBaroreceptorResistanceScale() const
{
  if (m_BaroreceptorResistanceScale == nullptr)
    return SEScalar::dNaN();
  return m_BaroreceptorResistanceScale->GetValue();
}
//-------------------------------------------------------------------------------

bool SENervousSystem::HasBaroreceptorComplianceScale() const
{
  return m_BaroreceptorComplianceScale == nullptr ? false : m_BaroreceptorComplianceScale->IsValid();
}
//-------------------------------------------------------------------------------
SEScalar& SENervousSystem::GetBaroreceptorComplianceScale()
{
  if (m_BaroreceptorComplianceScale == nullptr)
    m_BaroreceptorComplianceScale = new SEScalar();
  return *m_BaroreceptorComplianceScale;
}
//-------------------------------------------------------------------------------
double SENervousSystem::GetBaroreceptorComplianceScale() const
{
  if (m_BaroreceptorComplianceScale == nullptr)
    return SEScalar::dNaN();
  return m_BaroreceptorComplianceScale->GetValue();
}
//-------------------------------------------------------------------------------

bool SENervousSystem::HasChemoreceptorHeartRateScale() const
{
  return m_ChemoreceptorHeartRateScale == nullptr ? false : m_ChemoreceptorHeartRateScale->IsValid();
}
//-------------------------------------------------------------------------------
SEScalar& SENervousSystem::GetChemoreceptorHeartRateScale()
{
  if (m_ChemoreceptorHeartRateScale == nullptr)
    m_ChemoreceptorHeartRateScale = new SEScalar();
  return *m_ChemoreceptorHeartRateScale;
}
//-------------------------------------------------------------------------------
double SENervousSystem::GetChemoreceptorHeartRateScale() const
{
  if (m_ChemoreceptorHeartRateScale == nullptr)
    return SEScalar::dNaN();
  return m_ChemoreceptorHeartRateScale->GetValue();
}
//-------------------------------------------------------------------------------

bool SENervousSystem::HasChemoreceptorHeartElastanceScale() const
{
  return m_ChemoreceptorHeartElastanceScale == nullptr ? false : m_ChemoreceptorHeartElastanceScale->IsValid();
}
//-------------------------------------------------------------------------------
SEScalar& SENervousSystem::GetChemoreceptorHeartElastanceScale()
{
  if (m_ChemoreceptorHeartElastanceScale == nullptr)
    m_ChemoreceptorHeartElastanceScale = new SEScalar();
  return *m_ChemoreceptorHeartElastanceScale;
}
//-------------------------------------------------------------------------------
double SENervousSystem::GetChemoreceptorHeartElastanceScale() const
{
  if (m_ChemoreceptorHeartElastanceScale == nullptr)
    return SEScalar::dNaN();
  return m_ChemoreceptorHeartElastanceScale->GetValue();
}
//-------------------------------------------------------------------------------

bool SENervousSystem::HasPainVisualAnalogueScale() const
{
  return m_PainVisualAnalogueScale == nullptr ? false : m_PainVisualAnalogueScale->IsValid();
}
//-------------------------------------------------------------------------------
SEScalar& SENervousSystem::GetPainVisualAnalogueScale()
{
  if (m_PainVisualAnalogueScale == nullptr)
    m_PainVisualAnalogueScale = new SEScalar();
  return *m_PainVisualAnalogueScale;
}
//-------------------------------------------------------------------------------
double SENervousSystem::GetPainVisualAnalogueScale() const
{
  if (m_PainVisualAnalogueScale == nullptr)
    return SEScalar::dNaN();
  return m_PainVisualAnalogueScale->GetValue();
}
//-------------------------------------------------------------------------------

bool SENervousSystem::HasLeftEyePupillaryResponse() const
{
  return (m_LeftEyePupillaryResponse != nullptr);
}
//-------------------------------------------------------------------------------
SEPupillaryResponse& SENervousSystem::GetLeftEyePupillaryResponse()
{
  if (m_LeftEyePupillaryResponse == nullptr)
    m_LeftEyePupillaryResponse = new SEPupillaryResponse(GetLogger());
  return *m_LeftEyePupillaryResponse;
}
//-------------------------------------------------------------------------------
const SEPupillaryResponse* SENervousSystem::GetLeftEyePupillaryResponse() const
{
  return m_LeftEyePupillaryResponse;
}
//-------------------------------------------------------------------------------
void SENervousSystem::RemoveLeftEyePupillaryResponse()
{
  SAFE_DELETE(m_LeftEyePupillaryResponse);
}
//-------------------------------------------------------------------------------

bool SENervousSystem::HasRightEyePupillaryResponse() const
{
  return (m_RightEyePupillaryResponse != nullptr);
}
//-------------------------------------------------------------------------------
SEPupillaryResponse& SENervousSystem::GetRightEyePupillaryResponse()
{
  if (m_RightEyePupillaryResponse == nullptr)
    m_RightEyePupillaryResponse = new SEPupillaryResponse(GetLogger());
  return *m_RightEyePupillaryResponse;
}
//-------------------------------------------------------------------------------
const SEPupillaryResponse* SENervousSystem::GetRightEyePupillaryResponse() const
{
  return m_RightEyePupillaryResponse;
}
//-------------------------------------------------------------------------------
void SENervousSystem::RemoveRightEyePupillaryResponse()
{
  SAFE_DELETE(m_RightEyePupillaryResponse);
}
//-------------------------------------------------------------------------------
Tree<const char*> SENervousSystem::GetPhysiologyRequestGraph() const
{
  return Tree<const char*>{classname()}
    .emplace_back(idBaroreceptorHeartRateScale)
    .emplace_back(idBaroreceptorHeartElastanceScale)
    .emplace_back(idBaroreceptorResistanceScale)
    .emplace_back(idBaroreceptorComplianceScale)
    .emplace_back(idChemoreceptorHeartRateScale)
    .emplace_back(idChemoreceptorHeartElastanceScale)
    .emplace_back(idPainVisualAnalogueScale)
    .emplace_back(idLeftEyePupillaryResponse)
    .emplace_back(idRightEyePupillaryResponse)
  ;
}
}