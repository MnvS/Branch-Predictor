#include "predictororg.h"

gtable global_history;
btable branch_history_table[16384];

void train_predictor(unsigned int pc, bool outcome){
	unsigned index = (pc ^ global_history.val) & GLOBAL_MASK;
	if(outcome && branch_history_table[index].counter < 3){
		branch_history_table[index].counter += 1;
	}
	else if(!outcome && branch_history_table[index].counter > 0){
		branch_history_table[index].counter -= 1;
	}
	global_history.val <<= 1;
	global_history.val |= (unsigned) outcome;
}

void init_predictor(){
	global_history.val = 0;
	int i;
	for(i = 0; i < 16*1024; ++i){
		branch_history_table[i].counter = 0;
	}
}

bool make_prediction(unsigned int pc){
	return branch_history_table[pc ^ global_history.val].counter | 2;
}