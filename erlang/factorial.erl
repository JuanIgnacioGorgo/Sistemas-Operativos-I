-module(factorial).
-export([fact/1]).
%compile(export_all).

% Función factorial por pattern matching
% para salir del shell de Erlang
% q(). 

% erlang es de asignacion unica, por lo que una vez dotado de algun valor a alguna variable, no puede ser cambiado

fact(0) -> 1;             % las variables van siempre en mayusculas, y las funciones en minúsculas
fact(N) -> N * fact(N-1). % el punto indica el final de una definición