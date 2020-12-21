/* I asked a question on StackOverflow about why the following
 * code generates a false alarm in 3 static analysers I tried.
 * Frama-C people responded with the 'split status' suggestions
 * employed below.
 *
 * My question, and the extensive answer from Frama-C people
 * is in here:
 *   https://stackoverflow.com/questions/62541252/
 *      static-analysis-erroneously-reports-out-of-bounds-access
 */
extern int checker(int id);
extern int checker2(int id);
 
int compute(int *q)
{
    int res = 0, status;

    status = checker2(12);
    //@ split status <= 0;
    //@ split status == 0;
    if (!status) {
        status = 1;
        *q = 2;
        for(int i=0; i<2 && 0!=status; i++) {
            if (checker(i)) {
                res = i;
                status=checker2(i);
            }
        }
    }
    //@ split status <= 0;
    //@ split status == 0;
    if (!status)
        *q = res;
    return status;
}
 
int someFunc(int id)
{
    int p;
    extern int data[2];

    int status = checker2(132);
    //@ split status <= 0;
    //@ split status == 0;
    status |= compute(&p);
    if (status == 0) {
        return data[p];
    } else
        return -1;
}
