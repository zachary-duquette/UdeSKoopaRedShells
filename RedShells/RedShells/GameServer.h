#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <thread>
#include <iostream>
#include <sstream>
#include <string>
#include <boost/foreach.hpp>
#include <algorithm>

using boost::asio::ip::tcp;
class CellphoneController;

class GameServer
{
public:
	GameServer();
	~GameServer();

private:

	struct Player
	{
		bool mi_isAlive;
		CellphoneController* mi_playerController;
	};

	std::thread m_socketListener;
	std::thread m_newConnection;

	void Listen();
	void Update();
	//void NewConnection();
	void AcceptSocket(tcp::socket& socket);
	void DenySocket(tcp::socket& socket);

	std::string WriteJson(std::string id, std::string value);
	boost::property_tree::ptree ReadJson(std::string json);

	std::vector<std::pair<Player, tcp::socket>>m_inGameSockets;
	std::vector<tcp::socket> m_inQueueSockets;
};