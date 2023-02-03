#include "gathereddata.hpp"

#include <fstream>

void GatheredData::loadall(
	const std::filesystem::path& folder, 
	const std::filesystem::path& scenejson
) {
	auto datafolder = folder;

	const std::filesystem::path lengths_fp = 
		folder / "paths" / "lengths.bin";
	const std::filesystem::path positions_fp = 
		folder / "bounces" / "positions.bin";
	const std::filesystem::path radiance_fp = 
		folder / "paths" / "radiance.bin";
	const std::filesystem::path camerasamples_fp = 
		folder / "paths" / "camerasamples.bin";

	LOG(lengths_fp.string());
	LOG(positions_fp.string());
	LOG(radiance_fp.string());
	LOG(camerasamples_fp.string());

	std::ifstream lengths_ifs(lengths_fp);
	std::ifstream positions_ifs(positions_fp);
	std::ifstream radiance_ifs(radiance_fp);
	std::ifstream camerasamples_ifs(camerasamples_fp);
	
	const unsigned lenghts_bytesize   = std::filesystem::file_size(lengths_fp);
	const unsigned positions_bytesize = std::filesystem::file_size(positions_fp);

	npaths = lenghts_bytesize / sizeof(uint8_t);
	nbounces = positions_bytesize / sizeof(Vec3h);

	pathslength.resize(npaths);
	bouncesposition.resize(nbounces);
	pathsradiance.resize(npaths);
	pathscamerasamples.resize(npaths);

	lengths_ifs.read((char*)pathslength.data(), lenghts_bytesize);
	positions_ifs.read((char*)bouncesposition.data(), positions_bytesize);
	radiance_ifs.read((char*)pathsradiance.data(), npaths * sizeof(Vec3h));
	camerasamples_ifs.read((char*)pathscamerasamples.data(), npaths * sizeof(CameraSample));

	lengths_ifs.close();
	positions_ifs.close();
	radiance_ifs.close();
	camerasamples_ifs.close();

	firstbounceindexes.reserve(npaths);
	unsigned off = 0;
	for(uint8_t l : pathslength)
	{
		firstbounceindexes.push_back(off);
		off += l;
	}

	LOG("Loaded all paths");

	nlohmann::json json_data;
	std::ifstream json_file{scenejson};
	if(!json_file) 
	{
		LOG("Could not open \"" + scenejson.string() + "\"");
		throw std::runtime_error("Could not open scene file");
	}
	json_file >> json_data;
	json_file.close();

	rendersamples = json_data["render"]["spp"];

	rendersize = Vec2i{
		json_data["render"]["width"],
		json_data["render"]["height"]
	};

	selectedpaths.reserve(npaths);

	selectedpathstmpbuf.reserve(npaths);
}