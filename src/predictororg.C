#include "predictororg.h"

struct gtable global_history;
struct btable branch_history_table[16384];

/**
 * Update global history and branch history table
 */
void train_predictor(unsigned int pc, bool outcome){
	
	//update branch history
	unsigned index = (pc ^ global_history.val) & GLOBAL_MASK;
	if(outcome && branch_history_table[index].counter < 3){
		branch_history_table[index].counter += 1;
	}
	else if(!outcome && branch_history_table[index].counter > 0){
		branch_history_table[index].counter -= 1;
	}
	
	//update global history
	global_history.val <<= 1;
	global_history.val |= (unsigned) outcome;
}

/**
 * Initialize predictor
 * All counters are set to 0 (not taken)
 */
void init_predictor(){
	global_history.val = 0;
	int i;
	for(i = 0; i < 16*1024; ++i){
		branch_history_table[i].counter = 0;
	}
}

/**
 * Give prediction of branch
 */
bool make_prediction(unsigned int pc){
	unsigned index = (pc ^ global_history.val) & GLOBAL_MASK;
	return branch_history_table[index].counter & 2;
}