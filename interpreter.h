#pragma once
#include <string>
#include <memory>
#include <regex>
#include <algorithm>

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
using ExpressionPtr = std::shared_ptr<Expression>;

class TerminalExpression : public Expression
{
    public:
        TerminalExpression(const std::string& reg_expr);

        bool interpret(const std::string& input) override;

    private:
        const std::regex reg_exp_;
};

template<typename T, typename... Args>
class NonTerminalExpression : public Expression
{
    public:
        NonTerminalExpression(T first, Args... other)
            : Expression ("NonTerminalExpression",
                          Expression::Type::NonTerminalExpression)
            , terms_ { first, other... }
        {}


        bool interpret(const std::string& input) override
        {
            return std::any_of(std::begin(terms_), std::end(terms_),
                               [&input](const T& term) {
                return term->interpret(input);
            });
        }

    private:
        std::array<T, sizeof... (Args)+1> terms_;
};
