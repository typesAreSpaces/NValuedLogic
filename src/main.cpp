#include <iostream>
#include "NValuation.h"
#include <z3++.h>

void unaryFormulas(z3::expr const &, z3::expr const &);
void binaryFormulas(z3::expr const &, z3::expr const &, z3::expr const &);
void threeAryFormulas(z3::expr const &, z3::expr const &, z3::expr const &, z3::expr const &);

int main(){

  z3::context ctx;

  z3::expr A = ctx.bool_const("A");
  z3::expr B = ctx.bool_const("B");
  z3::expr C = ctx.bool_const("C");
  z3::expr formula_1 = not(A) || A;
  z3::expr formula_2 = z3::implies(not(not(A)), A);
  z3::expr formula_3 = z3::implies(z3::implies(not(B), not(A)), z3::implies(A, B));
  z3::expr formula_4 = z3::implies(z3::implies(A, z3::implies(B, C)), z3::implies(z3::implies(A, B), z3::implies(A, C)));

  //unaryFormulas(formula_1, A);
  //unaryFormulas(formula_2, A);
  //binaryFormulas(formula_3, A, B);
  threeAryFormulas(formula_4, A, B, C);

  return 0;
}

void unaryFormulas(z3::expr const & formula, z3::expr const & var1){
  bool found_assignment = false;
  unsigned num_values = 2;
  while(true){
    NValuation n(formula.ctx(), num_values);

    for(unsigned i = 0; i < num_values; i++){
      n.setEval(var1, i);
      if(n.eval(formula) != 0){
        std::cout << "Formula" << std::endl;
        std::cout << formula << std::endl;
        std::cout << "evals to " << n.eval(formula) 
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
}

void binaryFormulas(z3::expr const & formula, z3::expr const & var1, z3::expr const & var2){
  bool found_assignment = false;
  unsigned num_values = 2;
  while(true){
    NValuation n(formula.ctx(), num_values);

    for(unsigned i = 0; i < num_values; i++){
      n.setEval(var1, i);
      for(unsigned j = 0; j < num_values; j++){
        n.setEval(var2, j);
        if(n.eval(formula) != 0){
          std::cout << "Formula" << std::endl;
          std::cout << formula << std::endl;
          std::cout << "evals to " << n.eval(formula) 
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
}

void threeAryFormulas(z3::expr const & formula, z3::expr const & var1, z3::expr const & var2, z3::expr const & var3){
  bool found_assignment = false;
  unsigned num_values = 2;
  while(true){
    NValuation n(formula.ctx(), num_values);

    for(unsigned i = 0; i < num_values; i++){
      n.setEval(var1, i);
      for(unsigned j = 0; j < num_values; j++){
        n.setEval(var2, j);
        for(unsigned k = 0; k < num_values; k++){
          n.setEval(var3, k);
          if(n.eval(formula) != 0){
            std::cout << "Formula" << std::endl;
            std::cout << formula << std::endl;
            std::cout << "evals to " << n.eval(formula) 
              << " with" << std::endl;
            std::cout << "Num of truth values: " << num_values 
              << std::endl;
            std::cout << "Assignment:" << std::endl;
            std::cout << n << std::endl;
            found_assignment = true;
          }

        }
      }
    }
    num_values++;
    if(found_assignment)
      break;
  }
}
