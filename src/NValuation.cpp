#include "NValuation.h"
#include <z3++.h>

NValuation::NValuation(
    z3::context & ctx, 
    unsigned num_values):
  ctx(ctx),
  num_values(num_values),
  id_of_props({}),
  props(ctx)
{
}

void NValuation::setEval(
    z3::expr const & prop, 
    unsigned assignment_value){

  assert(assignment_value <= num_values);
  assert(prop.is_bool() && prop.is_const());

  unsigned curr_prop_id = prop.id();

  if(inSet(curr_prop_id, id_of_props)){
    valuation[prop.id()] = assignment_value;
    return;
  }

  id_of_props.insert(curr_prop_id);
  valuation.insert(
      std::pair<unsigned, unsigned>(
        curr_prop_id, assignment_value));
  props.push_back(prop);
}

unsigned NValuation::eval(z3::expr const & form){
  assert(form.is_bool());
  if(form.is_const()){

    if(valuation.find(form.id()) == valuation.end())
      throw "Error: propositional hasn't been assigned a value";

    return valuation.find(form.id())->second;
  }

  switch(form.decl().decl_kind()){
    case Z3_OP_AND:
      {
        unsigned curr_max = 0;
        for(unsigned i = 0; i < form.num_args(); i++){
          unsigned temp_max = eval(form.arg(i));
          if(curr_max < temp_max)
            curr_max = temp_max;
        }
        return curr_max;
      }
    case Z3_OP_OR:
      {
        unsigned curr_min = num_values;
        for(unsigned i = 0; i < form.num_args(); i++){
          unsigned temp_min = eval(form.arg(i));
          if(curr_min > temp_min)
            curr_min = temp_min;
        }
        return curr_min;
      }
    case Z3_OP_IMPLIES:
      {
        unsigned eval_a = eval(form.arg(0));
        unsigned eval_b = eval(form.arg(1));
        if(eval_a >= eval_b)
          return 0;
        return eval_b;
      }
    case Z3_OP_NOT:
      {
        unsigned eval_a = eval(form.arg(0));
        if(eval_a == num_values)
          return 0;
        return num_values;
      }
    default:
      throw "Error: operation not supported";
  }

  return 0;
}

std::ostream & operator << (std::ostream & os, NValuation const & n){

  for(auto const & prop : n.props)
    os << "Proposition: " <<  prop 
      << " Assignment: " << n.valuation.find(prop.id())->second
      << std::endl;
  return os;
}
