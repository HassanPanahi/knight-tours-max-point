#ifndef ChessTablePieceMovement_H
#define ChessTablePieceMovement_H

#include "chess_table_law_abstract.h"

namespace algorithms {

class ChessTablePieceMovement
{
public:
    ChessTablePieceMovement(const ChessPieceType piece_type);
    bool has_next();
    Position get_next();
    ChessPieceType get_type() const;
    virtual ~ChessTablePieceMovement();
private:
    void init();

    uint32_t read_index_;
    ChessPieceType piece_type_;
    std::vector<Position> pieces_move_;
};

} // namespace
#endif // ChessTablePieceMovement_H
