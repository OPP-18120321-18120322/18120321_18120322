#include "Highscores.h"

Highscores::Highscores(SDL_Renderer*& renderer) {
	_render = renderer;

	_ranks.LoadImg(_render, { 0,0,DEFAULT_WIGHT,DEFAULT_HEIGHT }, "image//Rank//highscores.png");
}

Info Highscores::ReadInfo(string info) {
	stringstream line(info);
	string temp;
	Info player;

	getline(line, temp, ',');
	player.name = temp;
	getline(line, temp, ',');
	player.score = temp;

	return player;
}

void Highscores::ReadFile(string name_file) {
	ifstream file_in(name_file);
	string line;
	Info player;

	if (file_in.fail()) {
		cout << "Khong the mo file" << endl;
		return;
	}

	//getline(file_in, line);//So player trong bang xep hang (top 10).

	while (!file_in.eof()) {
		getline(file_in, line);
		if (line != "") {
			_players.push_back(this->ReadInfo(line));
		}
	}
}

void Highscores::ShowHighscores() {
	int count = _players.size();

	string fontPath = "Lib\\font\\MTO Yikes.ttf";
	vector<SDL_TextView> listText;
	_ranks.ShowImg();

	for (int i = 0; i < count; i++) {
		listText.push_back(SDL_TextView(_render, 450, 82 + 61 * i, _players[i].name, 28, fontPath, { 0x00,0xFF,0xFF,0xFF }));
		listText[listText.size() - 1].SetCenterX(0, 1062);
		listText.push_back(SDL_TextView(_render, 770, 83 + 61 * i, _players[i].score, 28, fontPath, { 0x00,0xFF,0xFF,0xFF }));
		listText[listText.size() - 1].SetCenterX(0, 1590);
	}

	for (auto text : listText) {
		text.Show();
	}

	SDL_RenderPresent(_render);
	system("pause");
}
