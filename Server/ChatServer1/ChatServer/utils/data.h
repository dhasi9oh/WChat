#pragma once

#include <string>

struct UsrInfo
{
	int sex;
	int uid;
	std::string name;
	std::string pwd;
	std::string email;
	std::string nick;
	std::string desc;
	std::string icon;
	std::string back;
};

struct ApplyInfo
{
	ApplyInfo(int uid, std::string name, std::string desc, std::string icon, std::string nick, int sex, int status)
		: uid(uid), name(name), desc(desc), icon(icon), nick(nick), sex(sex), status(status) {}

	int uid;
	int sex;
	int status;
	std::string name;
	std::string desc;
	std::string icon;
	std::string nick;
};