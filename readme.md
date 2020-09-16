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
 
### ***TODO:***
 - [ ] add quit game option
    - catch sigint
 - [ ] add highscore screen @rabernethy
    - [ ] 10 leader board spots
    - show at the end and save to score file
 - [x] fix game over (make it bring back up the default terminal upon quitting).
 - [x] add colors to the numbers @invention64
 - [x] stop displaying 0 tiles