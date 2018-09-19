#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "NodeVisitor.hpp"
#include "Parser.hpp"
#include "RAM.hpp"


class Interpreter: public NodeVisitor {
    public:
        Interpreter(Parser* parser);

        Parser* parser;

        void error(std::string message);

        anything visit_AST_BinOp(AST_BinOp* node);
        anything visit_AST_UnaryOp(AST_UnaryOp* node);
        int visit_AST_Num(AST_Num* node);
        std::string visit_AST_Str(AST_Str* node);

        anything visit_AST_Assign(AST_Assign* node);
        anything visit_AST_Var(AST_Var* node);
        int visit_AST_Compound(AST_Compound* node);
        int visit_AST_NoOp(AST_NoOp* node);
        int visit_AST_VarDecl(AST_VarDecl* node);
        int visit_AST_If(AST_If* node);
        anything visit_AST_functionCall(AST_FunctionCall* node);



        anything operation(anything left, std::string op, anything right);
        anything operation(int left, std::string op, int right);
        anything operation(float left, std::string op, float right);
        anything operation(std::string left, std::string op, std::string right);


        anything unary_operation(std::string op, anything right);
        anything unary_operation(std::string op, int right);
        anything unary_operation(std::string op, float right);
        anything unary_operation(std::string op, std::string right);

        anything interpret();
};
#endif
