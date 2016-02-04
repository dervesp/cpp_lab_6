// task01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include "Triangle.h"

void ProcessLine(std::string & line, std::ostream & ostream);

int _tmain(int argc, _TCHAR* argv[])
{
	std::string line;
	while (std::getline(std::cin, line))
	{
		ProcessLine(line, std::cout);
	}
	return 0;
}

void ProcessLine(std::string & line, std::ostream & ostream)
{
	std::istringstream istream(line);

	double side1, side2, side3;

	if (istream >> side1 >> side2 >> side3)
	{
		try
		{
			CTriangle triangle(side1, side2, side3);
			ostream << "triangle( " << std::to_string(side1) << " " << std::to_string(side2) << " " << std::to_string(side3) << " ):" << std::endl;
			ostream << "  perimeter: " << std::to_string(triangle.GetPerimeter()) << std::endl;
			ostream << "  area:      " << std::to_string(triangle.GetArea()) << std::endl;
		}
		catch (std::exception const & ex)
		{
			ostream << "Error: " << ex.what() << std::endl;
		}
	}
	else
	{
		ostream << "Wrong sides format. Usage: <side1> <side2> <side3>" << std::endl;
	}
	ostream << std::endl;

}

