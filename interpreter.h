#pragma once
#include <string>
#include <memory>
#include <regex>

/**
 * @brief The expression tree
 * @details
 *  Expression: StartBlock | Command | EndBlock
 *  StartBlock: OpenBlock | Command
 *  Command: "[a-z0-9]+"
 *  EndBlock: CloseBlock | Command | OpenBlock
 *  OpenBlock: "{"
 *  CloseBlock: "}"
 */

class Expression
{
    public:
        enum class Type { TerminalExpression,
                          NonTerminalExpression };

        Expression(const std::string& name, Type type)
            : name_(name), type_(type) {}
        virtual bool interpret(const std::string& input) = 0;

        const std::string& name() const { return name_; }
        Type type() const { return type_; }

    private:
        const std::string name_;
        const Type type_;
};

using ExpressionUPtr = std::unique_ptr<Expression>;

class TerminalExpression : public Expression
{
    public:
        TerminalExpression(const std::string& reg_expr)
            : Expression (reg_expr, Expression::Type::TerminalExpression)
            , reg_exp_(reg_expr, std::regex::extended) {}

        bool interpret(const std::string& input) override;

    private:
        const std::regex reg_exp_;
};

class NonTerminalExpression : public Expression
{
    public:
        NonTerminalExpression(ExpressionUPtr& term_left,
                              ExpressionUPtr& term_right)
            : Expression ("NonTerminalExpression",
                          Expression::Type::NonTerminalExpression)
            , term_left_(std::move(term_left))
            , term_right_(std::move(term_right))
        {}

        bool interpret(const std::string& input) override;

    private:
        ExpressionUPtr term_left_;
        ExpressionUPtr term_right_;
};
