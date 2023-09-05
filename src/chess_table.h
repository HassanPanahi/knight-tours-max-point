#ifndef ChessTable_H
#define ChessTable_H

#include "chess_table_law_abstract.h"

namespace algorithms {

class ChessTable : public ChessTableLawsAbstract
{
public:
    ChessTable(const ChessTableStructure& table_structure);

    virtual ChessTableResult solve_table();
    virtual ChessTableStructure get_table_structure() const;

    virtual ~ChessTable();
private:
    void update_next_point();
    ChessTableStructure table_structure_;
    bool check_extra_validation(const ChessPiece& new_piece);
    void find_next_move(const ChessPiece& chess_piece,const int32_t point,  uint32_t move_count, const std::vector<ChessPiece>& track);

    ChessTableResult table_results_;
    //TODO(HP): Use chess_piece
    std::vector< std::vector<int32_t>> table_points_;
    std::vector<ChessPiece> track_;
};

} //namespace algorithms

#endif // ChessTable_H
