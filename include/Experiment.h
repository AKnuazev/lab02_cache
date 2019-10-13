#pragma once

#include <memory>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

struct ExpDuration
{
	float direct_duration, reverse_duration, random_duration;
};
class Experiment
{
private:
	void DirectPass();
	void ReversePass();
	void RandomPass();

public:
	uint64_t elements_quant;
	std::unique_ptr<uint64_t[]> buffer;
	ExpDuration time;

	Experiment(int elements_quant);
	void Start();

	static int experiments_counter;
};

