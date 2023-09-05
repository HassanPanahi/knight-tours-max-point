#include "chess_table_io_handler.h"
#include "project_config.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <istream>
#include <algorithm>

namespace algorithms {

ChessTableIOHandler::ChessTableIOHandler(const std::string& input_file, const std::string &output_address) :
    input_file_(input_file),
    output_address_(output_address),
    //TODO(HP): we can add uppercase too
    alphabetic_index_lookup_({{'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4}, {'f', 5}, {'g', 6}, {'h', 7}})
{
    total_piece_line_ = 0;
    init();
}

InputsChessPieces ChessTableIOHandler::get_table_chess_info() const
{
    return chess_table_inputs_;
}

AlgorithmError ChessTableIOHandler::is_valid_inputs() const
{
    //TODO(HP): complete this section
    return AlgorithmError::ValidInput;
}

void ChessTableIOHandler::handle_total_chess_piece(const std::string& line)
{
    try {
        total_piece_line_ = static_cast<uint32_t>(std::stoi(line));
    } catch (...) {
        //TODO(HP) we can handle this without throw exception... (total_piece_line_ = line of peices that can parse) ... set priority
        throw std::invalid_argument("Invalid total peice number: "+ line);
    }
}

void ChessTableIOHandler::handle_chess_piece_color(const std::string &line, ChessPiece &piece)
{
    try {
        piece.color = (std::stoi(line) == 0) ? ChessColor::BLACK : ChessColor::WHITE;
    } catch (...) {
        throw std::invalid_argument("Invalid color value: "+ line);
    }
}

void ChessTableIOHandler::handle_chess_piece_point(const std::string &line, ChessPiece &piece)
{
    try {
        piece.point =  std::stoi(line);
    } catch (...) {
        std::string data = "Invalid point value: "+ line;
        throw std::invalid_argument(data);
    }
}

void ChessTableIOHandler::handle_chess_piece_position(const std::string &line, ChessPiece &piece)
{
    if (line.size() < 2) {
        throw std::invalid_argument("Wrong col position in input data: "+ line);
    } else {
        auto look_iterator = alphabetic_index_lookup_.find(line[0]);
        if (look_iterator == alphabetic_index_lookup_.end())
            throw  std::invalid_argument("Wrong alphabetic peice data: "+ line);
        else
            piece.pos.col = static_cast<int32_t>(look_iterator->second);

        // -1 : want to start col from 0
        piece.pos.row = std::atoi(&line[1]) - 1;
    }
}

ChessPiece ChessTableIOHandler::analyse_chess_piece(const std::string &info)
{
    std::istringstream iss(info);
    std::string colon_data;
    uint32_t colon_index = 0;
    //TODO(HP): check piece start in valid?
    //TODO(HP): check reapeated chess piece
    ChessPiece chess_peice;
    while (std::getline(iss, colon_data, Colon_Seperator_Char)) {
        auto colon_type = static_cast<ColonContent>(colon_index);
        auto is_handle_colon = colon_function_ptr.find(colon_type);

        if (is_handle_colon == colon_function_ptr.end()) {
            //TODO(HP)
            std::cout << "Wrong info: " << static_cast<uint32_t>(colon_type) << std::endl;
        } else {
            auto handle_colon_funptr = is_handle_colon->second;
            handle_colon_funptr(colon_data, chess_peice);
        }
        colon_index++;
    }
    return chess_peice;
}

void ChessTableIOHandler::handle_other_chess_piece(const std::string &info)
{
    auto peice = analyse_chess_piece(info);
    chess_table_inputs_.other_pieces.push_back(peice);
}

void ChessTableIOHandler::handle_start_piece_position(const std::string &info)
{
    auto peice = analyse_chess_piece(info);
    chess_table_inputs_.start_position = peice;
}

void ChessTableIOHandler::handle_total_move_piece(const std::string &line)
{
    try {
        chess_table_inputs_.move_count = static_cast<uint32_t>(std::stoi(line));
    } catch (...) {
        throw std::invalid_argument("Invalid input data for total move: "+ line);
    }
}

void ChessTableIOHandler::read_and_analyse_file()
{
    std::ifstream file_handler(input_file_.c_str());
    if (!file_handler.is_open()) {
        throw std::runtime_error("Failed to open file "+ input_file_);
    } else {
        uint32_t line_counter = 0;
        std::string line;
        //TODO(HP): handle this steps with open/close principle (command design, like colon handlers)
        while (std::getline(file_handler, line)) {
            if (line.size() == 0) {
                std::cout << "There is empty line" << std::endl;
                continue;  // for empty line between information
            } else if (line_counter == 0) {
                handle_total_chess_piece(line);
            } else if (line_counter == 1) {
                handle_start_piece_position(line);
            } else if (line_counter <= total_piece_line_) {
                handle_other_chess_piece(line);
            } else if (line_counter == total_piece_line_ + 1){ //For first line
                handle_total_move_piece(line);
            }
            line_counter++;
        }
    }
}

void ChessTableIOHandler::register_functions_ptr()
{
    colon_function_ptr[ColonContent::POINT] = std::bind(&ChessTableIOHandler::handle_chess_piece_point, this, std::placeholders::_1, std::placeholders::_2);
    colon_function_ptr[ColonContent::COLOR] = std::bind(&ChessTableIOHandler::handle_chess_piece_color, this, std::placeholders::_1, std::placeholders::_2);
    colon_function_ptr[ColonContent::POSITION] = std::bind(&ChessTableIOHandler::handle_chess_piece_position, this, std::placeholders::_1, std::placeholders::_2);
}

void ChessTableIOHandler::init()
{
    register_functions_ptr();
    read_and_analyse_file();
}

void algorithms::ChessTableIOHandler::report_chess_result(const ChessTableResult &result)
{
    std::ofstream file_handler;
    file_handler.open(output_address_);

    if (result.pieces.size() == 0) {
        file_handler << Empty_Result_String;
        std::cout << "!" << std::endl;
    } else {
        for (auto chess_piece : result.pieces) {
            char alpha = '\0';
            for (const auto& pair : alphabetic_index_lookup_) {
                if (pair.second == static_cast<uint32_t>(chess_piece.pos.col))
                    alpha = pair.first;
            }
            std::string output = std::string(sizeof (alpha), alpha)+ std::to_string(chess_piece.pos.row + 1);
            std::cout << output << "  ";
            file_handler << output << "\n";
        }
        std::cout << std::endl;
    }
    file_handler.flush();
    file_handler.close();
}

ChessTableIOHandler::~ChessTableIOHandler()
{

}

} //namespace algorithms
