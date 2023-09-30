#include <chess/chess_lib.h>
#include <iostream>
#include <windows.h>

using namespace std;
using namespace chess_space;

void insert_piece(ChessBoard& board) {
	cout << "������� ��� ������(������ - 1, ����� - 2, ���� - 3)"<< endl;
	int type;
	cin >> type;
	Type t = king;
	do {
		switch (type) {
		case 1:
			t = king;
			break;
		case 2:
			t = queen;
			break;
		case 3:
			t = knight;
			break;
		default:
			cout << "�������� ����. ������� ��� ������(������ - 1, ����� - 2, ���� - 3)" << endl;
			cout << "";
			cin >> type;
		}
	} while (type < 1 || type>4);
	cout << "������� ���� ������(������ - 1, ����� - 2)" << endl;
	int color;
	cin >> color;
	Color c = white;
	do {
		switch (color) {
		case 1:
			c = black;
			break;
		case 2:
			c = white;
			break;
		default:
			cout << "�������� ����. ������� ���� ������(������ - 1, ����� - 2)" << endl;
			cout << "";
			cin >> color;
		}
	} while (color < 1 || color>3);
	
	cout << "������� ���������� ����� ������, ������� ���������, ����� �����������" << endl;
	int vertical, horisontal;
	cin >> vertical >> horisontal;
	while (horisontal > 8 || horisontal < 1 || vertical > 8 || vertical < 1) {
		cout << "������� ������� ����������. ������� ���������� ����� ������, ������� ���������, ����� �����������" << endl;
		cout << "";
		cin >> vertical >> horisontal;
	}
	
	Position position = { vertical-1, horisontal-1 };
	ChessPiece piece = { t, c, position };
	try {
		board.insert_piece(piece);
	}
	catch (runtime_error& a) {
		cerr << a.what()<< endl;
	}
}

void delete_piece(ChessBoard& board) {
	cout << "������� ���������� ����� ������, ������� ���������, ����� �����������" << endl;
	int vertical, horisontal;
	cin >> vertical >> horisontal;
	board.delete_piece(vertical-1, horisontal-1);
}

void piece_move(ChessBoard& board) {
	cout << "������� ���������� ������ ����� ������, ������� ���������, ����� �����������" << endl;
	int vertical, horisontal;
	cin >> vertical >> horisontal;
	if (board.get_piece(vertical-1, horisontal-1).get_type() == square) {
		cout << "������ ������ �� �����" << endl;
		return;
	}
	cout << "������� ���������� ����������� ����� ������, ������� ���������, ����� �����������" << endl;
	int vertical_, horisontal_;
	cin >> vertical_ >> horisontal_;
	if (board.get_piece(vertical-1, horisontal-1).get_type() == king) {
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				if (board[i][j].get_type() == square) continue;
				if (board[i][j].piece_attack(board.get_piece(vertical_-1, horisontal_-1))) {
					cout << "������ �� ����� ������ ����" << endl;
					return;
				}
			}
		}
	}
		if (board.get_piece(vertical-1, horisontal-1).piece_attack(board.get_piece(vertical-1, horisontal-1)) == true) {
			board.delete_piece(vertical_-1, horisontal_-1);
			ChessPiece piece = { board.get_piece(vertical-1, horisontal-1).get_type(),board.get_piece(vertical-1, horisontal-1).get_color(), {vertical_-1, horisontal_-1} };
			board.insert_piece(piece);
			board.delete_piece(vertical-1, horisontal-1);
		}
		else {
			if (board.get_piece(vertical-1, horisontal-1).piece_move(vertical_-1, horisontal_-1) == true) {
				board.delete_piece(vertical_ - 1, horisontal_ - 1);
				ChessPiece piece = { board.get_piece(vertical-1, horisontal-1).get_type(),board.get_piece(vertical-1, horisontal-1).get_color(), {vertical_-1, horisontal_-1} };
				board.insert_piece(piece);
				board.delete_piece(vertical-1, horisontal-1);
			}
			else cout << "������ �� ����� ���� ������" << endl;
		}
	}

void search_piece_to_attack(ChessBoard& board) {
	cout << "������� ���������� ����� ������, ������� ���������, ����� �����������" << endl;
	int vertical, horisontal;
	cin >> vertical >> horisontal;
	--vertical;
	--horisontal;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (board[i][j].get_type() == square) continue;
			if (board[i][j].get_type() == king) {
				for (int k = 0; k < 8; ++k) {
					for (int m = 0; m < 8; ++m) {
						if (board[k][m].get_type() == square) continue;
						if (board[k][m].piece_attack(board.get_piece(vertical, horisontal))) break;
					}
				}
			}
			else {
				if (board[i][j].piece_attack(board.get_piece(vertical, horisontal)) == true) {
					board.delete_piece(vertical, horisontal);
					ChessPiece piece = { board[i][j].get_type(),board[i][j].get_color(), {vertical, horisontal} };
					board.insert_piece(piece);
					board.delete_piece(board[i][j].get_position().vertical, board[i][j].get_position().horisontal);
					return;
				}
				else {
					if (board.get_piece(vertical, horisontal).get_type() == square) {
						if (board[i][j].piece_move(vertical, horisontal) == true) {
							ChessPiece piece = { board[i][j].get_type(),board[i][j].get_color(), {vertical, horisontal} };
							board.insert_piece(piece);
							board.delete_piece(board[i][j].get_position().vertical, board[i][j].get_position().horisontal);
							return;
						}
					}
				}
			}
		}
	}
	cout << "����� �� ����� ������ ����" << endl;
}

void print_board(ChessBoard& board) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	cout << "�����->�������, ������->�������"<<endl;
	cout << "  ";

	for (int k = 0; k < 8; ++k) {
		cout << " " << k+1;
	}
	cout << endl;
	for (int i = 0; i < 8; ++i) {
		SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << i+1<<" ";
		for (int j = 0; j < 8; ++j) {
			if (board[i][j].get_type() == square) {
				if (board[i][j].get_color() == white) {
					SetConsoleTextAttribute(handle, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
					cout << "  ";
				}
				else { 
					SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
					cout << "  "; 
				}
				cout << "";
			}
			else {
				switch (board[i][j].get_type()) {
				case king: {
					if (board[i][j].get_color() == white) {
						SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
						cout << "KK";
						cout << "";
					}
					else {
						SetConsoleTextAttribute(handle, FOREGROUND_RED);
						cout << "KK";
						cout << "";
					}
					break;
				}
				case knight: {
					if (board[i][j].get_color() == white) {
						SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
						cout << " K";
						cout << "";
					}
					else {
						SetConsoleTextAttribute(handle, FOREGROUND_RED);
						cout << " K";
						cout << "";
					}
					break;
				}
				case queen: {
					if (board[i][j].get_color() == white) {
						SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
						cout << " Q";
						cout << "";
					}
					else {
						SetConsoleTextAttribute(handle, FOREGROUND_RED);
						cout << " Q";
						cout << "";
					}
					break;
				}
				}
				cout << "";
			}
		}
		SetConsoleTextAttribute(handle, FOREGROUND_RED);
		cout << endl;
	}
	SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ChessBoard board;
	cout << "����" << endl;
	bool flag = true;
	while (flag) {
		cout << "��������� ��������:" << endl << endl;
		cout << "1) �������� ������" << endl;
		cout << "2) ������� ������" << endl;
		cout << "3) ������� ������" << endl;
		cout << "4) ����� ������ ������ ��� ����������� �� ������ ������" << endl;
		cout << "5) ���������� ������ ���������" << endl << endl;
		int command;
		cout << "������� ����� �������: ";
		cout << "";
		cin >> command;
		cout << endl;
		switch (command) {
		case 1: {
			insert_piece(board);
			print_board(board);
			break;
		}
		case 2: {
			delete_piece(board);
			print_board(board);
			break;
		}
		case 3: {
			try {
				piece_move(board);
			}
			catch (runtime_error& a) {
				cerr << a.what() << endl;
			}
			print_board(board);
			break;
		}
		case 4: {
			search_piece_to_attack(board);
			print_board(board);
			break;
		}
		case 5: flag = false;
		}
	}
}
