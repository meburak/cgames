# cgames
Terminal games for practicing C
## SNAKE 
```terminal
> gcc snake.c mygamelib.c -o snake
> ./snake
```

<img width="504" height="844" alt="image" src="https://github.com/user-attachments/assets/03f2b73d-539e-4356-8294-99d16a4ee875" />

*Date: 12.02.2026* 
**Newest**

**Added Features**

- Entry screen, player name input,
- HUD Displaying Player Name, HP and Points,
- Optimized check for updates in player status, using `statusChange`,
- Player power use, will add new powers but for now pressing H gives 1 HP in exchange off 5 Points.

Ideas for next release: 

I should rely on probably creating more functions now and tidying up the code. Also, I can deepen library with colors, special print functions that does not return to 0,Y. 



<img width="500" height="200" alt="image" src="https://github.com/user-attachments/assets/332a3966-6ae3-4fcd-8042-ed7bb40962d1" />

**Features:** 
(V3) 
- OK Tile Creation
- OK User Input for direction
- OK Moving the head (first commit)
- [OK] Timing the input,
  - Sleep, using seconds,
- [OK] Input raw, process without pressing return,
  - Terminal settings, GAME ON/OFF logic  
- [OK] Clearing old tiles, frames, refreshing,
  - system("clear"),
- [OK] Placing points (xp)
- [] Implementing tail logic
V3 NOTES:
Unblocking the input is still a problem,
For some reason, when I clear the cache, it seems to be stucking the whole thing.
Also added changing head icons.
FIX: Unblocked input, thanks to someones answer in the internet. 
```C
int kbhit(void){
    struct timeval tv;
    fd_set read_fd;

    tv.tv_sec = 0;
    tv.tv_usec = 0;

    FD_ZERO(&read_fd); //clear "bitmask" of read_fd
    FD_SET(0, &read_fd); //set 1, the 0th bit in read_fd

    if(select(1, &read_fd, NULL, NULL, &tv) == -1){
        return 0;
    }
    if(FD_ISSET(0, &read_fd)){
        return 1;
    }
    else{
        return 0;
    }
}
```
