/*
 * Author: 318324563 - Daniel Meir Karl
 */

#ifndef CLI_H_
#define CLI_H_
#include <vector>
#include <algorithm>
#include <string.h>
#include "commands.h"

using namespace std;

class CLI {
    vector<Command*> commands;
	DefaultIO* dio;
	// you can add data members
public:
	CLI(DefaultIO* dio);
	void start();
	virtual ~CLI();
};

#endif /* CLI_H_ */
