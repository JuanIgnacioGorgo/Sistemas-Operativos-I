-module(min).
-export([minimo/1]).

minimo([Hd]) -> Hd;
minimo([Hd|Tl]) -> 
    M = minimo(Tl),
    if
        Hd < M -> Hd;
        true -> M
    end.