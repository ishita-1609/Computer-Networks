// RoutingTable.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <cmath>
#include <stdint.h>
#include <iostream>
#include <string>
#include <fstream>
#include "PrefixTree.h"
#include "IPAddress.h"
#include "RoutingTable.h"

#define INPUT "./table.input"

using namespace std;

int main()
{
	PrefixTree* tree = new PrefixTree();

	ifstream input;
	input.open(INPUT);
	if (!input.good())
	{
		cout << "Error opening input file";
		return 1;
	}
	int amt_routing;
	int amt_destinations;
	input >> amt_routing;
	input >> amt_destinations;
	cout << "Loading routing table: \n";
	float progress = 0.0;
	int percentPart = ceil((float)amt_routing / 200.0);
	for (int i = 0; i < amt_routing; i++) {
		if ((i % percentPart == 0) || (i+1 == amt_routing)) {
			progress = ((float)(i+1) / (float)amt_routing);
			int barWidth = 50;

			std::cout << "[";
			int pos = barWidth * progress;
			for (int i = 0; i < barWidth; ++i) {
				if (i < pos) std::cout << "=";
				else if (i == pos) std::cout << ">";
				else std::cout << " ";
			}
			std::cout << "] " << int(progress * 100.0) << "% " << i+1 << "/" << amt_routing << "\r";
			std::cout.flush();
			
		}
		string str_destination, str_netmask, str_gateway;
		input >> str_destination;
		input >> str_netmask;
		input >> str_gateway;
		IPAddress* destination = new IPAddress(str_destination);
		IPAddress* netmask = new IPAddress(str_netmask);
		IPAddress* gateway = new IPAddress(str_gateway);
		tree->setValueAt(destination->get_value(), netmask->get_mask(), gateway);
	}
	cout << "\n";
	for (int i = 0; i < amt_destinations; i++) {
		string str_destination;
		input >> str_destination;
		IPAddress* destination = new IPAddress(str_destination);
		IPAddress* to = tree->getValueAt(destination->get_value(), 32);
		if (to) {
			cout << to->to_string() << "\n";
		}
		else {
			cout << "NO ROUTE\n";
		}
		
	}
    return 0;
}

