#pragma once
#include <fstream>
#include <string>
#include <sstream>

#include <cereal/archives/json.hpp>
#include <cereal/archives/binary.hpp>

#define CONFIG_FILENAME "config.txt"

// Config class
class Config {
public:
	// Create config class with initializer var-s
	Config();
	// Destroy object and save var-s
	~Config();

	// Config properties: 
	int console_width = 0;
	int console_height = 0;

	// Serialize config object
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(console_width, console_height);
	}

	// Save while program is running
	void save();
};