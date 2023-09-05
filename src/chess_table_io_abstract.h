#ifndef INPUT_HANDLER_ABSTRACT_H
#define INPUT_HANDLER_ABSTRACT_H

#include "chess_table_law_abstract.h"

namespace algorithms {

class ChessTableIOAbstract
{
public:
    virtual AlgorithmError is_valid_inputs() const = 0;
    virtual InputsChessPieces get_table_chess_info() const = 0;
    virtual void report_chess_result(const ChessTableResult& result) = 0;
    virtual ~ChessTableIOAbstract() {}
};

} //namespace algorithms
#endif // INPUT_HANDLER_ABSTRACT_H
