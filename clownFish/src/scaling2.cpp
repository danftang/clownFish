#include <iostream>
#include <cstdlib>
#include <cmath>
#include <random>

std::default_random_engine randGen;

// flip a coin n times and return the number of heads
long randBinomial(long n) {
  std::binomial_distribution<long> dist(n,0.5);
  return(dist(randGen));
}

int main() {
  const long TRIALS = 50000;
  long trial,n;
  long unmatched; // unmatched fish after first round
  long unmatched2; // unmatched fish after second round
  double unmatchedInfected; 	// first-round infected
  double matchedInfected;	// infected from affairs

  for(n = 15; n < 2000000; n*=1.2) {
      unmatchedInfected = 0.0;
      matchedInfected = 0.0;
      for(trial = 0; trial < TRIALS; ++trial) {
	unmatched = labs(2*randBinomial(n) - n);
	unmatched2 = labs(2*randBinomial(unmatched) - unmatched);
	unmatchedInfected += unmatched;
	matchedInfected += floor(((n-unmatched)/2)*
				 (1.0-pow(39.0/40.0,unmatched2)));
      }
      unmatchedInfected /= n*1.0*TRIALS;
      matchedInfected /= n*1.0*TRIALS;
      std::cout <<
	log(n) << " " << unmatchedInfected << " " << matchedInfected
	       << " " << unmatchedInfected + matchedInfected
	       << std::endl;
  }

  return 0;
}
