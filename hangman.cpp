#include <iostream>
#include <vector>
#include <algorithm>



#define FgC1 "\033[38;5;67m" // "Forground Color 1"
#define FgC2 "\033[38;5;31m" 
#define FgC3 "\033[38;5;181m"
#define FgC4 "\033[38;5;161m"

/*EXTRAUPPGIFT:

 #10.5 Programmera HANGMAN spelet
Här är ett exempel på hur dialogen mellan användaren och datorn kan se ut.
Den som ska spela måste titta bort nu!
Skriv in ett ord: Hammare
(skärmen rensas…)
Ord: _ _ _ _ _ _ _
Gissa en bokstav eller ordet? E
Bra! Du har 6 gissningar kvar.
Ord: _ _ _ _ _ _ E
Gissa en bokstav? A
Ord: _ A _ _ A _ E
Bra! Du har 6 gissningar kvar.
Gissa en bokstav eller ordet? N
Ord: _ A _ _ A _ E
Missar: N
Fel! Du har 5 gissningar kvar.
Gissa en bokstav eller ordet? r
Ord: _ A _ _ A R E
Missar: N
Rätt! Du har 5 gissningar kvar.
Gissa en bokstav eller ordet? Tattare
Ord: _ A _ _ A R E
Missar: N
Fel ord! Du har 4 gissningar kvar.
Gissa en bokstav eller ordet? n
Ord: _ A _ _ A R E
Missar: N
Du har redan försökt med N! Du har 4 gissningar kvar.



OBS: Håll reda på redan gjorda ”Du har redan försökt med N”*/


class Hangman
{
private:
    int hit_points = 10;
    int correct_letters = 0;
    bool win_condition;
    std::vector<std::string> incorrect_guesses;
    std::vector<std::string> correct_guesses;

    std::string awnser;


public:
    Hangman(/* args */){}
    ~Hangman(){}


    void getawnser()
    {
        std::cout << FgC1 <<"Choose one player to write in awnser\nAll the other players looks away!\nInput: "<< FgC2;
        std::cin >> awnser; std::cout<<std::endl;
        win_condition = false;
        system("clear");

    }

    void printIncorretGuesses()
    {
        std::cout<< FgC3 <<"Misses: ";
        for (std::string x : incorrect_guesses)
        {
            std::cout << FgC4 << x << FgC3 <<", ";
        }
    }

    void printCorrectGuesses()
    {
        std::cout<< FgC1 <<"Word so far: ";

        //std::cout << " awnser size is: " << awnser.size() << std::endl;


        for (int i = 0; i < awnser.size(); i++)
        {
            if (correct_guesses.empty())
                {
                    std::cout<< FgC2 <<" _";
                }

            for (int y = 0; y < correct_guesses.size(); y++)
            {   
                //std::cout<<"Correct guess is: " << correct_guesses[y] << std::endl;
                std::string compare = correct_guesses[y];
                if (awnser[i] == compare[0])
                {
                    std::cout << FgC2<< " " << awnser[i];
                    break;
                }
                else if (awnser[i] != compare[0] && y+1 >= correct_guesses.size())
                {
                    std::cout<< FgC2<<" _";
                }
            }
        }
        std::cout<<std::endl;
    }




    bool guess()
    {
        std::cout<<std::endl;
        printCorrectGuesses();
        printIncorretGuesses();
        std::string guess;
        std::cout << FgC1 << "\nYou have " << FgC3 << hit_points 
                  << FgC1 <<" chances left\n"
                  << "Guess: "<< FgC2;
        std::cin >> guess;
        system("clear");

        for (int i = 0; i < awnser.size(); i++)
        { 
            if (guess == awnser) // check whole word
            {
                std::string pause;
                std::cout<< FgC1 << "You have guessed the correct word: "<< FgC2 << awnser 
                                << FgC1 << "!\nCongratulations! You have won the game!\n" 
                                << "You had " << FgC3 << hit_points << " chances left!\n" << FgC1
                                << " << press Enter to continue >>"
                                << std::endl;


                //Pause(dont know why 2 are needed, have trailing problem)
                std::getline(std::cin, pause);
                std::getline(std::cin, pause);

                system("clear");
                win_condition = true;
                break;
            }
            else if (guess.size() == 1 && guess[0] == awnser[i]) // check if its a correct letter
            {
                for (std::string x : correct_guesses)
                {
                    if (guess == x)
                    {
                        std::cout<<FgC1<<"You have alrdy guessed: " << FgC4 << guess << FgC1 << "!" << std::endl;
                        return win_condition = false;
                    } 
                }

                //checks for how many times a correct letter exists in the word
                for (char a : awnser)
                {
                    if (a == guess[0])
                    {
                        correct_letters++;
                    }
                }
                
                //std::cout << "Correct letters is: " << correct_letters << std::endl;

                if (awnser.size() == correct_letters)
                {
                    std::string pause;
                    std::cout<< FgC1 << "You have uncovered the correct word: "<< FgC2 << awnser 
                                << FgC1 << "!\nCongratulations! You have won the game!\n" 
                                << "You had " << FgC3 << hit_points << " chances left!\n" << FgC1
                                << " << press Enter to continue >>"
                                << std::endl;


                    //Pause(dont know why 2 are needed, have trailing problem)
                    std::getline(std::cin, pause);
                    std::getline(std::cin, pause);

                    system("clear");
                    win_condition = true;
                    break;
                }
                else
                {
                    std::cout << FgC1 << "You guessed the correct letter!" << std::endl;
                    correct_guesses.push_back(guess);
                    win_condition = false;
                    break;
                }
            }
            else if(i+1 >= awnser.size()) // if its an incorrect guess
            {
                for (std::string x : incorrect_guesses)
                {
                    if (guess == x)
                    {
                        std::cout<<FgC1<<"You have alrdy guessed: " << FgC4 << guess << FgC1 << "!" << std::endl;
                        return win_condition = false;
                    }
                }
                
                hit_points--;

                if (hit_points == 0)
                {
                    std::string pause;
                    std::cout<< FgC1 << "You have run out of chances and eLost the game\n" << 
                                FgC1 << "The word was: " << FgC2 << awnser << "\n" <<
                                FgC1 << " << press Enter to continue >>"
                                << std::endl;


                    //Pause(dont know why 2 are needed, have trailing problem)
                    std::getline(std::cin, pause);
                    std::getline(std::cin, pause);

                    system("clear");
                    
                    win_condition = true;
                    break;
                }
                else
                {
                    incorrect_guesses.push_back(guess);
                    std::cout << FgC1 << "Incorrect guess! You have now " << FgC3 << hit_points << FgC1 <<" chances left!" << std::endl;
                    win_condition = false;
                    break;
                }
            }
        }
        return win_condition;
    }




    void gameloop()
    {
        bool win_test = false;

        // function that handles geting the hangmanword from the user
        getawnser();

        do
        {
            win_test = guess();

        } while (win_test == false);
    }
};


int main()
{
    int user_input;

    do
    {
        Hangman new_game;
        std::cout << FgC1 << "Welcome to Hangman!\n"
              FgC2 << "1" << FgC1 <<". Start new game\n"
              FgC2 << "2" << FgC1". Exit game\n"
              << "Input: "<< FgC2;
        std::cin >> user_input; std::cout << std::endl;
        system("clear");

        if (user_input == 1)
        {
            new_game.gameloop();
        }
        else if (user_input == 2)
        {
            std::cout << "EXITING GAME";
        }
        else
        {
            std::cout << "invalid input!";
        }

    } while (user_input !=2);


    return 0;
}