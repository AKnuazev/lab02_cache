#include "Investigation.h"

Investigation::Investigation()
{
	buffer.START_size = 0.5 * cache.MIN_size;
	buffer.current_size = buffer.START_size;
	buffer.MAX_size = 1.5 * cache.MAX_size;
}

void Investigation::Start()
{
	int64_t elements_quant = buffer.START_size / sizeof(int64_t); 
	int64_t degree = std::log2(buffer.START_size);

	while (buffer.current_size <= buffer.MAX_size)
	{
		auto *experiment = new Experiment(elements_quant);
		experiment->Start();
		Results.push_back(experiment);

		degree++;
		buffer.current_size = pow(2, degree);
		elements_quant = buffer.current_size / sizeof(int64_t);
	} 
}

void Investigation::MakeReport(std::ofstream& file)
{
	file << "investigation:\n";
	file << "  travel_variant: Direct\n";
	file << "  experiments:\n";
	for (size_t i=0; i<Results.size(); i++)
	{
		file << "  - experiment:\n";
		file << "      number: " << i << "\n";
		file << "      input_data:\n";
		file << "        buffer_size: " << Results[i]->elements_quant*sizeof(int64_t)/1024 << " kB\n";
		file << "      results:\n";
		file << "        duration: " << Results[i]->time.direct_duration<< " ms\n";
	}
	file << "\n";

	file << "investigation:\n";
	file << "  travel_variant: Reverse\n";
	file << "  experiments:\n";
	for (size_t i = 0; i < Results.size(); i++)
	{
		file << "  - experiment:\n";
		file << "      number: " << i << "\n";
		file << "      input_data:\n";
		file << "        buffer_size: " << Results[i]->elements_quant << "\n";
		file << "      results:\n";
		file << "        duration: " << Results[i]->time.reverse_duration<< "\n";
	}
	file << "\n";

	file << "investigation:\n";
	file << "  travel_variant: Random\n";
	file << "  experiments:\n";
	for (size_t i = 0; i < Results.size(); i++)
	{
		file << "  - experiment:\n";
		file << "      number: " << i << "\n";
		file << "      input_data:\n";
		file << "        buffer_size: " << Results[i]->elements_quant << "\n";
		file << "      results:\n";
		file << "        duration: " << Results[i]->time.random_duration<< "\n";
	}
	file << "\n";
}

Investigation::~Investigation()
{
	for (auto iter : Results)
		delete iter;
	Results.clear();
}
