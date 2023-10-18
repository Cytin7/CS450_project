# ZJUI CS450 Fa23 - Course Problem Simulator

This simulator is a simulator of the following problem:

> For the third day in a row, you find yourself in Squid Game as one of N players in a game similar to “Red Light, Green Light” from the first episode.
>
> The game begins with the $N$ players on the starting line and then proceeds as a series of turns. On a given turn, all players move forward from their current position by one step of the same length and then attempt to freeze. Player $i$ is unsuccessful at freezing with probability $p_i$, independent from the other players. The turn concludes with Young-hee (the large robotic doll) selecting at most $L$ players (with $L < N$) which return to the starting line according to the following rules:
>
> - If there are less than or equal to $L$ players who failed to freeze, they all return to the starting line.
> - If there are more than $L$ players who failed to freeze, select those $L$ players that have traveled the farthest from the starting line to return to the starting line.
>
> When the game has been played for a sufficient amount of time, i.e., in the limit as the number of turns increases to infinity, what is the probability that player $n$ (you) is $k$ steps from the starting line in the following cases:
>
> 1. When $p_1 = p_2 = \ldots = p_N = p$.
> 2.  When the failure to freeze probability $p_i$ can be different for each player.

To run the simulator, first change the `N`, `L`, `p` variables in the`main()` function in  `main.cpp`.

Then run the `main.cpp` file to generate probability data.

Finally, run `graph.py` to generate visualization.





---

Code by CYTIN.