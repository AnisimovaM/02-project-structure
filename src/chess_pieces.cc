#include <chess/chess_lib.h>
#include <stdexcept>
#include <cmath>

using namespace chess_space;

bool chess_space::operator==(const Position& lhs, const Position& rhs) {
	if (lhs.horisontal == rhs.horisontal && lhs.vertical == rhs.vertical) {
		return true;
	}
	else return false;
}

std::ostream& chess_space::operator<<(std::ostream& out, const ChessPiece*& other)
{
	out << other->get_color() << other->get_type() << other->get_position().vertical << other->get_position().horisontal;
	return out;
}

Position::Position() {

	vertical = 0;

	horisontal = 0;

}

Position::Position(const int vertical,const int horisontal) {
	if (horisontal > 7 || horisontal < 0 || vertical > 7 || vertical < 0) {
		throw std::runtime_error("The piece went off the board");
	}
	else {
		this->vertical = vertical;

		this->horisontal = horisontal;
	}
}

ChessPiece::ChessPiece () {

	_type = Type::square;

	_color = Color::black;

	_position = Position::Position();

}

ChessPiece::ChessPiece(const Type type, const Color color, const Position position) {

		this->_type = type;

		this->_color = color;

		this->_position.horisontal = position.horisontal;

		this->_position.vertical = position.vertical;
	
}

Type ChessPiece::get_type() const {
	return _type;
}

Position ChessPiece::get_position() const {
	return _position;
}

Color ChessPiece::get_color() const {
	return _color;
}

bool ChessPiece::piece_move(const int vertical, const int horisontal) const {
	if (horisontal > 7 || horisontal < 0 || vertical > 7 || vertical < 0) {
		return false;
	}
	else {
		Position check(vertical, horisontal);
		if (this->get_position() == check) {
			return false;
		}
		switch (this->get_type()) {
		case Type::king: {
			if (this->get_position().horisontal - horisontal >= -1 && this->get_position().horisontal - horisontal <= 1 && this->get_position().vertical - vertical >= -1 && this->get_position().vertical - vertical <= 1) {
				return true;
			}
			else return false;
			break;
		}
		case Type::queen: {

			if (this->get_position().horisontal - horisontal == 0 || this->get_position().vertical - vertical == 0 || (this->get_position().horisontal - horisontal) + (this->get_position().vertical - vertical) == 0 || this->get_position().horisontal - horisontal == this->get_position().vertical - vertical) {
				return true;
			}
			else return false;
			break;
		}
		case Type::knight: {

			if (std::abs(this->get_position().horisontal - horisontal) == 2 && std::abs(this->get_position().vertical - vertical) == 1 || std::abs(this->get_position().horisontal - horisontal) == 1 && std::abs(this->get_position().vertical - vertical) == 2) {
				return true;
			}
			else return false;
			break;
		}
		default: return false;
		}
	}
}

bool ChessPiece::piece_attack(const ChessPiece piece) const {
	if (piece.get_type() == square) return false;
	if (this->get_color() == piece.get_color()) return false;
	return this->piece_move(piece.get_position().vertical, piece.get_position().horisontal);
}

bool ChessPiece::pieces_move(ChessPiece* set, int size, const int vertical, const int horisontal) const {
	for (int i = 0; i < size; ++i) {
		if (set[i].get_position() == Position(vertical, horisontal)) return false;
	}
	if (this->piece_move(vertical, horisontal)) {
		if (this->get_type() == king) {
			for (int i = 0; i < size; ++i) {
				if (set[i].get_color() != this->get_color() && set[i].piece_move(vertical, horisontal)) return false;
			}
		}
		return true;
	}
	else return false;
}

bool ChessPiece::pieces_attack(ChessPiece* set, int size, const ChessPiece piece) const {
	if (this->piece_attack(piece)) {
		if (this->get_type() == king) {
			for (int i = 0; i < size; ++i) {
				if (set[i].get_color() != this->get_color() && set[i].piece_move(piece.get_position().vertical, piece.get_position().horisontal)) return false;
			}
		}
		return true;
	}
	else return false;
}

int ChessPiece::search_piece_to_attack(ChessPiece* set, int size, const ChessPiece piece) const {
	for (int i = 0; i < size; ++i) {
		if (set[i].pieces_attack(set, size, piece)) return i;
	}
	return -1;
}
