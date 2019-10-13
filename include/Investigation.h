#pragma once

#include <iostream>
#include <cmath>
#include "Experiment.h"
#include <vector>
#include <fstream>

struct BufferInfo
{
	double START_size;
	double current_size;
	double MAX_size;
};

struct CacheInfo // Intel Core i7-7700HQ
{
	const double_t MIN_size = 256 * 1024;       // In bytes
	const double_t MAX_size = 6 * 1024 * 1024;
};

class Investigation
{
private:
	BufferInfo buffer;
	CacheInfo cache;
	std::vector<Experiment*> Results;
public:
	Investigation();
	~Investigation();
	void Start();
	void MakeReport(std::ofstream& file);
};

