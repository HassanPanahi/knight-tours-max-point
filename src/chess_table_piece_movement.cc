#include "chess_table_piece_movement.h"

namespace algorithms {

ChessTablePieceMovement::ChessTablePieceMovement(const ChessPieceType piece_type) :
    read_index_(0),
    piece_type_(piece_type)
{
    init();
}

void ChessTablePieceMovement::init()
{
    pieces_move_ = get_positions(piece_type_);
}

bool ChessTablePieceMovement::has_next()
{
   return read_index_ < pieces_move_.size();
}

Position ChessTablePieceMovement::get_next()
{
    if (has_next()) {
             return pieces_move_[read_index_++];
    }
    throw std::out_of_range("No more moves available.");
}

ChessPieceType ChessTablePieceMovement::get_type() const
{
    return piece_type_;
}

ChessTablePieceMovement::~ChessTablePieceMovement()
{

}



}
