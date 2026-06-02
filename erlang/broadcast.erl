-module(broadcast).

%% Librería
% Funciones control
-export([start/0,stop/1]).
% Funciones interacción
-export([broadcast/2,registrar/1]).
%%%
-export([loopBroadcast/1, loopClient/0]).
-export([test/0,client/1]).

start() ->
  spawn(?MODULE, loopBroadcast, [[]]).

stop(Broadcast) ->
  Broadcast ! stopp.

broadcast(Broadcast, Msg) ->
  Broadcast ! {brod, Msg}.

registrar(Broadcast) ->
  Broadcast ! {reg, self()}.

loopBroadcast(RegisteredPids) -> % Ayuda: Utilizar la función lists:foreach(fun (Pid) -> Pid ! Msg end , PidsList)
  receive
    stopp -> io:fwrite("Servidor broadcast termino ~n", []);
    {reg, PidClient} ->
      io:fwrite("se registro ~p ~n", [PidClient]),
      loopBroadcast([PidClient | RegisteredPids]);
    {brod, Msg} ->
      lists:foreach(fun (Pid) -> Pid ! Msg end , RegisteredPids),  %fun es una funcion lambda
      loopBroadcast(RegisteredPids)
  end.

client(Broadcast) ->
  registrar(Broadcast),
  loopClient().

loopClient() ->
  receive
    Msg ->
      io:fwrite("El cliente ~p recibio el mensaje ~p ~n", [self(), Msg]),
      loopClient()
  end.

test() ->
  Broadcast = ?MODULE:start(),
  spawn(?MODULE, client, [Broadcast]),
  spawn(?MODULE, client, [Broadcast]),
  timer:sleep(1000),
  broadcast(Broadcast, "hola"),
  broadcast(Broadcast, "chau"),
  stop(Broadcast).