#include "traffic/traffic_cache.hpp"

namespace traffic
{
void TrafficCache::Set(MwmSet::MwmId const & mwmId, TrafficInfo::Coloring && coloring)
{
  m_trafficColoring[mwmId] = make_shared<TrafficInfo::Coloring>(move(coloring));
}

void TrafficCache::Remove(MwmSet::MwmId const & mwmId) { m_trafficColoring.erase(mwmId); }

shared_ptr<TrafficInfo::Coloring> TrafficCache::GetTrafficInfo(MwmSet::MwmId const & mwmId) const
{
  auto it = m_trafficColoring.find(mwmId);

  if (it == m_trafficColoring.cend())
    return shared_ptr<TrafficInfo::Coloring>();
  return it->second;
}

void TrafficCache::Clear() { m_trafficColoring.clear(); }
}  // namespace traffic
