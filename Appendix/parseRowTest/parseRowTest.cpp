
//
// Local includes
//

#include "parseRow.h"
#include "ReturnValues.h"


//
// STL includes
//

#include <vector>


//
// Standard Includes
//

#include <iostream>
#include <string>


//
// Function: main()
//

int main(int argc, char* argv[]) {

	// Each token is separated by a comma
	std::string testString = "This, is, a, test, string.";

	auto p = parseRow(testString);

	std::cout << "TEST STRING : " << testString << std::endl;

	for (auto e : p) {
		std::cout << "TOKEN : " << e << std::endl;
	}



	return _OKAY_;
}

