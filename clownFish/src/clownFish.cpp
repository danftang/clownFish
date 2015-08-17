/*
 * clowfnFish.cpp
 *
 *  Created on: 16 Aug 2015
 *      Author: daniel
 */

#include <algorithm>
#include <iostream>
#include <functional>
#include "Fish.h"

using namespace std;

default_random_engine ranGen;
bernoulli_distribution flip(0.5);

bool myFlip() {
	return(flip(ranGen));
	//[&](char a){ return f(a); }
}

Fish sexChange(Fish &oldFish) {
	Fish newFish;
	newFish.married = oldFish.married;
	newFish.male = flip(ranGen);
	return(newFish);
}

int main() {
	long n=1000; // Initial number of fish
	long nMales;
	long nMarried;
//	long unmatched; // unmatched fish after first round
//	long unmatched2; // unmatched fish after second round
//	double unmatchedInfected; 	// first-round infected
//	double matchedInfected;	// infected from affairs

	vector<Fish> fish(n);

	// --- first sex change
//	generate(fish.begin(), fish.end(), myFlip);
	transform(fish.begin(), fish.end(), fish.begin(), sexChange);

	nMales = count_if(fish.begin(), fish.end(), [](Fish f){ return f.male; });
	cout << nMales << endl;
//	unmatched = labs(2*nMales - n);

	// --- write a version of this using transform
	for_each(fish.begin(), fish.end(), [&fish](Fish &f) {
		if(f.male) {
			// parallel search, lock on find (i.e. unique find)
			vector<Fish>::iterator partner = find_if(fish.begin(), fish.end(), [](Fish &f2) {
				return(f2.married == false && f2.male == false);
			});
			if(partner != fish.end()) {
				f.married = true;
				partner->married = true; // this is a side-effect (perhaps easier not to allow this)
			}
		}
	});
	nMarried = count_if(fish.begin(), fish.end(), [](Fish f){ return f.married; });

	cout << nMarried << endl;

	return(0);
}
