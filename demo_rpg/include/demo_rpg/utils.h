#pragma once
#include "types.h"
#include <chrono>
#include <random>

namespace Random
{
	DamageType random(DamageType min_damage_value, DamageType max_damage_value)
	{
		if (min_damage_value > max_damage_value) {
			std::swap(min_damage_value, max_damage_value);
		}

		static uint64_t time_seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();

		static std::seed_seq ss{ uint32_t(time_seed & 0xffffffff), uint32_t(time_seed >> 32) };

		static std::mt19937 gen{ ss };

		std::uniform_int_distribution<uint64_t> dist{ min_damage_value, max_damage_value };

		return dist(gen);
	}
}