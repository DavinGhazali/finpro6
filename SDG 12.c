#include <stdio.h>
#include <string.h>
#include <time.h>   // <-- for timer

#define MAX_NAME 50
#define NUM_QUESTIONS 12   // using the 12 trivia items (0–11)
#define TIME_LIMIT 20      // seconds allowed per question

typedef struct {
    const char *sceneText;     // Story + trivia + question
    const char *optA;
    const char *optB;
    const char *optC;
    const char *optD;
    char correct;              // 'A', 'B', 'C', or 'D'
    const char *successText;   // Story feedback if correct
    const char *failText;      // Story feedback if wrong
} Question;

void clearScreen() {
    // Simple fake "clear" for portability
    printf("\n\n\n\n\n\n\n\n\n\n");
}

void waitEnter() {
    int c;
    printf("\n(Press ENTER to continue...)");
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void printIntro(char name[]) {
    clearScreen();
    printf("=================================================\n");
    printf("      SDG 12 SIMULATION TRIVIA \n");
    printf("=================================================\n\n");
    printf("Welcome to the SDG 12 Trivia!\n");
    printf("In here, You will be simulated as an employee in a software company.\n");
    printf("Its your payday and your task is to use your salary as effiecient and effective as possible\n\n");
    printf("Your decision relies on your answer\n");
    printf("The more correct answers you give, the greater the output of your score and summary.\n");
    printf("Each scene gives you a question and gives out a fact after answering.\n");
    printf("With this simulation hopefully we can develop a greener mindset for a better future!\n\n");
    printf("Each question is TIMED: you have %d seconds to answer!\n\n", TIME_LIMIT);

    printf("Before we start, what is your name? ");
    fgets(name, MAX_NAME, stdin);

    // remove trailing newline
    size_t len = strlen(name);
    if (len > 0 && name[len - 1] == '\n') {
        name[len - 1] = '\0';
    }

    clearScreen();
    printf("Nice to meet you, %s.\n\n", name);
    printf("Your mission:\n");
    printf("- Answer the questions correctly AND quickly with every knowledge you have in mind.\n");

    waitEnter();
}

int askQuestion(Question q, int index) {
    char answer;
    int c;

    clearScreen();
    printf("-------------------------------------------------\n");
    printf("  SCENE %d\n", index);
    printf("-------------------------------------------------\n\n");

    printf("%s\n\n", q.sceneText);

    printf("A) %s\n", q.optA);
    printf("B) %s\n", q.optB);
    printf("C) %s\n", q.optC);
    printf("D) %s\n", q.optD);

    printf("\nYou have %d seconds to answer.\n", TIME_LIMIT);

    // start timer
    time_t start = time(NULL);

    // get answer
    while (1) {
        printf("\nYour choice (A/B/C/D): ");
        if (scanf(" %c", &answer) != 1) {
            while ((c = getchar()) != '\n' && c != EOF) {}
            continue;
        }

        // normalize to uppercase
        if (answer >= 'a' && answer <= 'z') {
            answer = answer - 'a' + 'A';
        }

        if (answer == 'A' || answer == 'B' || answer == 'C' || answer == 'D')
            break;

        printf("Please enter A, B, C, or D only.\n");
    }

    // clear leftover newline
    while ((c = getchar()) != '\n' && c != EOF) {}

    // stop timer
    time_t end = time(NULL);
    double elapsed = difftime(end, start);

    clearScreen();
    printf("? You took %.0f seconds.\n", elapsed);

    // check timeout first
    if (elapsed > TIME_LIMIT) {
        printf("Time's up! The limit was %d seconds.\n\n", TIME_LIMIT);
        printf("? Your answer is counted as WRONG because you ran out of time.\n\n");
        printf("%s\n", q.failText);
        waitEnter();
        return 0;  // wrong due to timeout
    }

    // then check correctness
    if (answer == q.correct) {
        printf("? Correct!\n\n");
        printf("%s\n", q.successText);
        waitEnter();
        return 1;
    } else {
        printf("? Not the best choice.\n\n");
        printf("%s\n", q.failText);
        waitEnter();
        return 0;
    }
}

void printTally(int score, int total) {
    int wrong = total - score;

    printf("\nYour SDG 12 Impact Tally:\n");
    printf("-------------------------\n");

    printf("correct: ");
    for (int i = 0; i < score; i++) {
        printf("#");
        if ((i + 1) % 5 == 0) printf(" ");
    }
    printf("  (%d)\n", score);

    printf("wrong: ");
    for (int i = 0; i < wrong; i++) {
        printf("#");
        if ((i + 1) % 5 == 0) printf(" ");
    }
    printf("  (%d)\n", wrong);
}

void printEnding(int score, char name[]) {
    clearScreen();
    printf("=================================================\n");
    printf("                FINAL REPORT\n");
    printf("=================================================\n\n");
    printf("Employee: %s\n", name);
    printf("Total correct decisions: %d / %d\n\n", score, NUM_QUESTIONS);

    printTally(score, NUM_QUESTIONS);
    printf("\n");

    if (score == NUM_QUESTIONS) {
        printf("?? Amazing work!\n");
        printf("Your an expert in SDG 12.\n");
        printf("With your knowledge you can help the earth to be greener!\n");
    } else if (score >= NUM_QUESTIONS / 2) {
        printf("? Good job!\n");
        printf("You still got some knowledge about SDG 12!\n");
        printf("Dig up more information about it and use it to create a better earth!\n");
    } else {
        printf("?? A tough beginning.\n");
        printf("Failing is not the end.\n");
        printf("You can try again later and study more about SDG 12!.\n");
    }

    printf("\nThank you for playing and learning about SDG 12!\n");
    printf("=================================================\n");
}

int main(void) {
    char name[MAX_NAME];

    Question questions[NUM_QUESTIONS] = {
        {
            // 0
            "You wanted to buy some meat but you need to answer this:\n"
            "How much of the world's food is wasted?\n",
            "10%",
            "One-third",
            "50%",
            "One-fourth",
            'B',
            "You're Correct!\n"
            "Did you know? 1/3 of all food produced globally is wasted.\n"
            "You put it inside the basket"
			,
            "You're Wrong!\n"
            "Did you know? 1/3 of all food produced globally is wasted.\n"
            "You put it back into the freezer"
        },
        {
            // 1
            "Next you planned to buy some Chitato but he reconsiders if he should buy it or not\n"
            "After this question he'll decide for the greater good:"
            "What should you always check before eating packaged food?",
            "The color",
            "The expiration date",
            "The brand",
            "The portion size",
            'B',
            "You're Correct!\n"
            "Did you know? Every food has an expiration date, always check it before eating.\n"
            "He realizes that its not healthy for him. Therefore he puts it back.\n"
			,
            "You're Wrong!\n"
            "Did you know? Every food has an expiration date, always check it before eating.\n"
            "Regardless of the effects, he puts it in the basket\n"
        },
        {
            // 2
            "Next you needed soem carbs, You planned to buy some rice\n"
            "The question is:\n"
            "Why shouldn't you eat too much artificially colored food?",
            "It tastes strange",
            "It's too expensive",
            "It may contain harmful chemicals",
            "It melts easily",
            'C',
             "You're Correct!\n"
             "Did you know? A lot of food that is colored may have bad chemicals in it,\n"
             "Bought 4 kg of rice\n"
			,
            "You're Wrong!\n"
             "Did you know? A lot of food that is colored may have bad chemicals in it,\n"
             "Puts back the rixe back to its shelf\n"
        },
        {
            // 3
            "You search for some fruits at the store\n"
            "But you also saw that its GMO free\n"
            "The question is:\n"
            "How do you kill bacteria in food?",
            "Freeze it",
            "Cook it",
            "Dry it",
            "Soak it in water",
            'B',
            "You're Correct!\n"
            "Did you know? To kill off bacteria in your food you must first cook it.\n"
            "You purchased it!\n"
			,
            "You're Wrong!\n"
             "Did you know? To kill off bacteria in your food you must first cook it.\n"
             "You put it back\n"
        },
        {
            // 4
            "After buying your daily needs, you planned to buy clothes just to lighthen your mood\n"
            "You say this t-shirt. Stylish but its not eco friendly\n"
            "Whatever your choice is according to what your answer is\n"
            "Which method helps food last longer?",
            "Crushing it",
            "Salting or smoking it",
            "Adding sugar",
            "Leaving it outside",
            'B',
            "You're Correct!\n"
             "Did you know? To preserve foods longer you can either salt them or smoke them.\n"
             "You put it back and find something more eco friendly"
			,
            "You're Wrong!\n"
             "Did you know? To preserve foods longer you can either salt them or smoke them.\n"
             "Regardless of the effects, you just purchased it"
        },
        {
            // 5
            "Next you bought some drinks after a long day of shopping\n"
            "You then was asked if wanted plastic with it or not/n"
            "The question for your decision is:"
            "Did you know? Choosing local food cuts transport emissions.\n"
            "Brightville is planning a 'Green Market' event.\n"
            "Why is choosing local food better for the environment?",
            "It tastes better",
            "It reduces transportation emissions",
            "It is always cheaper",
            "It looks fresher",
            'B',
            "You're Correct!\n"
            "Did you know? Choosing local food cuts transport emissions.\n"
            "You refused the offer\n"
			,
            "You're Wrong!\n"
             "Did you know? Choosing local food cuts transport emissions.\n"
             "You accepted the offer\n"
        },
        {
            // 6
            "You saw some plastic near the drink stand\n"
            "Your choice depends on this question:\n"
            "What is the main focus of SDG 12?",
            "Renewable energy",
            "Sustainable consumption and production",
            "Peace and justice",
            "Healthy living",
            'B',
            "You're Correct!\n"
             "Did you know? SDG 12 focuses on safe consumption and production.\n"
             "You picked it up and threw it\n"
			,
            "You're Wrong!\n"
             "Did you know? SDG 12 focuses on safe consumption and production.\n"
             "You let it be\n"
        },
        {
            // 7
            "You saw someone throwing their trash carelessly\n"
            "Your good deeds will be tested from this question:\n"
            "One of the goals of SDG 12 is to…",
            "Create more waste",
            "Use resources wisely and reduce waste",
            "Produce more plastic",
            "Increase factory pollution",
            'B',
            "You're Correct!\n"
              "Did you know? Using resources wisely and reducing waste is one of SDG 12's goals.\n"
              "You reminded that people\n"
			,
            "You're Wrong!\n"
              "Did you know? Using resources wisely and reducing waste is one of SDG 12's goals.\n"
              "You just let it be\n"
        },
        {
            // 8
            "After sometime, you felt bored.\n"
            "Someone started to talked and discussed a lot of things to you\n"
            "He asks what are your thoughts about SDG?\n"
            "The question that you need to answer:\n"
            "A local factory wants to align with SDG 12.\n"
            "SDG 12 wants to make products that…",
            "Use fewer resources and create less pollution",
            "Are more expensive",
            "Use more materials",
            "Are made faster",
            'A',
            "You're Correct!\n"
             "Did you know? SDG 12 strives to make products using fewer\n"
            "resources and less pollution.\n"
            "SGD is really important as it will create a better earth!"
			,
            "You're Wrong!\n"
             "Did you know? SDG 12 strives to make products using fewer\n"
            "resources and less pollution.\n"
            "It is okay. But we still got time\n"
        },
        {
            // 9
            "The man stated that he started a 3R campaign and aksed you to join him\n"
            "Your answer depends on this question:\n"
            "What do the 3Rs stand for?",
            "Read, Rewrite, Recycle",
            "Reduce, Reuse, Recycle",
            "Remove, Restore, Rework",
            "Return, Refill, Repair",
            'B',
            "You're Correct!\n"
             "Did you know? The 3Rs of SDG 12 are Reduce, Reuse, Recycle.\n"
             "You accepted!\n"
			,
            "You're Wrong!\n"
             "Did you know? The 3Rs of SDG 12 are Reduce, Reuse, Recycle.\n"
             "You refused\n"
        },
        {
            // 10
            "With your knowledge after that insightful discussion,\n"
            "You tested your knowledge.\n"
            "You have some plastic up your shopping bags\n"
            "What colour of bin will it be putted in?\n"
            "You need to answer this correctly:\n"
            "In a meeting with farmers and transport companies,\n"
            "someone asks about losses.\n"
            "How much food is lost along the supply chain?",
            "1%%",
            "5%%",
            "13%%",
            "25%%",
            'C',
            "You're Correct!\n"
             "Did you know? 13%% of food is lost along the supply chain.\n"
             "You put it in the yellow bin"
			,
            "You're Wrong!\n"
             "Did you know? 13%% of food is lost along the supply chain.\n"
             "You put it in the green bin"
        },
        {
            // 11
            "You're planning to get home after a long day/n"
            "Its either you use public electric transportation or the combustion type\n"
            "Your choice is decided by this question:\n"
            "How much food is wasted at the consumer level?",
            "19%%",
            "3%%",
            "40%%",
            "10%%",
            'A',
            "You're Correct!\n"
             "Did you know? 19%% of food is lost at the consumer level.\n"
             "you use the electric transportation!\n"
			,
            "You're Wrong!\n"
             "Did you know? 19%% of food is lost at the consumer level.\n"
             "You use the combustion transportation!\n"
        }
    };

    printIntro(name);

    int score = 0;
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        score += askQuestion(questions[i], i + 1);
    }

    printEnding(score, name);

    return 0;
}