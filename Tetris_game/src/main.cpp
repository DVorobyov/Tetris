#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "Figure.h"
#pragma comment(lib, "ws2_32.lib")



#define SIZE_X 600
#define SIZE_Y 600


using namespace sf;


int main()
{
	// Loading of the required library
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		std::cout << "Error" << std::endl;
		exit(1);
	}
	int game = 0;
	while (true)
	{
		// Choose offline or online game
		if ((game != 1) || (game != 2))
		{
			std::cout << std::endl;
			std::cout << "Enter 1 for offline or 2 for online" << std::endl;
			std::cin >> game;
			std::cout << std::endl;
		}
		// Offline
		if (game==1)
		{
			int counter = 0;
			int score = 0;
			int old_state = 0;
			int new_state = 0;
			srand(time(NULL));
			Field field;
			// Window
			RenderWindow window(VideoMode(SIZE_X, SIZE_Y), "Tetris");
			Texture texture;
			Texture texture2;
			// Texture of an empty cell
			texture.loadFromFile("Empty.png");
			// Texture of an filled cell
			texture2.loadFromFile("Cell.png");
			Figure *figure = new Figure(field);
			int button = 0;
			Sprite *sprite[NUMBER];
			for (int i = 0; i < NUMBER; i++)
			{
				sprite[i] = new Sprite[NUMBER]();
			}
			// Filling in the right places whith sprites
			for (int i = 0; i < NUMBER; i++)
			{
				for (int j = 0; j < NUMBER; j++)
				{
					Sprite new_sprite(texture);
					sprite[i][j] = new_sprite;
					sprite[i][j].move(i*CELL_SIZE, j*CELL_SIZE);
				}
			}
			while (window.isOpen())
			{
				counter++;
				Event event;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
						window.close();
					if (event.type == Event::KeyPressed)
					{
						// Processing of pressing
						if (event.key.code == Keyboard::Right) button = 1;
						if (event.key.code == Keyboard::Left) button = 2;
						if (event.key.code == Keyboard::Up) button = 3;
						if (event.key.code == Keyboard::Down) button = 4;

					}
				}
				// Fall deceleration and processing of generation of the new figure
				if (counter % 500 == 0)
				{
					old_state = figure->cell[0]->y;
					figure->move_down(field);
					new_state = figure->cell[0]->y;
					if (old_state == new_state)
					{
						for (int i = 0; i < N; i++)
						{
							figure->cell[i]->isBlocked = true;
						}
						figure = new Figure(field);
					}
				}
				// Actions according to buttons
				if (button == 1)
				{
					figure->move_right(field);
					button = 0;
				}
				else if (button == 2)
				{
					figure->move_left(field);
					button = 0;
				}
				else if (button == 3)
				{
					figure->rotate(field);
					button = 0;
				}
				else if (button == 4)
				{
					figure->move_down(field);
					button = 0;
				}
				// Delete cells
				field.delete_cells(score);
				std::cout << score << std::endl;
				// End
				for (int i = 0; i < NUMBER; i++)
				{
					if (field.cell[i][0]->isBlocked)
					{
						game = 0;
					}
				}
				if (game == 0)
				{
					std::cout << std::endl;
					std::cout << "END." << std::endl;
					std::cout << "Your score: " << score << std::endl;
					window.close();
				}
				// Draw
				window.clear(Color::White);
				for (int i = 0; i < NUMBER; i++)
				{
					for (int j = 0; j < NUMBER; j++)
					{
						if (field.cell[i][j]->isEmpty == true)
						{
							sprite[i][j].setTexture(texture);
						}
						else
						{
							sprite[i][j].setTexture(texture2);
						}
					}
				}
				for (int i = 0; i < NUMBER; i++)
				{
					for (int j = 0; j < NUMBER; j++)
					{
						window.draw(sprite[i][j]);
					}
				}
				window.display();
			}
		}
		// Online
		else if (game == 2)
		{

			int counter = 0;
			int score = 0;
			int score2 = 0;
			int old_state = 0;
			int new_state = 0;
			srand(time(NULL));
			Field field;
			// Window
			RenderWindow window(VideoMode(SIZE_X * 2, SIZE_Y), "Tetris");
			Texture texture;
			Texture texture2;
			// Texture of an empty cell
			texture.loadFromFile("Empty.png");
			// Texture of an filled cell
			texture2.loadFromFile("Cell.png");
			Figure *figure = new Figure(field);
			int button = 0;
			Sprite *sprite[NUMBER];
			for (int i = 0; i < NUMBER; i++)
			{
				sprite[i] = new Sprite[NUMBER]();
			}
			// Filling in the right places of the first field whith sprites
			for (int i = 0; i < NUMBER; i++)
			{
				for (int j = 0; j < NUMBER; j++)
				{
					Sprite new_sprite(texture);
					sprite[i][j] = new_sprite;
					sprite[i][j].move(i*CELL_SIZE, j*CELL_SIZE);
				}
			}
			Sprite *sprite2[NUMBER];
			for (int i = 0; i < NUMBER; i++)
			{
				sprite2[i] = new Sprite[NUMBER]();
			}
			// Filling in the right places of the second field whith sprites
			for (int i = 0; i < NUMBER; i++)
			{
				for (int j = 0; j < NUMBER; j++)
				{
					Sprite new_sprite(texture);
					sprite2[i][j] = new_sprite;
					sprite2[i][j].move(i*CELL_SIZE + NUMBER * CELL_SIZE, j*CELL_SIZE);
				}
			}

			SOCKET sock = 0;
			int valread;
			// Socket address and other info about socket
			SOCKADDR_IN serv_addr;
			char converted_field[NUMBER*NUMBER+1];
			char buffer[NUMBER*NUMBER+1] = { 0 };
			if ((sock = socket(AF_INET, SOCK_STREAM, NULL)) < 0)
			{
				printf("\n Socket creation error \n");
				return -1;
			}
			serv_addr.sin_family = AF_INET;
			serv_addr.sin_port = htons(1111);
			// Convert IPv4 and IPv6 addresses from text to binary form 
			if (InetPton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
			{
				printf("\nInvalid address/ Address not supported \n");
				return -1;
			}
			if (connect(sock, (SOCKADDR *)&serv_addr, sizeof(serv_addr)) < 0)
			{
				printf("\nConnection Failed \n");
				return -1;
			}
			// Waiting for start
			while (buffer[0] != 's')
			{
				std::cout << "Waiting for the second partner..." << std::endl;
				valread = recv(sock, buffer, NUMBER*NUMBER + 1, 0);
			}
			if (buffer[0] == 's')
			{
				while (window.isOpen())
				{
					counter++;
					if (game == 0)
					{
						window.close();
					}
					Event event;
					while (window.pollEvent(event))
					{
						if (event.type == Event::Closed)
							window.close();
						if (event.type == Event::KeyPressed)
						{
							// Processing of pressing
							if (event.key.code == Keyboard::Right) button = 1;
							if (event.key.code == Keyboard::Left) button = 2;
							if (event.key.code == Keyboard::Up) button = 3;
						}
					}
					// Fall deceleration and processing of generation of the new figure
					if (counter % 250 == 0)
					{
						old_state = figure->cell[0]->y;
						figure->move_down(field);
						new_state = figure->cell[0]->y;
						if (old_state == new_state)
						{
							for (int i = 0; i < N; i++)
							{
								figure->cell[i]->isBlocked = true;
							}
							figure = new Figure(field);
						}
					}
					// Actions according to buttons
					if (button == 1)
					{
						figure->move_right(field);
						button = 0;
					}
					else if (button == 2)
					{
						figure->move_left(field);
						button = 0;
					}
					else if (button == 3)
					{
						figure->rotate(field);
						button = 0;
					}
					// Delete cells
					field.delete_cells(score);
					std::cout << score << std::endl;
					// End
					for (int i = 0; i < NUMBER; i++)
					{
						if (field.cell[i][0]->isBlocked)
						{
							game = 0;
						}
					}
					// Converting field for sending
					for (int i = 0; i < NUMBER; i++)
					{
						for (int j = 0; j < NUMBER; j++)
						{
							if (field.cell[i][j]->isEmpty)
							{
								converted_field[i*NUMBER + j] = 0;
							}
							else
							{
								converted_field[i*NUMBER + j] = 1;
							}
						}
					}
					converted_field[NUMBER*NUMBER] = score;
					// Sending state of field
					send(sock, converted_field, NUMBER*NUMBER+1, 0);
					// Reading state of the second field
					valread = recv(sock, buffer, NUMBER*NUMBER+1, 0);
					score2 = buffer[NUMBER*NUMBER];
					// Checking of enemy's end
					if (buffer[0] == 'e')
					{
						game = 0;
					}
					if (game == 0)
					{
						std::cout << std::endl;
						std::cout << "END." << std::endl;
						std::cout << "Your score: " << score << std::endl;
						std::cout << "Enemy score: " << score2 << std::endl;
						send(sock, "end\0", 4, 0);
						window.close();
					}
					// Draw
					window.clear(Color::White);
					for (int i = 0; i < NUMBER; i++)
					{
						for (int j = 0; j < NUMBER; j++)
						{
							if (field.cell[i][j]->isEmpty == true)
							{
								sprite[i][j].setTexture(texture);
							}
							else
							{
								sprite[i][j].setTexture(texture2);
							}
						}
					}
					for (int i = 0; i < NUMBER; i++)
					{
						for (int j = 0; j < NUMBER; j++)
						{
							if (buffer[i*NUMBER + j] == 0)
							{
								sprite2[i][j].setTexture(texture);
							}
							else
							{
								sprite2[i][j].setTexture(texture2);
							}
						}
					}
					for (int i = 0; i < NUMBER; i++)
					{
						for (int j = 0; j < NUMBER; j++)
						{
							window.draw(sprite[i][j]);
						}
					}
					for (int i = 0; i < NUMBER; i++)
					{
						for (int j = 0; j < NUMBER; j++)
						{
							window.draw(sprite2[i][j]);
						}
					}
					window.display();
				}
			}
		}
	}
	return 0;
}