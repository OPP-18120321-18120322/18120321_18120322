#include "MatchScore.h"


MatchScore::MatchScore(SDL_Renderer*& renderer) {
	_render = renderer;

	_number.push_back(Object::Object(_render, { 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT }, "image//number//Number0.png"));
	_number.push_back(Object::Object(_render, { 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT }, "image//number//Number1.png"));
	_number.push_back(Object::Object(_render, { 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT }, "image//number//Number2.png"));
	_number.push_back(Object::Object(_render, { 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT }, "image//number//Number3.png"));
	_number.push_back(Object::Object(_render, { 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT }, "image//number//Number4.png"));
	_number.push_back(Object::Object(_render, { 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT }, "image//number//Number5.png"));
	_number.push_back(Object::Object(_render, { 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT }, "image//number//Number6.png"));
	_number.push_back(Object::Object(_render, { 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT }, "image//number//Number7.png"));
	_number.push_back(Object::Object(_render, { 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT }, "image//number//Number8.png"));
	_number.push_back(Object::Object(_render, { 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT }, "image//number//Number9.png"));


	_position.push_back({ POS_HUNDRED_X, POS_Y, DEFAULT_WIDTH , DEFAULT_HEIGHT });
	_position.push_back({ POS_TEN_X, POS_Y, DEFAULT_WIDTH , DEFAULT_HEIGHT });
	_position.push_back({ POS_ONE_X, POS_Y, DEFAULT_WIDTH , DEFAULT_HEIGHT });

	for (int i = 0; i < 3; i++) {
		_scores[i] = 0;
	}

	
}

void MatchScore::CalcScore(int score) {
	//if (score < 10) {
	//	_scores[0] = _scores[1] = 0;
	//}

	//if (score < 100) {
	//	_scores[0] = 0;
	//}

	//if (score > 999) {
	//	//Do something.
	//}
	for (int i = 0; i < 3; i++) {
		_scores[i] = 0;
	}
	
	int i = 2;
	while (score > 0 && i >= 0) {
		_scores[i] = score % 10;
		//cout << "\n" << _scores[i];
		i--;
		score = score / 10;
	}
}

void MatchScore::ShowScore() {
	for (int i = 0; i < 3; i++) {
		//cout << _scores[i] << endl;
		_number[_scores[i]].ShowImgWithRect(_position[i]);
	}
}