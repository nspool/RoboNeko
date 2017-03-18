//
//  Markov.cpp
//  RoboNeko
//
//  Created by nsp on 16/3/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#include "Markov.hpp"

int Markov::GetNextState()
{
  int next = arc4random_uniform(5);
  return next;
}
