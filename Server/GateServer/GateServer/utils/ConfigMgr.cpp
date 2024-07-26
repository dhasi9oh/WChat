#include "ConfigMgr.h"
#include "const.h"

std::string ConfigInfo::FAILED_CONFIG_ITEM = "";

// ���Ҿ����������
std::string ConfigInfo::getItem(const std::string& key) const
{
	if (m_configItems.find(key) != m_configItems.end())
	{
		return m_configItems.at(key);
	}

	// ���������
	return FAILED_CONFIG_ITEM;
}

// ���þ����������
void ConfigInfo::setItem(const std::string& key, const std::string& value)
{
	m_configItems[key] = value;
}

ConfigMgr::ConfigMgr()
{
	// ��ȡ��ǰĿ¼��·��
	boost::filesystem::path path = boost::filesystem::current_path();
	// ��ȡ�����ļ���·��
	boost::filesystem::path config_file_path = path / "config.ini";

	std::cout << "config file path: " << config_file_path.string() << std::endl;

	// ��ȡ�����ļ�
	boost::property_tree::ptree pt;
	boost::property_tree::ini_parser::read_ini(config_file_path.string(), pt);

	// �������ļ�Ϊ��ʱ���׳��쳣
	assert(!pt.empty());

	// ���������ļ��е�ģ��������
	for (auto& module_info : pt) {
		ConfigInfo configInfo;
		std::string name = module_info.first;

		// ����ģ��������Ϣ�е�������
		for (auto& item : module_info.second) {
			configInfo.setItem(item.first, item.second.get_value<std::string>());
		}

		// ����ģ��������Ϣ
		m_modConfigInfo[name] = configInfo;
	}

	// ��ӡһ������
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

// ��ȡģ���������Ϣ
ConfigInfo ConfigMgr::getConfigInfo(const std::string& modName) const
{
	assert(m_modConfigInfo.find(modName) != m_modConfigInfo.end());
	
	return m_modConfigInfo.at(modName);
}

// ��ȡģ���������Ϣ�е�ĳ���������ֵ
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
