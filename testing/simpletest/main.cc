#include <iostream>
#include "PTL.h"
int main(void)
{
	std::string filename = "test.ptl";
	PTL::PropertyTree input;

	int testInteger1, testInteger2;
	input["userDefinedSection"]["test1"].MapTo(&testInteger1) = new PTL::PTLInteger(199, "A test integer");
	input["userDefinedSection"]["test2"].MapTo(&testInteger2) = new PTL::PTLInteger(100, "A test integer2");
	input.ReadInputFileToTreeData(filename);
	input.StrictParse();
	std::cout << "Test read the following: " << testInteger1 << ", " << testInteger2 << std::endl;
	std::cout << "(SUCCESS)" << std::endl;
	return 0;
}
