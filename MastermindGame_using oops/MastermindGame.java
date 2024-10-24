
/* 
Name-Samanpreet Kaur
Student Number- 100399074
Course- 1150(Section:6)
Date - 3 November 2023
Purpose- Designing masterMind Game
Input- how many digit number user wants to guess, and the guess
Output- Results produced after comparing computer created and user created array

 */import java.util.Scanner;

public class MastermindGame {
    private static Scanner keyboard = new Scanner(System.in);

    public static void main(String[] args) {

        System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        //int count = 0;
        do
        {
            int maxSize = validatingSize();

            do                         //Inner Loop
            {
                String guessedString = validatingGuess( maxSize);
                int [] userArray = createUserArray( guessedString);
                int[] computerArray = createComputerArray( maxSize);
                wantCheaterMode();
                int exactlyPositioned= comparingBothArrays();
            } while(trySameGameAgain( exactlyPositioned, userArray));

        } while ( 


    }

    // ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
    /**
     * This method takes the bigDecision of user of how-many digit number and check its validity 
     * @param guessedString The inputted guess by user for number of digits in guess
     * @return The valid size (digit count)
     */

    private static int validatingSize() {
        
        System.out.print("Please Enter How Many Digit-Number You Want To Guess? (2-10) : ");
        int maxSize = keyboard.nextInt();
        while (maxSize < 2 || maxSize > 10)             // Verifying the choosen size is valid or not
        {
            System.out.print("Sorry, You Entered An Invalid Input, Please Enter Between 2 and 10.");
            maxSize = keyboard.nextInt();
        }
        return maxSize;
    }

    // ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

    /**
     * This method takes the input in string form and check its validity
     * @param guessedString The inputted guess by user in string form
     * @return The valid string (guess)
     */

    private static String validatingGuess(int maxSize) {

        System.out.print("Ok, So Tell Your " + maxSize + "-Digit Number Guess."); // For asking user's guess
        System.out.print(" Make Sure Every Digit Is Unique: ");
        int guess = keyboard.nextInt();
        String guessedString = Integer.toString(guess); // Converted it to string to check if every digit is unique(that is to access every index)

        while (guessedString.length() != maxSize) // Checking size is same as declared by user before as maxsize(number  of digits)
        {
            System.out.print("Sorry, Your Size is Not Matching! Please TRy Again: ");
            guess = keyboard.nextInt();
            guessedString = Integer.toString(guess);
        }

        while (!areDigitsUnique(guessedString)) // To validate the user input, by uniqueness factor
        {
            System.out.print("Every Digit In Your Guess Should Be A Unique Number(Never-Repeating Again).");
            guess = keyboard.nextInt();
            guessedString = Integer.toString(guess);
        }
        return guessedString;
    }

    // ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

    /**
     * This verifies that whether the digits in the user's guess are all different.
     * @param guessedString The number guessed by user, converted in String form
     * @return The true/false based on answering the question: "Whether all digits unique"
     */
    private static boolean areDigitsUnique(String guessedString) 
    {
        for (int i = 0; i < guessedString.length(); i++) {
            int compareAgainst = (int) guessedString.charAt(i);
            for (int j = 1 + i; j < guessedString.length(); j++) // set indexes with different variables to keep loops idea separate
            {
                if (compareAgainst == (int) guessedString.charAt(j)) {
                    System.out.println("Invalid Input! Please Try Again With 'Unique Digits' One More Time: ");
                    return false;
                }
            }
        }
        return true;
    }

    // ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

     /**
     * This creates A Array For Storing User's Guessed Number.
     * @param guessedString The User's Guessed String.
     * @return The number generated by user in Array Form
     */
    private static int[] createUserArray(String guessedString) {    

        int[] userArray = new int[guessedString.length()];

        for (int i = 0; i < userArray.length; i++) 
        {
            userArray[i] = Character.getNumericValue(guessedString.charAt(i)); // Typecasting character into int 
        
        }

        return userArray;
    }

    // ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

    /**
     * This creates the computer generated random sequence of the numbers, which
     * user needs to guess in game
     * @param maxSize The count of the number of digits in the secret (random) number generated
     * @return The number generated by computer in array Form
     */
    private static int[] createComputerArray(int maxSize) 
    {
        int[] computerArray = new int[maxSize];
        String options = "0123456789"; // Later on, random indexes will be picked from this string to fill the number

        for (int index = 0; index < computerArray.length; index++) {
            int random = (int) (Math.random() * options.length());
            computerArray[index] = random;
            options = options.substring(0, random) + options.substring(random + 1); // To Eliminate The Repitition of the Numbers
        }
        return computerArray;
    }

    // ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

    /**
     * It asks if user wants to see the computer generated array
     * @return computer array
     */
    private static void wantCheaterMode() 
    {
        int maxSize = 0;
        // int [] computerArray = createComputerArray(int maxSize); // Do we neeeed to
        // call another method to give us maxSize
        System.out.print("If You Want The Cheater Mode On, Please Enter 'Yes': ");
        String choice = keyboard.next().toLowerCase();

        if (choice.equals("yes")) // To compare 2 strings
        {
            System.out.print("The Number Thought By Computer Is:");
            int[] computerArray = createComputerArray(maxSize); // Called createComputerArray method & asked for the array from it
            printComputerArray(computerArray);
            System.out.println("");
        }

    }

    // ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
    /**
     * This method prints the computer-generated array (for cheat-mode) 
     * @param The random number generated by computer in array form
     */
    private static void printComputerArray(int[] computerArray) {
        for (int index = 0; index < computerArray.length; index++) {
            System.out.print(computerArray[index]);
        }
    }

    // ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

    /**
     * This method matches every digit in user's number with the computer generated number
     * @param userArray     The number generated by user in array form
     * @param computerArray The number generated by computer in array form
     */
    private static int comparingBothArrays (int[] userArray, int[] computerArray) { //isGuessAndExactSequenceEqual

        int countOfCorrect = 0; // TO KEEP TRACK HOW MANY WERE RIGHT
        int exactlyPositioned = 0; // TO KEEP TRACK HOW MANY OF THEM WERE AT RIGHT POSITION AS WELL

        for (int i = 0; i < userArray.length; i++) {
            int matchAgainst = userArray[i];
            for (int j = 0; j < computerArray.length; j++) {
                if (matchAgainst == computerArray[j]) {
                    countOfCorrect++;
                    if (i == j) {
                        exactlyPositioned++;
                    }
                }
            }
        }
        System.out.println("The number of correct digit(s): " + countOfCorrect + " and out of those, "
                + exactlyPositioned + " in the correct place.");
        if (exactlyPositioned == userArray.length) {
            return true; // System.out.print("Do You Wanna Try Another Guess in The Same Game Again?");
        }
        return exactlyPositioned;
    }

    /**
     * It asks user if they want to mae another guess while staying in the same game
     * @return boolean true or false
     */
    private static boolean trySameGameAgain(int exactlyPositioned, int[] userArray) 
    {
        int count = 0;
        if  (exactlyPositioned == userArray.length)
        {
            System.out.print("Hurray! You won the game!!");
        }
        
        else
        {
            System.out.print("Do You Wanna Try Another Guess in The Same Game Again? Yes/No");
            String smallDecision = keyboard.next().toLowerCase(); // Set up inner loop with this
            if (smallDecision == "yes") 
            {
                return true;
            }
        }
        count++;
        return false;
    }

    private static boolean wannaStartNewGame(int[] userArray, int[] computerArray) 
    {
        int exactlyPositioned = comparingBothArrays(userArray, computerArray)
        if( exactlyPositioned == userArray.length){

        } comparingBothArrays(userArray, computerArray)
        {
            System.out.println("Do You Wanna Play The Whole Game Again? Yes/No");
            String bigDecision = keyboard.next().toLowerCase();
            if (bigDecision == "yes") 
            {
                return true;
            }
        }
        
    return false;
    }

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    private static void printIdentification()
    {
        System.out.println("astermind Writer: Samanpreet Kaur");
        System.out.println("*** Course/Section - CPSC1150-06   St.# -100399074 ***\n");
        System.out.println(new java.util.Date());
        System.out.println();
    }                                                                                   //printIdentification

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    private static void printInstructions()
    {
        System.out.println("*****======================================Assignmnent ======================================*****");
        System.out.println("This program performs a mastermind game.\n");
    }               
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

