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
	while (true)//!Game::Get()->IsGameFinished())
	{
		for (int player = 0; player < m_inGameSockets.size(); ++player)
		{
			try
			{
				if (m_inGameSockets[player].first.mi_isAlive)
				{
					char message[100];
					boost::asio::read(m_inGameSockets[player].second, boost::asio::buffer(&message, 100));
					std::string id{ message, 1 };
					char* payload = message;
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
			catch (...)
			{
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

	if (true)// game->CanPlayersJoin())
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
	boost::asio::io_service io_service;
	tcp::acceptor acceptor(io_service, tcp::endpoint(boost::asio::ip::address::from_string("192.168.0.100"), 8779));
	for (;;)
	{
		tcp::socket newSocket(io_service);
		try
		{
			acceptor.accept(newSocket);

			/*if (!Game::Get()->IsGameFull())
			{*/
				AcceptSocket(newSocket);
			/*}
			else
			{
				DenySocket(newSocket);
			}*/

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
