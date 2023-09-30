#pragma once
#include <iostream>


namespace chess_space {
	
	enum Type { square, king, queen, knight };

	enum Color { white, black };

	struct Position {

		int vertical;
		int horisontal;
		Position();
		Position(const int vertical,const int horisontal);

	};

	bool operator==(const Position& lhs, const Position& rhs);

	class ChessPiece {

		Type _type;
		Color _color;
		Position _position;

	public:

		ChessPiece();

		ChessPiece(const Type type, const Color color, const Position position);

		Type get_type() const;

		Position get_position() const;

		Color get_color() const;

		bool piece_move(const int vertical, const int horisontal) const;

		bool piece_attack(const ChessPiece piece) const;

		bool pieces_move(ChessPiece* set, int size, const int vertical, const int horisontal) const;

		bool pieces_attack(ChessPiece* set, int size, const ChessPiece piece) const;

		int search_piece_to_attack(ChessPiece* set, int size, const ChessPiece piece) const;

	};

	class ChessBoard {

		ChessPiece** _board;

		int _amount_pieces;

	public:

		ChessBoard();

		~ChessBoard();

		ChessBoard& operator=(const ChessBoard& other);

		ChessPiece* operator[](const int index) const;

		void swap(ChessBoard& other);

		int get_amount_pieces() const;

		ChessPiece get_piece(const int vertical, const int horisontal) const;

		void insert_piece(ChessPiece piece);

		void delete_piece(const int vertical, const int horisontal);

	};

	std::ostream& operator<<(std::ostream& out, const ChessPiece*& other);
	
}
