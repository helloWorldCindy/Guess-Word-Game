# Guess-Word-Game

Program author: Qianyi Yu

Purpose: to let two players connect together and play probe. Which is a game that Each player will be prompted to enter a phrase that the other player will try to guess.

List of source: main.c

Header: stdio.h ,string.h,stdlib.h,sys/types.h,sys/socket.h,netinet/in.h,arpa/inet.h,signal.h

Compilation command :gcc -o exe main.c

Launching and operation instruction: 

    1. Untar the file using tar -xvf
    2. Place the file in the directory that the user want to compile and run
    3. Use “gcc -o exe main.c” to compile the program
    4. If user is server,use ”./exe” to run the program,and wait till the client is connect
    5.  If the user is client , use ”./exe” and indicate the IP address using the command line, and connect to the server
    6. Enter the word that the user want the other player to guess
    7. It will show up the word that the oppoent's want the user to guess
    8. Enter the word or a letter that the user trying to guess
    9. If it is right , it will show up the letter that you have guessed , and show what does the opponent guess of the user's word
    10. If it is wrong , the user need to keep guessing
    11. If the other player finish guessing the whole word before the user did , then the oppoent win , the user lose. Otherwise , the user win, the opponent lose
    12. The winner can choose if he want to continue playing or quit, the loser does not
