#include "Parser.h"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/variant/recursive_wrapper.hpp>
#include <QDebug>
#include "CompoundFilter.h"
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
    Builder(CompoundFilterNodePtr& currentRoot, const Filters& filters)
       : _currentRoot(currentRoot)
       , _filters{filters}
    {
       _currentRoot = CompoundFilterNodePtr::create();
    }
    CompoundFilterNodePtr& _currentRoot;
    const Filters& _filters;

    void operator()(const var& filterName) const
    {
       const auto it = std::find_if(_filters.begin(), _filters.end(),
          [&](const auto& filter)
       {
          return filter->GetName() == filterName.data();
       });
       if (it != _filters.end())
       {
          _currentRoot->operation = Operation::Value;
          _currentRoot->m_filter = *it;
       }
       else
       {
          throw std::invalid_argument("Filter not found");
       }
    }

    void operator()(const binop<op_and>& b) const { buildExpression(Operation::And, b.oper1, b.oper2); }
    void operator()(const binop<op_or >& b) const { buildExpression(Operation::Or, b.oper1, b.oper2); }

    void buildExpression(Operation op, const expr& l, const expr& r) const
    {
        boost::apply_visitor(Builder(_currentRoot->m_leftOperand, _filters), l);
        _currentRoot->operation = op;
        boost::apply_visitor(Builder(_currentRoot->m_rightOperand, _filters), r);
    }

    void operator()(const unop<op_not>& u) const
    {
       _currentRoot->operation = Operation::Not;
       boost::apply_visitor(Builder(_currentRoot->m_leftOperand, _filters), u.oper1);
    }
};

void createCompoundNode(const expr& e, CompoundFilterNodePtr& root, const Filters& filters)
{
   boost::apply_visitor(Builder(root, filters), e);
}

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
}

FilterPtr Parser::ParseExpression(const QString& name, std::string expression, const Filters& filters, QString& error)
{
   if (!expression.empty() && expression[expression.length() - 1] != ';')
   {
      expression += ";";
   }

   auto f(std::begin(expression)), l(std::end(expression));
   parser<decltype(f)> p;
   CompoundFilterNodePtr root;
   try
   {
      expr result;
      auto ok = qi::phrase_parse(f,l,p > ';',qi::space,result);
      if (ok)
      {
         createCompoundNode(result, root, filters);
      }
      else
      {
         return nullptr;
      }
   }
   catch (const qi::expectation_failure<decltype(f)>& e)
   {
      error = "Incorrect expression";
      qDebug() << "expectation_failure at \n";
      return nullptr;
   }
   catch (const std::exception& e)
   {
      error = e.what();
      qDebug() << "exception " <<  e.what() << "\n";
      return nullptr;
   }

   return QSharedPointer<CompoundFilter>::create(name, expression.data(), SearchType::Compound, root);
}
