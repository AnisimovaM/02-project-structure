#include <chess/chess_lib.h>
#include <stdexcept>


using namespace chess_space;

ChessBoard::ChessBoard() : _board(new ChessPiece* [8]), _amount_pieces(0) {
	for (int i = 0; i < 8; ++i) {
		_board[i] = new ChessPiece[8];
		for (int j = 0; j < 8; j++) {
			if ((i + j) % 2 == 0) {
				_board[i][j] = { Type::square, Color::black, Position::Position(i,j) };
			}
			else {
				_board[i][j] = { Type::square, Color::white, Position::Position(i,j) };
			}
		}
	}
}

ChessBoard::~ChessBoard() {
	for (int i = 0; i < 8; ++i) {
		delete(_board[i]);
	}
	delete[](_board);
}

ChessPiece* ChessBoard::operator[](const int index) const {
	return _board[index];
}

void ChessBoard::swap(ChessBoard& other) {
	std::swap(this->_board, other._board);
	std::swap(this->_amount_pieces, other._amount_pieces);
}

ChessBoard& ChessBoard::operator=(const ChessBoard& other) {
	ChessBoard copy(other);
	copy.swap(*this);
	return *this;
}

int ChessBoard::get_amount_pieces() const {
	return _amount_pieces;
}

ChessPiece ChessBoard::get_piece(const int vertical, const int horisontal) const {
	return _board[vertical][horisontal];
}

void ChessBoard::insert_piece(ChessPiece piece) {
	if (this->get_piece(piece.get_position().vertical, piece.get_position().horisontal).get_type() != square) {
		throw std::runtime_error("This position blocked by another piece");
	}
	else {
		_board[piece.get_position().vertical][piece.get_position().horisontal] = piece;
		++_amount_pieces;
	}
}

void ChessBoard::delete_piece(const int vertical, const int horisontal){
	if ((horisontal + vertical) % 2 == 0) {
		_board[vertical][horisontal] = { Type::square, Color::black, Position::Position(vertical, horisontal) };
	}
	else {
		_board[vertical][horisontal] = { Type::square, Color::white, Position::Position(vertical, horisontal) };
	}
}
