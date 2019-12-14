#include "Highscores.h"

Highscores::Highscores(SDL_Renderer*& renderer) {
	_render = renderer;

	_position.push_back({ POS_RANK_X, POS_RANK_Y, DEFAULT_WIGHT, POS_Y });
	_position.push_back({ POS_RANK_X, POS_Y, DEFAULT_WIGHT, DEFAULT_HEIGHT });
	_position.push_back({ POS_RANK_X, POS_Y + DEFAULT_HEIGHT, DEFAULT_WIGHT, DEFAULT_HEIGHT });
	_position.push_back({ POS_RANK_X, POS_Y + DEFAULT_HEIGHT * 2, DEFAULT_WIGHT, DEFAULT_HEIGHT });
	_position.push_back({ POS_RANK_X, POS_Y + DEFAULT_HEIGHT * 3, DEFAULT_WIGHT, DEFAULT_HEIGHT });
	_position.push_back({ POS_RANK_X, POS_Y + DEFAULT_HEIGHT * 4, DEFAULT_WIGHT, DEFAULT_HEIGHT });
	_position.push_back({ POS_RANK_X, POS_Y + DEFAULT_HEIGHT * 5, DEFAULT_WIGHT, DEFAULT_HEIGHT });
	_position.push_back({ POS_RANK_X, POS_Y + DEFAULT_HEIGHT * 6, DEFAULT_WIGHT, DEFAULT_HEIGHT });
	_position.push_back({ POS_RANK_X, POS_Y + DEFAULT_HEIGHT * 7, DEFAULT_WIGHT, DEFAULT_HEIGHT });
	_position.push_back({ POS_RANK_X, POS_Y + DEFAULT_HEIGHT * 8, DEFAULT_WIGHT, DEFAULT_HEIGHT });
	_position.push_back({ POS_RANK_X, POS_Y + DEFAULT_HEIGHT * 9, DEFAULT_WIGHT, DEFAULT_HEIGHT });

	_ranks.push_back(Object::Object(_render, _position[0], "image//Rank//rank_empty.png"));//Menu rank
	_ranks.push_back(Object::Object(_render, _position[0], "image//Rank//rank.png"));
	_ranks.push_back(Object::Object(_render, _position[1], "image//Rank//rank_1_no.png"));//Rank 1
	_ranks.push_back(Object::Object(_render, _position[1], "image//Rank//rank_1_yes.png"));
	_ranks.push_back(Object::Object(_render, _position[2], "image//Rank//rank_2_no.png"));//Rank 2
	_ranks.push_back(Object::Object(_render, _position[2], "image//Rank//rank_2_yes.png"));
	_ranks.push_back(Object::Object(_render, _position[3], "image//Rank//rank_3_no.png"));//Rank 3
	_ranks.push_back(Object::Object(_render, _position[3], "image//Rank//rank_3_yes.png"));
	_ranks.push_back(Object::Object(_render, _position[4], "image//Rank//rank_4_no.png"));//Rank 4
	_ranks.push_back(Object::Object(_render, _position[4], "image//Rank//rank_4_yes.png"));
	_ranks.push_back(Object::Object(_render, {0,0,1280,720}, "image//background//bk.png"));

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
	//cout <<"\n"<< count << endl;

	_ranks[10].ShowImg();

	switch (count) {
	case 0:
		_ranks[0].ShowImg();
		break;
	case 1:
		_ranks[1].ShowImg(); 
		_ranks[2].ShowImg();
		break;
	case 2:
		_ranks[1].ShowImg();
		_ranks[3].ShowImg();
		_ranks[4].ShowImg();
		break;
	case 3:
		_ranks[1].ShowImg();
		_ranks[3].ShowImg();
		_ranks[5].ShowImg();
		_ranks[6].ShowImg();
		break;
	case 4:
		_ranks[1].ShowImg();
		_ranks[3].ShowImg();
		_ranks[5].ShowImg();
		_ranks[7].ShowImg();
		_ranks[8].ShowImg();
		break;
	default:
		_ranks[1].ShowImg();
		_ranks[3].ShowImg();
		_ranks[5].ShowImg();
		_ranks[7].ShowImg();
		_ranks[9].ShowImg();

		int i = 5;
		while (i != count) {
			_ranks[9].ShowImgWithRect(_position[i]);
			i++;
		}
		_ranks[8].ShowImgWithRect(_position[count]);
	}
	SDL_RenderPresent(_render);
	system("pause");
}
