# midi-synth
Basic MIDI processor to generate WAV files from MIDI input file.

### CMake build instructions
- Create and cd into directory `build`
- `cmake ..`
- `make` to build executable

### Usage
  Run `build/synth` to generate WAV file in current directory. The first argument is the MIDI input file (samples are located in `tests/`), the second argument is the output WAV file.

Example:
  `build/synth tests/test3.mid extest`
  This will create an audio file named extest-0.wav in the current directory.
