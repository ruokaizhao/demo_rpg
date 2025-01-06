#pragma once
#include "types.h"
#include <chrono>
#include <random>

namespace Random
{
	static uint64_t time_seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();

	static std::seed_seq ss{ uint32_t(time_seed & 0xffffffff), uint32_t(time_seed >> 32) };

	static std::mt19937 gen{ ss };

	std::uint64_t random(std::uint64_t floor, std::uint64_t ceiling)
	{
		if (floor > ceiling) {
			std::swap(floor, ceiling);
		}

		std::uniform_int_distribution<uint64_t> dist{ floor, ceiling };

		return dist(gen);
	}

	int random(int floor, int ceiling)
	{
		if (floor > ceiling) {
			std::swap(floor, ceiling);
		}

		std::uniform_int_distribution<int> dist{ floor, ceiling };

		return dist(gen);
	}
}