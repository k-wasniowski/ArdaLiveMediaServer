/* -----------------------------------------------------------------------------
 * Rule_time_repeat_field.cpp
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

#include "Rule_time_repeat_field.hpp"
#include "Visitor.hpp"
#include "ParserAlternative.hpp"
#include "ParserContext.hpp"

#include "Rule_repeat_field.hpp"
#include "Rule_time_field.hpp"

using namespace abnf;

Rule_time_repeat_field::Rule_time_repeat_field(
  const string& spelling, 
  const vector<Rule*>& rules) : Rule(spelling, rules)
{
}

Rule_time_repeat_field::Rule_time_repeat_field(const Rule_time_repeat_field& rule) : Rule(rule)
{
}

Rule_time_repeat_field& Rule_time_repeat_field::operator=(const Rule_time_repeat_field& rule)
{
  Rule::operator=(rule);
  return *this;
}

Rule* Rule_time_repeat_field::clone() const
{
  return new Rule_time_repeat_field(this->spelling, this->rules);
}

void* Rule_time_repeat_field::accept(Visitor& visitor)
{
  return visitor.visit(this);
}

Rule_time_repeat_field* Rule_time_repeat_field::parse(ParserContext& context)
{
  context.push("time-repeat-field");

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
      Rule* rule = Rule_time_field::parse(context);
      if ((f1 = rule != NULL))
      {
        a1.add(rule, context.index);
        c1++;
      }
      parsed = c1 == 1;
    }
    if (parsed)
    {
      bool f1 = true;
      int c1 = 0;
      while (f1)
      {
        unsigned int g1 = context.index;
        vector<const ParserAlternative*> as2;
        parsed = false;
        {
          int s2 = context.index;
          ParserAlternative a2(s2);
          parsed = true;
          if (parsed)
          {
            bool f2 = true;
            int c2 = 0;
            Rule* rule = Rule_repeat_field::parse(context);
            if ((f2 = rule != NULL))
            {
              a2.add(rule, context.index);
              c2++;
            }
            parsed = c2 == 1;
          }
          if (parsed)
          {
            as2.push_back(new ParserAlternative(a2));
          }
          context.index = s2;
        }

        const ParserAlternative* b = ParserAlternative::getBest(as2);

        if ((parsed = b != NULL))
        {
          a1.add(b->rules, b->end);
          context.index = b->end;
        }

        for (vector<const ParserAlternative*>::const_iterator a = as2.begin(); a != as2.end(); a++)
        {
          delete *a;
        }

        f1 = context.index > g1;
        if (parsed) c1++;
      }
      parsed = true;
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
    rule = new Rule_time_repeat_field(context.text.substr(a0.start, a0.end - a0.start), a0.rules);
  }
  else
  {
    context.index = s0;
  }

  context.pop("time-repeat-field", parsed);

  return (Rule_time_repeat_field*)rule;
}

/* -----------------------------------------------------------------------------
 * eof
 * -----------------------------------------------------------------------------
 */
