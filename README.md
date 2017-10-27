# Starcraft2Streamer

Goal of this application is to take a number of SC2 replay files (`.SC2Replay`) as an input and automatically run them via the SC2API, using its [C++ library by Blizzard](https://github.com/Blizzard/s2client-api).

As of now, this is merely a test. It is based upon [this example](https://github.com/Blizzard/s2client-api/blob/master/src/sc2api/sc2_replay_observer.cc). 

## Replay Speed
Running replays works using the SC2API C++ library, but only in non-realtime (i.e., as fast as possibly executed). Setting `coordinator->SetRealtime(true);` yields an assertion in the C++ library to fail, [indicating that this feature is not implemented yet](https://github.com/Blizzard/s2client-api/blob/master/src/sc2api/sc2_coordinator.cc#L690). A ticket for this has been opened [here](https://github.com/Blizzard/s2client-api/issues/167). 

Caused by this, the SC2Streamer emulates realtime playback by manually making the playback slower on each game loop, approximating the 22.4 game loops per second the game has on speed "Faster".

## Todo
* Configurability of main settings like replay file path and replay speed
* CLI parameter to override replay file path
* Interoperability with the [Sc2LadderServer](https://github.com/Cryptyc/Sc2LadderServer), probably via the [SC2LadderWebHost](https://github.com/Cryptyc/SC2LadderWebHost)