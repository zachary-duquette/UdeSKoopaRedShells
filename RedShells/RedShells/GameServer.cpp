#include "GameServer.h"
#include "CellphoneController.h"
#include "Game.h"

GameServer::GameServer()
: m_socketListener{ &GameServer::Update, this }
, m_newConnection{ &GameServer::Listen, this }
, m_inGameSockets{}
, m_inQueueSockets{}
{
}

GameServer::~GameServer()
{
	m_socketListener.join();
	m_newConnection.join();
}

void GameServer::Update()
{
	while (true )//!Game::Get()->IsGameFinished())
	{
		for (int player = 0; player < m_inGameSockets.size(); ++player)
		{
			try
			{
				if (m_inGameSockets[player].first.mi_isAlive)
				{
					char message[100]{};
					m_inGameSockets[player].second.receive(boost::asio::buffer(&message, 100));
					std::string id{ message, 1};
					char* payload = message;
					//std::string payload{ p + 3 };
					if (id == "A") // Avg
					{
						float value = std::stof(payload + 1);
						m_inGameSockets[player].first.mi_playerController->UpdateValue(value);
						//if (m_inGameSockets[socket].first.mi_playerController->GetStatus() == Dead)
						//{
						//	m_inGameSockets[player].first.mi_isAlive = false;
						//	char answer[100];
						//	std::string answerMessage{ "End", "Dead" };
						//	std::copy(answerMessage.begin(), answerMessage.end(), answer);
						//	m_inGameSockets[player].second.send(boost::asio::buffer(&answer, answerMessage.size()));
						//}
						//if (m_inGameSockets[socket].first.mi_playerController->GetStatus() == Winner)
						//{
						//		m_inGameSockets[player].first.mi_isAlive = false;
						//		char answer[100];
						//		std::string answerMessage{ "End", "Winner" };
						//		std::copy(answerMessage.begin(), answerMessage.end(), answer);
						//		m_inGameSockets[player].second.send(boost::asio::buffer(&answer, answerMessage.size()));
						//}
					}
					else
					{
						m_inGameSockets[player].first.mi_isAlive = false;
						m_inGameSockets[player].second.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
						m_inGameSockets[player].second.close();
					}
				}

			}
			catch (boost::system::error_code ec)
			{
				std::cerr << ec.message() << std::endl;
				m_inGameSockets[player].first.mi_isAlive = false;
				m_inGameSockets[player].second.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
				m_inGameSockets[player].second.close();
				Update();
			}
		}
	}
}

void GameServer::AcceptSocket(tcp::socket& socket)
{
	char answer[100]{};
	Game* game = Game::Get();

	if (true )// game->CanPlayersJoin())
	{
		auto controller = new CellphoneController;
		int playerId = game->AddPlayer(controller);
		std::string answerMessage = "C" + std::to_string(playerId); // Col
		std::copy(answerMessage.begin(), answerMessage.end(), answer);

		socket.send(boost::asio::buffer(&answer, answerMessage.size()));
		m_inGameSockets.emplace_back(std::make_pair(Player{ true, controller }, std::move(socket)));
	}
	else
	{
		std::string answerMessage{ "Wai" };
		std::copy(answerMessage.begin(), answerMessage.end(), answer);

		socket.send(boost::asio::buffer(&answer, answerMessage.size()));
		m_inQueueSockets.emplace_back(std::move(socket));
	}

}

void GameServer::DenySocket(tcp::socket& socket)
{
	char answer[100]{};
	std::string answerMessage{ "D" }; // Denied
	std::copy(answerMessage.begin(), answerMessage.end(), answer);

	socket.send(boost::asio::buffer(&answer, answerMessage.size()));
	socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
	socket.close();
}

void GameServer::Listen()
{
	//stop condition...
	boost::asio::io_service io_service;
	tcp::acceptor acceptor(io_service, tcp::endpoint(boost::asio::ip::address::from_string("192.168.0.100"), 8779));
	for (;;)
	{
		tcp::socket newSocket(io_service);
		try
		{
			acceptor.accept(newSocket);
			//char message[100] {};
			//newSocket.receive(boost::asio::buffer(&message, 100));
			//std::string id{ message, 3 };
			//char* p = message;
			//std::string payload{ p + 3 };

			//if (id == "Joi")
			//{
			//	if (!Game::Get()->IsGameFull())
			//	{
			AcceptSocket(newSocket);
//				}
	//			else
		//		{
		//			DenySocket(newSocket);
		//		}
	//		}
	//		else
	//		{
	//			newSocket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
	//			newSocket.close();
	//		}
		}
		catch (boost::system::error_code ec)
		{
			std::cerr << ec.message() << std::endl;
			newSocket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
			newSocket.close();
			Listen();
		}
	}
}


//std::string GameServer::WriteJson(std::string id, std::string value)
//{
//	boost::property_tree::ptree pt{};
//	pt.put(id, value);
//	std::ostringstream buf{};
//	boost::property_tree::write_json(buf, pt, false);
//	return buf.str();
//}
//
//boost::property_tree::ptree GameServer::ReadJson(std::string json)
//{
//	boost::property_tree::ptree pt2{};
//	std::istringstream is{ json };
//	boost::property_tree::read_json(is, pt2);
//	return pt2;
//}

//
//void GameServer::NewConnection()
//{
//	try
//	{
//		char message[100] {};
//		m_newSocket->receive(boost::asio::buffer(&message, 100));
//		auto json = ReadJson(std::string{ message });
//
//		if (json.back().first == "")
//		{
//			if (true /*GameState.getNumPlayers() <= GameState.getMaxNumPlayers*/)
//			{
//				AcceptSocket();
//			}
//			else
//			{
//				DenySocket();
//			}
//		}
//		else
//		{
//			m_newSocket->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
//			m_newSocket->close();
//		}
//
//		*m_newSocket = tcp::socket{ m_ioService };
//		m_acceptor->async_accept(*m_newSocket, boost::bind(&GameServer::NewConnection, this));
//	}
//	catch (boost::system::error_code ec)
//	{
//		m_newSocket->shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
//		m_newSocket->close();
//		std::cerr << ec.message() << std::endl;
//		*m_newSocket = tcp::socket{ m_ioService };
//		m_acceptor->async_accept(*m_newSocket, boost::bind(&GameServer::NewConnection, this));
//	}
//}