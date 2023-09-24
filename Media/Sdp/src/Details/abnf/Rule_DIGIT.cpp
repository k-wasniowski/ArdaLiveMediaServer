/* -----------------------------------------------------------------------------
 * Rule_DIGIT.cpp
 * -----------------------------------------------------------------------------
 *
 * Producer : com.parse2.aparse.Parser 2.5
 * Produced : Mon Jan 08 13:30:55 CET 2018
 *
 * -----------------------------------------------------------------------------
 */

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "Rule_DIGIT.hpp"
#include "Visitor.hpp"
#include "ParserAlternative.hpp"
#include "ParserContext.hpp"

#include "Terminal_NumericValue.hpp"

using namespace abnf;

Rule_DIGIT::Rule_DIGIT(
  const string& spelling, 
  const vector<Rule*>& rules) : Rule(spelling, rules)
{
}

Rule_DIGIT::Rule_DIGIT(const Rule_DIGIT& rule) : Rule(rule)
{
}

Rule_DIGIT& Rule_DIGIT::operator=(const Rule_DIGIT& rule)
{
  Rule::operator=(rule);
  return *this;
}

Rule* Rule_DIGIT::clone() const
{
  return new Rule_DIGIT(this->spelling, this->rules);
}

void* Rule_DIGIT::accept(Visitor& visitor)
{
  return visitor.visit(this);
}

Rule_DIGIT* Rule_DIGIT::parse(ParserContext& context)
{
  context.push("DIGIT");

  bool parsed = true;
  int s0 = context.index;
  ParserAlternative a0(s0);

  vector<const ParserAlternative*> as1;
  parsed = false;
  {
    int s1 = context.index;
    ParserAlternative a1(s1);
    parsed = true;
    if (parsed)
    {
      bool f1 = true;
      int c1 = 0;
      Rule* rule = Terminal_NumericValue::parse(context, "%x30-39", 0x30, 0x39);
      if ((f1 = rule != NULL))
      {
        a1.add(rule, context.index);
        c1++;
      }
      parsed = c1 == 1;
    }
    if (parsed)
    {
      as1.push_back(new ParserAlternative(a1));
    }
    context.index = s1;
  }

  const ParserAlternative* b = ParserAlternative::getBest(as1);

  if ((parsed = b != NULL))
  {
    a0.add(b->rules, b->end);
    context.index = b->end;
  }

  for (vector<const ParserAlternative*>::const_iterator a = as1.begin(); a != as1.end(); a++)
  {
    delete *a;
  }

  Rule* rule = NULL;
  if (parsed)
  {
    rule = new Rule_DIGIT(context.text.substr(a0.start, a0.end - a0.start), a0.rules);
  }
  else
  {
    context.index = s0;
  }

  context.pop("DIGIT", parsed);

  return (Rule_DIGIT*)rule;
}

/* -----------------------------------------------------------------------------
 * eof
 * -----------------------------------------------------------------------------
 */
