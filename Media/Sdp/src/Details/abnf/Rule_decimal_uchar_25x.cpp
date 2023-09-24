/* -----------------------------------------------------------------------------
 * Rule_decimal_uchar_25x.cpp
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

#include "Rule_decimal_uchar_25x.hpp"
#include "Visitor.hpp"
#include "ParserAlternative.hpp"
#include "ParserContext.hpp"

#include "Terminal_StringValue.hpp"

using namespace abnf;

Rule_decimal_uchar_25x::Rule_decimal_uchar_25x(
  const string& spelling, 
  const vector<Rule*>& rules) : Rule(spelling, rules)
{
}

Rule_decimal_uchar_25x::Rule_decimal_uchar_25x(const Rule_decimal_uchar_25x& rule) : Rule(rule)
{
}

Rule_decimal_uchar_25x& Rule_decimal_uchar_25x::operator=(const Rule_decimal_uchar_25x& rule)
{
  Rule::operator=(rule);
  return *this;
}

Rule* Rule_decimal_uchar_25x::clone() const
{
  return new Rule_decimal_uchar_25x(this->spelling, this->rules);
}

void* Rule_decimal_uchar_25x::accept(Visitor& visitor)
{
  return visitor.visit(this);
}

Rule_decimal_uchar_25x* Rule_decimal_uchar_25x::parse(ParserContext& context)
{
  context.push("decimal-uchar-25x");

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
      Rule* rule = Terminal_StringValue::parse(context, "2");
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
      Rule* rule = Terminal_StringValue::parse(context, "5");
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
          Rule* rule = Terminal_StringValue::parse(context, "0");
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
      {
        int s2 = context.index;
        ParserAlternative a2(s2);
        parsed = true;
        if (parsed)
        {
          bool f2 = true;
          int c2 = 0;
          Rule* rule = Terminal_StringValue::parse(context, "1");
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
      {
        int s2 = context.index;
        ParserAlternative a2(s2);
        parsed = true;
        if (parsed)
        {
          bool f2 = true;
          int c2 = 0;
          Rule* rule = Terminal_StringValue::parse(context, "2");
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
      {
        int s2 = context.index;
        ParserAlternative a2(s2);
        parsed = true;
        if (parsed)
        {
          bool f2 = true;
          int c2 = 0;
          Rule* rule = Terminal_StringValue::parse(context, "3");
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
      {
        int s2 = context.index;
        ParserAlternative a2(s2);
        parsed = true;
        if (parsed)
        {
          bool f2 = true;
          int c2 = 0;
          Rule* rule = Terminal_StringValue::parse(context, "4");
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
      {
        int s2 = context.index;
        ParserAlternative a2(s2);
        parsed = true;
        if (parsed)
        {
          bool f2 = true;
          int c2 = 0;
          Rule* rule = Terminal_StringValue::parse(context, "5");
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
    rule = new Rule_decimal_uchar_25x(context.text.substr(a0.start, a0.end - a0.start), a0.rules);
  }
  else
  {
    context.index = s0;
  }

  context.pop("decimal-uchar-25x", parsed);

  return (Rule_decimal_uchar_25x*)rule;
}

/* -----------------------------------------------------------------------------
 * eof
 * -----------------------------------------------------------------------------
 */
