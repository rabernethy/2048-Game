# Terminal 2048
## **Requirements:**
- ### ***Homebrew:*** 
    ```console
    user@derek:~$ /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
    ``` 
 - ### ***GNU C Compiler:***
    ```console
    user@derek:~$ brew install gcc
    ```
- ### ***Ncurses:***
    ```console
    user@derek:~$ brew install ncurses
    ```
- ### ***Git:***
    ```console
    user@derek:~$ brew install git
    ```
## **How to download:**
```console
user@derek:~$ git clone https://github.com/rabernethy/2048-Game.git
```

## **How to run:**
```console
user@derek:~$ make && ./game
```
 

### TODO:

 - [x] add highscore screen
 - [ ] add quit game option
    - catch sigint
 - [ ] add highscore screen
 - [ ] 10 leader board spots
    - [ ] show at the end and save to score file
 - [x] fix game over (make it bring back up the default terminal upon quitting).