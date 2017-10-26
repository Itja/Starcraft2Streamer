# Starcraft2Streamer

Goal of this application is to take a number of SC2 replay files (`.SC2Replay`) as an input and automatically run them via the SC2API, using its [C++ library by Blizzard](https://github.com/Blizzard/s2client-api).

As of now, this is merely a test. It is based upon [this example](https://github.com/Blizzard/s2client-api/blob/master/src/sc2api/sc2_replay_observer.cc). Running replays works, but only in non-realtime (i.e., as fast as possibly executed). Setting `coordinator->SetRealtime(true);` yields an assertion in the C++ library to fail, [indicating that this feature is not implemented yet](https://github.com/Blizzard/s2client-api/blob/master/src/sc2api/sc2_coordinator.cc#L690).