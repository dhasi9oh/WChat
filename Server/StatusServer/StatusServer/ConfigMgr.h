#pragma once
#include <map>
#include <string>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "Singleton.h"

struct ConfigInfo
{
	static std::string FAILED_CONFIG_ITEM;
	using ConfigItem = std::map<std::string, std::string>;

	std::string getItem(const std::string& key) const;
	void setItem(const std::string& key, const std::string& value);

	std::string operator[](const std::string& key) { return getItem(key); }

	// ¥¢¥Ê key=value µƒ≈‰÷√œÓ
	ConfigItem m_configItems;

};


class ConfigMgr
{
public:

	using ModConfig = std::map<std::string, ConfigInfo>;

	static ConfigMgr& Instance() {
		static ConfigMgr instance;
		return instance;
	}

	~ConfigMgr();

	ConfigInfo getConfigInfo(const std::string& modName) const;
	std::string getConfigItem(const std::string& modName, const std::string& key) const;

	ConfigInfo operator[](const std::string& modName) const;

private:

	ConfigMgr();

private:

	ModConfig m_modConfigInfo;

};