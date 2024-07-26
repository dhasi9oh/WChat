#include "ConfigMgr.h"
#include "const.h"

std::string ConfigInfo::FAILED_CONFIG_ITEM = "";

// 查找具体的配置项
std::string ConfigInfo::getItem(const std::string& key) const
{
	if (m_configItems.find(key) != m_configItems.end())
	{
		return m_configItems.at(key);
	}

	// 配置项不存在
	return FAILED_CONFIG_ITEM;
}

// 设置具体的配置项
void ConfigInfo::setItem(const std::string& key, const std::string& value)
{
	m_configItems[key] = value;
}

ConfigMgr::ConfigMgr()
{
	// 获取当前目录的路径
	boost::filesystem::path path = boost::filesystem::current_path();
	// 获取配置文件的路径
	boost::filesystem::path config_file_path = path / "config.ini";

	std::cout << "config file path: " << config_file_path.string() << std::endl;

	// 读取配置文件
	boost::property_tree::ptree pt;
	boost::property_tree::ini_parser::read_ini(config_file_path.string(), pt);

	// 当配置文件为空时，抛出异常
	assert(!pt.empty());

	// 遍历配置文件中的模块配置项
	for (auto& module_info : pt) {
		ConfigInfo configInfo;
		std::string name = module_info.first;

		// 遍历模块配置信息中的配置项
		for (auto& item : module_info.second) {
			configInfo.setItem(item.first, item.second.get_value<std::string>());
		}

		// 保存模块配置信息
		m_modConfigInfo[name] = configInfo;
	}

	// 打印一遍配置
	for (auto& module_info : m_modConfigInfo) {
		std::cout << "[" << module_info.first << "]" << std::endl;
		for (auto& item : module_info.second.m_configItems) {
			std::cout << item.first << "=" << item.second << std::endl;
		}
	}
}

ConfigMgr::~ConfigMgr()
{
}

// 获取模块的配置信息
ConfigInfo ConfigMgr::getConfigInfo(const std::string& modName) const
{
	assert(m_modConfigInfo.find(modName) != m_modConfigInfo.end());
	
	return m_modConfigInfo.at(modName);
}

// 获取模块的配置信息中的某个配置项的值
std::string ConfigMgr::getConfigItem(const std::string& modName, const std::string& key) const
{
	auto configInfo = getConfigInfo(modName);
	std::string value = configInfo[key];
	assert(value != ConfigInfo::FAILED_CONFIG_ITEM);

	return value;
}

ConfigInfo ConfigMgr::operator[](const std::string& modName) const
{
	return getConfigInfo(modName);
}
