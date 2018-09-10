#include "includes/Interpreter.hpp"
#include <iostream>


extern std::string T_INTEGER;
extern std::string T_PLUS;
extern std::string T_MINUS;
extern std::string T_MULTIPLY;
extern std::string T_DIVIDE;
extern std::string T_LPAREN;
extern std::string T_RPAREN;

Interpreter::Interpreter(Parser* parser) {
    this->parser = parser;
};

int Interpreter::visit_BinOp(BinOp* node) {
    if (node->op->type == T_PLUS)
        return this->visit(node->left) + this->visit(node->right);
    else if (node->op->type == T_MINUS)
        return this->visit(node->left) - this->visit(node->right);
    else if (node->op->type == T_MULTIPLY)
        return this->visit(node->left) * this->visit(node->right);
    else if (node->op->type == T_DIVIDE)
        return this->visit(node->left) / this->visit(node->right);

    return 0;
};

int Interpreter::visit_UnaryOp(UnaryOp * node) {
    if (node->op->type == T_PLUS)
        return +this->visit(node->expr);
    else if (node->op->type == T_MINUS)
        return -this->visit(node->expr);

    return this->visit(node->expr);
}

int Interpreter::visit_Num(Num* node) {
    return node->value;
};

int Interpreter::visit_Compound(Compound* node) {
    int result = 0;

    for (std::vector<AST*>::iterator it = node->children.begin(); it != node->children.end(); ++it) {
        result += this->visit((*it));
    }

    return result;
};

int Interpreter::visit_Assign(Assign* node) {
    std::string varname = node->left->value;
    
    if (!RAM::has_variable(varname))
        throw std::runtime_error("Trying to assign to undeclared variable: `" + varname + "`");

    int value = this->visit(node->right);

    RAM::set_variable(varname, std::to_string(value));

    return value;
};

int Interpreter::visit_Var(Var* node) {
    std::string varname = node->value;
    std::string value = RAM::get_variable(varname);

    return std::stoi(value);
};

void Interpreter::visit_VarDecl(VarDecl* node) {
    RAM::set_variable(node->key, "");
};

int Interpreter::visit_NoOp(NoOp* node) { return 0;};

std::string Interpreter::interpret() {
    AST* tree = this->parser->parse();
    return std::to_string(this->visit(tree));
};
