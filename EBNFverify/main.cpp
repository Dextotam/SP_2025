#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
/************************************************************************
* N.Kozak // Lviv'2024-2025 // example syntax analysis by boost::spirit *
*                              file: one_file__x86_Debug.cpp            *
*                                                (0.04v/draft version ) *
*************************************************************************/
//#pragma once
//#include "stdafx.h"
#if !defined(_DEBUG) || !defined(_WIN32) || !defined(_M_IX86)
#include "stdio.h"
int main() {
    printf("Please, switch to mode VS + x86 + Debug.\r\n");
    (void)getchar();

    return 0;
}
#elif !defined(TO_SPIRIT_IMPLEMENTATION)
//#ifndef TO_SPIRIT_IMPLEMENTATION

#define TO_SPIRIT_IMPLEMENTATION
#include __FILE__

#define DEBUG__IF_ERROR

#define RERUN_MODE

#define DEFAULT_INPUT_FILE "file1.k03"
//#define DEFAULT_INPUT_FILE "../other_test_programs_2025/file4.k03"

#define MAX_TEXT_SIZE 8192

namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

#define SAME_RULE(RULE) ((RULE) | (RULE))
//#define USE_REVERSE_ASSIGNMENT
#define USE_COMPARE_WITH_EQUAL
template <typename Iterator>
struct cwgrammar : qi::grammar<Iterator> {
    cwgrammar(std::ostringstream& error_stream) : cwgrammar::base_type(program), error_stream_(error_stream) {
           
        
        program_name = SAME_RULE(ident);
        value_type = SAME_RULE(tokenINT2);
        declaration_element = ident >> -(tokenLEFTSQUAREBRACKETS >> unsigned_value >> tokenRIGHTSQUAREBRACKETS);
        other_declaration_ident = tokenCOMMA >> declaration_element;
        declaration = value_type >> declaration_element >> *other_declaration_ident;
        index_action = tokenLEFTSQUAREBRACKETS >> expression >> tokenRIGHTSQUAREBRACKETS;
        unary_operator = SAME_RULE(tokenNOT);
        unary_operation = unary_operator >> expression;
        binary_operator = tokenAND | tokenOR | tokenEQUAL | tokenNOTEQUAL | tokenLESS | tokenGREATER | tokenPLUS | tokenMINUS | tokenMUL | tokenDIV | tokenMOD;
        binary_action = binary_operator >> expression;
        left_expression = group_expression | unary_operation | ident >> -index_action | value;
        expression = left_expression >> *binary_action;
        group_expression = tokenGROUPEXPRESSIONBEGIN >> expression >> tokenGROUPEXPRESSIONEND;
        bind_left_to_right = expression >> tokenLRBIND >> ident >> -index_action;
        if_expression = SAME_RULE(expression);
        body_for_true = SAME_RULE(block_statements_in_while_and_if_body);
        false_cond_block_without_else = tokenELSE >> cond_block;
        body_for_false = tokenELSE >> block_statements_in_while_and_if_body;
        cond_block = tokenIF >> if_expression >> body_for_true >> *false_cond_block_without_else >> (-body_for_false);
        block_statements_in_while_and_if_body = tokenBEGINBLOCK >> *statement_in_while_and_if_body >> tokenENDBLOCK;
        statement_in_while_and_if_body = statement | break_while;
        block_statements_in_while_and_if_body = tokenBEGINBLOCK >> *statement_in_while_and_if_body >> tokenENDBLOCK;
        repeat_until_cycle_cond = SAME_RULE(expression);
        repeat_until_cycle = tokenREPEAT >> (*statement | block_statements) >> tokenUNTIL >> repeat_until_cycle_cond;
        input = tokenINPUT >> tokenGROUPEXPRESSIONBEGIN >> ident >> tokenGROUPEXPRESSIONEND;
        output = tokenOUTPUT >> tokenGROUPEXPRESSIONBEGIN >> expression >> tokenGROUPEXPRESSIONEND;
        statement = (bind_left_to_right | cond_block | repeat_until_cycle | input | output) >> -tokenSEMICOLON;
        block_statements = tokenBEGINBLOCK >> *statement >> tokenENDBLOCK;
        program = BOUNDARIES >> tokenPROGRAM >> ident >> tokenSEMICOLON >> tokenBEGIN >> tokenVAR >> (-declaration) >> tokenSEMICOLON >> *statement >> tokenEND >> tokenSEMICOLON;
        digit = digit_0 | digit_1 | digit_2 | digit_3 | digit_4 | digit_5 | digit_6 | digit_7 | digit_8 | digit_9;
        non_zero_digit = digit_1 | digit_2 | digit_3 | digit_4 | digit_5 | digit_6 | digit_7 | digit_8 | digit_9;
        unsigned_value = ((non_zero_digit >> *digit) | digit_0) >> BOUNDARIES;
        value = (-sign) >> unsigned_value >> BOUNDARIES;
        letter_in_upper_case = A | B | C | D | E | F | G | H | I | J | K | L | M | N | O | P | Q | R | S | T | U | V | W | X | Y | Z;
        ident = letter_in_upper_case >> letter_in_upper_case >> BOUNDARIES;
        sign = sign_plus | sign_minus;
        sign_plus = '+' >> BOUNDARIES;
        sign_minus = '-' >> BOUNDARIES;
        digit_0 = '0';
        digit_1 = '1';
        digit_2 = '2';
        digit_3 = '3';
        digit_4 = '4';
        digit_5 = '5';
        digit_6 = '6';
        digit_7 = '7';
        digit_8 = '8';
        digit_9 = '9';
        tokenCOLON = ":" >> BOUNDARIES;
        tokenINT2 = "INT_2" >> STRICT_BOUNDARIES;
        tokenCOMMA = "," >> BOUNDARIES;
        tokenNOT = "!!" >> STRICT_BOUNDARIES;
        tokenAND = "&&" >> STRICT_BOUNDARIES;
        tokenOR = "||" >> STRICT_BOUNDARIES;
        tokenEQUAL = "=" >> BOUNDARIES;
        tokenNOTEQUAL = "<>" >> BOUNDARIES;
        tokenLESS = "LT" >> BOUNDARIES;
        tokenGREATER = "GT" >> BOUNDARIES;
        tokenPLUS = "+" >> BOUNDARIES;
        tokenMINUS = "-" >> BOUNDARIES;
        tokenMUL = "*" >> BOUNDARIES;
        tokenDIV = "DIV" >> STRICT_BOUNDARIES;
        tokenMOD = "MOD" >> STRICT_BOUNDARIES;
        tokenGROUPEXPRESSIONBEGIN = "(" >> BOUNDARIES;
        tokenGROUPEXPRESSIONEND = ")" >> BOUNDARIES;
        tokenLRBIND = "->" >> BOUNDARIES;
        tokenELSE = "ELSE" >> STRICT_BOUNDARIES;
        tokenIF = "IF" >> STRICT_BOUNDARIES;
        tokenREPEAT = "REPEAT" >> STRICT_BOUNDARIES;
        tokenUNTIL = "UNTIL" >> STRICT_BOUNDARIES;
        tokenINPUT = "INPUT" >> STRICT_BOUNDARIES;
        tokenOUTPUT = "OUTPUT" >> STRICT_BOUNDARIES;
        tokenPROGRAM = "PROGRAM" >> STRICT_BOUNDARIES;
        tokenBEGIN = "BEGIN" >> STRICT_BOUNDARIES;
        tokenVAR = "VAR" >> STRICT_BOUNDARIES;
        tokenEND = "END" >> STRICT_BOUNDARIES;
        tokenBEGINBLOCK = "{" >> BOUNDARIES;
        tokenENDBLOCK = "}" >> BOUNDARIES;
        tokenLEFTSQUAREBRACKETS = "[" >> BOUNDARIES;
        tokenRIGHTSQUAREBRACKETS = "]" >> BOUNDARIES;
        tokenSEMICOLON = ";" >> BOUNDARIES;
        STRICT_BOUNDARIES = (BOUNDARY >> *(BOUNDARY)) | (!(qi::alpha | qi::char_("_")));
        BOUNDARIES = (BOUNDARY >> *(BOUNDARY) | NO_BOUNDARY);
        BOUNDARY = BOUNDARY_SPACE | BOUNDARY_TAB | BOUNDARY_CARRIAGE_RETURN | BOUNDARY_LINE_FEED | BOUNDARY_NULL;
        BOUNDARY_SPACE = " ";
        BOUNDARY_TAB = "\t";
        BOUNDARY_CARRIAGE_RETURN = "\r";
        BOUNDARY_LINE_FEED = "\n";
        BOUNDARY_NULL = "\0";
        NO_BOUNDARY = "";
        A = "A";
        B = "B";
        C = "C";
        D = "D";
        E = "E";
        F = "F";
        G = "G";
        H = "H";
        I = "I";
        J = "J";
        K = "K";
        L = "L";
        M = "M";
        N = "N";
        O = "O";
        P = "P";
        Q = "Q";
        R = "R";
        S = "S";
        T = "T";
        U = "U";
        V = "V";
        W = "W";
        X = "X";
        Y = "Y";
        Z = "Z";

    }
    std::ostringstream& error_stream_;

        qi::rule<Iterator>
       
        program_name,
        value_type,
        declaration_element,
        other_declaration_ident,
        declaration,
        index_action,
        unary_operator,
        unary_operation,
        binary_operator,
        binary_action,
        left_expression,
        expression,
        group_expression,
        // #ifdef USE_REVERSE_ASSIGNMENT
        bind_left_to_right,
        // #else
      
        // #endif
        if_expression,
        body_for_true,
        false_cond_block_without_else,
        body_for_false,
        cond_block,
       
        // #ifdef USE_REVERSE_ASSIGNMENT
        cycle_counter_lr_init,
        // #else
        cycle_counter_rl_init,
        // #endif
        cycle_counter_init,
        cycle_counter_last_value,
        cycle_body,

  
       break_while,
        statement_in_while_and_if_body,
        block_statements_in_while_and_if_body,
        repeat_until_cycle_cond,
        repeat_until_cycle,
        input,
        output,
        statement,
        block_statements,
        program,
        //
        tokenCOLON, tokenINT2, tokenCOMMA, tokenNOT, tokenAND, tokenOR, tokenEQUAL, tokenNOTEQUAL,
        // #else
        tokenLESS,
        tokenGREATER,
        // #endif
        tokenPLUS, tokenMINUS, tokenMUL, tokenDIV, tokenMOD, tokenGROUPEXPRESSIONBEGIN, tokenGROUPEXPRESSIONEND, tokenRLBIND, tokenLRBIND,
        tokenELSE, tokenIF, tokenBREAK, tokenREPEAT, tokenUNTIL, tokenINPUT, tokenOUTPUT, tokenPROGRAM, tokenBEGIN, tokenVAR, tokenEND, tokenBEGINBLOCK, tokenENDBLOCK, tokenLEFTSQUAREBRACKETS, tokenRIGHTSQUAREBRACKETS, tokenSEMICOLON,
        //
        STRICT_BOUNDARIES, BOUNDARIES, BOUNDARY, BOUNDARY_SPACE, BOUNDARY_TAB, BOUNDARY_CARRIAGE_RETURN, BOUNDARY_LINE_FEED, BOUNDARY_NULL,
        NO_BOUNDARY,
        //
        sign, sign_plus, sign_minus,
        digit_0, digit_1, digit_2, digit_3, digit_4, digit_5, digit_6, digit_7, digit_8, digit_9,
        digit, non_zero_digit, value, unsigned_value,
        letter_in_upper_case, letter_in_lower_case, ident,
        //label, 
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z;
};

int main(int argc, char* argv[]) {
    char* text_;
    char fileName[128] = DEFAULT_INPUT_FILE;
    char choice[2] = { fileName[0], fileName[1] };
    system("CLS");
    std::cout << "Enter file name(Enter \"" << choice[0] << "\" to use default \"" DEFAULT_INPUT_FILE "\"):";
    std::cin >> fileName;
    if (fileName[0] == choice[0] && fileName[1] == '\0') {
        fileName[1] = choice[1];
    }
    size_t sourceSize = loadSource(&text_, fileName);
    if (!sourceSize) {
#ifdef RERUN_MODE
        (void)getchar();
        printf("\nEnter 'y' to rerun program action(to pass action enter other key): ");
        char valueByGetChar = getchar();
        if (valueByGetChar == 'y' || valueByGetChar == 'Y') {
            system((std::string("\"") + argv[0] + "\"").c_str());
        }
        return 0;
#else
        printf("Press Enter to exit . . .");
        (void)getchar();
        return 0;
#endif
    }
    printf("Original source:\r\n");
    printf("-------------------------------------------------------------------\r\n");
    printf("%s\r\n", text_);
    printf("-------------------------------------------------------------------\r\n\r\n");
    int commentRemoverResult = commentRemover(text_, "#*", "*#");
    if (commentRemoverResult) {
        printf("Comment remover return %d\r\n", commentRemoverResult);
        printf("Press Enter to exit . . .");
        (void)getchar();
        return 0;
    }
    printf("Source after comment removing:\r\n");
    printf("-------------------------------------------------------------------\r\n");
    printf("%s\r\n", text_);    
    printf("-------------------------------------------------------------------\r\n\r\n");

    std::string text(text_);

    typedef std::string     str_t;
    typedef str_t::iterator str_t_it;

    std::ostringstream error_stream;
    cwgrammar<str_t_it> cwg(error_stream);

    str_t_it begin = text.begin(), end = text.end();


    bool success = qi::parse(begin, end, cwg);

    if (!success) {
        std::cout << "\nParsing failed!\n";
        std::cout << "Error message: " << error_stream.str();
    }
    else if (begin != end) {
        std::cout << "\nUnknown fragment ofter successs parse at: \"" << str_t(begin, end) << "\"\n";
    }
    else {
        std::cout << "\nParsing success!\n";
    }

    free(text_);

    (void)getchar();

#ifdef RERUN_MODE
    printf("\nEnter 'y' to rerun program action(to pass action enter other key): ");
    char valueByGetChar = getchar();
    if (valueByGetChar == 'y' || valueByGetChar == 'Y') {
        system((std::string("\"") + argv[0] + "\"").c_str());
    }
#endif

    return 0;
}
