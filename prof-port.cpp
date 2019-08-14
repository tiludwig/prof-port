/**
 *
 *
 *
 */
#include <iostream>

#include "T3Framework/framework.h"
#include <Components/Target/GenericTarget.h>

using namespace std;


int main(int argc, char** argv) {

	CommunicationDriver* driver = nullptr;
	TargetWrapper* target = new GenericTarget();
	ExecutionTimer* timingMethod = nullptr;

	frameworkEntryPoint(driver, target, timingMethod);


	return 0;
}
