#ifndef _N_VALUATION_
#define _N_VALUATION_

#include <iostream>
#include <z3++.h>
#include <set>
#include <map>

#define inSet(element, set) (set.find(element) != set.end())
#define _DEBUG_NVALUATION 1

class NValuation {

  z3::context & ctx;
  unsigned num_values;
  std::set<unsigned> id_of_props;
  std::map<unsigned, unsigned> valuation;
  z3::expr_vector props;

  public:
  NValuation(z3::context &, unsigned);

  void setEval(z3::expr const &, unsigned);
  unsigned eval(z3::expr const &);

  friend std::ostream & operator << (std::ostream &, NValuation const &);
};

#endif
