#pragma once

#include "indexer/mwm_set.hpp"

#include <cstdint>
#include <string>

namespace feature
{
enum class GeomType
{
  Undefined = -1,
  Point = 0,
  Line = 1,
  Area = 2
};

std::string DebugPrint(GeomType type);
}  // namespace feature

struct FeatureID
{
  static char const * const kInvalidFileName;
  static int64_t const kInvalidMwmVersion;

  MwmSet::MwmId m_mwmId;
  uint32_t m_index;

  FeatureID() : m_index(0) {}
  FeatureID(MwmSet::MwmId const & mwmId, uint32_t index) : m_mwmId(mwmId), m_index(index) {}

  bool IsValid() const { return m_mwmId.IsAlive(); }

  inline bool operator<(FeatureID const & r) const
  {
    if (m_mwmId == r.m_mwmId)
      return m_index < r.m_index;
    else
      return m_mwmId < r.m_mwmId;
  }

  inline bool operator==(FeatureID const & r) const
  {
    return (m_mwmId == r.m_mwmId && m_index == r.m_index);
  }

  inline bool operator!=(FeatureID const & r) const { return !(*this == r); }

  std::string GetMwmName() const;
  int64_t GetMwmVersion() const;

  friend std::string DebugPrint(FeatureID const & id);
};
