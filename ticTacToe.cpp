#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>
#include <vector>
#include <ctime>
#include <chrono>
#include <thread>
#include <fstream>

bool inMenu = true;
bool yourTurn = true;
bool oc1 = false;
bool oc2 = false;
bool oc3 = false;
bool oc4 = false;
bool oc5 = false;
bool oc6 = false;
bool oc7 = false;
bool oc8 = false;
bool oc9 = false;
bool picked = false;
int cRound = 1;
int filled = 0;
int wins = 0;
int ties = 0;
int losses = 0;
bool plwin = false;
bool cwin = false;
bool pwin = false;
void drawNum(sf::RenderWindow& window, sf::Texture& font, int number, sf::Vector2f position);

std::vector<int> squares;

std::random_device rd;
std::mt19937 gen(rd());

sf::FloatRect first({ 768.f, 348.f }, { 132.f, 132.f });
sf::FloatRect second({ 912.f, 348.f }, { 132.f, 132.f });
sf::FloatRect third({ 1056.f, 348.f }, { 132.f, 132.f });

sf::FloatRect fourth({ 768.f, 492.f }, { 132.f, 132.f });
sf::FloatRect fifth({ 912.f, 492.f }, { 132.f, 132.f });
sf::FloatRect sixt({ 1056.f, 492.f }, { 132.f, 132.f });

sf::FloatRect seventh({ 768.f, 636.f }, { 132.f, 132.f });
sf::FloatRect eight({ 912.f, 636.f }, { 132.f, 132.f });
sf::FloatRect ninth({ 1056.f, 636.f }, { 132.f, 132.f });

sf::Vector2f sq1(816.f, 396.f);
sf::Vector2f sq2(960.f, 396.f);
sf::Vector2f sq3(1104.f, 396.f);
sf::Vector2f sq4(816.f, 540.f);
sf::Vector2f sq5(960.f, 540.f);
sf::Vector2f sq6(1104.f, 540.f);
sf::Vector2f sq7(816.f, 684.f);
sf::Vector2f sq8(960.f, 684.f);
sf::Vector2f sq9(1104.f, 684.f);

void round1(sf::Sprite& xSign, sf::Vector2f mappedMousePos, int& cRound, std::vector<int>& squares);
void round2(sf::Sprite& oSign, int& cRound);
void round3(sf::Sprite& x2, int& cRound, sf::Vector2f mappedMousePos);
void round4(sf::Sprite& o2, int& cRound, int& c);
void round5(sf::Sprite& x3, int& cRound, sf::Vector2f mappedMousePos);
void round6(sf::Sprite& o3, int& cRound, int& c, int& p);
void round7(sf::Sprite& x4, int& cRound, sf::Vector2f mappedMousePos);
void round8(sf::Sprite& o4, int& cRound, int& c, int& p);
void round9(sf::Sprite& x5, int& cRound, sf::Vector2f mappedMousePos);
bool winc();
bool winpl();
int checkpl(int& c);
int checkc(int& p);
int generate();
void load();
void save();
sf::IntRect getDigitRect(char digit);

int main() {

	load();

	int c = 0;
	int p = 0;
	bool pb = false;

	sf::RenderWindow window(sf::VideoMode({ 1920u, 1080u }), "Tic tac toe", sf::Style::Default, sf::State::Windowed);
	window.setFramerateLimit(60);

	std::cout << "Please don't close this window. This is for debuging.\nIf there is a problem it will appear here. Example: Could not load example texture\n\n";
	std::cout << "Problems: \n";

	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("background.png")) {
		std::cout << "Could not load game background!\n";
		pb = true;
	}
	sf::Texture background2Texture;
	if (!background2Texture.loadFromFile("background2.png")) {
		std::cout << "Could not load menu background!\n";
		pb = true;
	}
	sf::Texture playTexture;
	if (!playTexture.loadFromFile("playButton.png")) {
		std::cout << "Could not load play button texture!\n";
		pb = true;
	}
	sf::Texture exitTexture;
	if (!exitTexture.loadFromFile("exitButton.png")) {
		std::cout << "Could not load exit button texture!\n";
		pb = true;
	}
	sf::Texture boardTexture;
	if (!boardTexture.loadFromFile("board.png")) {
		std::cout << "Could not load board texture!\n";
		pb = true;
	}
	sf::Texture xTexture;
	if (!xTexture.loadFromFile("x.png")) {
		std::cout << "Could not load x texture!\n";
		pb = true;
	}
	sf::Texture oTexture;
	if (!oTexture.loadFromFile("o.png")) {
		std::cout << "Could not load o texture!\n";
		pb = true;
	}
	sf::Texture lTexture;
	if (!lTexture.loadFromFile("lost.png")) {
		std::cout << "Could not load lose texture!\n";
		pb = true;
	}
	sf::Texture wTexture;
	if (!wTexture.loadFromFile("won.png")) {
		std::cout << "Could not load win texture!\n";
		pb = true;
	}
	sf::Texture tTexture;
	if (!tTexture.loadFromFile("tie.png")) {
		std::cout << "Could not load tie texture!\n";
		pb = true;
	}
	sf::Texture font;
	if (!font.loadFromFile("font.png")) {
		std::cout << "Could not load font texture!\n";
		pb = true;
	}
	sf::Texture stats;
	if (!stats.loadFromFile("stats.png")) {
		std::cout << "Could not load stats texture!\n";
		pb = true;
	}
	sf::Texture lossesT;
	if (!lossesT.loadFromFile("losses.png")) {
		std::cout << "Could not load losses texture!\n";
		pb = true;
	}
	sf::Texture winsT;
	if (!winsT.loadFromFile("wins.png")) {
		std::cout << "Could not load wins texture!\n";
		pb = true;
	}
	sf::Texture tiesT;
	if (!tiesT.loadFromFile("ties.png")) {
		std::cout << "Could not load ties texture!\n";
		pb = true;
	}
	sf::Texture resetT;
	if (!resetT.loadFromFile("reset.png")) {
		std::cout << "Could not load reset texture!\n";
		pb = true;
	}

	sf::Music music;
	if (!music.openFromFile("chilllofir-loop.ogg")) {
		std::cout << " Couldn't load music!\n";
		pb = true;
	}
	if (!pb) {
		std::cout << "None :]\n";
	}

	music.setLooping(true);
	music.play();

	backgroundTexture.setSmooth(false);
	background2Texture.setSmooth(false);
	playTexture.setSmooth(false);
	exitTexture.setSmooth(false);
	boardTexture.setSmooth(false);
	oTexture.setSmooth(false);
	xTexture.setSmooth(false);
	lTexture.setSmooth(false);
	wTexture.setSmooth(false);
	tTexture.setSmooth(false);
	font.setSmooth(false);
	stats.setSmooth(false);
	winsT.setSmooth(false);
	lossesT.setSmooth(false);
	tiesT.setSmooth(false);
	resetT.setSmooth(false);

	sf::Sprite background(backgroundTexture);
	sf::Sprite menuBackground(background2Texture);
	sf::Sprite playButton(playTexture);
	sf::Sprite exitButton(exitTexture);
	sf::Sprite board(boardTexture);
	sf::Sprite oSign(oTexture);
	sf::Sprite xSign(xTexture);
	sf::Sprite lost(lTexture);
	sf::Sprite win(wTexture);
	sf::Sprite tie(tTexture);
	sf::Sprite statsB(stats);
	sf::Sprite winsS(winsT);
	sf::Sprite lossesS(lossesT);
	sf::Sprite tiesS(tiesT);
	sf::Sprite reset(resetT);

	background.setScale({ 8.f, 8.f });
	menuBackground.setScale({ 8.f,8.f });
	playButton.setScale({ 8.f, 8.f });
	exitButton.setScale({ 8.f, 8.f });
	board.setScale({ 12.f, 12.f });
	oSign.setScale({ 12.f, 12.f });
	xSign.setScale({ 12.f, 12.f });
	lost.setScale({ 12.f, 12.f });
	win.setScale({12.f, 12.f});
	tie.setScale({ 12.f, 12.f });
	statsB.setScale({ 8.f, 8.f });
	winsS.setScale({ 12.f, 12.f });
	lossesS.setScale({ 12.f, 12.f });
	tiesS.setScale({ 12.f, 12.f });
	reset.setScale({ 8.f, 8.f });

	playButton.setOrigin({ 18.f, 5.5f });
	exitButton.setOrigin({ 13.f, 4.5f });
	board.setOrigin({ 19.5f, 19.5f });
	oSign.setOrigin({ 3.5f, 3.5f });
	xSign.setOrigin({ 3.5f, 3.5f });
	lost.setOrigin({ 15.5f, 7.5f });
	win.setOrigin({ 15.5f, 7.5f });
	tie.setOrigin({ 10.f, 5.f });
	statsB.setOrigin({ 18.f, 5.5f });
	winsS.setOrigin({ 11.f, 2.5f });
	lossesS.setOrigin({ 15.5f, 2.5f });
	tiesS.setOrigin({ 9.f, 2.5f });
	reset.setOrigin({ 17.f, 5.5f });

	playButton.setPosition({ 960.f, 500.f });
	exitButton.setPosition({ 965.f, 800.f });
	board.setPosition({ 960.f, 540.f });
	xSign.setPosition({ 2000.f, 1500.f });
	oSign.setPosition({ 2000.f, 1500.f });
	lost.setPosition({ 960.f, 540.f });
	win.setPosition({ 960.f, 540.f });
	tie.setPosition({ 960.f, 540.f });
	statsB.setPosition({ 960.f, 650.f });
	winsS.setPosition({ 960.f, 200.f });
	lossesS.setPosition({ 960.f, 300.f });
	tiesS.setPosition({ 960.f, 400.f });
	reset.setPosition({ 960.f, 700.f });

	sf::Sprite x2 = xSign;
	sf::Sprite x3 = xSign;
	sf::Sprite x4 = xSign;
	sf::Sprite x5 = xSign;

	x2.setOrigin({ 3.5f, 3.5f });
	x3.setOrigin({ 3.5f, 3.5f });
	x4.setOrigin({ 3.5f, 3.5f });
	x5.setOrigin({ 3.5f, 3.5f });

	sf::Sprite o2 = oSign;
	sf::Sprite o3 = oSign;
	sf::Sprite o4 = oSign;

	o2.setOrigin({ 3.5f, 3.5f });
	o3.setOrigin({ 3.5f, 3.5f });
	o4.setOrigin({ 3.5f, 3.5f });

	sf::Sprite exitB = exitButton;

	exitB.setOrigin({ 13.f, 4.5f });
	exitB.setPosition({ 965.f, 600.f });

	sf::Clock clock;
	sf::Clock end;
	bool wait = false;
	bool gameOver = false;
	bool inst = false;

	while (window.isOpen()) {
		while (const std::optional ev = window.pollEvent()) {
			if (ev->is<sf::Event::Closed>()) {
				window.close();
			}

			if (const sf::Event::MouseButtonPressed* mouseClicked = ev->getIf<sf::Event::MouseButtonPressed>()) {
				if (mouseClicked->button == sf::Mouse::Button::Left) {

					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					sf::Vector2f mappedMousePos = window.mapPixelToCoords(mousePos);

					if (inMenu) {
						if (exitButton.getGlobalBounds().contains(mappedMousePos)) {
							window.close();
						}

						if (playButton.getGlobalBounds().contains(mappedMousePos)) {
							inMenu = false;
							inst = false;
						}
						if (statsB.getGlobalBounds().contains(mappedMousePos)) {
							inst = true;
							inMenu = false;
						}
					}

					else if (inst) {
						if (exitB.getGlobalBounds().contains(mappedMousePos)) {
							inst = false;
							inMenu = true;
						}
						if (reset.getGlobalBounds().contains(mappedMousePos)) {
							wins = 0;
							ties = 0;
							losses = 0;
							save();
						}
					}

					else {
						if (cwin == false && pwin == false) {
							if (cRound == 1) {
								round1(xSign, mappedMousePos, cRound, squares);
								wait = true;
								clock.restart();
							}
							if (cRound == 3) {
								round3(x2, cRound, mappedMousePos);
								wait = true;
								clock.restart();
							}
							if (cRound == 5) {
								round5(x3, cRound, mappedMousePos);
								wait = true;
								clock.restart();
							}
							if (cRound == 7) {
								round7(x4, cRound, mappedMousePos);
								wait = true;
								clock.restart();
							}
							if (cRound == 9) {
								round9(x5, cRound, mappedMousePos);
							}
						}
					}
				}
			}
		}
		if (cwin == false && pwin == false) {
			if (!inMenu && !inst) {
				winpl();

				if (pwin) {
					continue;
				}
				if (filled > 9) {
					continue;
				}
				if (wait && clock.getElapsedTime().asSeconds() > 1.f) {

					if (cRound == 2) {
						round2(oSign, cRound);
						wait = false;
						winc();
					}
					else if (cRound == 4) {
						round4(o2, cRound, c);
						wait = false;
						winc();
					}
					else if (cRound == 6) {
						round6(o3, cRound, c, p);
						wait = false;
						winc();
					}
					else if (cRound == 8) {
						round8(o4, cRound, c, p);
						wait = false;
						winc();
					}
				}
			}
		}

		window.clear(sf::Color::Black);
		if (inMenu && !inst) {
			window.draw(menuBackground);
			window.draw(playButton);
			window.draw(statsB);
			window.draw(exitButton);
		}

		if (inst && !inMenu) {
			window.draw(background);
			window.draw(winsS);
			window.draw(lossesS);
			window.draw(tiesS);
			window.draw(reset);
			window.draw(exitB);
			drawNum(window, font, wins, { 1200.f, 160.f });
			drawNum(window, font, losses, { 1200.f, 260.f });
			drawNum(window, font, ties, { 1200.f, 360.f });
		}

		if (!inMenu && !inst) {

			window.draw(background);
			window.draw(board);
			if (filled >= 1) {
				window.draw(xSign);
			}
			if (filled >= 2) {
				window.draw(oSign);
			}
			if (filled >= 3) {
				window.draw(x2);
			}
			if (filled >= 4) {
				window.draw(o2);
			}
			if (filled >= 5) {
				window.draw(x3);
			}
			if (filled >= 6) {
				window.draw(o3);
			}
			if (filled >= 7) {
				window.draw(x4);
			}
			if (filled >= 8) {
				window.draw(o4);
			}
			if (filled >= 9) {
				window.draw(x5);
			}

			if ((cRound == 10 && pwin == false && cwin == false) || pwin == true || cwin == true) {

				if (!gameOver) {

					if (cwin) {
						losses++;
						save();
					}
					if (pwin) {
						wins++;
						save();
					}
					if (cRound == 10 && pwin == false && cwin == false) {
						ties++;
						save();
					}

					end.restart();
					gameOver = true;
				}

				if (cRound == 10 && pwin == false && cwin == false) {
					window.draw(tie);
				}
				if (cwin == true) {
					window.draw(lost);
				}
				if (pwin == true) {
					window.draw(win);
				}

				if (end.getElapsedTime().asSeconds() > 2.f) {
					cRound = 1;
					filled = 0;
					squares.clear();
					oc1 = false;
					oc2 = false;
					oc3 = false;
					oc4 = false;
					oc5 = false;
					oc6 = false;
					oc7 = false;
					oc8 = false;
					oc9 = false;
					c = 0;
					p = 0;
					pwin = false;
					cwin = false;
					inMenu = true;
					gameOver = false;
				}
			}
		}
		window.display();

	}
	return 0;
}

int generate() {

	static std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr)));
	std::uniform_int_distribution<int> a(1, 9);

	return a(gen);
}

void round1(sf::Sprite& xSign, sf::Vector2f mappedMousePos, int& cRound, std::vector<int>& squares) {
	if (first.contains(mappedMousePos)) {
		xSign.setPosition(sq1);
		oc1 = true;
		cRound++;
		filled++;
		squares.push_back(1);
	}
	else if (second.contains(mappedMousePos)) {
		xSign.setPosition(sq2);
		oc2 = true;
		cRound++;
		filled++;
		squares.push_back(2);
	}
	else if (third.contains(mappedMousePos)) {
		xSign.setPosition(sq3);
		oc3 = true;
		cRound++;
		filled++;
		squares.push_back(3);
	}
	else if (fourth.contains(mappedMousePos)) {
		xSign.setPosition(sq4);
		oc4 = true;
		cRound++;
		filled++;
		squares.push_back(4);
	}
	else if (fifth.contains(mappedMousePos)) {
		xSign.setPosition(sq5);
		oc5 = true;
		cRound++;
		filled++;
		squares.push_back(5);
	}
	else if (sixt.contains(mappedMousePos)) {
		xSign.setPosition(sq6);
		oc6 = true;
		cRound++;
		filled++;
		squares.push_back(6);
	}
	else if (seventh.contains(mappedMousePos)) {
		xSign.setPosition(sq7);
		oc7 = true;
		cRound++;
		filled++;
		squares.push_back(7);
	}
	else if (eight.contains(mappedMousePos)) {
		xSign.setPosition(sq8);
		oc8 = true;
		cRound++;
		filled++;
		squares.push_back(8);
	}
	else if (ninth.contains(mappedMousePos)) {
		xSign.setPosition(sq9);
		oc9 = true;
		cRound++;
		filled++;
		squares.push_back(9);
	}
}

void round2(sf::Sprite& oSign, int& cRound) {

	bool right = false;
	int f;

	do {
		f = generate();

		if (f != squares[0]) {
			right = true;
		}

	} while (right == false);

	if (f == 1) {
		oSign.setPosition(sq1);
		squares.push_back(1);
		oc1 = true;
	}
	else if (f == 2) {
		oSign.setPosition(sq2);
		squares.push_back(2);
		oc2 = true;
	}
	else if (f == 3) {
		oSign.setPosition(sq3);
		squares.push_back(3);
		oc3 = true;
	}
	else if (f == 4) {
		oSign.setPosition(sq4);
		squares.push_back(4);
		oc4 = true;
	}
	else if (f == 5) {
		oSign.setPosition(sq5);
		squares.push_back(5);
		oc5 = true;
	}
	else if (f == 6) {
		oSign.setPosition(sq6);
		squares.push_back(6);
		oc6 = true;
	}
	else if (f == 7) {
		oSign.setPosition(sq7);
		squares.push_back(7);
		oc7 = true;
	}
	else if (f == 8) {
		oSign.setPosition(sq8);
		squares.push_back(8);
		oc8 = true;
	}
	else if (f == 9) {
		oSign.setPosition(sq9);
		squares.push_back(9);
		oc9 = true;
	}

	cRound++;
	filled++;

}

int checkpl(int& c) {

	std::vector<int> playerSquares;

	if (squares.size() > 0) playerSquares.push_back(squares[0]);
	if (squares.size() > 2) playerSquares.push_back(squares[2]);
	if (squares.size() > 4) playerSquares.push_back(squares[4]);
	if (squares.size() > 6) playerSquares.push_back(squares[6]);
	if (squares.size() > 8) playerSquares.push_back(squares[8]);


	if (playerSquares.size() < 2) {
		return 0;
	}

	for (size_t i = 0; i < playerSquares.size(); i++) {
		for (size_t j = i + 1; j < playerSquares.size(); j++) {
			int a = playerSquares[i];
			int b = playerSquares[j];

			if (((a == 1 && b == 2) || (b == 1 && a == 2)) && !oc3) {
				c = 3;
				return c;
			}
			else if (((a == 1 && b == 3) || (b == 1 && a == 3)) && !oc2) {
				c = 2;
				return c;
			}
			else if (((a == 2 && b == 3) || (b == 2 && a == 3)) && !oc1) {
				c = 1;
				return c;
			}
			else if (((a == 4 && b == 5) || (b == 4 && a == 5)) && !oc6) {
				c = 6;
				return c;
			}
			else if (((a == 4 && b == 6) || (b == 4 && a == 6)) && !oc5) {
				c = 5;
				return c;
			}
			else if (((a == 5 && b == 6) || (b == 5 && a == 6)) && !oc4) {
				c = 4;
				return c;
			}
			else if (((a == 7 && b == 8) || (b == 7 && a == 8)) && !oc9) {
				c = 9;
				return c;
			}
			else if (((a == 8 && b == 9) || (b == 8 && a == 9)) && !oc7) {
				c = 7;
				return c;
			}
			else if (((a == 7 && b == 9) || (b == 7 && a == 9)) && !oc8) {
				c = 8;
				return c;
			}
			else if (((a == 1 && b == 4) || (b == 1 && a == 4)) && !oc7) {
				c = 7;
				return c;
			}
			else if (((a == 1 && b == 7) || (b == 1 && a == 7)) && !oc4) {
				c = 4;
				return c;
			}
			else if (((a == 4 && b == 7) || (b == 4 && a == 7)) && !oc1) {
				c = 1;
				return c;
			}
			else if (((a == 2 && b == 5) || (b == 2 && a == 5)) && !oc8) {
				c = 8;
				return c;
			}
			else if (((a == 2 && b == 8) || (b == 2 && a == 8)) && !oc5) {
				c = 5;
				return c;
			}
			else if (((a == 5 && b == 8) || (b == 5 && a == 8)) && !oc2) {
				c = 2;
				return c;
			}
			else if (((a == 3 && b == 6) || (b == 3 && a == 6)) && !oc9) {
				c = 9;
				return c;
			}
			else if (((a == 3 && b == 9) || (b == 3 && a == 9)) && !oc6) {
				c = 6;
				return c;
			}
			else if (((a == 6 && b == 9) || (b == 6 && a == 9)) && !oc3) {
				c = 3;
				return c;
			}
			else if (((a == 1 && b == 5) || (b == 1 && a == 5)) && !oc9) {
				c = 9;
				return c;
			}
			else if (((a == 1 && b == 9) || (b == 1 && a == 9)) && !oc5) {
				c = 5;
				return c;
			}
			else if (((a == 5 && b == 9) || (b == 5 && a == 9)) && !oc1) {
				c = 1;
				return c;
			}
			else if (((a == 3 && b == 5) || (b == 3 && a == 5)) && !oc7) {
				c = 7;
				return c;
			}
			else if (((a == 3 && b == 7) || (b == 3 && a == 7)) && !oc5) {
				c = 5;
				return c;
			}
			else if (((a == 5 && b == 7) || (b == 5 && a == 7)) && !oc3) {
				c = 3;
				return c;
			}

		}
	}

	return c = 0;

}

void round3(sf::Sprite& x2, int& cRound, sf::Vector2f mappedMousePos) {
	if (first.contains(mappedMousePos) && !oc1) {
		x2.setPosition(sq1);
		oc1 = true;
		cRound++;
		filled++;
		squares.push_back(1);
	}
	else if (second.contains(mappedMousePos) && !oc2) {
		x2.setPosition(sq2);
		oc2 = true;
		cRound++;
		filled++;
		squares.push_back(2);
	}
	else if (third.contains(mappedMousePos) && !oc3) {
		x2.setPosition(sq3);
		oc3 = true;
		cRound++;
		filled++;
		squares.push_back(3);
	}
	else if (fourth.contains(mappedMousePos) && !oc4) {
		x2.setPosition(sq4);
		oc4 = true;
		cRound++;
		filled++;
		squares.push_back(4);
	}
	else if (fifth.contains(mappedMousePos) && !oc5) {
		x2.setPosition(sq5);
		oc5 = true;
		cRound++;
		filled++;
		squares.push_back(5);
	}
	else if (sixt.contains(mappedMousePos) && !oc6) {
		x2.setPosition(sq6);
		oc6 = true;
		cRound++;
		filled++;
		squares.push_back(6);
	}
	else if (seventh.contains(mappedMousePos) && !oc7) {
		x2.setPosition(sq7);
		oc7 = true;
		cRound++;
		filled++;
		squares.push_back(7);
	}
	else if (eight.contains(mappedMousePos) && !oc8) {
		x2.setPosition(sq8);
		oc8 = true;
		cRound++;
		filled++;
		squares.push_back(8);
	}
	else if (ninth.contains(mappedMousePos) && !oc9) {
		x2.setPosition(sq9);
		oc9 = true;
		cRound++;
		filled++;
		squares.push_back(9);
	}
}

void round4(sf::Sprite& o2, int& cRound, int& c) {

	int g;
	bool r;	

	c = checkpl(c);

	if (c != 0) {
		if (c == 1) {
			o2.setPosition(sq1);
			oc1 = true;
			cRound++;
			filled++;
			squares.push_back(1);
		}
		else if (c == 2) {
			o2.setPosition(sq2);
			oc2 = true;
			cRound++;
			filled++;
			squares.push_back(2);
		}
		else if (c == 3) {
			o2.setPosition(sq3);
			oc3 = true;
			cRound++;
			filled++;
			squares.push_back(3);
		}
		else if (c == 4) {
			o2.setPosition(sq4);
			oc4 = true;
			cRound++;
			filled++;
			squares.push_back(4);
		}
		else if (c == 5) {
			o2.setPosition(sq5);
			oc5 = true;
			cRound++;
			filled++;
			squares.push_back(5);
		}
		else if (c == 6) {
			o2.setPosition(sq6);
			oc6 = true;
			cRound++;
			filled++;
			squares.push_back(6);
		}
		else if (c == 7) {
			o2.setPosition(sq7);
			oc7 = true;
			cRound++;
			filled++;
			squares.push_back(7);
		}
		else if (c == 8) {
			o2.setPosition(sq8);
			oc8 = true;
			cRound++;
			filled++;
			squares.push_back(8);
		}
		else if (c == 9) {
			o2.setPosition(sq9);
			oc9 = true;
			cRound++;
			filled++;
			squares.push_back(9);
		}

	}
	else if (c == 0) {
		do {

			g = generate();
			r = true;

			for (int v = 0; v < squares.size(); v++) {
				if (g == squares[v]) {
					r = false;
					break;
				}
			}

		} while (r == false);

		if (g == 1) {
			o2.setPosition(sq1);
			squares.push_back(1);
			oc1 = true;
		}
		else if (g == 2) {
			o2.setPosition(sq2);
			squares.push_back(2);
			oc2 = true;
		}
		else if (g == 3) {
			o2.setPosition(sq3);
			squares.push_back(3);
			oc3 = true;
		}
		else if (g == 4) {
			o2.setPosition(sq4);
			squares.push_back(4);
			oc4 = true;
		}
		else if (g == 5) {
			o2.setPosition(sq5);
			squares.push_back(5);
			oc5 = true;
		}
		else if (g == 6) {
			o2.setPosition(sq6);
			squares.push_back(6);
			oc6 = true;
		}
		else if (g == 7) {
			o2.setPosition(sq7);
			squares.push_back(7);
			oc7 = true;
		}
		else if (g == 8) {
			o2.setPosition(sq8);
			squares.push_back(8);
			oc8 = true;
		}
		else if (g == 9) {
			o2.setPosition(sq9);
			squares.push_back(9);
			oc9 = true;
		}

		filled++;
		cRound++;

	}
}

void round5(sf::Sprite& x3, int& cRound, sf::Vector2f mappedMousePos) {
	if (first.contains(mappedMousePos) && !oc1) {
		x3.setPosition(sq1);
		oc1 = true;
		cRound++;
		filled++;
		squares.push_back(1);
	}
	else if (second.contains(mappedMousePos) && !oc2) {
		x3.setPosition(sq2);
		oc2 = true;
		cRound++;
		filled++;
		squares.push_back(2);
	}
	else if (third.contains(mappedMousePos) && !oc3) {
		x3.setPosition(sq3);
		oc3 = true;
		cRound++;
		filled++;
		squares.push_back(3);
	}
	else if (fourth.contains(mappedMousePos) && !oc4) {
		x3.setPosition(sq4);
		oc4 = true;
		cRound++;
		filled++;
		squares.push_back(4);
	}
	else if (fifth.contains(mappedMousePos) && !oc5) {
		x3.setPosition(sq5);
		oc5 = true;
		cRound++;
		filled++;
		squares.push_back(5);
	}
	else if (sixt.contains(mappedMousePos) && !oc6) {
		x3.setPosition(sq6);
		oc6 = true;
		cRound++;
		filled++;
		squares.push_back(6);
	}
	else if (seventh.contains(mappedMousePos) && !oc7) {
		x3.setPosition(sq7);
		oc7 = true;
		cRound++;
		filled++;
		squares.push_back(7);
	}
	else if (eight.contains(mappedMousePos) && !oc8) {
		x3.setPosition(sq8);
		oc8 = true;
		cRound++;
		filled++;
		squares.push_back(8);
	}
	else if (ninth.contains(mappedMousePos) && !oc9) {
		x3.setPosition(sq9);
		oc9 = true;
		cRound++;
		filled++;
		squares.push_back(9);
	}
}

int checkc(int& p) {

	std::vector<int> cSquares;

	if (squares.size() > 1) { 
		cSquares.push_back(squares[1]); 
	}
	if (squares.size() > 3) {
		cSquares.push_back(squares[3]);
	}
	if (squares.size() > 5) {
		cSquares.push_back(squares[5]);
	}
	if (squares.size() > 7) {
		cSquares.push_back(squares[7]);
	}
	if (cSquares.size() < 2) {
		return 0;
	}

	for (size_t v = 0; v < cSquares.size(); v++) {
		for (size_t h = v + 1; h < cSquares.size(); h++) {

			int a = cSquares[v];
			int b = cSquares[h];

			if (((a == 1 && b == 2) || (b == 1 && a == 2)) && !oc3) {
				p = 3;
				return p;
			}
			else if (((a == 1 && b == 3) || (b == 1 && a == 3)) && !oc2) {
				p = 2;
				return p;
			}
			else if (((a == 2 && b == 3) || (b == 2 && a == 3)) && !oc1) {
				p = 1;
				return p;
			}
			else if (((a == 4 && b == 5) || (b == 4 && a == 5)) && !oc6) {
				p = 6;
				return p;
			}
			else if (((a == 4 && b == 6) || (b == 4 && a == 6)) && !oc5) {
				p = 5;
				return p;
			}
			else if (((a == 5 && b == 6) || (b == 5 && a == 6)) && !oc4) {
				p = 4;
				return p;
			}
			else if (((a == 7 && b == 8) || (b == 7 && a == 8)) && !oc9) {
				p = 9;
				return p;
			}
			else if (((a == 8 && b == 9) || (b == 8 && a == 9)) && !oc7) {
				p = 7;
				return p;
			}
			else if (((a == 7 && b == 9) || (b == 7 && a == 9)) && !oc8) {
				p = 8;
				return p;
			}
			else if (((a == 1 && b == 4) || (b == 1 && a == 4)) && !oc7) {
				p = 7;
				return p;
			}
			else if (((a == 1 && b == 7) || (b == 1 && a == 7)) && !oc4) {
				p = 4;
				return p;
			}
			else if (((a == 4 && b == 7) || (b == 4 && a == 7)) && !oc1) {
				p = 1;
				return p;
			}
			else if (((a == 2 && b == 5) || (b == 2 && a == 5)) && !oc8) {
				p = 8;
				return p;
			}
			else if (((a == 2 && b == 8) || (b == 2 && a == 8)) && !oc5) {
				p = 5;
				return p;
			}
			else if (((a == 5 && b == 8) || (b == 5 && a == 8)) && !oc2) {
				p = 2;
				return p;
			}
			else if (((a == 3 && b == 6) || (b == 3 && a == 6)) && !oc9) {
				p = 9;
				return p;
			}
			else if (((a == 3 && b == 9) || (b == 3 && a == 9)) && !oc6) {
				p = 6;
				return p;
			}
			else if (((a == 6 && b == 9) || (b == 6 && a == 9)) && !oc3) {
				p = 3;
				return p;
			}
			else if (((a == 1 && b == 5) || (b == 1 && a == 5)) && !oc9) {
				p = 9;
				return p;
			}
			else if (((a == 1 && b == 9) || (b == 1 && a == 9)) && !oc5) {
				p = 5;
				return p;
			}
			else if (((a == 5 && b == 9) || (b == 5 && a == 9)) && !oc1) {
				p = 1;
				return p;
			}
			else if (((a == 3 && b == 5) || (b == 3 && a == 5)) && !oc7) {
				p = 7;
				return p;
			}
			else if (((a == 3 && b == 7) || (b == 3 && a == 7)) && !oc5) {
				p = 5;
				return p;
			}
			else if (((a == 5 && b == 7) || (b == 5 && a == 7)) && !oc3) {
				p = 3;
				return p;
			}
		}
	}

	return p = 0;

}

void round6(sf::Sprite& o3, int& cRound, int& c, int& p) {

	int a = checkc(p);
	int b = checkpl(c);

	int g;
	bool r;

	if (a != 0) {
		if (p == 1) {
			o3.setPosition(sq1);
			oc1 = true;
			cRound++;
			filled++;
			squares.push_back(1);
		}
		else if (p == 2) {
			o3.setPosition(sq2);
			oc2 = true;
			cRound++;
			filled++;
			squares.push_back(2);
		}
		else if (p == 3) {
			o3.setPosition(sq3);
			oc3 = true;
			cRound++;
			filled++;
			squares.push_back(3);
		}
		else if (p == 4) {
			o3.setPosition(sq4);
			oc4 = true;
			cRound++;
			filled++;
			squares.push_back(4);
		}
		else if (p == 5) {
			o3.setPosition(sq5);
			oc5 = true;
			cRound++;
			filled++;
			squares.push_back(5);
		}
		else if (p == 6) {
			o3.setPosition(sq6);
			oc6 = true;
			cRound++;
			filled++;
			squares.push_back(6);
		}
		else if (p == 7) {
			o3.setPosition(sq7);
			oc7 = true;
			cRound++;
			filled++;
			squares.push_back(7);
		}
		else if (p == 8) {
			o3.setPosition(sq8);
			oc8 = true;
			cRound++;
			filled++;
			squares.push_back(8);
		}
		else if (p == 9) {
			o3.setPosition(sq9);
			oc9 = true;
			cRound++;
			filled++;
			squares.push_back(9);
		}

	}
	else if (a == 0) {
		if (b != 0) {
			if (c == 1) {
				o3.setPosition(sq1);
				oc1 = true;
				cRound++;
				filled++;
				squares.push_back(1);
			}
			else if (c == 2) {
				o3.setPosition(sq2);
				oc2 = true;
				cRound++;
				filled++;
				squares.push_back(2);
			}
			else if (c == 3) {
				o3.setPosition(sq3);
				oc3 = true;
				cRound++;
				filled++;
				squares.push_back(3);
			}
			else if (c == 4) {
				o3.setPosition(sq4);
				oc4 = true;
				cRound++;
				filled++;
				squares.push_back(4);
			}
			else if (c == 5) {
				o3.setPosition(sq5);
				oc5 = true;
				cRound++;
				filled++;
				squares.push_back(5);
			}
			else if (c == 6) {
				o3.setPosition(sq6);
				oc6 = true;
				cRound++;
				filled++;
				squares.push_back(6);
			}
			else if (c == 7) {
				o3.setPosition(sq7);
				oc7 = true;
				cRound++;
				filled++;
				squares.push_back(7);
			}
			else if (c == 8) {
				o3.setPosition(sq8);
				oc8 = true;
				cRound++;
				filled++;
				squares.push_back(8);
			}
			else if (c == 9) {
				o3.setPosition(sq9);
				oc9 = true;
				cRound++;
				filled++;
				squares.push_back(9);
			}

		} 
		else if (b == 0) {
			do {

				g = generate();
				r = true;

				for (int v = 0; v < squares.size(); v++) {
					if (g == squares[v]) {
						r = false;
						break;
					}
				}

			} while (r == false);

			if (g == 1) {
				o3.setPosition(sq1);
				squares.push_back(1);
				oc1 = true;
			}
			else if (g == 2) {
				o3.setPosition(sq2);
				squares.push_back(2);
				oc2 = true;
			}
			else if (g == 3) {
				o3.setPosition(sq3);
				squares.push_back(3);
				oc3 = true;
			}
			else if (g == 4) {
				o3.setPosition(sq4);
				squares.push_back(4);
				oc4 = true;
			}
			else if (g == 5) {
				o3.setPosition(sq5);
				squares.push_back(5);
				oc5 = true;
			}
			else if (g == 6) {
				o3.setPosition(sq6);
				squares.push_back(6);
				oc6 = true;
			}
			else if (g == 7) {
				o3.setPosition(sq7);
				squares.push_back(7);
				oc7 = true;
			}
			else if (g == 8) {
				o3.setPosition(sq8);
				squares.push_back(8);
				oc8 = true;
			}
			else if (g == 9) {
				o3.setPosition(sq9);
				squares.push_back(9);
				oc9 = true;
			}

			filled++;
			cRound++;
		}

	}

}

void round7(sf::Sprite& x4, int& cRound, sf::Vector2f mappedMousePos) {
	if (first.contains(mappedMousePos) && !oc1) {
		x4.setPosition(sq1);
		oc1 = true;
		cRound++;
		filled++;
		squares.push_back(1);
	}
	else if (second.contains(mappedMousePos) && !oc2) {
		x4.setPosition(sq2);
		oc2 = true;
		cRound++;
		filled++;
		squares.push_back(2);
	}
	else if (third.contains(mappedMousePos) && !oc3) {
		x4.setPosition(sq3);
		oc3 = true;
		cRound++;
		filled++;
		squares.push_back(3);
	}
	else if (fourth.contains(mappedMousePos) && !oc4) {
		x4.setPosition(sq4);
		oc4 = true;
		cRound++;
		filled++;
		squares.push_back(4);
	}
	else if (fifth.contains(mappedMousePos) && !oc5) {
		x4.setPosition(sq5);
		oc5 = true;
		cRound++;
		filled++;
		squares.push_back(5);
	}
	else if (sixt.contains(mappedMousePos) && !oc6) {
		x4.setPosition(sq6);
		oc6 = true;
		cRound++;
		filled++;
		squares.push_back(6);
	}
	else if (seventh.contains(mappedMousePos) && !oc7) {
		x4.setPosition(sq7);
		oc7 = true;
		cRound++;
		filled++;
		squares.push_back(7);
	}
	else if (eight.contains(mappedMousePos) && !oc8) {
		x4.setPosition(sq8);
		oc8 = true;
		cRound++;
		filled++;
		squares.push_back(8);
	}
	else if (ninth.contains(mappedMousePos) && !oc9) {
		x4.setPosition(sq9);
		oc9 = true;
		cRound++;
		filled++;
		squares.push_back(9);
	}
}

void round8(sf::Sprite& o4, int& cRound, int& c, int& p) {

	int a = checkc(p);
	int b = checkpl(c);

	int g;
	bool r;

	if (a != 0) {
		if (p == 1) {
			o4.setPosition(sq1);
			oc1 = true;
			cRound++;
			filled++;
			squares.push_back(1);
		}
		else if (p == 2) {
			o4.setPosition(sq2);
			oc2 = true;
			cRound++;
			filled++;
			squares.push_back(2);
		}
		else if (p == 3) {
			o4.setPosition(sq3);
			oc3 = true;
			cRound++;
			filled++;
			squares.push_back(3);
		}
		else if (p == 4) {
			o4.setPosition(sq4);
			oc4 = true;
			cRound++;
			filled++;
			squares.push_back(4);
		}
		else if (p == 5) {
			o4.setPosition(sq5);
			oc5 = true;
			cRound++;
			filled++;
			squares.push_back(5);
		}
		else if (p == 6) {
			o4.setPosition(sq6);
			oc6 = true;
			cRound++;
			filled++;
			squares.push_back(6);
		}
		else if (p == 7) {
			o4.setPosition(sq7);
			oc7 = true;
			cRound++;
			filled++;
			squares.push_back(7);
		}
		else if (p == 8) {
			o4.setPosition(sq8);
			oc8 = true;
			cRound++;
			filled++;
			squares.push_back(8);
		}
		else if (p == 9) {
			o4.setPosition(sq9);
			oc9 = true;
			cRound++;
			filled++;
			squares.push_back(9);
		}

	}
	else if (a == 0) {
		if (b != 0) {
			if (c == 1) {
				o4.setPosition(sq1);
				oc1 = true;
				cRound++;
				filled++;
				squares.push_back(1);
			}
			else if (c == 2) {
				o4.setPosition(sq2);
				oc2 = true;
				cRound++;
				filled++;
				squares.push_back(2);
			}
			else if (c == 3) {
				o4.setPosition(sq3);
				oc3 = true;
				cRound++;
				filled++;
				squares.push_back(3);
			}
			else if (c == 4) {
				o4.setPosition(sq4);
				oc4 = true;
				cRound++;
				filled++;
				squares.push_back(4);
			}
			else if (c == 5) {
				o4.setPosition(sq5);
				oc5 = true;
				cRound++;
				filled++;
				squares.push_back(5);
			}
			else if (c == 6) {
				o4.setPosition(sq6);
				oc6 = true;
				cRound++;
				filled++;
				squares.push_back(6);
			}
			else if (c == 7) {
				o4.setPosition(sq7);
				oc7 = true;
				cRound++;
				filled++;
				squares.push_back(7);
			}
			else if (c == 8) {
				o4.setPosition(sq8);
				oc8 = true;
				cRound++;
				filled++;
				squares.push_back(8);
			}
			else if (c == 9) {
				o4.setPosition(sq9);
				oc9 = true;
				cRound++;
				filled++;
				squares.push_back(9);
			}

		}
		else if (b == 0) {
			do {

				g = generate();
				r = true;

				for (int v = 0; v < squares.size(); v++) {
					if (g == squares[v]) {
						r = false;
						break;
					}
				}

			} while (r == false);

			if (g == 1) {
				o4.setPosition(sq1);
				squares.push_back(1);
				oc1 = true;
			}
			else if (g == 2) {
				o4.setPosition(sq2);
				squares.push_back(2);
				oc2 = true;
			}
			else if (g == 3) {
				o4.setPosition(sq3);
				squares.push_back(3);
				oc3 = true;
			}
			else if (g == 4) {
				o4.setPosition(sq4);
				squares.push_back(4);
				oc4 = true;
			}
			else if (g == 5) {
				o4.setPosition(sq5);
				squares.push_back(5);
				oc5 = true;
			}
			else if (g == 6) {
				o4.setPosition(sq6);
				squares.push_back(6);
				oc6 = true;
			}
			else if (g == 7) {
				o4.setPosition(sq7);
				squares.push_back(7);
				oc7 = true;
			}
			else if (g == 8) {
				o4.setPosition(sq8);
				squares.push_back(8);
				oc8 = true;
			}
			else if (g == 9) {
				o4.setPosition(sq9);
				squares.push_back(9);
				oc9 = true;
			}

			filled++;
			cRound++;
		}

	}
}

void round9(sf::Sprite& x5, int& cRound, sf::Vector2f mappedMousePos) {
	if (first.contains(mappedMousePos) && !oc1) {
		x5.setPosition(sq1);
		oc1 = true;
		cRound++;
		filled++;
		squares.push_back(1);
	}
	else if (second.contains(mappedMousePos) && !oc2) {
		x5.setPosition(sq2);
		oc2 = true;
		cRound++;
		filled++;
		squares.push_back(2);
	}
	else if (third.contains(mappedMousePos) && !oc3) {
		x5.setPosition(sq3);
		oc3 = true;
		cRound++;
		filled++;
		squares.push_back(3);
	}
	else if (fourth.contains(mappedMousePos) && !oc4) {
		x5.setPosition(sq4);
		oc4 = true;
		cRound++;
		filled++;
		squares.push_back(4);
	}
	else if (fifth.contains(mappedMousePos) && !oc5) {
		x5.setPosition(sq5);
		oc5 = true;
		cRound++;
		filled++;
		squares.push_back(5);
	}
	else if (sixt.contains(mappedMousePos) && !oc6) {
		x5.setPosition(sq6);
		oc6 = true;
		cRound++;
		filled++;
		squares.push_back(6);
	}
	else if (seventh.contains(mappedMousePos) && !oc7) {
		x5.setPosition(sq7);
		oc7 = true;
		cRound++;
		filled++;
		squares.push_back(7);
	}
	else if (eight.contains(mappedMousePos) && !oc8) {
		x5.setPosition(sq8);
		oc8 = true;
		cRound++;
		filled++;
		squares.push_back(8);
	}
	else if (ninth.contains(mappedMousePos) && !oc9) {
		x5.setPosition(sq9);
		oc9 = true;
		cRound++;
		filled++;
		squares.push_back(9);
	}
}

bool winc() {

	std::vector<int> cmoves;

	if (squares.size() > 1) {
		cmoves.push_back(squares[1]);
	}
	if (squares.size() > 3) {
		cmoves.push_back(squares[3]);
	}
	if (squares.size() > 5) {
		cmoves.push_back(squares[5]);
	}
	if (squares.size() > 7) {
		cmoves.push_back(squares[7]);
	}

	if (cmoves.size() < 3) {
		cwin = false;
		return cwin;
	}

	for (size_t q = 0; q < cmoves.size(); q++) {
		for (size_t w = q + 1; w < cmoves.size(); w++) {
			for (size_t e = w + 1; e < cmoves.size(); e++) {
				int a = cmoves[q];
				int b = cmoves[w];
				int c = cmoves[e];

				if ((a == 1 && b == 2 && c == 3) || (a == 1 && b == 3 && c == 2) || (a == 2 && b == 1 && c == 3) || (a == 2 && b == 3 && c == 1) || (a == 3 && b == 1 && c == 2) || (a == 3 && b == 2 && c == 1)) {
					cwin = true;
					return cwin;
				}
				else if ((a == 4 && b == 5 && c == 6) || (a == 4 && b == 6 && c == 5) || (a == 5 && b == 4 && c == 6) || (a == 5 && b == 6 && c == 4) || (a == 6 && b == 4 && c == 5) || (a == 6 && b == 5 && c == 4)) {
					cwin = true;
					return cwin;
				}
				else if ((a == 7 && b == 8 && c == 9) || (a == 7 && b == 9 && c == 8) || (a == 8 && b == 7 && c == 9) || (a == 8 && b == 9 && c == 7) || (a == 9 && b == 7 && c == 8) || (a == 9 && b == 8 && c == 7)) {
					cwin = true;
					return cwin;
				}
				else if ((a == 1 && b == 5 && c == 9) || (a == 1 && b == 9 && c == 5) || (a == 5 && b == 1 && c == 9) || (a == 5 && b == 9 && c == 1) || (a == 9 && b == 1 && c == 5) || (a == 9 && b == 5 && c == 1)) {
					cwin = true;
					return cwin;
				}
				else if ((a == 3 && b == 5 && c == 7) || (a == 3 && b == 7 && c == 5) || (a == 5 && b == 3 && c == 7) || (a == 5 && b == 7 && c == 3) || (a == 7 && b == 3 && c == 5) || (a == 7 && b == 5 && c == 3)) {
					cwin = true;
					return cwin;
				}
				else if ((a == 1 && b == 4 && c == 7) || (a == 1 && b == 7 && c == 4) || (a == 4 && b == 1 && c == 7) || (a == 4 && b == 7 && c == 1) || (a == 7 && b == 1 && c == 4) || (a == 7 && b == 4 && c == 1)) {
					cwin = true;
					return cwin;
				}
				else if ((a == 2 && b == 5 && c == 8) || (a == 2 && b == 8 && c == 5) || (a == 5 && b == 2 && c == 8) || (a == 5 && b == 8 && c == 2) || (a == 8 && b == 2 && c == 5) || (a == 8 && b == 5 && c == 2)) {
					cwin = true;
					return cwin;
				}
				else if ((a == 3 && b == 6 && c == 9) || (a == 3 && b == 9 && c == 6) || (a == 6 && b == 3 && c == 9) || (a == 6 && b == 9 && c == 3) || (a == 9 && b == 3 && c == 6) || (a == 9 && b == 6 && c == 3)) {
					cwin = true;
					return cwin;
				}
			}
		}
	}
	cwin = false;
	return cwin;
}

bool winpl() {
	std::vector<int> pmoves;

	if (squares.size() > 0) {
		pmoves.push_back(squares[0]);
	}
	if (squares.size() > 2) {
		pmoves.push_back(squares[2]);
	}
	if (squares.size() > 4) {
		pmoves.push_back(squares[4]);
	}
	if (squares.size() > 6) {
		pmoves.push_back(squares[6]);
	}
	if (squares.size() >= 9) {
		pmoves.push_back(squares[8]);
	}

	if (pmoves.size() < 3) {
		pwin = false;
		return pwin;
	}

	for (size_t q = 0; q < pmoves.size(); q++) {
		for (size_t w = q + 1; w < pmoves.size(); w++) {
			for (size_t e = w + 1; e < pmoves.size(); e++) {
				int a = pmoves[q];
				int b = pmoves[w];
				int c = pmoves[e];

				if ((a == 1 && b == 2 && c == 3) || (a == 1 && b == 3 && c == 2) || (a == 2 && b == 1 && c == 3) || (a == 2 && b == 3 && c == 1) || (a == 3 && b == 1 && c == 2) || (a == 3 && b == 2 && c == 1)) {
					pwin = true;
					return pwin;
				}
				else if ((a == 4 && b == 5 && c == 6) || (a == 4 && b == 6 && c == 5) || (a == 5 && b == 4 && c == 6) || (a == 5 && b == 6 && c == 4) || (a == 6 && b == 4 && c == 5) || (a == 6 && b == 5 && c == 4)) {
					pwin = true;
					return pwin;
				}
				else if ((a == 7 && b == 8 && c == 9) || (a == 7 && b == 9 && c == 8) || (a == 8 && b == 7 && c == 9) || (a == 8 && b == 9 && c == 7) || (a == 9 && b == 7 && c == 8) || (a == 9 && b == 8 && c == 7)) {
					pwin = true;
					return pwin;
				}
				else if ((a == 1 && b == 5 && c == 9) || (a == 1 && b == 9 && c == 5) || (a == 5 && b == 1 && c == 9) || (a == 5 && b == 9 && c == 1) || (a == 9 && b == 1 && c == 5) || (a == 9 && b == 5 && c == 1)) {
					pwin = true;
					return pwin;
				}
				else if ((a == 3 && b == 5 && c == 7) || (a == 3 && b == 7 && c == 5) || (a == 5 && b == 3 && c == 7) || (a == 5 && b == 7 && c == 3) || (a == 7 && b == 3 && c == 5) || (a == 7 && b == 5 && c == 3)) {
					pwin = true;
					return pwin;
				}
				else if ((a == 1 && b == 4 && c == 7) || (a == 1 && b == 7 && c == 4) || (a == 4 && b == 1 && c == 7) || (a == 4 && b == 7 && c == 1) || (a == 7 && b == 1 && c == 4) || (a == 7 && b == 4 && c == 1)) {
					pwin = true;
					return pwin;
				}
				else if ((a == 2 && b == 5 && c == 8) || (a == 2 && b == 8 && c == 5) || (a == 5 && b == 2 && c == 8) || (a == 5 && b == 8 && c == 2) || (a == 8 && b == 2 && c == 5) || (a == 8 && b == 5 && c == 2)) {
					pwin = true;
					return pwin;
				}
				else if ((a == 3 && b == 6 && c == 9) || (a == 3 && b == 9 && c == 6) || (a == 6 && b == 3 && c == 9) || (a == 6 && b == 9 && c == 3) || (a == 9 && b == 3 && c == 6) || (a == 9 && b == 6 && c == 3)) {
					pwin = true;
					return pwin;
				}
			}
		}
	}
	pwin = false;
	return pwin;
}

void load() {
	std::ifstream file("stats.txt");

	if (!file.is_open()) {
		return;
	}

	file >> wins;
	file >> losses;
	file >> ties;

	file.close();
}

void save() {
	std::ofstream file("stats.txt");

	if (!file.is_open()) {
		return;
	}

	file << wins << "\n";
	file << losses << "\n";
	file << ties << "\n";

	file.close();

}

sf::IntRect getDigitRect(char digit) {

	return sf::IntRect({ (digit - '0') * 6, 0 }, { 5, 6 });

}

void drawNum(sf::RenderWindow& window, sf::Texture& font, int number, sf::Vector2f position) {

	const int digitWidth = 5;
	const int gap = 1;
	const float scale = 12.f;

	sf::Sprite digit(font);
	digit.setScale({ scale, scale });

	std::string text = std::to_string(number);

	float x = position.x;

	for (char c : text) {
		digit.setTextureRect(getDigitRect(c));
		digit.setPosition({ x, position.y });

		window.draw(digit);

		x += digitWidth * scale;

	}

}