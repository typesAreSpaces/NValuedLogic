#include <iostream>
#include "NValuation.h"
#include <z3++.h>

int main(){

  z3::context ctx;

  z3::expr A = ctx.bool_const("A");
  z3::expr B = ctx.bool_const("B");
  z3::expr formula_1 = not(A) || A;
  z3::expr formula_2 = z3::implies(not(not(A)), A);
  z3::expr formula_3 = z3::implies(z3::implies(not(B), not(A)), z3::implies(A, B));

  bool found_assignment = false;
  unsigned num_values = 2;
  while(true){
    NValuation n(ctx, num_values);

    for(unsigned i = 0; i < num_values; i++){
      n.setEval(A, i);

      if(n.eval(formula_1) != 0){
        std::cout << "Formula" << std::endl;
        std::cout << formula_1 << std::endl;
        std::cout << "evals to " << n.eval(formula_1) 
          << " with" << std::endl;
        std::cout << "Num of truth values: " << num_values 
          << std::endl;
        std::cout << "Assignment:" << std::endl;
        std::cout << n << std::endl;
        found_assignment = true;
      }

    }

    num_values++;
    if(found_assignment)
      break;
  }

  found_assignment = false;
  num_values = 2;
  while(true){
    NValuation n(ctx, num_values);

    for(unsigned i = 0; i < num_values; i++){
      n.setEval(A, i);

      if(n.eval(formula_2) != 0){
        std::cout << "Formula" << std::endl;
        std::cout << formula_2 << std::endl;
        std::cout << "evals to " << n.eval(formula_2) 
          << " with" << std::endl;
        std::cout << "Num of truth values: " << num_values 
          << std::endl;
        std::cout << "Assignment:" << std::endl;
        std::cout << n << std::endl;
        found_assignment = true;
      }

    }

    num_values++;
    if(found_assignment)
      break;
  }

  found_assignment = false;
  num_values = 2;
  while(true){
    NValuation n(ctx, num_values);

    for(unsigned i = 0; i < num_values; i++){
      n.setEval(A, i);

      for(unsigned j = 0; j < num_values; j++){
        n.setEval(B, j);

        if(n.eval(formula_3) != 0){
          std::cout << "Formula" << std::endl;
          std::cout << formula_3 << std::endl;
          std::cout << "evals to " << n.eval(formula_3) 
            << " with" << std::endl;
          std::cout << "Num of truth values: " << num_values 
            << std::endl;
          std::cout << "Assignment:" << std::endl;
          std::cout << n << std::endl;
          found_assignment = true;
        }

      }

    }

    num_values++;
    if(found_assignment)
      break;
  }

  return 0;
}
