#include "ChatGrpcClient.h"


#include <jsoncpp/json/json.h>

ChatGrpcClient::ChatGrpcClient()
{
	auto& cfg = ConfigMgr::Instance();
	auto server_list = cfg["chatservers"]["name"];

	std::vector<std::string> words;

	std::stringstream ss(server_list);
	std::string word;

	while (std::getline(ss, word, ',')) {
		words.push_back(word);
	}

	for (auto& word : words) {
		if (cfg[word]["Name"].empty()) {
			continue;
		}

		_pools[cfg[word]["Name"]] = std::make_unique<ChatConPool>(5, cfg[word]["host"], cfg[word]["port"]);
	}

}

AddFriendRsp ChatGrpcClient::NotifyAddFriend(const AddFriendReq& req)
{
	auto to_uid = req.touid();
	std::string  uid_str = std::to_string(to_uid);

	AddFriendRsp rsp;
	return rsp;
}