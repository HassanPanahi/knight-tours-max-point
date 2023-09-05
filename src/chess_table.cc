#include "chess_table.h"

#include <iostream>

namespace algorithms {

//TODO(HP): find better place for this
std::map<ChessPieceType, std::vector<Position>> ChessTableMoveStrategyAbstract::pieces_move_= {
    {ChessPieceType::Knight,{ {-1, -2}, {1,-2}, {-2,-1}, {2,-1}, {-2, 1}, {2, 1}, {-1,2}, {1,2}} }
};

ChessTable::ChessTable(const ChessTableStructure &table_structure) :table_structure_(table_structure)
{
    table_points_ = std::vector<std::vector<int32_t>>(table_structure_.table_row, std::vector<int32_t>(table_structure_.table_col, 0));

    //TODO(HP): check table structure data... row & col and same things
    for (const auto& piece : table_structure_.input_chess_pieces.other_pieces) {
        uint32_t row = static_cast<uint32_t>(piece.pos.row);
        uint32_t col = static_cast<uint32_t>(piece.pos.col);
        table_points_[row][col] = piece.point;
    }
}

ChessTableResult ChessTable::solve_table()
{
    table_results_.max_point = INT32_MIN;
    find_next_move(table_structure_.input_chess_pieces.start_position, 0, table_structure_.input_chess_pieces.move_count, track_);
    if (table_results_.pieces.size() > 0)
        std::cout << "max point is: " << table_results_.max_point << std::endl;
    return table_results_;
}

ChessTableStructure ChessTable::get_table_structure() const
{
    return table_structure_;
}

bool ChessTable::check_extra_validation(const ChessPiece& new_piece)
{
    bool ret = true;
    for (auto& piece : table_structure_.input_chess_pieces.other_pieces) {
        if (piece.color == ChessColor::WHITE && new_piece.pos == piece.pos) {
            ret = false;
            break;
        }
    }
    return ret;
}

void ChessTable::find_next_move(const ChessPiece& chess_piece,const int32_t point,  uint32_t move_count, const std::vector<ChessPiece>& track)
{
    if (move_count == 0) {
        if (point > table_results_.max_point) {
            table_results_.max_point = point;
            table_results_.pieces = track;
        }
    } else {
        //TODO(HP): wrote move_strategy modern cpp: while(move_strategy->has_next())
        for (uint32_t move = 0; move < table_structure_.move_strategy.size(); move++) {
            auto new_pos = chess_piece.pos+ table_structure_.move_strategy[move];

            if (!is_valid_position(new_pos))
                continue;

            ChessPiece new_chess_piece;
            new_chess_piece.pos = new_pos;
            if (!check_extra_validation(new_chess_piece))
                continue;

            track_.push_back(new_chess_piece);
            uint32_t new_row = static_cast<uint32_t>(new_pos.row);
            uint32_t new_col = static_cast<uint32_t>(new_pos.col);

            auto current_peice = table_points_[new_row][new_col];
            table_points_[new_row][new_col] = 0;

            find_next_move(new_chess_piece, point + current_peice, move_count - 1, track_);
            table_points_[new_row][new_col] = current_peice;
            track_.pop_back();
        }
    }
}

ChessTable::~ChessTable()
{

}

} //namespace
