/**
 *
 *
 *
 */
#include <iostream>

#include "T3Framework/framework.h"

using namespace std;


int main(int argc, char** argv) {

	if(argc < 4) {
		cout << "Usage: prof-port <driver> <target> <timing-method>" << endl;
		return 0;
	}





	frameworkEntryPoint(nullptr, nullptr, nullptr);


	return 0;
}
