#include <stdio.h>
#include <stdlib.h>

//program to output binomial distribution probabilities with specified number of things and probability of success in selecting 
//all r (# of choices (selections) that are the choice that we care about and not the other) 
//will be generated and outputted with the associated probability of success
//so if there were 7 things and the probability of choosing the type that we care about is 0.2, 
//then for each r (# of choices (selections)) the probality of selecting the type that we care about will be output

struct bin_dist_probability{
    int n;
    int r;
    float prob;
};

int n_choose_r_func(int n, int r){
    int n_choose_r;
    if(r == 0){
        n_choose_r = 1;
    }
    else{
        n_choose_r = n;
        int i;
        for(i = 1; i < r; i++){
            n_choose_r = n_choose_r * (n - i);
        }
        for(i = r; i > 0; i--){
            n_choose_r = n_choose_r / i;
        }
    }

    return n_choose_r;
}

float exp_func(float base, int power){
    if(power == 0){
        return 1;
    }
    int i;
    float ret = base;
    for(i = 0; i < power - 1; i++){
        ret = ret * base;
    }

    return ret;
}

void find_prob_n_r_and_prob(struct bin_dist_probability *one_prob, float prob){
    int n_choose_r = n_choose_r_func(one_prob->n, one_prob->r);

    //just printing
    printf("n: %d, r: %d\n", one_prob->n, one_prob->r);

    one_prob->prob = n_choose_r * exp_func(prob, one_prob->r) * exp_func((1 - prob), (one_prob->n - one_prob->r));
    //just printing
    printf("one_prob->prob: %f\n", one_prob->prob);
}

int main(int argc, char **argv){
    int n = 0;
    float p = 0;

    printf("n (number of things selecting from):\n");
    scanf("%d", &n);
    printf("p (probability of selecting the one of the two available things to select that we care about):\n");
    scanf("%f", &p);

    struct bin_dist_probability **bin_dist_probabilities = (struct bin_dist_probability *)malloc(n * sizeof(struct bin_dist_probability));

    int i;
    for(i = 0; i <= n; i++){
        bin_dist_probabilities[i] = (struct bin_dist_probability *)malloc(sizeof(struct bin_dist_probability));
        bin_dist_probabilities[i]->n = n;
        bin_dist_probabilities[i]->r = i;
        find_prob_n_r_and_prob(bin_dist_probabilities[i], p);
    }
    
    for(i = 0; i < n; i++){
        free(bin_dist_probabilities[i]);
    }
    free(bin_dist_probabilities);

}