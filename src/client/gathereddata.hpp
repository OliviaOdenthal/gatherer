#ifndef _GATHEREDDATA_HPP_
#define _GATHEREDDATA_HPP_

#include "utils.hpp"

#include "json.hpp"
#include "gatherer.hpp"

class GatheredData
{
public:
	std::filesystem::path datafolder;

	Vec2i rendersize;
	unsigned rendersamples;

	unsigned npaths;
	unsigned nbounces;
	std::vector<uint8_t> pathslength;
	std::vector<Vec3h> bouncesposition;
	std::vector<Vec3h> pathsradiance;
	std::vector<CameraSample> pathscamerasamples;

	std::vector<unsigned> firstbounceindexes;

	std::vector<unsigned> selectedpaths;
	// Used to store temporary data;
	std::vector<unsigned> selectedpathstmpbuf;

	void loadall(
		const std::filesystem::path& folder,
		const std::filesystem::path& scenejson
	);

	float heatmapmax = 1;
	GLuint texid_heatmap;
};

#endif