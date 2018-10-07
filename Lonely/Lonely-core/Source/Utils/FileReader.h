#pragma once

#include <iostream>

#include <fstream>
#include <sstream>

namespace lonely
{

	inline std::string FileToString(const std::string& filePath)
	{
		std::fstream stream(filePath);

		if (!stream)
		{
			std::cout << "[ WARNING ]: Failed to open file by FileToString function in location: " 
				      << filePath << std::endl;
			return "Could not open requested file";
		}
		else
		{
			std::stringstream output;
			std::string line;

			while (std::getline(stream, line))
				output << line << '\n';
			
			return output.str();
		}
	}

}