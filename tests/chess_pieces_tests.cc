#include <gtest/gtest.h>

#include <chess/chess_lib.h>

using namespace chess_space;

TEST(ChessPiecesTest, PieceMove) {

	ChessPiece king(Type::king, white, Position::Position(2, 3));
	ChessPiece knight(Type::knight, black, Position::Position(4, 1));
	ChessPiece queen(Type::queen, white, Position::Position(6, 2));

	EXPECT_TRUE(king.piece_move(3,4));
	EXPECT_TRUE(king.piece_move(1,3));
	EXPECT_TRUE(knight.piece_move(6,0));
	EXPECT_TRUE(knight.piece_move(3, 3));
	EXPECT_TRUE(queen.piece_move(4,0));
	EXPECT_TRUE(queen.piece_move(0, 2));
	EXPECT_FALSE(queen.piece_move(0, 8));
}

TEST(ChessPiecesTest, PieceAttack) {

	ChessPiece piece_1(Type::king, white, Position::Position(1, 1));
	ChessPiece piece_2(Type::knight, black, Position::Position(2, 1));
	ChessPiece piece_3(Type::queen, white, Position::Position(7, 3));
	ChessPiece piece_4(Type::king, black, Position::Position(5, 1));
	ChessPiece piece_5(Type::knight, white, Position::Position(3, 3));
	ChessPiece piece_6(Type::queen, black, Position::Position(4, 5));

	EXPECT_TRUE(piece_1.piece_attack(piece_2));
	EXPECT_TRUE(piece_2.piece_attack(piece_5));
	EXPECT_TRUE(piece_3.piece_attack(piece_4));
	EXPECT_FALSE(piece_4.piece_attack(piece_6));
	EXPECT_TRUE(piece_5.piece_attack(piece_6));
	EXPECT_FALSE(piece_6.piece_attack(piece_1));
}

TEST(ChessPiecesTest, PiecesMove) {

	ChessPiece piece_1(Type::king, white, Position::Position(1, 1));
	ChessPiece piece_2(Type::knight, black, Position::Position(3, 1));
	ChessPiece piece_3(Type::queen, white, Position::Position(7, 3));
	ChessPiece piece_4(Type::king, black, Position::Position(2, 4));
	ChessPiece piece_5(Type::knight, white, Position::Position(0, 6));
	ChessPiece piece_6(Type::queen, black, Position::Position(4, 6));

	ChessPiece set[] = { piece_1, piece_2, piece_3, piece_4, piece_5, piece_6 };

	EXPECT_TRUE(piece_1.pieces_move(set, 6, 0, 0));
	EXPECT_TRUE(piece_1.pieces_move(set, 6, 2, 0));
	EXPECT_TRUE(piece_2.pieces_move(set, 6, 5, 2));
	EXPECT_TRUE(piece_2.pieces_move(set, 6, 1, 0));
	EXPECT_TRUE(piece_3.pieces_move(set, 6, 0, 3));
	EXPECT_TRUE(piece_3.pieces_move(set, 6, 4, 0));
	EXPECT_TRUE(piece_4.pieces_move(set, 6, 3, 5));
	EXPECT_FALSE(piece_4.pieces_move(set, 6, 1, 4));
	EXPECT_TRUE(piece_5.pieces_move(set, 6, 1, 4));
	EXPECT_TRUE(piece_5.pieces_move(set, 6, 2, 7));
	EXPECT_TRUE(piece_6.pieces_move(set, 6, 0, 2));
	EXPECT_TRUE(piece_6.pieces_move(set, 6, 4, 0));
}

TEST(ChessPiecesTest, PiecesAttack) {

	ChessPiece piece_1(Type::king, white, Position::Position(1, 1));
	ChessPiece piece_2(Type::knight, black, Position::Position(3, 1));
	ChessPiece piece_3(Type::queen, white, Position::Position(7, 3));
	ChessPiece piece_4(Type::king, black, Position::Position(2, 3));
	ChessPiece piece_5(Type::knight, white, Position::Position(5, 4));
	ChessPiece piece_6(Type::queen, black, Position::Position(4, 6));

	ChessPiece set[] = { piece_1, piece_2, piece_3, piece_4, piece_5, piece_6 };

	EXPECT_FALSE(piece_1.pieces_attack(set, 6, piece_2));
	EXPECT_FALSE(piece_1.pieces_attack(set, 6, piece_6));
	EXPECT_FALSE(piece_2.pieces_attack(set, 6, piece_4));
	EXPECT_FALSE(piece_2.pieces_attack(set, 6, piece_1));
	EXPECT_TRUE(piece_3.pieces_attack(set, 6, piece_4));
	EXPECT_FALSE(piece_3.pieces_attack(set, 6, piece_5));
	EXPECT_FALSE(piece_4.pieces_attack(set, 6, piece_3));
	EXPECT_FALSE(piece_4.pieces_attack(set, 6, piece_5));
	EXPECT_FALSE(piece_5.pieces_attack(set, 6, piece_3));
	EXPECT_TRUE(piece_5.pieces_attack(set, 6, piece_6));
	EXPECT_FALSE(piece_6.pieces_attack(set, 6, piece_1));
	EXPECT_FALSE(piece_6.pieces_attack(set, 6, piece_5));
}

TEST(ChessPiecesTest, SearchPieceToAttack) {

	ChessPiece piece_1(Type::king, white, Position::Position(1, 1));
	ChessPiece piece_2(Type::knight, black, Position::Position(2, 1));
	ChessPiece piece_3(Type::queen, white, Position::Position(5, 6));
	ChessPiece piece_4(Type::king, black, Position::Position(3, 2)); 
	ChessPiece piece_5(Type::knight, white, Position::Position(3, 3));
	ChessPiece piece_6(Type::queen, black, Position::Position(6, 6));

	ChessPiece set[] = { piece_1, piece_2, piece_3, piece_4, piece_5, piece_6 };

	EXPECT_EQ(piece_1.search_piece_to_attack(set, 6, piece_1), 5);
	EXPECT_EQ(piece_2.search_piece_to_attack(set, 6, piece_2), 4);
	EXPECT_EQ(piece_3.search_piece_to_attack(set, 6, piece_3), 5);
	EXPECT_EQ(piece_5.search_piece_to_attack(set, 6, piece_5), 1);
	EXPECT_EQ(piece_6.search_piece_to_attack(set, 6, piece_6), 2);

}

