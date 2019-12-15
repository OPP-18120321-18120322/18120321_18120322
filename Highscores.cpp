
#include "Highscores.h"

Highscores::Highscores(SDL_Renderer*& renderer) {
	_render = renderer;

	_ranks.LoadImg(_render, { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT }, "image//material//highscores.png");
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
void Highscores::WriteFile(Info data,string name_file)
{
	ReadFile(name_file);
	for (int i = 0; i < _players.size(); i++)
	{
		if (stoi(data.score) > stoi(_players[i].score))
		{
			_players[i] = data;
			break;
		}
	}
	fstream file(name_file, ios::out);
	for (int i = 0; i < _players.size(); i++)
	{
		file << _players[i].name << "," << _players[i].score << endl;
	}
}
void Highscores::ShowHighscores() {
	int count = _players.size();
	bool isInRank = true;

	Object buttonclose;
	buttonclose.LoadImg(_render, {1040,620,150,85},"image//button//button_close 1.png");
	SDL_Event even;

	string fontPath = "Lib\\font\\MTO Yikes.ttf";
	vector<SDL_TextView> listText;
	while (isInRank)
	{

		while (SDL_PollEvent(&even))
		{
			
			if (buttonclose.ClickMouse(even))
			{
				isInRank = false;
			}
			
		}
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
		buttonclose.ShowImg();

		SDL_RenderPresent(_render);
	}
}
