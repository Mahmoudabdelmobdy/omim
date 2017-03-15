#pragma once

#include "routing/road_access.hpp"

#include "generator/intermediate_elements.hpp"

#include <cstdint>
#include <fstream>
#include <string>

struct OsmElement;
class FeatureParams;

// The road accessibility information is collected in the same manner
// as the restrictions are.
// See generator/restriction_generator.hpp for details.
namespace routing
{
class RoadAccessWriter
{
public:
  void Open(std::string const & filePath);

  void Process(OsmElement * p, FeatureParams & params);

private:
  bool IsOpened();

  std::ofstream m_stream;
};

class RoadAccessCollector
{
public:
  RoadAccessCollector(std::string const & roadAccessPath, std::string const & osmIdsToFeatureIdsPath);

  RoadAccess & GetRoadAccess() { return m_roadAccess; }
  RoadAccess const & GetRoadAccess() const { return m_roadAccess; }

  bool IsValid() const { return m_valid; }

private:
  bool ParseRoadAccess(std::string const & roadAccessPath);

  map<uint64_t, uint32_t> m_osmIdToFeatureId;
  RoadAccess m_roadAccess;
  bool m_valid;
};

// The generator tool's interface to writing the section with
// road accessibility information for one mwm file.
void BuildRoadAccessInfo(std::string const & dataFilePath, std::string const & roadAccessPath,
                         std::string const & osmIdsToFeatureIdsPath);
}  // namespace routing
