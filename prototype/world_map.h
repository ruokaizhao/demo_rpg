#pragma once
#include <vector>
#include <string>

// static in a cpp file means that the variable has internal linkage and is only visible within that specific file,
// but static in a header file means that the variable is visible in all cpp files that include the header file,
// but each cpp file gets its own copy of the variable, which is not what we want here.
std::vector<std::string> world_map =
{
	"xxxxxxxxxxxx",
	"x          x",
	"x          x",
	"x          x",
	"x          x",
	"x          x",
	"x          x",
	"x          x",
	"x          x",
	"x          x",
	"x          x",
	"xxxxxxxxxxxx",
};