#include<stdio.h>

int driver(int, int);
int user_move(int, char);
int table_print();
int table_evaluation(char);
int minimax(char, char, int, int);
int best_move(char, char);
int turns_left();

char table[3][3] = {
        {'1','2','3'},
        {'4','5','6'},
        {'7','8','9'}};

int main(){
    int user_shape = 1, ai_shape=0; // 1 for X, 0 for O.
    int shape_choice;
    printf("Choose your shape: \n");
    printf("Enter 1 for X \n");
    printf("Enter 2 for O \n");
    scanf("%d",&shape_choice);
    if(shape_choice==2){
        user_shape=0;
        ai_shape=1;
    }
    else if(shape_choice>2 || shape_choice<1){
        printf("Invalid choice, please try again.\n");
        main();
    }
    int start_condition;
    printf("Would you like to have the first turn in the game? : \n");
    printf("Enter 1 for Yes \n");
    printf("Enter 2 for No \n");
    scanf("%d",&start_condition);
    if (start_condition == 2)
        start_condition = 0;
    else if(start_condition>2 || start_condition<1){
        printf("Invalid choice, please try again.\n");
        main();
    }
    printf("The game table would look like this \n");
    printf("You will be required to enter the number of the block you would like to place your shape in: \n");
    table_print(table);
    driver(user_shape,start_condition);
    int play_again;
    printf("Would you like to play again? \n");
    printf("Enter 1 for Yes \n");
    printf("Enter 2 for No \n");
    scanf("%d",&play_again);
    if (play_again==1){
        int reset = 1;
        for(int row=0;row<3;row++){
            for(int col=0;col<3;col++){
                table[row][col]=reset + '0';
                reset++;
            }
        }
        main();
    }
    else
        return 0;
}


int driver(int user_s,int turn_condition){
    char user_shape,ai_shape;
    int user_choice;
    if(user_s == 1){
        user_shape = 'X';
        ai_shape = 'O';
    }
    else{
        user_shape = 'O';
        ai_shape = 'X';
    }
    while(1){
        if (turn_condition == 1){
            int check;
            printf("It is your turn \n");
            printf("Which block would you like to place your shape in? \n");
            scanf("%d",&user_choice);
            check = user_move(user_choice,user_shape);
            if (check==0){
                turn_condition--;
                table_print();
            }
        }
        else if (turn_condition == 0){
            best_move(user_shape,ai_shape);
            printf("The AI has made the following move : \n");
            table_print();
            turn_condition++;
        }
        if (table_evaluation(ai_shape)==10){
            printf("AI has won the game and the final table looks like: \n ");
            table_print();
            return 0;
        }
        else if(table_evaluation(ai_shape==-10)){
            printf("You won and the final table looks like: \n");
            table_print();
            return 0;
        }
        if(turns_left()==0){
            printf("Its a tie and the final table looks like: \n");
            table_print();
            return 0;
        }
    }
}


int table_print(){
    printf("-------------\n");
    for(int row=0;row<3;row++){
        for(int col=0;col<3;col++){
            if(col==0){
                printf("|");
            }
            printf(" %c |",table[row][col]);
        }
        printf("\n");
        printf("-------------");
        printf("\n");
    }
    return 0;
}


int user_move(int user_choice, char user_shape){
    char choice = user_choice + '0';
    for(int row=0;row<3;row++){
        for(int col=0;col<3;col++){
            if(table[row][col]==choice){
                table[row][col]=user_shape;
                return 0;
            }
        }
    }
    printf("Entered value is invalid. Please choose a valid choice \n");
    return 1;
}


int table_evaluation(char shape){
    for(int row=0; row<3; row++){
        if (table[row][0] == table[row][1] &&
            table[row][0] == table[row][2]){
                if (table[row][0] == shape)
                    return (10);
                else
                    return (-10);
        }
    }
    for(int col=0; col<3; col++){
        if (table[0][col] == table[1][col] &&
            table[0][col] == table[2][col]){
                if (table[0][col] == shape)
                    return (10);
                else
                    return (-10);
        }
    }
    if (table[0][0] == table[1][1] &&
        table[0][0] == table[2][2]){
            if (table[0][0] == shape)
                return (10);
            else
                return (-10);
    }
    else if (table[2][0] == table[1][1] &&
             table[2][0] == table[0][2]){
                if (table[2][0] == shape)
                    return (10);
                else
                    return (-10);
        }
    return 0;
}


int minimax(char user_shape, char ai_shape, int turn_condition, int depth){
    int score = table_evaluation(ai_shape);
    if (score == 10)
        return (score-depth);
    if (score == -10)
        return (score+depth);
    if (turns_left()==0)
        return 0;
    if (turn_condition==0){
        int best = -1000;
        for(int row=0; row<3; row++){
            for(int col=0; col<3; col++){
                if((table[row][col] != 'X') && (table[row][col]!='O')){
                    char save = table[row][col];
                    table[row][col] = ai_shape;
                    best = ((minimax(user_shape,ai_shape,1,depth+1)>best) ? minimax(user_shape,ai_shape,1,depth+1) : best);
                    table[row][col] = save;
                }
            }
        }
        return best;
    }
    else if (turn_condition==1){
        int best = 1000;
        for(int row=0; row<3; row++){
            for(int col=0; col<3; col++){
                if((table[row][col] != 'X') && ((table[row][col])!='O')){
                    char save = table[row][col];
                    table[row][col] = user_shape;
                    best = ((minimax(user_shape,ai_shape,0,depth+1)<best) ? minimax(user_shape,ai_shape,0,depth+1) : best);
                    table[row][col] = save;
                }
            }
        }
        return best;
    }
}


int best_move(char user_shape, char ai_shape){
    int r,c;
    int best_value = -1000;
    for(int row=0; row<3; row++){
        for(int col=0; col<3; col++){
            if((table[row][col] != 'X')&&(table[row][col] != 'O')){
                char save = table[row][col];
                table[row][col] =  ai_shape;
                int value = minimax(user_shape,ai_shape,1,0);
                table[row][col] = save;
                if (value>best_value){
                    best_value = value;
                    r=row;
                    c=col;
               }
            }
        }
    }
    table[r][c]=ai_shape;
}


int turns_left(){
    for(int row=0; row<3; row++){
        for(int col=0; col<3; col++){
            if ((table[row][col] != 'X')&&(table[row][col] != 'O')){
                return 1;
            }
        }
    }
    return 0;
}
