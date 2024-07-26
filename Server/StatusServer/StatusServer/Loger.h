#ifndef UTILS_LOG_H
#define UTILS_LOG_H

#include <string>
#include <atomic>
#include <iomanip>
#include <assert.h>
#include <spdlog/async.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include "fmt/core.h"
#include "ConfigMgr.h"

class Log
{
public:

	using Level = spdlog::level::level_enum;

public:

	static Log* getInstanceance()
	{
		static Log log;
		return &log;
	}

public:

	//д��־
	bool write(Level level, const std::string& s)
	{
		if (!b_open) return false;

		_switchWrite(level, s);
		return true;
	}

	//��ƴ���ַ�����д��־
	template <class ...Args>
	bool write(Level level, const std::string& s, Args&& ...args)
	{
		if (!b_open) return false;

		std::string str = fmt::format(s, std::forward<Args>(args)...);
		return this->write(level, str);
	}


private:

	//����̨��־
	void initOut(Level level)
	{
		if (b_async) {
            spdlog::init_thread_pool(m_maxSize, m_coreCnt);
			m_loger = spdlog::stdout_color_mt<spdlog::async_factory>("m_Out");
		}
		else {
			m_loger = spdlog::stdout_color_mt("m_Out");
		}

		m_minLevel = level;
		b_open = true;
	}

	//��ͨ��־
	void  initBasic(std::string name, Level level)
	{
		if (b_async) {
            spdlog::init_thread_pool(m_maxSize, m_coreCnt);
			m_loger = spdlog::basic_logger_mt<spdlog::async_factory>("m_AsyncBasic", name, true);
		}
		else {
			m_loger = spdlog::basic_logger_mt("m_Basic", name, true);
		}

		m_minLevel = level;
		b_open = true;
	}

	//ѭ��������־
	void initRotating(std::string name, Level level, size_t memory_size, size_t file_cnt)
	{
		if (b_async) {
            spdlog::init_thread_pool(m_maxSize, m_coreCnt);
			m_loger = spdlog::rotating_logger_mt<spdlog::async_factory>("m_AsyncRotating", name, memory_size, file_cnt, true);
		}
		else {
			m_loger = spdlog::rotating_logger_mt("m_Rotating", name, memory_size, file_cnt, true);
		}

		m_minLevel = level;
		b_open = true;
	}

	//ÿ��׼ʱˢ�µ���־
	void initDaily(std::string name, Level level, int hour, int min, size_t file_cnt)
	{
		if (b_async) {
            spdlog::init_thread_pool(m_maxSize, m_coreCnt);
			m_loger = spdlog::daily_logger_mt<spdlog::async_factory>("m_AsyncDaily", name, hour, min, true, file_cnt);
		}
		else {
			m_loger = spdlog::daily_logger_mt("m_Daily", name, hour, min, true, file_cnt);
		}
		m_minLevel = level;
		b_open = true;
	}

	Log()
	{
		// ���������ļ���ʼ��
		b_open = std::stoi(ConfigMgr::Instance()["Logger"]["open"]);//�Ƿ�����־
        b_async = std::stoi(ConfigMgr::Instance()["Logger"]["async"]);//�Ƿ��첽��־
        m_maxSize = std::stoi(ConfigMgr::Instance()["Logger"]["max_size"]);//�첽��־���д�С
        m_coreCnt = std::stoi(ConfigMgr::Instance()["Server"]["core_count"]);//�첽��־�߳���
		m_minLevel = static_cast<Level>(std::stoi(ConfigMgr::Instance()["Logger"]["level"]));//��־��С�������

		if (!b_open) return;

        auto type = std::stoi(ConfigMgr::Instance()["Logger"]["type"]);//��־����
		std::string file_name = ConfigMgr::Instance()["Logger"]["file_name"];//��־�ļ���
		int file_size = std::stoi(ConfigMgr::Instance()["Logger"]["file_size"]);//��־�ļ���С
		int file_cnt = std::stoi(ConfigMgr::Instance()["Logger"]["file_cnt"]);//��־�ļ�����

		//��־�ļ�ˢ��ʱ��
		int hour = std::stoi(ConfigMgr::Instance()["Logger"]["hour"]);
		int minute = std::stoi(ConfigMgr::Instance()["Logger"]["minute"]);

		switch (type)
		{
		case 0: {
			initOut(m_minLevel);
			break;
		}
		case 1: {
			initBasic(file_name, m_minLevel);
			break;
		}
		case 2: {
			initRotating(file_name, m_minLevel, file_size, file_cnt);
			break;
		}
		case 3: {
			initDaily(file_name, m_minLevel, hour, minute, file_cnt);
			break;
		}
		default:
			break;
		}
	}

	void _switchWrite(Level level, const std::string& str)
	{
		assert(m_loger != nullptr);
		m_loger->log(level, str);
	}

private:

    int m_coreCnt;
    int m_maxSize;
    Level m_minLevel;
    bool b_open;
    bool b_async;
    std::shared_ptr<spdlog::logger> m_loger;
};

//��ͬ�������־�궨��
#define LOG_DEBUG(...) Log::getInstanceance()->write(Log::Level::debug, ##__VA_ARGS__)//DEBUG������־
#define LOG_INFO(...) Log::getInstanceance()->write(Log::Level::info, ##__VA_ARGS__)//INFO������־
#define LOG_WARN(...) Log::getInstanceance()->write(Log::Level::warn, ##__VA_ARGS__)//WARN������־
#define LOG_ERR(...) Log::getInstanceance()->write(Log::Level::err, ##__VA_ARGS__)//ERROR������־


#endif // !UTILS_LOGER_H
