#include <gtest/gtest.h>

#include <chess/chess_lib.h>

using namespace chess_space;

TEST(ChessBoardTests, AmountTest) {

	ChessPiece piece_1(Type::king, Color::white, Position::Position(1, 5));
	ChessPiece piece_2(Type::king, Color::black, Position::Position(4, 0));
	ChessPiece piece_3(Type::king, Color::white, Position::Position(3, 4));
	ChessPiece piece_4(Type::king, Color::black, Position::Position(4, 7));
	ChessPiece piece_5(Type::king, Color::white, Position::Position(4, 3));
	ChessPiece piece_6;

	ChessBoard board;

	board.insert_piece(piece_1);
	board.insert_piece(piece_2);
	board.insert_piece(piece_3);
	board.insert_piece(piece_4);
	board.insert_piece(piece_5);
	board.insert_piece(piece_6);

	EXPECT_EQ(board.get_amount_pieces(), 6);
}

TEST(ChessBoardTests, GetTest) {

	ChessPiece piece_1(Type::king, Color::white, Position::Position(1, 5));
	ChessPiece piece_2(Type::king, Color::black, Position::Position(4, 0));
	ChessPiece piece_3(Type::king, Color::white, Position::Position(3, 4));
	ChessPiece piece_4(Type::queen, Color::black, Position::Position(4, 7));
	ChessPiece piece_5(Type::knight, Color::white, Position::Position(4, 3));
	ChessPiece piece_6;

	ChessBoard board;

	board.insert_piece(piece_1);
	board.insert_piece(piece_2);
	board.insert_piece(piece_3);
	board.insert_piece(piece_4);
	board.insert_piece(piece_5);
	board.insert_piece(piece_6);

	EXPECT_EQ(board.get_piece(4,0).get_color(), Color::black);
	EXPECT_EQ(board.get_piece(1, 5).get_position().vertical, 1);
	EXPECT_EQ(board.get_piece(0, 0).get_type(), Type::square);
	EXPECT_EQ(board.get_piece(3, 4).get_color(), Color::white);
	EXPECT_EQ(board.get_piece(4, 7).get_type(), Type::queen);
	EXPECT_EQ(board.get_piece(4, 3).get_type(), Type::knight);
}


TEST(ChessBoardTests, InsertTest) {

	ChessPiece piece_1(Type::king, Color::white, Position::Position(4, 4));
	ChessPiece piece_2(Type::king, Color::black, Position::Position(4, 4));

	ChessBoard board;

	EXPECT_NO_THROW(board.insert_piece(piece_1), std::runtime_error);
	EXPECT_ANY_THROW(board.insert_piece(piece_2), std::runtime_error);
}

TEST(ChessBoardTests, DeleteTest) {
	ChessPiece piece_1(Type::king, Color::white, Position::Position(7, 0));
	ChessPiece piece_2(Type::knight, Color::black, Position::Position(6, 4));

	ChessBoard board;

	board.insert_piece(piece_1);
	board.insert_piece(piece_2);

	Type t_1 = board.get_piece(7, 0).get_type();
	Type t_2 = board.get_piece(6, 4).get_type();

	EXPECT_EQ(t_1, Type::king);
	EXPECT_EQ(t_2, Type::knight);

	board.delete_piece(7, 0);
	board.delete_piece(6, 4);

	t_1 = board.get_piece(7, 0).get_type();
    t_2 = board.get_piece(6, 4).get_type();

	EXPECT_EQ(t_1, Type::square);
	EXPECT_EQ(t_2, Type::square);
}