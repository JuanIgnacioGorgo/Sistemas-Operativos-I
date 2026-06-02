-module(pingpong)
-export([])

% pong

pong() ->
    receive
        {0, Ping_pid} -> io:fwrite("Pong recv: ~p ~p ~n", [N, Ping_pid]),
                        Ping_pid ! {fin, self()},
                        okPong;
        {N, Ping_pid} -> io:fwrite("Pong recv: ~p ~p ~n", [N, Ping_pid]),        
                        Ping_pid ! {N - 1, self()},
                        pong()


% ping

ping() ->
    receive
        {fin, Pong_pid} -> io:fwrite("Ping termino: ~p ~n", [Pong_pid])
        {N, Pong_pid} -> io:fwrite("", []),
                        Pong_pid ! {N - 1, self()}


% main - inicia el juego

play() ->
    Ping_pid = spawn(pingpong, ping, []),
    Pong_pid = spawn(pingpong, pong, []),
    Pong_pid ! {10, Ping_pid},
    playok.