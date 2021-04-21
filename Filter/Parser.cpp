#include "Parser.h"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/variant/recursive_wrapper.hpp>
#include <QDebug>
namespace
{

namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

struct op_or  {};
struct op_and {};
struct op_not {};

using var = std::string;
template <typename tag> struct binop;
template <typename tag> struct unop;

using expr = boost::variant<var,
        boost::recursive_wrapper<unop<op_not> >,
        boost::recursive_wrapper<binop<op_and> >,
        boost::recursive_wrapper<binop<op_or> >
        >;

template <typename tag>
struct binop
{
    explicit binop(const expr& l, const expr& r) : oper1{l}, oper2{r} { }
    expr oper1, oper2;
};

template <typename tag>
struct unop
{
    explicit unop(const expr& o) : oper1{o} { }
    expr oper1;
};

struct Builder : boost::static_visitor<void>
{
    Builder(QDebug& os) : _os(os) {}
    QDebug& _os;

    void operator()(const var& v) const { _os << v.data(); }

    void operator()(const binop<op_and>& b) const { print(" & ", b.oper1, b.oper2); }
    void operator()(const binop<op_or >& b) const { print(" | ", b.oper1, b.oper2); }

    void print(const std::string& op, const expr& l, const expr& r) const
    {
        _os << "(";
            boost::apply_visitor(*this, l);
            _os << op.data();
            boost::apply_visitor(*this, r);
        _os << ")";
    }

    void operator()(const unop<op_not>& u) const
    {
        _os << "(";
            _os << "!";
            boost::apply_visitor(*this, u.oper1);
        _os << ")";
    }
};

QDebug& operator<<(QDebug& os, const expr& e)
{ boost::apply_visitor(Builder(os), e); return os; }

template <typename It, typename Skipper = qi::space_type>
    struct parser : qi::grammar<It, expr(), Skipper>
{
    parser() : parser::base_type(expr_)
    {
        using namespace qi;

       expr_  = or_.alias();

       not_ = ("!" > simple       ) [ _val = phx::construct<unop <op_not>>(_1)     ] | simple [ _val = _1 ];
       or_  = and_ [ _val = _1 ] >> *("||"  >> and_ [ _val = phx::construct<binop<op_or>> (_val, _1) ]);
       and_ = not_ [ _val = _1 ] >> *("&&" >> not_ [ _val = phx::construct<binop<op_and>>(_val, _1) ]);

       simple = (('(' > expr_ > ')') | var_);
       var_ = qi::lexeme[ +alpha ];

        BOOST_SPIRIT_DEBUG_NODE(expr_);
        BOOST_SPIRIT_DEBUG_NODE(or_);
        BOOST_SPIRIT_DEBUG_NODE(and_);
        BOOST_SPIRIT_DEBUG_NODE(not_);
        BOOST_SPIRIT_DEBUG_NODE(simple);
        BOOST_SPIRIT_DEBUG_NODE(var_);
    }

  private:
    qi::rule<It, var() , Skipper> var_;
    qi::rule<It, expr(), Skipper> not_, and_, or_, simple, expr_;
};

   void parseExpression(const QString&)
   {

   }
}

void Parser::ParseExpression(const QString&)
{
   for (auto& input : std::list<std::string> {
           // From the OP:
//           "a && b;"
           "a && b && (c || (d && a) || b);",

           /// Simpler tests:
//           "!a;",
//           "!a && b;",
//           "! (a && b);"
           })
   {
       auto f(std::begin(input)), l(std::end(input));
       parser<decltype(f)> p;

       try
       {
           expr result;
           bool ok = qi::phrase_parse(f,l,p > ';',qi::space,result);

           if (!ok)
               qDebug() << "invalid input\n";
           else
               qDebug() << "result: " << result << "\n";

       } catch (const qi::expectation_failure<decltype(f)>& e)
       {
           qDebug() << "expectation_failure at \n";
       }
   }
}
