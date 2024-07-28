#include "GateServer.h"

int main()
{
	try {
		auto& gCfgMgr = ConfigMgr::Instance();
		std::string gate_port_str = gCfgMgr["GateServer"]["port"];
		boost::asio::io_context io_context;
		boost::asio::signal_set singal_set(io_context, SIGINT, SIGTERM);
		singal_set.async_wait(
			[&io_context](const boost::system::error_code& error, int signal_number)
			{
				if (!error) io_context.stop();
			}
		);
		
		GateServer(io_context, gate_port_str).start();
		io_context.run();
	}
	catch (std::exception& e) {
		LOG_ERR("{}", e.what());
		return EXIT_FAILURE;
	}

	return 0;
}