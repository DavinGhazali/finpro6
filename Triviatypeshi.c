#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void RandomTrivia(char *trivia[], int n);
char Again();

int main() {
    char *trivia[] = {
        "Did you know? 1/3 of all food produced globally is wasted.",
        "Did you know? Every foods have an expiration date, always check them before eating.",
        "Did you know? A lot of food that is colored may have bad chemicals in them, don't eat too much of it!",
        "Did you know? To kill off bacteria in your food you must first cook them.",
        "Did you know? To preserve foods longer you can either salt them or smoke them.",
        "Did you know? Choosing local food cuts transport emissions.",
        "Did you know? SDG 12 focuses on safe consumption and production.",
        "Did you know? Using resources wisely and reducing waste is one of SDG 12 goals.",
        "Did you know? SDG12 strives to make products using fewer resources and less pollution.",
        "Did you know? The 3Rs of SDG 12 are Reduce, Reuse, Recycle.",
        "Did you know? 13% of food is lost along the supply chain.",
        "Did you know? 19% of food is lost at the consumer level."
    };

    int n = sizeof(trivia) / sizeof(trivia[0]);
    char again;

    srand(time(NULL));

    do {
        RandomTrivia(trivia, n);
        again = Again();
    } while (again == 'y' || again == 'Y');

    printf("\nBye Bye!\n");
    return 0;
}


void RandomTrivia(char *trivia[], int n) {
    int i = rand() % n;
    printf("\n%s\n", trivia[i]);
}


char Again() {
    char input;
    printf("More trivia? (y/n): ");
    scanf(" %c", &input);
    return input;
}
