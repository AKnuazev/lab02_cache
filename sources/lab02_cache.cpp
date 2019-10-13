#include <iostream>
#include "Investigation.h"

int main()
{
	Investigation investigation;

	investigation.Start();

	std::ofstream report("../reports/report.txt");
	investigation.MakeReport(report);

	report.close();
}