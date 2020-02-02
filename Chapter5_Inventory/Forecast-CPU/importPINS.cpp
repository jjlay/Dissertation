

//
// STL Includes
//

#include <vector>


//
// Standard includes
//

#include <string>


//
// Local includes
//

#include "importRawData.h"
#include "parseRow.h"


//
// Function: importPINS()
//


std::vector<std::vector<std::string>> importPINS(std::string pFilename) {

	auto rawData = importRawData(pFilename);
	std::vector<std::vector<std::string>> result;

	for (auto v : rawData) {
		auto p = parseRow(v);
		result.push_back(p);
	}

	return result;
}

