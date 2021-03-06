#include "../../includes/AST/builtin_objects/AST_WScript_Echo.hpp"
#include "../../includes/typedefs.hpp"


AST_WScript_Echo::AST_WScript_Echo(std::string name) : AST_BuiltinFunctionDefinition(name) {
    this->unlimited_args = true;
};

AST_WScript_Echo::~AST_WScript_Echo() {
    this->expected_args.clear();
};

AST* AST_WScript_Echo::call(std::vector<AST*> args, Interpreter* interpreter) {
    if (args.size()) {
        for (
                std::vector<AST*>::iterator it = args.begin();
                it != args.end();
                ++it
            ) {

            anything x = interpreter->visit((*it));
            coutprint(x);
        }
    }

    AST_NoOp* noop = new AST_NoOp();

    args.clear();

    return noop;
};
