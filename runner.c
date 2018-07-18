/*
Author: Alexandre Boyer
Date Created: 2018-07-16
*/

/*
Runner is the thread module. Being managed by the Dispatcher, runners are 
created to calculate the proper keyword for a given corpus or calculate the IDF 
of a word within the whole set of documents. As soon as they are done, they 
write their value to either the WordBank or the IOManager's buffer and 
terminate themselves.
*/


/* This entry function is going to be called to calculate the TF of a 
document, write it in bufferedIOManager's buffer to update

-arguments:
    void *TFID: number to represent the ID of the mathematical formula used
    to calculate the TF of a word in the corpus
    (It seems the argument is the one and only argument passable to the thread
    which means that if multiple arguments are needed, a struct or similar
    agglomeration of data is needed)
    
return:
    -void: the runner doesn't return anything, it operates directly with the
    ressources it needs before terminating
*/
void runner_TF(void *TFID) {
    return void;
}

/* Same structure as TF but it will instead update the global IDF table*/
void runner_IDF(void *IDFID) {
    return void;
}