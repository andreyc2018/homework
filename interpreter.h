#pragma once
#include "command.h"

class ParserContext;

/**
 * @brief The expression tree
 * @details
 *  Expression: StartBlock | Command | EndBlock
 *  StartBlock: "{" | Command
 *  Command: "[a-z0-9]+"
 *  EndBlock: "}" | Command | "{"
 */

class Expression
{
    public:
        enum class Type { StartBlock, Command, EndBlock };

        Expression(const std::string& name, Type type)
            : name_(name), type_(type) {}
        virtual bool interpret(ParserContext& ctx, std::string input) = 0;

        const std::string& name() const { return name_; }
        Type type() const { return type_; }

    private:
        const std::string name_;
        const Type type_;
};

using ExpressionUPtr = std::unique_ptr<Expression>;

class StartBlockExpr: public Expression
{
    public:
        StartBlockExpr()
            : Expression("StartBlockExpr", Expression::Type::StartBlock) {}

        bool interpret(ParserContext& ctx, std::string input) override;
};

class CommandExpr: public Expression
{
    public:
        CommandExpr()
            : Expression("CommandExpr", Expression::Type::Command) {}

        bool interpret(ParserContext& ctx, std::string input) override;
};

class EndBlockExpr: public Expression
{
    public:
        EndBlockExpr()
            : Expression("EndBlockExpr", Expression::Type::EndBlock) {}

        bool interpret(ParserContext& ctx, std::string input) override;
};
