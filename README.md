# LuckyMaJong
Calculate the Numerological Reduction of a number

Finding the Numerological Reduction (also known as finding the Digital Root, Theosophical Addition, Single-Digit Calculation, or Feng Shui Reduction) is a common practice in Chinese culture, especially among practitioners of Feng Shui and Nine Star Ki numerology. In traditional Chinese metaphysics, all numbers are ultimately reduced to a single digit from 1 through 9. This is because of two ancient systems:

The Lo Shu Square: An ancient 3x3 magic square grid where every row, column, and diagonal adds up to 15, which then reduces to 6 (1+5=6).

The Nine Stars: Each single digit from 1 to 9 corresponds to a specific star, a Feng Shui element (Fire, Earth, Metal, Water, Wood), and a specific type of cosmic energy. 

By reducing a large number (like a house address or a bank account number) down to a single digit, a practitioner is finding the "core energy" or the governing planet/element of that entire sequence to see if it aligns well with the person's personal energy.


Personal Kua Number Calculation
To calculate a personal life/lucky number using Feng Shui and your birth year:

    Step 1: Find the Numerological Reduction of the last two digits of your birth. 
    Step 2: (For Males): Subtract that final single digit from 10 (or from 9 if born in 2000 or later). 
    Step 3: (For Females): Add 5 to that single digit (or add 6 if born in 2000 or later).
    Step 3: Reduce the sum to a single digit if necessary. 

Popular Lucky Combinations

    168: Sounds like "fortune all the way along the road" (yi lu fa).
    88 or 888: Represents double or triple prosperity and wealth.
    666: Symbolizes that everything will go smoothly without trouble.

If you pass the program a single argument, it assumes that the argument is a positive integer number that you wish to find the Numerological Reduction of. The result is printed to stdout.

I wrote this program for my wife. She likes to play a particular Mahjong solitaire game on her tablet. When played offline, the game gives you 2 points for your first win, 6 for your second, and 8 points for every win after that. She doesn't like to stop playing if the Numerological Reduction of her score isn't her lucky number. This, if you don't specify an argument the program will print out a table of numbers using this scoring sequence. Using this table, my wife can look up her current score and instantly see how many more games she will need to win to reach her lucky number goal.
