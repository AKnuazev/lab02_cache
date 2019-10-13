#include "Experiment.h"


Experiment::Experiment(int number) : elements_quant(number)
{
	Experiment::experiments_counter++;
	std::cout << "_____________________________________" << std::endl;
	std::cout << "Experiment number " << experiments_counter << std::endl;
	std::cout << "Elements quantity: " << elements_quant << std::endl;

	buffer = std::make_unique<uint64_t[]>(elements_quant);

	std::srand(clock());
	for (unsigned i = 0; i < elements_quant; ++i) 
		buffer[i] = rand();
}
int Experiment::experiments_counter = 0;

void Experiment::DirectPass()
{
	int64_t value;

	auto start = std::chrono::high_resolution_clock::now();
	for (int64_t i = 0; i < 1000; i++)
		for (uint64_t j = 0; j < elements_quant; j++)
			value = buffer[j];

	auto end = std::chrono::high_resolution_clock::now();
	buffer[0]=value;

	time.direct_duration=std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << "Direct pass duration: " << time.direct_duration << std::endl;
}

void Experiment::ReversePass() 
{
	int64_t value = 0;
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000; i++)
		for (unsigned j = elements_quant; j > 0; j--)
			value = buffer[j];

	auto end = std::chrono::high_resolution_clock::now();
    buffer[0]=value;
	time.reverse_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << "Reverse pass duration: " << time.reverse_duration << std::endl;
}

void Experiment::RandomPass() 
{
	int64_t value = 0;
	std::vector<uint32_t> indexes;
	for (uint64_t i = 0; i < elements_quant; i++)
		indexes.push_back(i);
	
	random_shuffle(indexes.begin(), indexes.end());
	
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000; i++) 
		for (size_t index : indexes) 
			value = buffer[index];

	auto end = std::chrono::high_resolution_clock::now();
    buffer[0]=value;
	time.random_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << "Random pass duration: " << time.random_duration << std::endl;
}

void Experiment::Start()
{
	DirectPass();
	ReversePass();
	RandomPass();
}