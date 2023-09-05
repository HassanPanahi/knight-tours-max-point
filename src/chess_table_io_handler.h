#ifndef ChessTableIOHandler_H
#define ChessTableIOHandler_H

#include "chess_table_io_abstract.h"

#include <functional>

namespace algorithms {

// every line of file content
enum class ColonContent {
    COLOR = 0,
    POINT,
    POSITION
};

using Colon_Handler_FuncPtr = std::function<void (const std::string&, ChessPiece& piece)>;

class ChessTableIOHandler final : public ChessTableIOAbstract
{
public:
    ChessTableIOHandler(const std::string& input_file, const std::string& output_address);
    ChessTableIOHandler(const ChessTableIOHandler& handler) = delete;

    virtual AlgorithmError is_valid_inputs() const;
    virtual InputsChessPieces get_table_chess_info() const;
    virtual void report_chess_result(const ChessTableResult& result);
    virtual ~ChessTableIOHandler();
private:
    uint32_t total_piece_line_;
    std::string input_file_;
    std::string output_address_;
    InputsChessPieces chess_table_inputs_;
    const std::map<char, uint32_t> alphabetic_index_lookup_;
    std::map<ColonContent, Colon_Handler_FuncPtr> colon_function_ptr; // commands design pattern

    void init();
    void read_and_analyse_file();
    void register_functions_ptr();

    void handle_chess_piece_color(const std::string& line, ChessPiece& piece);
    void handle_chess_piece_point(const std::string& line, ChessPiece& piece);
    void handle_chess_piece_position(const std::string& line, ChessPiece& piece);

    void handle_total_move_piece(const std::string& line);
    void handle_total_chess_piece(const std::string& info);
    void handle_other_chess_piece(const std::string& info);
    void handle_start_piece_position(const std::string& info);

    ChessPiece analyse_chess_piece(const std::string& info);
};

} //namespace algorithms
#endif // ChessTableIOHandler_H
