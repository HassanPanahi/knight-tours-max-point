#include <iostream>

#include "chess_table.h"
#include "project_config.h"
#include "chess_table_io_handler.h"

using namespace std;

int main(int argc, char **argv)
{
    //    if (argc != 3) {
    //        std::cerr << "Usage: " << argv[0] << " <input_file_address> <output_file_address>" << std::endl;
    //        return 1;
    //    }

    int ret = 0;
    try {
        for (uint32_t i= 1 ; i < 8; i++) {

            std::string inputs = "/home/hp/Videos/knight-tour-max-point/inputs/input"+ std::to_string(i)+ ".txt";
            std::string output = "/home/hp/Videos/knight-tour-max-point/inputs/output"+ std::to_string(i)+ ".txt";

            const char* input_file_address = inputs.c_str(); //argv[1];
            const char* output_file_address = output.c_str();//argv[2];

            algorithms::ChessTableStructure table_structure;
            table_structure.table_row = Chess_Table_Row_Count;
            table_structure.table_col = Chess_Table_Col_Count;
            table_structure.move_strategy = algorithms::ChessTableMoveStrategyAbstract::get_positions(algorithms::ChessPieceType::Knight);

            algorithms::ChessTableIOHandler ChessTableIOHandler(input_file_address, output_file_address);
            table_structure.input_chess_pieces = ChessTableIOHandler.get_table_chess_info();

            algorithms::ChessTable table(table_structure);
            auto result = table.solve_table();

            ChessTableIOHandler.report_chess_result(result);
        }
    } catch (std::invalid_argument& excep) {
        ret = -1;
        std::cout << "error: " << excep.what() << std::endl;
    }
    return ret;
}
