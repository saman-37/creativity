import java.util.Scanner;
import java.util.Random;

class MastermindGame {
    private Player player;
    private Computer computer;
    private int maxSize;
    private Scanner keyboard;

    public MastermindGame() {
        keyboard = new Scanner(System.in);
        player = new Player();
        computer = new Computer();
    }

    public void start() {
        displayWelcomeMessage();
        do {
            maxSize = player.requestMaxSize();
            computer.generateSecretNumber(maxSize);
            boolean won;
            do {
                String guess = player.makeGuess(maxSize);
                won = computer.checkGuess(guess);
                if (!won) {
                    computer.provideFeedback(guess);
                } else
                    System.out.println("Congrats, you won!");
            } while (!won);
            player.askToPlayAgain();
        } while (player.wantsToPlayAgain());
    }

    private void displayWelcomeMessage() {
        System.out.println("Welcome to the Mastermind Game!");
    }
}

class Player {
    private Scanner keyboard;

    public Player() {
        keyboard = new Scanner(System.in);
    }

    public int requestMaxSize() {
        int size;
        do {
            System.out.print("Enter how many digits you want to guess (2-10): ");
            size = keyboard.nextInt();
        } while (size < 2 || size > 10);
        return size;
    }

    public String makeGuess(int maxSize) {
        String guess;
        do {
            System.out.print("Enter your " + maxSize + "-digit guess (unique digits only): ");
            guess = keyboard.next();
        } while (!areDigitsUnique(guess) || guess.length() != maxSize);
        return guess;
    }

    private boolean areDigitsUnique(String guess) {
        for (int i = 0; i < guess.length(); i++) {
            for (int j = i + 1; j < guess.length(); j++) {
                if (guess.charAt(i) == guess.charAt(j)) {
                    System.out.println("Digits must be unique! Try again.");
                    return false;
                }
            }
        }
        return true;
    }

    public boolean wantsToPlayAgain() {
        System.out.print("Do you want to play again? (yes/no): ");
        return keyboard.next().equalsIgnoreCase("yes");
    }

    public void askToPlayAgain() {
        System.out.print("Do you want to play again? (yes/no): ");
        String response = keyboard.next().toLowerCase();
        if (response.equals("yes")) {
            System.out.println("Starting a new game...");
        } else {
            System.out.println("Thanks for playing!");
        }
    }
}

class Computer {
    private String secretNumber;

    public void generateSecretNumber(int size) {
        Random random = new Random();
        StringBuilder number = new StringBuilder();
        String options = "0123456789";
        for (int i = 0; i < size; i++) {
            int index = random.nextInt(options.length());
            number.append(options.charAt(index));
            options = options.substring(0, index) + options.substring(index + 1); // Remove used digit
        }
        secretNumber = number.toString();
        System.out.println("Computer generated secret number (for testing): " + secretNumber);
    }

    public boolean checkGuess(String guess) {
        return guess.equals(secretNumber);
    }

    public void provideFeedback(String guess) {
        int correctPosition = 0;
        int correctDigits = 0;
        for (int i = 0; i < guess.length(); i++) {
            char guessDigit = guess.charAt(i);
            if (guessDigit == secretNumber.charAt(i)) {
                correctPosition++;
            } else if (secretNumber.indexOf(guessDigit) != -1) {
                correctDigits++;
            }
        }
        System.out.println("Correct digits: " + correctDigits + ", Correct positions: " + correctPosition);
    }
}
