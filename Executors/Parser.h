#include <QString>
#include "Types.h"
class Parser
{
public:
   static FilterPtr ParseExpression(const QString& name, std::string expresion, const Filters& filters);
};

