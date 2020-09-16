# Terminal 2048
## **Requirements:**
- ### ***Homebrew:*** 
    ```console
    $ /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
    ``` 
 - ### ***GNU C Compiler:***
    ```console
    $ brew install gcc
    ```
- ### ***Ncurses:***
    ```console
    $ brew install ncurses
    ```
- ### ***Git:***
    ```console
    $ brew install git
    ```
## **How to download:**
```console
$ git clone https://github.com/rabernethy/2048-Game.git
```

## **How to run:**
```shell
$ make && ./game
```
 

### TODO:

 - [x]add highscore screen
 - [] add quit game option
    - catch sigint
 - [] add highscore screen
 - [] 10 leader board spots
    - [] show at the end and save to score file
 - [x] fix game over (make it bring back up the default terminal upon quitting).