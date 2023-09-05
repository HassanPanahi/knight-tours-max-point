#ifndef CHESS_TABLE_LAW_H
#define CHESS_TABLE_LAW_H

#include <vector>
#include <memory>
#include <map>
#include <iostream>

namespace algorithms {

enum class AlgorithmError
{
    ValidInput,
    Wrong_Input
};

enum class ChessColor
{
    BLACK,
    WHITE
};

struct Position
{
    int32_t row;
    int32_t col;

    bool operator==(const Position& new_pos) const {
        return (row == new_pos.row) && (col == new_pos.col);
    }

    bool operator!=(const Position& new_pos) const {
        return !(*this == new_pos);
    }

    Position operator+(const Position& other) const {
        return {row + other.row, col + other.col};
    }
};

struct ChessPiece {
    int32_t point;
    Position pos;
    ChessColor color;
};

struct InputsChessPieces
{
    uint32_t move_count;
    ChessPiece start_position;
    std::vector<ChessPiece> other_pieces;
};

enum ChessPieceType {
    Knight,
    Queen
};

class ChessTableMoveStrategyAbstract {
public:
    virtual bool has_next() = 0;
    virtual Position get_next() = 0;
    virtual ChessPieceType get_type() const = 0;
    virtual void start_again() = 0;
    static std::vector<Position> get_positions(const ChessPieceType piece) {
        std::vector<Position> result;
        auto pieces_iterator = pieces_move_.find(piece);
        if (pieces_iterator != pieces_move_.end())
            result = pieces_iterator->second;
        else
            std::cout << "This piece not emplemented yet!!!" << std::endl;
        return result;
    }
private:
    static std::map<ChessPieceType, std::vector<Position>> pieces_move_;
};


struct ChessTableStructure
{
    uint32_t table_row;
    uint32_t table_col;
    std::vector<Position> move_strategy;
    InputsChessPieces input_chess_pieces;
};

struct ChessTableResult
{
    int32_t max_point;
    std::vector<ChessPiece> pieces;
};

//TODO(HP): change This design for modern c++ and call back function for all...
// I want to use every strategy for this... like 8-queen & knight tour, and all chess table algorithms
// that can be part of backtracking or even using Dynamic programming... without changing the code again.

class ChessTableLawsAbstract
{
public:
    virtual ChessTableResult solve_table() = 0;
    virtual ChessTableStructure get_table_structure() const = 0;

    bool is_valid_position(const Position& pos)
    {
        auto table = get_table_structure();
        int32_t table_row = static_cast<int32_t>(table.table_row);
        int32_t table_col = static_cast<int32_t>(table.table_col);
        bool ret = true;
        if (pos.row < 0 || pos.row >= table_row || pos.col < 0 || pos.col >= table_col)
            ret = false;
        return ret;
    }

    virtual ~ChessTableLawsAbstract() {}
};


} //namespace algorithms

#endif // CHESS_TABLE_LAW_H
